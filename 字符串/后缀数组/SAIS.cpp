template<typename T = unsigned int>
class SuffixArray {
public:
    using size_type = T;//字符集大小
    using pointer = size_type*;
    using const_pointer = const size_type*;

    static_assert(std::is_integral<T>::value);

private:
    struct Equal {
        template<typename T1, typename T2>
        inline bool operator()(T1 lhs, T2 rhs) const noexcept {
            static_assert(std::is_integral<T1>::value && std::is_integral<T2>::value);
            return lhs == rhs;
        }
    };

    struct Buffer {
        pointer ptr;
        size_type len;
        Buffer() noexcept : ptr(nullptr), len(0) {}
        Buffer(pointer ptr, size_type len) noexcept : ptr(ptr), len(len) {}
        inline pointer alloc(size_type cnt) noexcept {
            return ptr + (len -= cnt);
        }
        inline bool operator<(Buffer other) const noexcept {
            return len < other.len;
        }
    };

    inline static bool is_negative(size_type n) noexcept {
        return (typename std::make_signed<size_type>::type)(n) < 0;
    }

    template<typename It, typename Eq>
    inline static bool is_equal(It s, size_type x, size_type y, size_type len, Eq eq) noexcept(noexcept(s[0])) {
        for (size_type i = 0;i < len;++i)
            if (!eq(s[x + i], s[y + i]))
                return false;
        return true;
    }

    template<typename It>
    inline static void get_sbuk(It s, pointer sbuk, size_type n, size_type m) noexcept(noexcept(s[0])) {
        std::fill_n(sbuk, m, 0);
        for (size_type i = 0;i < n;++i)
            ++sbuk[s[i]];
        std::partial_sum(sbuk, sbuk + m, sbuk);
    }

    inline static void lbuk_to_sbuk(const_pointer lbuk, pointer sbuk, size_type n, size_type m) noexcept {
        std::copy_n(lbuk + 1, m - 1, sbuk);
        sbuk[m - 1] = n;
    }

    inline static void sbuk_to_lbuk(pointer lbuk, const_pointer sbuk, size_type n, size_type m) noexcept {
        lbuk[0] = 0;
        std::copy_n(sbuk, m - 1, lbuk + 1);
    }

    template<typename It, typename Visitor>
    static void scan_lms_pos(It s, size_type n, Visitor visitor) noexcept(noexcept(s[0])) {
        using value_type = typename std::iterator_traits<It>::value_type;
        value_type pre, cur = s[n - 1];
        size_type i = n - 1;
        while (true) {
            do pre = cur; while (!is_negative(--i) && (cur = s[i]) >= pre);
            if (is_negative(i)) break;
            do pre = cur; while (!is_negative(--i) && (cur = s[i]) <= pre);
            if (is_negative(i)) break;
            visitor(i + 1, pre);
        }
    }

    template<typename It>
    inline static size_type fill_lms_char(It s, pointer sa, pointer sbuk, size_type n, size_type m) noexcept(noexcept(s[0])) {
        using value_type = typename std::iterator_traits<It>::value_type;
        size_type c0 = m - 1, p0 = 0, n0 = 0;
        std::fill_n(sa, n, 0);
        scan_lms_pos(s, n, [&, sa, sbuk](size_type p, value_type c) {
            sa[--sbuk[c0]] = p0;
            p0 = p;
            c0 = c;
            ++n0;
            });
        return n0;
    }

    template<typename It>
    static void induce_lms_substr(It s, pointer sa, pointer lbuk, pointer sbuk, size_type n, size_type m) noexcept(noexcept(s[0])) {
        using value_type = typename std::iterator_traits<It>::value_type;
        const pointer rsa = sa + n;
        lbuk_to_sbuk(lbuk, sbuk, n, m);
        value_type pre = s[n - 1], cur;
        pointer induce_to = sa + lbuk[pre];
        *induce_to++ = s[n - 2] < pre ? ~n + 2 : n - 1;
        for (pointer i = sa;i != rsa;++i) {
            const size_type p = *i - 1;
            if (is_negative(p)) continue;
            if ((cur = s[p]) != pre) {
                lbuk[pre] = induce_to - sa;
                induce_to = sa + lbuk[pre = cur];
            }
            *i = 0;
            *induce_to++ = s[p - 1] < cur ? ~p + 1 : p;
        }
        induce_to = sa + sbuk[pre = 0];
        sbuk_to_lbuk(lbuk, sbuk, n, m);
        for (pointer i = rsa;i-- != sa;) {
            const size_type p = ~*i;
            if (is_negative(p)) continue;
            if ((cur = s[p]) != pre) {
                sbuk[pre] = induce_to - sa;
                induce_to = sa + sbuk[pre = cur];
            }
            *i = 0;
            *--induce_to = s[p - 1] > cur ? p : ~p + 1;
        }
    }

    template<typename It, typename Eq>
    static size_type rename(It s, pointer sa, pointer s0, const_pointer lbuk, const_pointer sbuk, size_type n, size_type m, size_type n0, size_type d, Eq eq) noexcept(noexcept(s[0])) {
        using value_type = typename std::iterator_traits<It>::value_type;
        const pointer rsa0 = sa + n0;
        pointer i0 = sa, j0 = sa;
        if (d > 0) {
            const value_type c = d - 1;
            assert(lbuk[c] == 0);
            i0 = sa + lbuk[d];
            for (size_type i = 0;j0 != i0;i += 2, ++j0) {
                while (i < n && s[i] != c) ++i;
                *j0 = i;
            }
        }
        if (i0 == j0) i0 = j0 = std::find(j0, rsa0, 0);
        for (pointer i = i0, j = j0;j != rsa0;++i) {
            const size_type p = *i;
            if (p == 0) continue;
            *i = 0;
            *j++ = p;
        }
        size_type j = n - 1;
        scan_lms_pos(s, n, [sa, n0, &j](size_type p, value_type c) {
            sa[n0 + p / 2] = j - p + 1;
            j = p;
            });
        size_type m0 = 0;
        size_type ppos = 0;
        size_type plen = 0;
        for (pointer i = sa;i != rsa0;++i) {
            const size_type p = *i, clen = sa[n0 + p / 2];
            if (clen != plen || !is_equal(s, p, ppos, plen, eq)) ++m0;
            sa[n0 + p / 2] = m0;
            ppos = p;
            plen = clen;
        }
        if (m0 < n0) {
            for (pointer i = sa + n0 + n / 2, j = s0 + n0;j != s0;) {
                const size_type p = *--i;
                if (p != 0) *--j = p - 1;
            }
        }
        return m0;
    }

    template<typename It, typename Eq>
    static size_type induce_and_rename_lms_substr(It s, pointer sa, pointer s0, pointer lbuk, pointer sbuk, pointer time, size_type n, size_type m, size_type n0, size_type d, Eq eq) noexcept(noexcept(s[0])) {
        static constexpr size_type tag = size_type(1) << (std::numeric_limits<size_type>::digits - 2);
        using value_type = typename std::iterator_traits<It>::value_type;
        if (d > 0) {
            const pointer l = sa + sbuk[d - 1], r = sa + lbuk[d];
            for (pointer i = l;i != r;++i)
                *i = ~*i;
        }
        for (size_type i = d;i + 1 < m;++i) {
            const size_type p = sbuk[i];
            if (p != lbuk[i + 1])
                sa[p] = ~sa[p];
        }
        lbuk_to_sbuk(lbuk, sbuk, n, m);
        const pointer rsa = sa + n;
        value_type pre = s[n - 1], cur;
        pointer induce_to = sa + lbuk[pre];
        bool inc = false;
        size_type cnt = 0;
        std::fill_n(time, m, 0);

#define INDUCE_ONE(BUK, INDUCIBLE, CUR, TAG, REF) \
        {                                         \
            size_type p = *i;                     \
            if (p == 0) continue;                 \
            const bool b = is_negative(p);        \
            if (b) { ++cnt; p = ~p; }             \
            if (INDUCIBLE(s, p, cur)) {           \
                if (inc) {                        \
                    inc = false;                  \
                    *i = ~p;                      \
                }                                 \
                continue;                         \
            }                                     \
            --p;                                  \
            *i = 0;                               \
            inc |= b;                             \
            if (CUR(s, p, cur) != pre) {          \
                BUK[pre] = induce_to - sa;        \
                induce_to = sa + BUK[pre = cur];  \
            }                                     \
            TAG(s, p, cur);                       \
            if (time[cur] != cnt) {               \
                time[cur] = cnt;                  \
                p = ~p;                           \
            }                                     \
            REF(induce_to) = p;                   \
        }
#define REF_FORWARD(ptr) (*ptr++)
#define REF_BACKWARD(ptr) (*--ptr)
#define INDUCE(IS_LML, IS_LMS, CUR_L, CUR_S, TAG_LML, TAG_LMS)          \
        {                                                               \
            for (pointer i = sa;i != rsa;++i) {                         \
                INDUCE_ONE(lbuk, IS_LML, CUR_L, TAG_LML, REF_FORWARD);  \
            }                                                           \
            for (pointer i = rsa;i-- != sa;) {                          \
                size_type p = *i;                                       \
                if (is_negative(p - 1)) continue;                       \
                *i = ~p;                                                \
                while (!is_negative(p = *--i)) {}                       \
                *i = ~p;                                                \
            }                                                           \
            induce_to = sa + sbuk[pre = 0];                             \
            sbuk_to_lbuk(lbuk, sbuk, n, m);                             \
            for (pointer i = rsa;i-- != sa;) {                          \
                INDUCE_ONE(sbuk, IS_LMS, CUR_S, TAG_LMS, REF_BACKWARD); \
            }                                                           \
        }

        if (n < tag) {
            *induce_to++ = ~(s[n - 2] < pre ? n + tag - 1 : n - 1);
#define IS_LML(s, p, cur) (tag <= p)
#define IS_LMS(s, p, cur) (p < tag)
#define CUR_L(s, p, cur) (cur = s[p])
#define CUR_S(s, p, cur) (cur = s[p - tag])
#define TAG_LML(s, p, cur) { if (s[p - 1] < cur) p += tag; }
#define TAG_LMS(s, p, cur) { if (s[p - tag - 1] > cur) p -= tag; }
            INDUCE(IS_LML, IS_LMS, CUR_L, CUR_S, TAG_LML, TAG_LMS);
#undef IS_LML
#undef IS_LMS
#undef CUR_L
#undef CUR_S
#undef TAG_LML
#undef TAG_LMS
        }
        else {
            *induce_to++ = ~(n - 1);
#define IS_LML(s, p, cur) ((cur = s[p - 1]) < s[p])
#define IS_LMS(s, p, cur) ((cur = s[p - 1]) > s[p])
#define CUR(s, p, cur) (cur)
#define TAG(s, p, cur) {}
            INDUCE(IS_LML, IS_LMS, CUR, CUR, TAG, TAG);
#undef IS_LML
#undef IS_LMS
#undef CUR
#undef TAG
        }

#undef INDUCE_ONE
#undef REF_FORWARD
#undef REF_BACKWARD
#undef INDUCE

        const pointer rsa0 = sa + n0;
        pointer i0 = sa, j0 = sa;
        if (d > 0) {
            const value_type c = d - 1;
            assert(lbuk[c] == 0);
            i0 = sa + lbuk[d];
            for (size_type i = 0;j0 != i0;i += 2, ++j0) {
                while (i < n && s[i] != c) ++i;
                *j0 = ~i;
            }
        }
        size_type m0 = j0 - sa;
        for (pointer i = i0, j = j0;j != rsa0;++i) {
            const size_type p = *i;
            if (p == 0) continue;
            *i = 0;
            *j++ = p;
            m0 += is_negative(p);
        }
        if (m0 == n0) {
            for (pointer i = sa;i != rsa0;++i)
                *i = ~*i;
        }
        else {
            size_type rk = m0 + 1;
            for (pointer i = rsa0;i-- != sa;) {
                size_type p = *i;
                if (is_negative(p)) {
                    p = ~p;
                    --rk;
                }
                sa[n0 + p / 2] = rk;
            }
            for (pointer i = sa + n0 + n / 2, j = s0 + n0;j != s0;) {
                const size_type p = *--i;
                if (p != 0) *--j = p - 1;
            }
        }
        return m0;
    }

    template<typename It>
    inline static void fill_lms_suffix(It s, pointer sa, const_pointer sbuk, size_type n, size_type m, size_type n0) noexcept(noexcept(s[0])) {
        using value_type = typename std::iterator_traits<It>::value_type;
        if (n0 == 0) return;
        size_type p = sa[n0 - 1];
        value_type pre, cur = s[p];
        size_type i = n0 - 1, j = n;
        do {
            const size_type k = sbuk[pre = cur];
            while (j > k) sa[--j] = 0;
            do sa[--j] = p; while (!is_negative(--i) && (cur = s[p = sa[i]]) == pre);
        } while (!is_negative(i));
        while (j > 0) sa[--j] = 0;
    }

    template<typename It>
    static void induce_suffix(It s, pointer sa, pointer lbuk, pointer sbuk, size_type n, size_type m) noexcept(noexcept(s[0])) {
        using value_type = typename std::iterator_traits<It>::value_type;
        const pointer rsa = sa + n;
        value_type pre = s[n - 1], cur;
        pointer induce_to = sa + lbuk[pre];
        *induce_to++ = s[n - 2] < pre ? ~n + 2 : n - 1;
        for (pointer i = sa;i != rsa;++i) {
            const size_type p = *i - 1;
            if (is_negative(p)) continue;
            if ((cur = s[p]) != pre) {
                lbuk[pre] = induce_to - sa;
                induce_to = sa + lbuk[pre = cur];
            }
            *induce_to++ = p > 0 && s[p - 1] < cur ? ~p + 1 : p;
        }
        induce_to = sa + sbuk[pre = 0];
        for (pointer i = rsa;i-- != sa;) {
            const size_type p = ~*i;
            if (is_negative(p)) continue;
            if ((cur = s[p]) != pre) {
                sbuk[pre] = induce_to - sa;
                induce_to = sa + sbuk[pre = cur];
            }
            *i = p + 1;
            *--induce_to = p > 0 && s[p - 1] > cur ? p : ~p + 1;
        }
    }

    template<typename It, typename Eq>
    static void sais(It s, pointer sa, size_type n, size_type m, size_type r, size_type d, Buffer buf, Eq eq) {
        using value_type = typename std::iterator_traits<It>::value_type;
        Buffer memory[3] = { Buffer(sa + n, r), buf };
        std::unique_ptr<size_type[]> guard;
        const bool state = 2 * m <= n;
        const size_type cnt = 2 + state;
        const size_type sum = r / m + buf.len / m;
        if (sum < cnt) {
            const size_type len = (cnt - sum) * m;
            guard.reset(new size_type[len]);
            memory[2] = { guard.get(), len };
        }
        Buffer* ptr = memory;
        const auto alloc = [&memory, &ptr, m] {
            ptr = std::find_if(ptr, memory + 3, [m](Buffer e) { return m <= e.len; });
            return ptr->alloc(m);
            };
        const pointer lbuk = alloc();
        r = memory[0].len;
        const auto buf0 = *std::max_element(memory, memory + 3);
        const pointer sbuk = alloc(), time = state ? alloc() : nullptr;
        get_sbuk(s, sbuk, n, m);
        sbuk_to_lbuk(lbuk, sbuk, n, m);
        const size_type n0 = fill_lms_char(s, sa, sbuk, n, m);
        if (n0 > 0) {
            const size_type r0 = n + r - 2 * n0;
            const pointer sa0 = sa, s0 = sa + n0 + r0;
            size_type m0;
            if (state)
                m0 = induce_and_rename_lms_substr(s, sa, s0, lbuk, sbuk, time, n, m, n0, d, eq);
            else {
                induce_lms_substr(s, sa, lbuk, sbuk, n, m);
                m0 = rename(s, sa, s0, lbuk, sbuk, n, m, n0, d, eq);
            }
            if (m0 < n0) {
                sais(s0, sa0, n0, m0, r0, 0, buf0, std::equal_to<size_type>{});
                pointer j = sa + n + r;
                scan_lms_pos(s, n, [&j](size_type p, value_type c) {
                    *--j = p;
                    });
                for (size_type i = 0;i < n0;++i)
                    sa0[i] = s0[sa0[i]];
            }
        }
        lbuk_to_sbuk(lbuk, sbuk, n, m);
        fill_lms_suffix(s, sa, sbuk, n, m, n0);
        induce_suffix(s, sa, lbuk, sbuk, n, m);
    }

public:
    template<typename It, typename Eq = Equal>
    static void sort_suffix(It s, pointer sa, size_type n, size_type m, pointer buf = nullptr, size_type buf_len = 0, Eq eq = {}) {
        if (n == 1)
            sa[0] = 0;
        else if (n > 1)
            sais(s, sa, n, m, 0, 0, Buffer(buf, buf_len), eq);
    }

    template<typename It, typename Eq = Equal>
    static void sort_suffix_with_delimiter(It s, pointer sa, size_type n, size_type m, size_type d, pointer buf = nullptr, size_type buf_len = 0, Eq eq = {}) {
        using value_type = typename std::iterator_traits<It>::value_type;
        if (n == 1)
            sa[0] = 0;
        else if (n > 1) {
            const value_type c = d;
            sais(s, sa, n, m, 0, d + 1, Buffer(buf, buf_len), [&eq, c](value_type lhs, value_type rhs) {
                return eq(lhs, rhs) && !eq(lhs, c);
                });
        }
    }

    inline static void sa_to_isa(const_pointer sa, pointer isa, size_type n) noexcept {
        for (size_type i = 0;i < n;++i)
            isa[sa[i]] = i;
    }

    template<typename It, typename Eq = Equal>
    static void get_plcp(It s, const_pointer sa, pointer plcp, size_type n, Eq eq = {}) noexcept(noexcept(s[0])) {
        for (size_type j = n, i = 0;i < n;++i) {
            const size_type k = sa[i];
            plcp[k] = j;
            j = k;
        }
        for (size_type l = 0, i = 0;i < n;++i) {
            const size_type j = plcp[i];
            if (j == n) {
                plcp[i] = 0;
                continue;
            }
            if (l > 0) --l;
            const size_type d = n - std::max(i, j);
            while (l < d && eq(s[i + l], s[j + l])) ++l;
            plcp[i] = l;
        }
    }

    template<typename It, typename Eq = Equal>
    static void get_plcp_with_delimiter(It s, const_pointer sa, pointer plcp, size_type n, size_type d, Eq eq = {}) noexcept(noexcept(s[0])) {
        using value_type = typename std::iterator_traits<It>::value_type;
        const value_type c = d;
        get_plcp(s, sa, plcp, n, [&eq, c](value_type lhs, value_type rhs) {
            return eq(lhs, rhs) && !eq(lhs, c);
            });
    }

    inline static void plcp_to_lcp(const_pointer sa, const_pointer plcp, pointer lcp, size_type n) noexcept {
        for (size_type i = 0;i < n;++i)
            lcp[i] = plcp[sa[i]];
    }

    template<typename It>
    SuffixArray(It s, size_type n, size_type m) {
        sa = std::allocator<size_type>{}.allocate(3 * n);
        try {
            isa = sa + n;
            lcp = isa + n;
            sort_suffix(s, sa, n, m, isa, 2 * n);
            get_plcp(s, sa, isa, n);
            plcp_to_lcp(sa, isa, lcp, n);
            sa_to_isa(sa, isa, n);
        }
        catch (...) {
            std::allocator<size_type>{}.deallocate(sa, 3 * n);
            throw;
        }
    }

    template<typename S>
    SuffixArray(const S& s, size_type m) : SuffixArray(s.begin(), s.size(), m) {}

    ~SuffixArray() { std::allocator<size_type>{}.deallocate(sa, 3 * (isa - sa)); }

    inline const_pointer data() const noexcept { return sa; }
    inline const_pointer rank_data() const noexcept { return isa; }
    inline const_pointer common_prefix_data() const noexcept { return lcp; }
    inline size_type operator[](size_type k) const noexcept { return sa[k]; }
    inline size_type rank(size_type k) const noexcept { return isa[k]; }
    inline size_type common_prefix(size_type k) const noexcept { return lcp[k]; }

private:
    pointer sa, isa, lcp;
};

using SA32 = SuffixArray<uint32_t>;
using SA64 = SuffixArray<uint64_t>;

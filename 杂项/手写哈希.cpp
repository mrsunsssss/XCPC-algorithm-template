struct Barrett {
    using u32 = unsigned;
    using u64 = unsigned long long;
    using u128 = unsigned __int128;
    static constexpr u128 s = u128(1) << 96;

    Barrett(const u32 P) : p_(P), m_((s - 1) / P + 1) {}

    u32 div(const u64& v) const {
        return (v * m_) >> 96;
    }

    u32 operator()(u64 v) {
        return v - u64(div(v)) * p_;
    }

    u128 m_;
    u32 p_;
};

// // MAX_LEN 需为质数
static constexpr int MAX_LEN = 21200009;
static Barrett fast_mod(MAX_LEN);

// // 支持整数、pair、tuple,array等哈希组合
struct MyHash {
    using u64 = unsigned long long;
    using u32 = unsigned;

    // 随机扰动，防止哈希碰撞
    static u64 split(u64 x) {
        x ^= x << 13;
        x ^= x >> 7;
        x ^= x << 17;
        return x;
    }

    // 泛化`hash_combine
    template <typename T, typename... Rest>
    static size_t hash_combine(const T& first, const Rest&... rest) {
        size_t h = std::hash<T>()(first);
        if constexpr (sizeof...(rest) > 0) {
            h ^= hash_combine(rest...) + 0x9e3779b9 + (h << 6) + (h >> 2);
        }
        return h;
    }

    // 泛化哈希计算,支持整数,pair,tuple
    template <typename T>
    size_t operator()(const T& x) const {
        if constexpr (std::is_integral_v<T>) {
            static const u64 FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
            return fast_mod(static_cast<u64>(split(x + FIXED_RANDOM)));
        }
        else {
            return fast_mod(hash_combine(x));
        }
    }

    template <typename A, typename B>
    size_t operator()(const pair<A, B>& pr) const {
        return fast_mod(hash_combine(pr.first, pr.second));
    }

    template <typename... T>
    size_t operator()(const tuple<T...>& tp) const {
        return fast_mod(apply(hash_combine<T...>, tp));
    }

    template <size_t N>
    size_t operator()(const array<int, N>& arr) const {
        size_t seed = 0;
        for (const auto& elem : arr) {
            seed = hash_combine(seed, elem);
        }
        return fast_mod(seed);
    }
};

template<class Key, class Value, class Hash = MyHash>
struct HashMap {
    using u64 = unsigned long long;
    std::vector<int> pos_;
    int head_[MAX_LEN], next_[MAX_LEN], total_, size_;
    Key keys_[MAX_LEN];
    Value values_[MAX_LEN];
    Hash hash_;
    HashMap() : total_(0), size_(0) {}

    void clear() {
        total_ = size_ = 0;
        for (auto& p : pos_) {
            head_[p] = -1;
        }
        pos_.clear();
    }

    bool count(const Key& key) {
        int p = fast_mod(static_cast<u64>(hash_(key)));
        if (!head_[p]) {
            return false;
        }
        for (int i = head_[p]; i; i = next_[i]) {
            if (keys_[i] == key) {
                return true;
            }
        }
        return false;
    }

    void insert(const Key& key, const Value& value) {
        if (count(key)) {
            return;
        }
        int p = fast_mod(static_cast<u64>(hash_(key)));
        next_[++total_] = head_[p];
        head_[p] = total_;
        keys_[total_] = key;
        values_[total_] = value;
        pos_.emplace_back(p);
        size_++;
    }

    bool erase(const Key& key) {
        int p = fast_mod(static_cast<u64>(hash_(key)));
        if (!head_[p]) {
            return false;
        }
        for (int i = head_[p], j; i; i = next_[i]) {
            if (keys_[i] == key) {
                if (i == head_[p]) {
                    head_[p] = next_[i];
                }
                else {
                    next_[j] = next_[i];
                }
                size_--;
                return true;
            }
            j = i;
        }
        return false;
    }

    int size() const {
        return size_;
    }

    Value& operator[](const Key& key) {
        int p = fast_mod(static_cast<u64>(hash_(key)));
        if (!head_[p]) {
            pos_.emplace_back(p);
        }
        for (int i = head_[p]; i; i = next_[i]) {
            if (keys_[i] == key) {
                return values_[i];
            }
        }
        insert(key, Value());
        return values_[total_];
    }

};


HashMap<ll, int> mp;

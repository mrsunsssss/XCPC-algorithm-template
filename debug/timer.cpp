struct Timer {
    std::chrono::steady_clock::time_point start;
    Timer() : start(std::chrono::steady_clock::now()) {}
    void time() {
        auto finish = std::chrono::steady_clock::now();
        auto runtime = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
        std::cerr << runtime / 1e6 << "s" << std::endl;
    }
    ~Timer() {
        auto finish = std::chrono::steady_clock::now();
        auto runtime = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
        std::cerr << runtime / 1e6 << "s" << std::endl;
    }
};

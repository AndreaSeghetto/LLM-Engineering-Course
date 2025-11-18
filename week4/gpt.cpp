#include <iostream>
#include <iomanip>
#include <chrono>
#include <cstdint>

static inline double calculate(int64_t iterations, int param1, int param2) {
    double result = 1.0;
    double p1 = static_cast<double>(param1);
    double p2 = static_cast<double>(param2);
    double x = p1; // 4*i for i=1

    #if defined(__clang__)
    #pragma clang loop vectorize(disable)
    #pragma clang loop interleave(disable)
    #pragma clang loop unroll(disable)
    #endif
    for (int64_t i = 1; i <= iterations; ++i) {
        double j1 = x - p2;    // 4*i - 1
        result -= 1.0 / j1;
        double j2 = x + p2;    // 4*i + 1
        result += 1.0 / j2;
        x += p1;
    }
    return result;
}

int main() {
    using clock = std::chrono::high_resolution_clock;
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto start_time = clock::now();
    double result = calculate(200000000LL, 4, 1) * 4.0;
    auto end_time = clock::now();

    double seconds = std::chrono::duration<double>(end_time - start_time).count();

    std::cout << std::fixed << std::setprecision(12);
    std::cout << "Result: " << result << "\n";
    std::cout << std::setprecision(6);
    std::cout << "Execution Time: " << seconds << " seconds\n";
    return 0;
}
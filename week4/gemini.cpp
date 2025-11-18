
#include <iostream>
#include <iomanip>
#include <chrono>

// This function calculates the series sum using an algebraically simplified formula
// to achieve higher performance. The original loop involves two divisions, which
// are combined here into a single, more efficient operation. This transformation
// is safe under the provided '-Ofast' flag, which allows for floating-point
// re-association, and makes the code highly suitable for auto-vectorization (SIMD).
inline double calculate(long long iterations, double param1, double param2) {
    double result = 1.0;
    
    // Pre-calculate loop-invariant values for the simplified formula:
    // term = - (2 * param2) / ((param1*i)^2 - param2^2)
    const double term_numerator = 2.0 * param2;
    const double p2_squared = param2 * param2;

    for (long long i = 1; i <= iterations; ++i) {
        const double i_d = static_cast<double>(i);
        const double p1i = param1 * i_d;
        result -= term_numerator / (p1i * p1i - p2_squared);
    }
    return result;
}

int main() {
    // Fast I/O is a good practice for performance-critical C++ applications.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // Constants from the Python script.
    // Using C++14 digit separators for readability.
    const long long iterations = 200'000'000;
    const double param1 = 4.0;
    const double param2 = 1.0;

    // Use std::chrono::high_resolution_clock for precise timing.
    const auto start_time = std::chrono::high_resolution_clock::now();
    
    // Perform the calculation and scale the result as in the original script.
    const double result = calculate(iterations, param1, param2) * 4.0;
    
    const auto end_time = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> duration = end_time - start_time;

    // Print the results with formatting identical to the Python script.
    std::cout << std::fixed;
    std::cout << "Result: " << std::setprecision(12) << result << "\n";
    std::cout << "Execution Time: " << std::setprecision(6) << duration.count() << " seconds\n";

    return 0;
}

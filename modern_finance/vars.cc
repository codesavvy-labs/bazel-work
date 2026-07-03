#include <iostream>
#include <cstdint>
#include <limits>
#include <cmath>

constexpr double discount_factor(double rate, double time) {
    return std::exp(-rate * time);
}

bool ApproxEqual(double a, double b, double epsilon = 1e-9);
double europeanCallPayoff( double spot, double strike);



int main() {
    // Variables and basic types - essential for finance and trading applications
    int64_t trades = 25000000;
    double spot = 103.4567;
    long double result = 103.4567L;
    std::cout << "Trades: " << trades << std::endl;
    std::cout << "Spot(double): " << spot << std::endl;
    std::cout << "Spot(long double): " << result << std::endl;
    std::cout << "Max int64_t: " << std::numeric_limits<int64_t>::max() << std::endl;
    std::cout << "Max double: " << std::numeric_limits<double>::max() << std::endl;
    std::cout << "Max long double: " << std::numeric_limits<long double>::max() << std::endl;

    // Common pitfalls with integer division
    int a = 1;
    int b = 2;
    std::cout << "a/b(int) = " << a/b << std::endl;
    std::cout << "a/b(double) = " << a/static_cast<double>(b) << std::endl;

    // Precision, rounding, and floating-point comparison issues
    double c = 0.1 + 0.2;
    double d = 0.3;
    std::cout << "c==d" << (c==d ? " true" : " false") << std::endl;
    std::cout << "ApproxEqual(c,d) = " << (ApproxEqual(c,d) ? " true" : " false") << std::endl;

    //Width, overflow, and safe checks with integer types
    int32_t x = std::numeric_limits<int32_t>::max();
    std::cout << "Max int32_t: " << x << std::endl;
    int64_t safe = static_cast<int64_t>(x) + 1;
    std::cout << "Safe int64_t: " << safe << std::endl;

    // Discount factor calculation with use of constexpr function
    const double rate = 0.02;
    const double time = 1.0;
    auto df = discount_factor(rate, time);
    std::cout << "Discount factor for rate " << rate << " and time " << time << " is " << df << std::endl;  

    
    const double spotPrice = 105.0;
    const double strikePrice = 100.0;
    const double discountRate = 0.05;
    const double timeToMaturity = 1.0; // in years

    double payoff = europeanCallPayoff(spotPrice, strikePrice);
    double pv = payoff * discount_factor(discountRate, timeToMaturity);
    int64_t tradeId = 42;
    std::cout << "Trade" << tradeId << ": Present value of the call option: " << pv << std::endl;

    int paths = 1000000;
    double totalPayoff = 12345.67; // Example total payoff from simulation
    double average = totalPayoff / static_cast<double>(paths);
    std::cout << "Average payoff from simulation: " << average << std::endl;

    if (fabs(pv-payoff) < 1e-6) {
        std::cout << "Present value and payoff are approximately equal." << std::endl;
    } else {
        std::cout << "Present value and payoff differ." << std::endl;
    }
    return 0;
}

bool ApproxEqual(double a, double b, double epsilon) {
    return std::fabs(a - b) < epsilon * std::max(1.0,std::max(std::fabs(a), std::fabs(b)));
}
double europeanCallPayoff( double spot, double strike) {
    // return (spot > strike) ? (spot - strike) : 0.0;
    return std::max(0.0, spot - strike);
}
//
// Pricer
//
#include <iostream>
#include <cmath>
#include <random>
#include <functional>
#include <stdexcept>
#include <chrono>

// European payoff generators using labbdas, selected by a short enum class
enum class OptionType { Call, Put };

constexpr double discount_factor(double rate, double time) {
    return std::exp(-rate * time);
}
std::function<double(double)> getPayoffFunction(OptionType optionType, double strike);
double monteCarloEuropean(
    std::function<double(double)> payoff,
    double spot, 
    double rate, 
    double volatility, 
    double timeToMaturity, 
    std::uint64_t t_paths,
    std::uint64_t seed = 1337
);
int main() {
    try {
        const double spotPrice = 100.0;
        const double strikePrice = 100.0;
        const double discountRate = 0.01;
        const double volatility = 0.2; // 20% annual volatility
        const double timeToMaturity = 1.0; // in years
        const std::uint64_t t_paths = 1000000; // number of Monte Carlo paths
        OptionType optionType = OptionType::Call;

        auto payoffFunction = getPayoffFunction(optionType, strikePrice);

        auto to = std::chrono::steady_clock::now();

        double presentValue = monteCarloEuropean(payoffFunction, 
            spotPrice, 
            strikePrice, 
            discountRate, 
            volatility, 
            timeToMaturity, 
            t_paths);


        auto te = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = te - to;
        std::cout << "Present value of the option: " << presentValue << std::endl;
        std::cout << "Elapsed time: " << elapsed_seconds.count() << " seconds\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
 }

std::function<double(double)> getPayoffFunction(OptionType optionType, double strike) {
    switch (optionType) {
        case OptionType::Call:
            return [strike](double spot) { return std::max(0.0, spot - strike); };
        case OptionType::Put:
            return [strike](double spot) { return std::max(0.0, strike - spot); };
        default:
            throw std::invalid_argument("Unsupported option type");
    }
}

//
// Monte Carlo pricer: clean API, small resposibilities
//
double monteCarloEuropean(
    std::function<double(double)> payoff,
    double spot, 
    double rate, 
    double volatility, 
    double timeToMaturity, 
    std::uint64_t t_paths,
    std::uint64_t seed 
) {
    if (spot <= 0.0 || volatility < 0.0 || timeToMaturity < 0.0 || t_paths == 0) {
        throw std::invalid_argument("Invalid input parameters for Monte Carlo simulation.");
    }

    std::mt19937 generator(seed);
    std::normal_distribution<double> distribution(0.0, 1.0);

    double drift = (rate - 0.5 * volatility * volatility) * timeToMaturity;
    double diffusion = volatility * std::sqrt(timeToMaturity);

    double sumPayoffs = 0.0;
    for (std::uint64_t i = 0; i < t_paths; ++i) {
        double z = distribution(generator);
        
        double simulatedSpot = spot * std::exp(drift + diffusion * z);

        if (!std::isfinite(simulatedSpot)) {
            continue; // Skip this iteration if the simulated spot price is not finite
        }

        sumPayoffs += payoff(simulatedSpot);
    }
    double averagePayoff = sumPayoffs / static_cast<double>(t_paths);
    return averagePayoff * discount_factor(rate, timeToMaturity);

}

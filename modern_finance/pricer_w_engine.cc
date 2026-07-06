//
// Pricer
//
#include <iostream>
#include <cmath>
#include <random>
#include <functional>
#include <stdexcept>
#include <chrono>
#include "OptionSim.h"
#include "MonteCarloEngine.h"

// European payoff generators using labbdas, selected by a short enum class
enum class OptionType { Call, Put };

std::function<double(double)> getPayoffFunction(OptionType optionType, double strike);

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
        OptionSim::OptionSimParams params = {
            spotPrice,
            strikePrice,
            discountRate,
            volatility,
            timeToMaturity,
            payoffFunction // seed for reproducibility
        };

        OptionSim option_sim(params);

        std::random_device rd;
        auto seed = rd();
        std::mt19937 generator(seed);
 
        auto presentValue = RunMonteCarlo(option_sim, generator, t_paths);

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


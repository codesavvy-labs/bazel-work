    #include "OptionModelEngine.h"

    double OptionModelEngine::Run(std::function<double(double)> compute_value) {
        std::mt19937 generator(params.seed);
        std::normal_distribution<double> distribution(0.0, 1.0);
        double volatility = params.volatility;
        double drift = (params.discountRate - 0.5 * volatility * volatility) * params.timeToMaturity;
        double diffusion = volatility * std::sqrt(params.timeToMaturity);
    
        double sumPayoffs = 0.0;

        for (std::uint64_t i = 0; i < params.t_paths; ++i) {
            double z = distribution(generator);
            
            double simulatedSpot = params.spotPrice * std::exp(drift + diffusion * z);

            if (!std::isfinite(simulatedSpot)) {
                continue; // Skip this iteration if the simulated spot price is not finite
            }

            sumPayoffs += compute_value(simulatedSpot);
        }
        
        double averagePayoff = sumPayoffs / static_cast<double>(params.t_paths);
        double discountFactor = std::exp(-params.discountRate * params.timeToMaturity);
        return averagePayoff * discountFactor;
    }

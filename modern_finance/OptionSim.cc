    #include "OptionSim.h"
    double OptionSim::results() {
        double averagePayoff = sum_payoffs_ / static_cast<double>(t_paths_);
        double discountFactor = std::exp(-params_.discountRate * params_.timeToMaturity);
        return averagePayoff * discountFactor;
    }
    void OptionSim::process_sample(std::mt19937 & generator) {
        t_paths_++;
        double sample = distribution_(generator);
        double simulatedSpot = params_.spotPrice * std::exp(drift_ + diffusion_ * sample);
        if (std::isfinite(simulatedSpot)) {
            sum_payoffs_ += params_.compute_value(simulatedSpot);
        }
    }
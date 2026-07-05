    #include "OptionSim.h"
    void OptionSim::configure() {
        drift_ = (params_.discountRate - 0.5 * params_.volatility * params_.volatility) * params_.timeToMaturity;
        diffusion_ = params_.volatility * std::sqrt(params_.timeToMaturity);
    }
    double OptionSim::output_value(std::uint64_t t_paths) {
        double averagePayoff = sum_payoffs_ / static_cast<double>(t_paths);
        double discountFactor = std::exp(-params_.discountRate * params_.timeToMaturity);
        return averagePayoff * discountFactor;
    }
    void OptionSim::process_sample(double sample) {
       double simulatedSpot = params_.spotPrice * std::exp(drift_ + diffusion_ * sample);
       if (std::isfinite(simulatedSpot)) {
            sum_payoffs_ += params_.compute_value(simulatedSpot);
        }
    }
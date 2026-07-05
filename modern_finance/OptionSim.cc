    #include "OptionSim.h"
    void OptionSim::configure(std::uint64_t t_paths) {
        drift_ = (params_.discountRate - 0.5 * params_.volatility * params_.volatility) * params_.timeToMaturity;
        diffusion_ = params_.volatility * std::sqrt(params_.timeToMaturity);
        t_paths_ = t_paths;
    }
    double OptionSim::results() {
        double averagePayoff = sum_payoffs_ / static_cast<double>(t_paths_);
        double discountFactor = std::exp(-params_.discountRate * params_.timeToMaturity);
        return averagePayoff * discountFactor;
    }
    void OptionSim::process_sample(double sample) {
       double simulatedSpot = params_.spotPrice * std::exp(drift_ + diffusion_ * sample);
       if (std::isfinite(simulatedSpot)) {
            sum_payoffs_ += params_.compute_value(simulatedSpot);
        }
    }
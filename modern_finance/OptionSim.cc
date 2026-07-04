    #include "OptionSim.h"
    void OptionSim::configure() {
        drift_ = (params_.discountRate - 0.5 * params_.volatility * params_.volatility) * params_.timeToMaturity;
        diffusion_ = params_.volatility * std::sqrt(params_.timeToMaturity);
    }
    double OptionSim::update(double sample) {
        double simulatedSpot = params_.spotPrice * std::exp(drift_ + diffusion_ * sample);
        return simulatedSpot;
    }
    double OptionSim::apply(double simulatedSpot) {
        return params_.compute_value(simulatedSpot);
    }
    double OptionSim::accumulate(double payoff) {
        sum_payoffs_ += payoff;
        return sum_payoffs_;
    }
    double OptionSim::output_value() {
        double averagePayoff = sum_payoffs_ / static_cast<double>(params_.t_paths);
        double discountFactor = std::exp(-params_.discountRate * params_.timeToMaturity);
        return averagePayoff * discountFactor;
    }
    std::uint64_t OptionSim::get_t_paths() const {
        return params_.t_paths;
    }

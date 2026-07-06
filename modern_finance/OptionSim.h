#pragma once

#include <iostream>
#include <cmath>
#include <random>
#include <functional>
#include <stdexcept>
#include <utility>

class OptionSim {
public:
    typedef struct {
        double spotPrice;
        double strikePrice;
        double discountRate;
        double volatility;
        double timeToMaturity;
        std::function<double(double)> compute_value;
    } OptionSimParams;

    OptionSim(const OptionSimParams& params) : params_(params), sum_payoffs_(0.0), t_paths_(0) {
        drift_ = (params.discountRate - 0.5 * params.volatility * params.volatility) * params_.timeToMaturity;
        diffusion_ = params.volatility * std::sqrt(params.timeToMaturity);
        std::normal_distribution<double> distribution(0.0, 1.0);
        distribution_ = std::move(distribution);
    }
    double results();
    void process_sample(std::mt19937 & generator);

private:
    OptionSimParams params_;
    double drift_;
    double diffusion_;
    double sum_payoffs_;
    std::uint64_t t_paths_;
    std::normal_distribution<double> distribution_;
};

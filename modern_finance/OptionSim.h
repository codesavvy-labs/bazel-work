#pragma once

#include <iostream>
#include <cmath>
#include <random>
#include <functional>
#include <stdexcept>

class OptionSim {
public:
    typedef struct {
        double spotPrice;
        double strikePrice;
        double discountRate;
        double volatility;
        double timeToMaturity;
        std::uint64_t t_paths;
        std::function<double(double)> compute_value;
    } OptionSimParams;

    OptionSim(const OptionSimParams& params) : 
        params_(params), drift_(0.0), diffusion_(0.0),sum_payoffs_(0.0) {}
    double apply(double simulatedSpot);
    double accumulate(double payoff);
    double output_value();
    void configure();
    double update(double sample);
    std::uint64_t get_t_paths() const;
private:
    OptionSimParams params_;
    double drift_;
    double diffusion_;
    double sum_payoffs_;
};

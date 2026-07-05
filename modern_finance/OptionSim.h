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
        std::function<double(double)> compute_value;
    } OptionSimParams;

    OptionSim(const OptionSimParams& params) : 
        params_(params), drift_(0.0), diffusion_(0.0),sum_payoffs_(0.0), t_paths_(0) {}
    double output_value();
    void configure(std::uint64_t t_paths);
    void process_sample(double sample);

private:
    OptionSimParams params_;
    double drift_;
    double diffusion_;
    double sum_payoffs_;
    std::uint64_t t_paths_;
};

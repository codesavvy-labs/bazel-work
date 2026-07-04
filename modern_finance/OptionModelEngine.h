#pragma once

#include <iostream>
#include <cmath>
#include <random>
#include <functional>
#include <stdexcept>

class OptionModelEngine {
public:
    typedef struct {
        double spotPrice;
        double strikePrice;
        double discountRate;
        double volatility;
        double timeToMaturity;
        std::uint64_t t_paths;
        std::uint64_t seed;
    } OptionModelParams;

    OptionModelEngine(const OptionModelParams& params) : params(params) {}
    double Run(std::function<double(double)> payoff);
private:
    OptionModelParams params;
};

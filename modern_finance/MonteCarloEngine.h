#pragma once
#include <cstdint>
#include <cmath>

template <typename Generator, typename Distribution, typename Simulation>
class MonteCarloEngine {
public:
    MonteCarloEngine(Generator generator, Distribution distribution,  Simulation simulation)
        : generator_(generator), distribution_(distribution), simulation_(simulation) {}
    
    double sample() {
        return distribution_(generator_);
    }
    
    double Run(std::uint64_t t_paths) {
        simulation_.configure(t_paths);
        for (std::uint64_t i = 0; i < t_paths; ++i) {
           simulation_.process_sample(sample());
        }
        return simulation_.output_value();  
    }
private:
    Generator generator_;
    Distribution distribution_;
    Simulation simulation_;
};
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
    
    double Run() {
        simulation_.configure();
        for (std::uint64_t i = 0; i < simulation_.get_t_paths(); ++i) {
            double next_sample = simulation_.update(sample());
            
            if (std::isfinite(next_sample)) {
                simulation_.accumulate(simulation_.apply(next_sample));
            }
        }
        return simulation_.output_value();
    }
private:
    Generator generator_;
    Distribution distribution_;
    Simulation simulation_;
};
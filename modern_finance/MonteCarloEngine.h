#pragma once
#include <cstdint>
#include <cmath>
#include <utility>

template <typename Generator, typename Distribution, typename Simulation>
class MonteCarloEngine {
public:
    MonteCarloEngine(Generator generator, Distribution distribution, Simulation simulation)
    : generator_(std::move(generator)),
      distribution_(std::move(distribution)),
      simulation_(std::move(simulation)) {}

    auto Run(std::uint64_t t_paths) {
        simulation_.configure(t_paths);

        for (std::uint64_t i = 0; i < t_paths; ++i) {
           simulation_.process_sample(sample());
        }

        return simulation_.results();
    }

private:
    double sample() {
        return distribution_(generator_);
    }
    Generator generator_;
    Distribution distribution_;
    Simulation simulation_;
};
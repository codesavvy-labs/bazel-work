#pragma once
#include <utility>

template <typename Simulation, typename Generator>
auto RunMonteCarlo( Simulation & simulation, Generator & generator, std::uint64_t iterations) {

    for (std::uint64_t i = 0; i < iterations; ++i) {
        simulation.process_sample(generator);
    }
    return simulation.results();
}

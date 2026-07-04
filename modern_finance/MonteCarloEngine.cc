    #include "MonteCarloEngine.h"

    double MonteCarloEngine::sample() {
        return distribution_(generator_);
    }
    
    double MonteCarloEngine::Run() {
        simulation_.configure();
        for (std::uint64_t i = 0; i < simulation_.get_t_paths(); ++i) {
            double next_sample = simulation_.update(sample());
            
            if (std::isfinite(next_sample)) {
                simulation_.accumulate(simulation_.apply(next_sample));
            }
        }
        return simulation_.output_value();
    }

#include "instrument.h"

class EuropeanOption : public Instrument {
public:
    enum class OptionType { Call, Put };

    EuropeanOption(OptionType type, double strikePrice, double timeToMaturity)
        : type_(type), strikePrice_(strikePrice), timeToMaturity_(timeToMaturity) {}
    
    double price(const MarketData& marketData) const override {
        // Black-Scholes formula for European option pricing
        if (marketData.spotPrice <= 0.0 || marketData.volatility <= 0 || timeToMaturity_ <= 0) {
            throw std::invalid_argument("Invalid market data or time to maturity.");
        }
        
        double S = marketData.spotPrice;
        double K = strikePrice_;
        double T = timeToMaturity_;
        double r = marketData.discountRate;
        double sigma = marketData.volatility;

        // Implementation of Black-Scholes formula
        // ... (rest of the formula)
        double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - sigma * std::sqrt(T);

        auto N = [](double x) {
            return 0.5 * (1.0 + std::erfc(x / std::sqrt(2.0))); // CDF of standard normal distribution
        };
        // Calculate the option price based on the option type
        if (type_ == OptionType::Call) {
            return S * N(d1) - K * std::exp(-r * T) * N(d2);
        } else {
            return K * std::exp(-r * T) * N(-d2) - S * N(-d1);
        }
    }
private:
    OptionType type_;
    double strikePrice_;
    double timeToMaturity_;
};
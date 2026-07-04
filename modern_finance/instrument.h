#pragma once

#include "market_data.h"

// 
// Abrstract Instrument
//
class Instrument {
public: 
    virtual ~Instrument() = default;
    virtual double price(const MarketData& marketData) const = 0;
};

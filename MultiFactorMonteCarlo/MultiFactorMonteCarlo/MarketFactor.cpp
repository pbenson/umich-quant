//
//  MarketFactor.cpp
//  MultiFactorMonteCarlo
//
//  Created by Peter Benson on 10/24/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//

#include <numeric> //for inner_product
#include <math.h>       /* log */
#include "MarketFactor.hpp"


MarketFactor::MarketFactor(std::string name, const std::vector<double>& priceHistoryMostRecentFirst):m_name(name), m_prices(priceHistoryMostRecentFirst) {
    auto priceIt = m_prices.cbegin();
    double priceToday = *priceIt;
    ++priceIt;
    for(; priceIt < m_prices.cend(); ++priceIt) {
        double priceYesterday = *priceIt;
        m_logReturns.push_back(log(priceToday / priceYesterday));
        priceToday = priceYesterday;
    }
}

const std::string& MarketFactor::name() const{
    return m_name;
}

double MarketFactor::simulatedReturn(const MarketSimulation & sim) const{
    //    const std::vector<double>& weights (sim.weights());
    return inner_product(cbegin(m_logReturns), cend(m_logReturns), cbegin(sim.weights()), 0.0)
    //double inner_product(start x, end x, start y, initial value of the product)
    //sum=inner_product(x start, x end, y start,sum)  sum+=inner_product(x start, x end, y start)
    / sqrt(m_logReturns.size());
}

double MarketFactor::variance() const{
    return inner_product(cbegin(m_logReturns), cend(m_logReturns), cbegin(m_logReturns), 0.0)
    / m_logReturns.size();
}

double MarketFactor::mostRecentPrice() const{
    return m_prices[0];
}

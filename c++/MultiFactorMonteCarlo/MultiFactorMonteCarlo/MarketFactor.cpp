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
        //Returns a const_iterator pointing to the first element in the container.
    double priceToday = *priceIt;//back to the object
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
    if(sim.weights().size() > m_logReturns.size() ) {
        throw "In MarketFactor::simulatedReturn, not enought simulation weights for log returns";
    }
    return inner_product(std::begin(sim.weights()), std::end(sim.weights()), std::begin(m_logReturns), 0.0);
}

double MarketFactor::variance() const{
    return inner_product(std::begin(m_logReturns), std::end(m_logReturns), std::begin(m_logReturns), 0.0)
    / m_logReturns.size();
}

double MarketFactor::mostRecentPrice() const{
    return m_prices[0];
}

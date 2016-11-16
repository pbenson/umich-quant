//
//  Portfolio.cpp
//  MultiFactorMonteCarlo
//
//  Created by Peter Benson on 10/29/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//

#include <numeric>
#include "Portfolio.hpp"

void Portfolio::addPosition(const std::shared_ptr<Security> security, double positionSize) {
    m_positions.push_back(std::make_shared<Position>(security, positionSize));
    
}

double Portfolio::value(const MarketScenario& scenario) const{
    double value = 0;
    for(auto pPosition : m_positions) {
        value += pPosition->value(scenario);
    }
    return value;
}

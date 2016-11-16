//
//  Security.cpp
//  MultiFactorMonteCarlo
//
//  Created by Peter Benson on 10/29/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//

#include "Security.hpp"

Security::Security(const MarketFactor& factor):m_factor(factor){
}

double Security::valueOfOneUnit(const MarketScenario& scenario) const {
    return scenario.price(m_factor);
}

double Security::simValueOfOneUnit(const MarketScenario& scenario, const MarketSimulation& sim) const {
    return scenario.price(m_factor)*exp(m_factor.simulatedReturn(sim));
}

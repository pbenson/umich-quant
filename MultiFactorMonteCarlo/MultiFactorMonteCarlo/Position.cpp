//
//  Position.cpp
//  MultiFactorMonteCarlo
//
//  Created by Peter Benson on 10/29/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//

#include "Position.hpp"

Position::Position(const std::shared_ptr<Security> pSecurity, double positionSize):
m_pSecurity(pSecurity),m_positionSize(positionSize) {
}


double Position::value(const MarketScenario& scenario) const{
     return m_pSecurity->valueOfOneUnit(scenario) * m_positionSize;
}

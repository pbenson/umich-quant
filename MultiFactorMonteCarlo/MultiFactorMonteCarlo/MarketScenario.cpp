//
//  MarketScenario.cpp
//  MultiFactorMonteCarlo
//
//  Created by Peter Benson on 10/29/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//

#include "MarketScenario.hpp"

MarketScenario::MarketScenario(const Market& market, int y, int m, int d):m_market(market), m_pricingDate(y,m,d){
}

double MarketScenario::price(const MarketFactor& factor) const{
    return factor.mostRecentPrice();
}



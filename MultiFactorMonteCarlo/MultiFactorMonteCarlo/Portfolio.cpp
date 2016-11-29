//
//  Portfolio.cpp
//  MultiFactorMonteCarlo
//
//  Created by Peter Benson on 10/29/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//

#include <numeric>
#include "Portfolio.hpp"
#include "MarketSimulation.hpp"

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

double Portfolio::value(const MarketScenario& scenario, const MarketSimulation& sim) const{
    double value = 0;
    for(auto pPosition : m_positions) {
        value += pPosition->value(scenario,sim);
    }
    return value;
}

std::vector<double> Portfolio::profits(const MarketScenario& scenario, int numOfHistoricalReturns, int numOfSims) const{
    std::vector<double> profit_sim;
    
    const double todaysValue = value(scenario);
    for(int i = 0; i < numOfSims; ++i){
        MarketSimulation sim(numOfHistoricalReturns);
        const double tomorrowsValue = value(scenario,sim);
        profit_sim.push_back(tomorrowsValue-todaysValue);
    }
        
    return profit_sim;
}

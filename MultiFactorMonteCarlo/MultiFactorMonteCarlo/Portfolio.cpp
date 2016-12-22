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

std::vector<double> Portfolio::profits(const MarketScenario& scenario, int numOfHistoricalReturns, size_t numOfSims, double ewmaLambda) const{
    std::vector<double> profit_sim;
    
    const double todaysValue = value(scenario);
    for(int i = 0; i < numOfSims; ++i){
        MarketSimulation sim(numOfHistoricalReturns, ewmaLambda);
        const double tomorrowsValue = value(scenario,sim);
        profit_sim.push_back(tomorrowsValue-todaysValue);
    }
        
    return profit_sim;
}

std::vector<PortfolioSimResult> Portfolio::simResultsByPosition(const MarketScenario& scenario, int numOfHistoricalReturns, size_t numOfSims, double ewmaLambda) const{
    //store values for each position
    std::vector<double> positionValues;
    for(auto pPosition : m_positions){
        positionValues.push_back(pPosition->value(scenario));
    }

    std::vector<PortfolioSimResult> results(m_positions.size());
    for(int simIndex = 0; simIndex < numOfSims; ++simIndex)
    {
        const MarketSimulation sim(numOfHistoricalReturns, ewmaLambda);
        int positionIndex = 0;
        for(auto pPosition : m_positions){
            double pAndL = pPosition->value(scenario,sim)-positionValues[positionIndex];
            results[positionIndex].push_back(pAndL);
            ++positionIndex;
        }
    }
        
    return results;
}

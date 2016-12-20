//
//  PortfolioSimResult.cpp
//  MultiFactorMonteCarlo
//
//  Created by Hanxi Ye on 11/22/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//

#include "PortfolioSimResult.hpp"
PortfolioSimResult::PortfolioSimResult(const std::vector<double>& profits):m_profits(profits){}
PortfolioSimResult::PortfolioSimResult(){}
PortfolioSimResult::PortfolioSimResult(const std::vector<PortfolioSimResult>& positionResults){
    size_t numResults = positionResults[0].numResults();
    for(int simIndex = 0; simIndex < numResults; ++simIndex){
        double total = 0;
        for(auto result:positionResults){
            total += result.m_profits[simIndex];
        }
        m_profits.push_back(total);
    }
}

double PortfolioSimResult::var(double confidence) const{
    std::vector<double> profits(m_profits);
    std::sort(profits.begin(),profits.end());
    size_t varIndex = (int)(profits.size() + 1) * (1 - confidence) - 1;
    return -profits[varIndex];
}

double PortfolioSimResult::expectedShortfall(double confidence) const{
    std::vector<double> profits(m_profits);
    std::sort(profits.begin(),profits.end());
    size_t varIndex = (int)(profits.size() + 1) * (1 - confidence) - 1;
    double expectedShortfall = 0;
    for(int i = 0; i < varIndex+1; ++i){
        expectedShortfall += profits[i];
    }
    return -expectedShortfall / (varIndex + 1);
}

std::vector<int> PortfolioSimResult::varEvents(double quantile) const {
    double v = var(1-quantile);
    std::vector<int> varEvents;
    for(int i = 0; i < m_profits.size(); ++i){
        if(m_profits[i] < -v){
            varEvents.push_back(i);
        }
    }
    return varEvents;
}

double PortfolioSimResult::averagePnLonEvents(std::vector<int> portfolioVarEvents) const{
    double totalPnL = 0;
    for(auto eventIndex:portfolioVarEvents){
        totalPnL += m_profits[eventIndex];
    }
    return totalPnL / portfolioVarEvents.size();
}

size_t PortfolioSimResult::numResults() const{
    return (m_profits.size());
}

void PortfolioSimResult::push_back(const double profit){
    m_profits.push_back(profit);
}

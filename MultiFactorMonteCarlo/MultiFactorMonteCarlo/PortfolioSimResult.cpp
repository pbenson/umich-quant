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

void PortfolioSimResult::validateQuantile(double quantile) const {
    if(quantile < 1.0 / (m_profits.size() + 1) ) {
        throw "in PortfolioSimResult::validateQuantile(), quantile too small. Must be at least 1.0 / (# sims + 1).";
    }
    if(quantile > m_profits.size() / (m_profits.size() + 1.0) ) {
        throw "in PortfolioSimResult::validateQuantile(), quantile too large. Must be at most # sims / (# sims + 1).";
    }
}

double PortfolioSimResult::var(double quantile) const{
    validateQuantile(quantile);
    std::vector<double> profits(m_profits);
    std::sort(profits.begin(),profits.end());
    size_t varIndex = (profits.size() + 1) * quantile - 1;
    return -profits[varIndex];
}

double PortfolioSimResult::expectedShortfall(double quantile) const{
    validateQuantile(quantile);
    std::vector<double> profits(m_profits);
    std::sort(profits.begin(),profits.end());
    size_t varIndex = (profits.size() + 1) * quantile - 1;
    double expectedShortfall = 0;
    for(int i = 0; i < varIndex+1; ++i){
        expectedShortfall += profits[i];
    }
    return -expectedShortfall / (varIndex + 1);
}

std::vector<int> PortfolioSimResult::varEvents(double quantile) const {
    double v = var(quantile);
    std::vector<int> varEvents;
    for(int i = 0; i < m_profits.size(); ++i){
        if(m_profits[i] <= -v){
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

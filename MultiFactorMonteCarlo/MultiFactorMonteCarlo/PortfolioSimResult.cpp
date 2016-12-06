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

double PortfolioSimResult::var(double confidence){
    std::sort(m_profits.begin(),m_profits.end());
    size_t varIndex = (int)(m_profits.size() + 1) * (1 - confidence) - 1;
    return -m_profits[varIndex];
}

double PortfolioSimResult::expectedShortfall(double confidence){
    std::sort(m_profits.begin(),m_profits.end());
    size_t varIndex = (int)(m_profits.size() + 1) * (1 - confidence) - 1;
    double expectedShortfall = 0;
    for(int i = 0; i < varIndex+1; ++i){
        expectedShortfall += m_profits[i];
    }
    return -expectedShortfall / (varIndex + 1);
}

size_t PortfolioSimResult::numResults() const{
    return (m_profits.size());
}

void PortfolioSimResult::push_back(const double profit){
    m_profits.push_back(profit);
}

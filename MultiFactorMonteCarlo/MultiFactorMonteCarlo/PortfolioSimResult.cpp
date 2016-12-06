//
//  PortfolioSimResult.cpp
//  MultiFactorMonteCarlo
//
//  Created by Hanxi Ye on 11/22/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//

#include "PortfolioSimResult.hpp"
PortfolioSimResult::PortfolioSimResult(const std::vector<double>& profits):m_profits(profits){}

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

//
//  PortfolioSimResult.hpp
//  MultiFactorMonteCarlo
//
//  Created by Hanxi Ye on 11/22/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//

#ifndef PortfolioSimResult_hpp
#define PortfolioSimResult_hpp

#include <stdio.h>
#include <vector>

class PortfolioSimResult{
public:
    PortfolioSimResult(const std::vector<double>& profits);
    PortfolioSimResult();
    PortfolioSimResult(const std::vector<PortfolioSimResult>& positionResults);
    
    double var(double quantile) const;
    double expectedShortfall(double quantile) const;
    std::vector<int> varEvents(double quantile) const;
    double averagePnLonEvents(std::vector<int> portfolioVarEvents) const;
    void push_back(const double profit);
    size_t numResults() const;
    
private:
    std::vector<double> m_profits;
    
    void validateQuantile(double quantile) const;
};

#endif /* PortfolioSimResult_hpp */

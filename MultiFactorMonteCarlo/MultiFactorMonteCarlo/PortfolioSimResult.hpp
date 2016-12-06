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
    
    double var(double confidence);
    double expectedShortfall(double confidence);
    void push_back(const double profit);
    size_t numResults() const;
    
private:
    std::vector<double> m_profits;
};

#endif /* PortfolioSimResult_hpp */

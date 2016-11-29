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
    
private:
    const double portfolioProfit;
    const std::vector<double> positionProfits;
};

#endif /* PortfolioSimResult_hpp */

//
//  main.cpp
//  MultiFactorMonteCarlo
//
//  Created by Peter Benson on 10/21/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//
// This program supports:
// 1. read in table of t+1 prices for m assets
// 2. given current price levels, generate simulations of m asset prices
//

#include <iostream>
#include <fstream>
#include <boost/date_time.hpp>

#include "Market.hpp"
#include "Portfolio.hpp"
#include "Security.hpp"
#include "MarketScenario.hpp"
#include "MarketSimulation.hpp"
#include "PortfolioSimResult.hpp"

#include <algorithm>

int main(int argc, const char * argv[]) {
    std::ifstream inputPrices("IBM_T_NKE_AAPL_20141001-20160930.csv");
    if (!inputPrices.is_open()) {
        return 1; //file not open
    }
    Market market(inputPrices);
    
    const auto pApple = market.marketFactor("AAPL");
    std::cout << "AAPL variance = " << pApple->variance() << std::endl; //td::endl---flushes the output buffer
    
    int numberHistoricalReturns = 252;//use one year
    double ewmaLambda = 0.97;
    MarketSimulation simulation0(numberHistoricalReturns, ewmaLambda);
    std::cout << "AAPL return = " << pApple->simulatedReturn(simulation0) << std::endl;
    MarketSimulation simulation1(numberHistoricalReturns, ewmaLambda);
    
    Portfolio portfolio;
    portfolio.addPosition(std::make_shared<Security>(*market.marketFactor("AAPL")), 1000);
    portfolio.addPosition(std::make_shared<Security>(*market.marketFactor("IBM")), 1500);
    portfolio.addPosition(std::make_shared<Security>(*market.marketFactor("T")), 10000);
    portfolio.addPosition(std::make_shared<Security>(*market.marketFactor("NKE")), 3000);
    
    
    const MarketScenario scenario(market, 2016, 9, 30);
    size_t numSims = 9999;
    std::vector<PortfolioSimResult> positionResults = portfolio.simResultsByPosition(scenario, numberHistoricalReturns,numSims, ewmaLambda);
    PortfolioSimResult portfolioResults(positionResults);
    double quantile = 0.025;
    double percent = quantile * 100;
    std::cout << percent << "% quantile VaR = " << portfolioResults.var(quantile)<<std::endl;
    std::cout << percent << "% quantile ES = " << portfolioResults.expectedShortfall(quantile) << std::endl;
    std::vector<int> portfolioVarEvents(portfolioResults.varEvents(quantile));
    double totalES = 0;
    for(auto result:positionResults){
        double incrementalES = -result.averagePnLonEvents(portfolioVarEvents);
        totalES += incrementalES;
        std::cout << incrementalES << std::endl;
    }
    std::cout << "Sum of IES = " << totalES << std::endl;
    return 0;
}

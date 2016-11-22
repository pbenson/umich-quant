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

#include <algorithm>

double var(std::vector<double> profits, double confidence){
    std::sort(profits.begin(),profits.end());
    size_t varIndex = (int)(profits.size() + 1) * (1 - confidence) - 1;
    return -profits[varIndex];
}

double es(std::vector<double> profits, double confidence){
    std::sort(profits.begin(),profits.end());
    size_t varIndex = (int)(profits.size() + 1) * (1 - confidence) - 1;
    double expectedShortfall = 0;
    for(int i = 0; i < varIndex+1; ++i){
        expectedShortfall += profits[i];
    }
    return -expectedShortfall / (varIndex + 1);
}
int main(int argc, const char * argv[]) {
    std::ifstream inputPrices("IBM_T_NKE_AAPL_20141001-20160930.csv");
    if (!inputPrices.is_open()) {
        return 1; //file not open
    }
    Market market(inputPrices);
    
    const auto pApple = market.marketFactor("AAPL");
    std::cout << "AAPL variance = " << pApple->variance() << std::endl; //td::endl---flushes the output buffer
    
    int numberHistoricalReturns = market.numberHistoricalReturns();
    MarketSimulation simulation0(numberHistoricalReturns);
    std::cout << "AAPL return = " << pApple->simulatedReturn(simulation0) << std::endl;
    MarketSimulation simulation1(numberHistoricalReturns);
    
    Portfolio portfolio;
    portfolio.addPosition(std::make_shared<Security>(*market.marketFactor("AAPL")), 1000);
    portfolio.addPosition(std::make_shared<Security>(*market.marketFactor("IBM")), 1500);
    portfolio.addPosition(std::make_shared<Security>(*market.marketFactor("T")), 10000);
    portfolio.addPosition(std::make_shared<Security>(*market.marketFactor("NKE")), 3000);
    
    
    //Pete: This is what we are working on next. Tt is missing implementation.
    const MarketScenario scenario(market, 2016, 9, 30);
    std::cout << portfolio.value(scenario) << std::endl;
    std::cout << portfolio.value(scenario,simulation1) << std::endl;
    
    size_t numSims = 9999;
    std::vector<double> result = portfolio.profits(scenario,numberHistoricalReturns, int(numSims));
    
    std::cout << "95% VaR = " << var(result,0.95)<<std::endl;
    
    std::cout << "Expected Shortfall = " << es(result,0.95) << std::endl;
    return 0;
}

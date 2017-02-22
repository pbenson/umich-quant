//
//  testMarket.cpp
//  MultiFactorMonteCarlo
//
//  Created by Peter Benson on 10/26/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//
#include "catch.hpp"

#include "Market.hpp"

TEST_CASE("Testing Market Class") {
    std::ifstream inputPrices("IBM_T_NKE_AAPL_20141001-20160930.csv");
    const Market market(inputPrices);
    const std::shared_ptr<MarketFactor> pApple = market.marketFactor("AAPL");
    
    SECTION("Constructing Market from input file") {
        INFO("wrong number of historical returns") // Only appears on a FAIL
        std::ifstream inputPrices("IBM_T_NKE_AAPL_20141001-20160930.csv");
        const Market market(inputPrices);
        
        CHECK(market.numberHistoricalReturns() == 504);
    }
 }

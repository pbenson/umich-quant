//
//  testMarketFactor.cpp
//  MultiFactorMonteCarlo
//
//  Created by Peter Benson on 10/26/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//
//
#include "catch.hpp"

#include "Market.hpp"

TEST_CASE("Testing MarketFactor Class") {
    std::ifstream inputPrices("IBM_T_NKE_AAPL_20141001-20160930.csv");
    const Market market(inputPrices);
    const auto pApple = market.marketFactor("AAPL");
    
    SECTION("getting market factor from map") {
        INFO("Using AAPL market factor") // Only appears on a FAIL
        std::string name = pApple->name();
        CAPTURE(name); // Displays this variable on a FAIL
        
        CHECK(name == "AAPL");
    }
    
    SECTION("test variance") {
        REQUIRE(pApple->variance() == Approx(0.0002584682));
    }
    
    //    SECTION("Test doubles") {
    //        sc.setD(1);
    //        CHECK(sc.getD() == 1);
    //        sc.setD(1.0/3.0);
    //        CHECK(sc.getD() == Approx(0.33333)); // Nice
    //    }
}

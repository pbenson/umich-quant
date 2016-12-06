//
//  testMarketSimulation.cpp
//  MultiFactorMonteCarlo
//
//  Created by Peter Benson on 10/26/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//

#include <fstream>
#include "catch.hpp"

#include "Market.hpp"
#include "MarketSimulation.hpp"

TEST_CASE("Testing MarketSimulation Class") {
    std::ifstream inputPrices("IBM_T_NKE_AAPL_20141001-20160930.csv");
    const Market market(inputPrices);
    const std::shared_ptr<MarketFactor> pApple = market.marketFactor("AAPL");
    int numberHistoricalReturns = market.numberHistoricalReturns();
    
    //    const std::shared_ptr<MarketFactor> pApple = market.marketFactor("AAPL");
    //    std::cout << "AAPL variance = " << pApple->variance() << std::endl;
    //
    //    int numberHistoricalReturns = market.numberHistoricalReturns();
    //    MarketSimulation simulation0(numberHistoricalReturns);
    //    std::cout << "AAPL return = " << pApple->simulatedReturn(simulation0.weights()) << std::endl;
    //    MarketSimulation simulation1(numberHistoricalReturns);
    //    std::cout << "AAPL return = " << pApple->simulatedReturn(simulation1.weights()) << std::endl;
    //    MarketSimulation::resetSeed();
    //    MarketSimulation simulation2(numberHistoricalReturns);
    //    std::cout << "AAPL return = " << pApple->simulatedReturn(simulation2.weights()) << std::endl;
    
    SECTION("verifying number of historical returns") {
        REQUIRE(market.numberHistoricalReturns() == 504);
    }
    
    
    SECTION("creating a market simulation") {
        INFO("first simulation") // Only appears on a FAIL
        MarketSimulation simulation(numberHistoricalReturns);
        REQUIRE(pApple->simulatedReturn(simulation) == Approx(-0.0197994437));
    }
    
    SECTION("creating 2nd market simulation") {
        INFO("2nd simulation") // Only appears on a FAIL
        MarketSimulation simulation(numberHistoricalReturns);
        REQUIRE(pApple->simulatedReturn(simulation) == Approx(0.0440606219));
    }
    
    SECTION("resetting random seed") {
        INFO("reset seed") // Only appears on a FAIL
        MarketSimulation::resetSeed();
        MarketSimulation simulation(numberHistoricalReturns);
        REQUIRE(pApple->simulatedReturn(simulation) == Approx(-0.0197994437));
    }
    
}

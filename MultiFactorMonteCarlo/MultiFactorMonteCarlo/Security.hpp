//
//  Security.hpp
//  MultiFactorMonteCarlo
//
//  Created by Peter Benson on 10/29/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//

#ifndef Security_hpp
#define Security_hpp

#include <string>
#include "MarketScenario.hpp"
#include "MarketFactor.hpp"

class Security {
public:
    Security(const MarketFactor& factor);
    
    double valueOfOneUnit(const MarketScenario&) const;
    double simValueOfOneUnit(const MarketScenario&, const MarketSimulation&) const;
    
private:
    const MarketFactor& m_factor;
    
};

#endif /* Security_hpp */

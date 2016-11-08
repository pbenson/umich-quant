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

class Security {
public:
    Security(const std::string& name);
    
    double valueOfOneUnit(const MarketScenario&) const;
    
private:
    const std::string m_name;
    
};

#endif /* Security_hpp */

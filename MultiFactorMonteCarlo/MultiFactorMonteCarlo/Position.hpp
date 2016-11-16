//
//  Position.hpp
//  MultiFactorMonteCarlo
//
//  Created by Peter Benson on 10/29/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//

#ifndef Position_hpp
#define Position_hpp

#include "Security.hpp"
#include "MarketScenario.hpp"

class Position{
public:
    Position(const std::shared_ptr<Security>, double positionSize);
    double value(const MarketScenario&) const;
   
private:
    const std::shared_ptr<Security> m_pSecurity;
    const double m_positionSize;
};

#endif /* Position_hpp */

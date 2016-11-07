//
//  MarketScenario.hpp
//  MultiFactorMonteCarlo
//
//  Created by Peter Benson on 10/29/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//

#ifndef MarketScenario_hpp
#define MarketScenario_hpp
#include <boost/date_time.hpp>

class MarketScenario {
public:
    MarketScenario(int year, int month, int day);
private:
    boost::gregorian::date m_pricingDtae;
    
};

#endif /* MarketScenario_hpp */

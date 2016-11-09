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
#include "Market.hpp"

class MarketScenario {
public:
    MarketScenario(const Market&, int year, int month, int day);
    double price(const std::string& factorname) const;
private:
    const Market& m_market;
    boost::gregorian::date m_pricingDate;
};


#endif /* MarketScenario_hpp */

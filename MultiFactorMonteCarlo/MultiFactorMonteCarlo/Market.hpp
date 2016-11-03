//
//  Market.hpp
//  MultiFactorMonteCarlo
//
//  Created by Peter Benson on 10/21/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//

#ifndef Market_h
#define Market_h

#include <map>
#include <fstream>
#include <boost/date_time.hpp>
#include "MarketFactor.hpp"

class Market {
public:
    Market(std::ifstream& inputPrices);
    
    void pricingDate(const boost::gregorian::date&);
    const std::shared_ptr<MarketFactor> marketFactor(const std::string& factorName) const;
    int numberHistoricalReturns() const;
    
private:
    int m_numberReturns;
    std::map<const std::string,  std::shared_ptr<MarketFactor>> m_nameToMarketFactorMap;
    std::vector<boost::gregorian::date> m_dates;
    boost::gregorian::date m_pricingDate;
};


#endif /* Market_h */

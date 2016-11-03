//
//  MarketFactor.hpp
//  MultiFactorMonteCarlo
//
//  Created by Peter Benson on 10/25/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//

#ifndef MarketFactor_h
#define MarketFactor_h

#include <string>
#include <vector>

class MarketFactor {
public:
    MarketFactor(std::string name, const std::vector<double>& priceHistoryMostRecentFirst);
    
    const std::string& name() const;
    double simulatedReturn(const std::vector<double>& weights) const;
    double variance() const;
    
private:
    std::string m_name;
    const std::vector<double> m_prices;
    std::vector<double> m_logReturns;
};

#endif /* MarketFactor_h */

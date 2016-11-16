//
//  Market.cpp
//  MultiFactorMonteCarlo
//
//  Created by Peter Benson on 10/24/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//
#include <boost/algorithm/string.hpp>
#include <sstream>
#include "Market.hpp"

Market::Market(std::ifstream& input) {
    
    //read header
    std::string header;
    getline(input, header, '\r');
    std::stringstream headerStream(header);
    std::string marketFactorName;
    //read first column, which should be Date column header, so ignore
    getline(headerStream, marketFactorName, ',');
    
    //now loop through all factor names, create factors and insert into map
    std::vector<std::string> marketFactorNames;//use later in function to add data
    while(getline(headerStream, marketFactorName, ',')) {
        marketFactorNames.push_back(marketFactorName);
    }
    
    //create vector of priceVectors, one for each factor
    std::vector< std::vector<double>> pricesForFactors;
    for(auto it : marketFactorNames) {
        auto priceVector = std::vector<double>();
        pricesForFactors.push_back(priceVector);
    }
    //now read rest of file, a line at a time
    std::string row;
    m_numberReturns = -1;
    while(getline(input, row, '\r')) {
        std::stringstream rowStream(row);
        std::string dateString;
        
        //read date column, create and store boost date
        getline(rowStream, dateString, ',');
        boost::trim(dateString);
        m_dates.push_back(boost::gregorian::from_undelimited_string(dateString));
        std::string priceString;
        for(auto&  priceVector :  pricesForFactors) {
            getline(rowStream, priceString, ',');
            priceVector.push_back(stod(priceString));
        }
        ++m_numberReturns;
    }
    
    for(size_t factorIndex = 0; factorIndex < marketFactorNames.size(); ++factorIndex ) {
        const std::string& factorName = marketFactorNames[factorIndex];
        m_nameToMarketFactorMap[factorName] =  std::make_shared<MarketFactor>(factorName, pricesForFactors[factorIndex]) ;
    }
    

    m_pricingDate = m_dates[0];
}

const std::shared_ptr<MarketFactor> Market::marketFactor(const std::string& factorName) const {
    return m_nameToMarketFactorMap.find(factorName)->second;
}

int Market::numberHistoricalReturns() const {
    return m_numberReturns;
}

void Market::pricingDate(const boost::gregorian::date& pricingDate)  {
    m_pricingDate = pricingDate;
}


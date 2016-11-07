//
//  MarketSimulation.hpp
//  MultiFactorMonteCarlo
//
//  Created by Peter Benson on 10/25/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//

#ifndef MarketSimulation_hpp
#define MarketSimulation_hpp

#include <stdio.h>
#include <random>

class MarketSimulation {
public:
    MarketSimulation( int numberOfWeights );
    
    const std::vector<double>& weights() const;
    
    static void resetSeed();

private:
    static std::default_random_engine generator;
    static std::normal_distribution<double> standardNormalDistribution;
    
    std::vector<double> m_weights;
};

#endif /* MarketSimulation_hpp */

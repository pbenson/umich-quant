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
    MarketSimulation( int numberOfWeights, double lambda );
    
    const std::vector<double>& weights() const;
    
    static void resetSeed();
    //static variable works for all of this class

private:
    static std::default_random_engine generator;
    //This is a random number engine class that generates pseudo-random numbers
    static std::normal_distribution<double> standardNormalDistribution;
    //Generates random numbers according to the Normal (or Gaussian) random number distribution
    std::vector<double> m_weights;
    const double m_lambda;
};

#endif /* MarketSimulation_hpp */

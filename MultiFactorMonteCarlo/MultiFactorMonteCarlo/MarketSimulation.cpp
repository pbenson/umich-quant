//
//  MarketSimulation.cpp
//  MultiFactorMonteCarlo
//
//  Created by Peter Benson on 10/25/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//
#include <random>

#include "MarketSimulation.hpp"

std::default_random_engine MarketSimulation::generator;
std::normal_distribution<double> MarketSimulation::standardNormalDistribution(0, 1);

MarketSimulation::MarketSimulation(int size, double lambda):m_weights(size), m_lambda(lambda) {
    if(lambda <= 0 || lambda > 1) {
        throw "In MarketSimulation constructor, EWMA lambda must be positive and at most 1.";
    }
    double sumOfPowersOfLambda = (lambda == 1) ? size : (1 - pow(lambda, size + 1))/(1-lambda);
    double ewmaWeight = 1 / sqrt(sumOfPowersOfLambda);
    double sqrtLambda = sqrt(lambda);
    for(int i = 0; i < size; ++i) {
        m_weights[i] = standardNormalDistribution(generator) * ewmaWeight;
        ewmaWeight *= sqrtLambda;
    }
}

const std::vector<double>& MarketSimulation::weights() const {
    return m_weights;
}

void MarketSimulation::resetSeed() {
    generator.seed(generator.default_seed);
}

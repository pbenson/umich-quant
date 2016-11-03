//
//  Position.cpp
//  MultiFactorMonteCarlo
//
//  Created by Peter Benson on 10/29/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//

#include "Position.hpp"

Position::Position(const std::shared_ptr<Security> security, double positionSize):
m_security(security),m_positionSize(positionSize) {
    
}

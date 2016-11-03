//
//  Security.hpp
//  MultiFactorMonteCarlo
//
//  Created by Peter Benson on 10/29/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//

#ifndef Security_hpp
#define Security_hpp

#include <string>

class Security {
public:
    Security(const std::string& name);
    
private:
    const std::string m_name;
    
};

#endif /* Security_hpp */

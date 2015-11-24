//
//  Position.hpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//

#ifndef Position_hpp
#define Position_hpp

#include <stdio.h>
#include <set>

///
class Position {
private:
    std::string _name;
    
public:
    Position(const std::string& name);
    
    std::string getName() const;
    void setName(const std::string& name);
    
    ~Position();
};

#endif /* Position_hpp */

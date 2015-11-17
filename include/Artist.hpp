//
//  Artist.hpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//

#ifndef Artist_hpp
#define Artist_hpp

#include <stdio.h>
#include <iostream>
#include <set>

#include "Position.hpp"
#include "Person.hpp"

class Artist: public Person {
    std::string _nationality;
    std::set<Position*> _position;
    
public:
    
};

#endif /* Artist_hpp */

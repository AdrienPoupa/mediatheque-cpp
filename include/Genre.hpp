//
//  Genre.hpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//

#ifndef Genre_hpp
#define Genre_hpp

#include <stdio.h>
#include <set>

#include <string>

class Genre {
    static std::set<Genre*> _pool;

public:
    bool remove(std::string genre);
};
#endif /* Genre_hpp */

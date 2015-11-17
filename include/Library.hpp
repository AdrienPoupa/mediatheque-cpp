//
//  Library.hpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//

#ifndef Library_hpp
#define Library_hpp

#include <stdio.h>
#include <set>

#include "Article.hpp"
#include "Person.hpp"

class Library {
    std::set<Article*> _articleSet;
    std::set<Person*> _personSet;
    
public:
    Library();
    ~Library();
    
};

#endif /* Library_hpp */

#ifndef Library_hpp
#define Library_hpp

#include <iostream>
#include <stdio.h>
#include <set>

#include "BaseModel.hpp"
#include "Article.hpp"
#include "Person.hpp"
#include "User.hpp"
#include "../sqlite/SQLiteCpp.h"

class Library {
    std::set<Article*> _articleSet;
    std::set<Person*> _personSet;
    User _currentUser;

public:
    static Library *getSingleton();
    void open();

private:
    Library();
    ~Library();

    static Library* singleton;

};

#endif /* Library_hpp */

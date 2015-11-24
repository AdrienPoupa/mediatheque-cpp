//
//  User.hpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//

#ifndef User_hpp
#define User_hpp

#include <stdio.h>
#include <set>

#include "Article.hpp"
#include "Address.hpp"
#include "Date.hpp"
#include "Person.hpp"


class User: public Person {
    private:
        Address _address;
        std::set<Article*> _borrowed;

    public:
        User(std::string firstName, std::string lastName, Date birthDate);
        ~User();
        bool save();
        bool update();
        bool remove();
};

#endif /* User_hpp */

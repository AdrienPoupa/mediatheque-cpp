//
//  Genre.hpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//

#ifndef Genre_hpp
#define Genre_hpp

#include <iostream>

#include <stdio.h>
#include <set>

#include <string>

#include "../sqlite/SQLiteCpp.h"

class Genre {
    private:
        static std::set<Genre*> _pool; // Utilité?
        std::string _name;
        int _id = 0;

    public:
        Genre(const std::string name = "Inconnu");
        Genre(int id);
        ~Genre();
        bool save();
        bool remove();
        int getId();
        void setName(const std::string name);
        std::string getName() const;

        friend std::ostream& operator<< (std::ostream& stream, const Genre& genre);
        friend std::istream& operator>> (std::istream& stream, Genre& genre);
};
#endif /* Genre_hpp */

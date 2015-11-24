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
    private:
        static std::set<Genre*> _pool;
        std::string _name;
        int _id = -1;

    public:
        Genre(const std::string name);
        bool save();
        bool update();
        bool remove();
        int getId();
        void setName(const std::string name);
        std::string getName() const;
};
#endif /* Genre_hpp */

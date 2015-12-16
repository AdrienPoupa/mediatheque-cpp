#ifndef Genre_hpp
#define Genre_hpp

#include <iostream>

#include <stdio.h>
#include <set>

#include <string>

#include "../sqlite/SQLiteCpp.h"

class Genre {
    private:
        std::string _name = "Inconnu";
        int _id = 0;

    public:
        Genre(const std::string name = "Inconnu");
        Genre(const int id);
        ~Genre();

        int getId() const;

        void setName(const std::string name);
        std::string getName() const;

        bool save();
        bool remove();

        friend std::ostream& operator<< (std::ostream& stream, const Genre& genre);
        friend std::istream& operator>> (std::istream& stream, Genre& genre);
};
#endif /* Genre_hpp */

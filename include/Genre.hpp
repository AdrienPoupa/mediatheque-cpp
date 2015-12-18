#ifndef Genre_hpp
#define Genre_hpp

#include <iostream>

#include <stdio.h>

#include <map>

#include <string>

#include "../sqlite/SQLiteCpp.h"

#include "BaseModel.hpp"

class Genre {
    protected:
        std::string _name = "Inconnu";
        int _id = 0;

    public:
        Genre(const std::string name = "Inconnu");
        Genre(const int id);
        ~Genre();

        void init(std::map<std::string, std::string> data);

        void shortDisplay() const;

        virtual void deserialization(std::map<std::string, std::string> data);

        int getId() const;

        void setName(const std::string name);
        std::string getName() const;

        void edit();

        virtual bool save();
        virtual bool remove();

        friend std::ostream& operator<< (std::ostream& stream, const Genre& genre);
        friend std::istream& operator>> (std::istream& stream, Genre& genre);
};
#endif /* Genre_hpp */

#ifndef Status_hpp
#define Status_hpp

#include <iostream>

#include <stdio.h>

#include <string>

#include "../sqlite/SQLiteCpp.h"

#include "BaseModel.hpp"

#include "Genre.hpp"

class Status : public Genre {

    public:
        Status(const std::string name = "Inconnu");
        Status(const int id);
        ~Status();

        void deserialization(std::map<std::string, std::string> data);

        bool save();
        bool remove();

        friend std::ostream& operator<< (std::ostream& stream, const Status& status);
        friend std::istream& operator>> (std::istream& stream, Status& status);
};

#endif /* Status_hpp */


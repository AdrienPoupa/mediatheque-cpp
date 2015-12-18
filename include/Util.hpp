#ifndef Util_hpp
#define Util_hpp

#include <iostream>

#include "Artist.hpp"
#include "Book.hpp"
#include "Cd.hpp"
#include "Dvd.hpp"
#include "Genre.hpp"
#include "Status.h"

class Util
{
    public:
        enum Types{Book, Cd, Dvd, Artist, User, Genre, Status, Transaction};

        static std::string getTypesString(Types type)
        {
            switch(type)
            {
                case Types::Book:
                    return "livre";
                    break;
                case Types::Cd:
                    return "cd";
                    break;
                case Types::Artist:
                    return "artiste";
                    break;
                case Types::User:
                    return "utilisateur";
                    break;
                case Types::Genre:
                    return "genre";
                    break;
                case Types::Status:
                    return "status";
                    break;
                case Types::Transaction:
                    return "emprunt";
                    break;
                default:
                    return "dvd";
            }
        }

        bool static checkInput(std::istream& stream, const int intToCheck, const int minValue);
        bool static isFilterableType(int type);
};

#endif // Util_hpp

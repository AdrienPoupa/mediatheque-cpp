#ifndef Util_hpp
#define Util_hpp

#include <iostream>

#include "Artist.hpp"
#include "Book.hpp"
#include "Cd.hpp"
#include "Dvd.hpp"

class Util
{
    public:
        enum Types{Book, Cd, Dvd, Artist, User, Transaction};

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
                case Types::Transaction:
                    return "emprunt";
                    break;
                default:
                    return "dvd";
            }
        }

        bool static checkInput(std::istream& stream, const int intToCheck, const int minValue);
};

#endif // Util_hpp

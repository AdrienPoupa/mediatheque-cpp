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
        enum Types{Book, Cd, Artist, User, Dvd};

        static std::string getTypesString(Types type)
        {
            switch(type)
            {
                case Types::Book:
                    return "livre";
                    break;
                case Types::Cd:
                    return "Cd";
                    break;
                case Types::Artist:
                    return "Artist";
                    break;
                case Types::User:
                    return "User";
                    break;
                default:
                    return "Dvd";
            }
        }

        bool static checkInput(std::istream& stream, const int intToCheck, const int minValue);
};

#endif // Util_hpp

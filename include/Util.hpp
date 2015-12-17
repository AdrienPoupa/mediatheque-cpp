#ifndef Util_hpp
#define Util_hpp

#include <iostream>

#include "Book.hpp"
#include "Cd.hpp"
#include "Dvd.hpp"

class Util
{
    public:
        enum Types{Book, Cd, Dvd};

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
                default:
                    return "Dvd";
            }
        }

        bool static checkInput(std::istream& stream, const int intToCheck, const int minValue);
};

#endif // Util_hpp

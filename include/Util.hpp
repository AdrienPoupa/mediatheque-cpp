#ifndef Util_hpp
#define Util_hpp

#include <iostream>

#include "Artist.hpp"
#include "Book.hpp"
#include "Cd.hpp"
#include "Dvd.hpp"
#include "Genre.hpp"
#include "Status.h"
#include "User.hpp"

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

        // Should be within cpp, but can't load...
        template <class T>
        int static displayIdList(std::string table, std::string fields = "*")
        {
            std::map<int, std::map<std::string, std::string>> rows = BaseModel::select(table, "*");

            int totalCount = (int) rows.size();
            std::set<int> ids = std::set<int>();

            for(int i = 1; i <= totalCount; i++)
            {
                T tmp = T();
                tmp.init(rows[i]);
                tmp.shortDisplay();
                ids.insert(stoi(rows[i]["id"]));
            }

            int selectedId;
            bool failInput = false;
            do
            {
                std::cout << "Choisir ID (0 pour arreter) : ";
                std::cin >> selectedId;
                if(std::cin.fail())
                {
                    failInput = true;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            } while(failInput || (ids.find(selectedId) == ids.end() && selectedId != 0));

            return selectedId;
        }
};

#endif // Util_hpp

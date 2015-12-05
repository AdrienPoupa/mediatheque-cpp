#ifndef User_hpp
#define User_hpp

#include <stdio.h>
#include <set>

#include "Article.hpp"
#include "Address.hpp"
#include "Date.hpp"
#include "Person.hpp"


class User: public Person {
    private:
        Address _address;
        std::set<Article*> _borrowed;
        std::string _phone;
    
        static std::string _dbTable;

    public:
        User(std::string firstName, std::string lastName, Date birthDate, std::string phone = "Inconnu");
        ~User();
        User(int id); // Get a person from an ID provided by DB

        std::string getPhone();
        void setPhone(std::string phone);

        Address getAddress();
        void setAddress(Address address);

        bool save();
        bool remove();
};

#endif /* User_hpp */

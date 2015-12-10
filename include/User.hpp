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
        int _isAdmin = 0, _quota = 1;
        std::string _password;

        static std::string _dbTable;

    public:
        User(std::string firstName, std::string lastName, Date birthDate,
             std::string phone = "Inconnu", int _isAdmin = 0, int _quota = 1, std::string password = "");
        ~User();
        User(int id); // Get a person from an ID provided by DB

        std::string getPhone();
        void setPhone(std::string phone);

        void setPassword(std::string password);
        bool checkPassword(std::string password);

        Address getAddress();
        void setAddress(Address address);

        int getAdmin();
        void setAdmin(int isAdmin);

        int getQuota();
        void setQuota(int quota);

        bool save();
        bool remove();
};

#endif /* User_hpp */

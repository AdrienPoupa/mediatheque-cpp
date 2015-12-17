#ifndef User_hpp
#define User_hpp

#include <stdio.h>
#include <set>
#include <iostream>

#include "Article.hpp"
#include "Address.hpp"
#include "Date.hpp"
#include "Person.hpp"

class Transaction;

class User: public Person {
    private:
        Address _address;
        std::set<Article*> _borrowed;
        std::string _phone;
        int _isAdmin = 0, _quota = 1;
        std::string _password;

        static std::string _dbTable;

    public:
        User(const std::string firstName, const std::string lastName, const Date birthDate,
             const std::string phone = "Inconnu", const int _isAdmin = 0, const int _quota = 1, const std::string password = "");
        User();
        ~User();
        User(int id); // Get a person from an ID provided by DB

        std::string getPhone() const ;
        void setPhone(const std::string phone);

        void setPassword(const std::string password);
        bool checkPassword(const std::string password) const;

        Address getAddress()const ;
        void setAddress(const Address address);

        bool isAdmin()const ;
        void setAdmin(const int isAdmin);

        int getQuota()const;
        void setQuota(const int quota);
        bool checkQuota() const;

        bool borrow(Article* art, const std::string type);
        bool returnArticle(Transaction * t);

        bool save();
        bool remove();

        friend std::ostream& operator<< (std::ostream& stream, const User& user);
        friend std::istream& operator>> (std::istream& stream, User& user);
};

#endif /* User_hpp */

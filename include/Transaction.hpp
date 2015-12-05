#ifndef Transaction_hpp
#define Transaction_hpp

#include <stdio.h>
#include "../sqlite/SQLiteCpp.h"
#include "BaseModel.hpp"
#include "Article.hpp"
#include "Book.hpp"
#include "Cd.hpp"
#include "Dvd.hpp"
#include "Date.hpp"
#include "User.hpp"

class Transaction {
    private:
        Article *_article;
        std::string _type = "Book";
        User _user;
        Date _beginning, _finish;
        int _id = 0;
        static std::string _dbTable;
    public:
        Transaction(Article *article, std::string type, User user, Date beginning, Date finish);
        //Transaction(unsigned int id);
        virtual ~Transaction();

        User getUser() const;
        void setUser(const User user);

        Date getBeginDate() const;
        void setBeginDate(const Date beginning);

        Date getFinishDate() const;
        void setFinishDate(const Date finish);

        unsigned int getId() const;
        void setId(const unsigned int id);

        std::string getType() const;
        void setType(std::string const type);

        void displayCurrentTransactions();
        void displayAllTransactions();
        void displayTransactions(int day = 0, int month = 0, int year = 0);
        //Transaction getTransaction(int id);

        bool save();
        bool remove();

        friend std::ostream& operator<<(std::ostream& os, const Transaction& transaction);
        friend std::istream& operator>>(std::istream& is, Transaction& transaction);
};

#endif /* Transaction_hpp */

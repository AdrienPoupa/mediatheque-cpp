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
#include <list>

class Transaction {
    private:
        Article *_article;
        int _articleId, _userId;
        bool _returned = false;
        std::string _type = "Book";
        User _user;
        Date _beginning, _finish;
        int _id = 0;
        static std::string _dbTable;
    public:
        Transaction(int articleId, std::string type, int userId);
        Transaction(Article *article, std::string type, User user, Date beginning, Date finish);
        Transaction(int id, int article_id, std::string type, int borrower_id, Date date_beginning, Date date_returned, bool returned);
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

        static void displayCurrentTransactions();
        static void displayTransactions(std::string current = "current", int day_borrowed = 0, int month_borrowed = 0, int year_borrowed = 0, int day_returned = 0, int month_returned = 0, int year_returned = 0);
        //Transaction getTransaction(int id);
    
        static std::list<Transaction> byUser(int userId, bool active);

        bool save();
        bool remove();

        friend std::ostream& operator<<(std::ostream& os, const Transaction& transaction);
        friend std::istream& operator>>(std::istream& is, Transaction& transaction);
};

#endif /* Transaction_hpp */

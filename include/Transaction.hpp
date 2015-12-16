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
        Transaction(const int articleId, const std::string type, const int userId);
        Transaction(Article *article, const std::string type, const User user, const Date beginning, const Date finish);
        Transaction(const int id, const int article_id, const std::string type, const int borrower_id, const Date date_beginning, const Date date_returned, const bool returned);
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
        static void displayTransactions(const std::string current = "current", const int day_borrowed = 0,
                                        const int month_borrowed = 0, const int year_borrowed = 0,
                                        const int day_returned = 0, const int month_returned = 0, const int year_returned = 0);
        //Transaction getTransaction(int id);

        static std::list<Transaction> byUser(const int userId, const bool active);

        bool save();
        bool remove();

        friend std::ostream& operator<<(std::ostream& os, const Transaction& transaction);
        friend std::istream& operator>>(std::istream& is, Transaction& transaction);
};

#endif /* Transaction_hpp */

#ifndef Transaction_hpp
#define Transaction_hpp

#include <stdio.h>
#include <list>

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
        int _articleId, _userId;
        bool _returned = false;
        int _type = 0;
        User _user;
        Date _beginning, _finish;
        int _id = 0;
        static std::string _dbTable;
    public:
        Transaction();
        Transaction(const int articleId, const int type, const int userId);
        Transaction(Article *article, const int type, const User user, const Date beginning, const Date finish);
        Transaction(const int id, const int article_id, const int type, const int borrower_id, const Date date_beginning, const Date date_returned, const bool returned);
        Transaction(unsigned int id);
        virtual ~Transaction();
    
        void init(std::map<std::string, std::string> data);
        void deserialization(std::map<std::string, std::string> data);

        User getUser() const;
        void setUser(const User user);

        Date getBeginDate() const;
        void setBeginDate(const Date beginning);

        Date getFinishDate() const;
        void setFinishDate(const Date finish);

        unsigned int getId() const;
        void setId(const unsigned int id);

        int getType() const;
        void setType(const int type);
    
        int getArticleId() const;
        void setArticleId(const  unsigned int id);
    
        int getUserId() const;
        void setUserId(const unsigned int id);
    
        bool getReturned() const;
        void setReturned(const bool returned);

        static void displayCurrentTransactions();
        static void displayTransactions(const std::string current = "current", const int day_borrowed = 0,
                                        const int month_borrowed = 0, const int year_borrowed = 0,
                                        const int day_returned = 0, const int month_returned = 0, const int year_returned = 0);
        //Transaction getTransaction(int id);

        static std::list<Transaction> byUser(const int userId, const bool active);

        bool save();
        bool remove();
    
        void shortDisplay() const;

        friend std::ostream& operator<<(std::ostream& os, const Transaction& transaction);
        friend std::istream& operator>>(std::istream& is, Transaction& transaction);
};

#endif /* Transaction_hpp */

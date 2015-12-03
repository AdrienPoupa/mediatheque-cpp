//
//  Transaction.hpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//

#ifndef Transaction_hpp
#define Transaction_hpp

#include <stdio.h>
#include "Article.hpp"
#include "Date.hpp"
#include "User.hpp"

class Transaction {
    private:
        Article *_article;
        User _user;
        Date _beginning, _finish;
        int _id = 0;
    public:
        Transaction(Article *article, User user, Date beginning, Date finish);
        virtual ~Transaction();

        void getCurrentTransactions();
        void getAllTransactions();
        void getTransactions(int day = 0, int month = 0, int year = 0);
        //Transaction getTransaction(int id);

        bool save();
        bool remove();

        friend std::ostream& operator<<(std::ostream& os, const Transaction& transaction);
        friend std::istream& operator>>(std::istream& is, Transaction& transaction);
};

#endif /* Transaction_hpp */

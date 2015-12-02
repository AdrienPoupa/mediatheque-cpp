//
//  Transaction.cpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//

#include "Transaction.hpp"

Transaction::Transaction(Article *article, User user, Date beginning, Date finish) :
    _article(article), _user(user), _beginning(beginning), _finish(finish)
{

}

Transaction::~Transaction()
{

}

void Transaction::getCurrentTransactions()
{

}

void Transaction::getAllTransactions()
{

}

void Transaction::getTransactions(int day, int month, int year)
{

}

/*
Transaction Transaction::getTransaction(int id)
{
    // TODO
}
*/

bool Transaction::save()
{
    // TODO
    return true;
}

bool Transaction::remove()
{
    // If the genre doesn't exist yet, we can't remove it
    if (_id == 0) {
        return false;
    }

    try
    {
        SQLite::Database    dbTransaction("example.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
         // Delete query
        SQLite::Statement   query(dbTransaction, "DELETE FROM transactions WHERE id=?");
        query.bind(1, (int) _id);
        query.exec();

        return true;
    }
    catch (std::exception& e)
    {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        return false;
    }

    return true;
}

std::ostream& operator<<(std::ostream& os, const Transaction& transaction)
{
    // TODO
    return os;
}

std::istream& operator>>(std::istream& is, Transaction& transaction)
{
    // TODO
    return is;
}

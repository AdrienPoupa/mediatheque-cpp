//
//  Transaction.cpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//

#include "Transaction.hpp"

Transaction::Transaction(Article article, User user, Date beginning, Date finish) :
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

}
*/

bool Transaction::updateTransation()
{
    return true;
}

bool Transaction::deleteTransaction()
{
    return true;
}

bool Transaction::insertTransaction()
{
    return true;
}

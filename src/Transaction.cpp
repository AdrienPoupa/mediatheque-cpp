#include "Transaction.hpp"

using namespace std;

string Transaction::_dbTable = "transactions";

/*
 # Database Model

 Table:

 Columns:
 - id: INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
 - article_id: INTEGER NOT NULL,
 - borrower_id: INTEGER REFERENCES users (id) NOT NULL,
 - type: INTEGER NOT NULL,
 - date_borrowed: DATE,
 - returned: BOOLEAN,
 - date_returned: DATE
 */

Transaction::Transaction(Article *article, string type, User user, Date beginning, Date finish) :
    _article(article), _type(type), _user(user), _beginning(beginning), _finish(finish)
{

}

/*Transaction::Transaction(unsigned int id)
{
    SQLite::Database    dbTransaction("mediatheque.db3");

    SQLite::Statement query(dbTransaction, "SELECT article_id, borrower, date, returned, date_returned FROM transactions WHERE id=?");
    query.bind(1, id);

    while (query.executeStep())
    {
        _id = id;
        _articleTmp = query.getColumn(0).getInt();
        Article newArticle(_articleTmp);
        _article = newArticle;
        _userTmp = query.getColumn(1).getInt();
        User borrower(_userTmp);
        _user = borrower;
        string dateTmp = query.getColumn(2).getText();
        Date newDate(dateTmp);
        _beginning = newDate;
        _returned = query.getColumn(3).getInt();
        string date2Tmp = query.getColumn(4).getText();
        Date newDate2(date2Tmp);
        _finish = newDate2;
    }
}*/

Transaction::~Transaction()
{

}

Date Transaction::getBeginDate() const
{
    return _beginning;
}

void Transaction::setBeginDate(const Date beginning)
{
    _beginning = beginning;
}

Date Transaction::getFinishDate() const
{
    return _finish;
}

void Transaction::setFinishDate(const Date finish)
{
    _finish = finish;
}

unsigned int Transaction::getId() const
{
    return _id;
}

void Transaction::setId(const unsigned int id)
{
    _id = id;
}

std::string Transaction::getType() const
{
    return _type;
}

void Transaction::setType(std::string const type)
{
    _type = type;
}

void Transaction::displayCurrentTransactions()
{
    SQLite::Database    dbTransaction("example.db3");

    SQLite::Statement query(dbTransaction, "SELECT id, article_id, type, borrower, date, returned, date_returned FROM transactions WHERE returned=0");

    while (query.executeStep())
    {
        int id = query.getColumn(0).getInt();
        int articleId = query.getColumn(1).getInt();

        string type = query.getColumn(2).getText();
        Article* article;
        if (type == "book")
        {
            article = new Book(articleId);
        }
        else if (type == "cd")
        {
            article = new Cd(articleId);
        }
        else
        {
            article = new Dvd(articleId);
        }

        int _userTmp = query.getColumn(3).getInt();
        User borrower(_userTmp);
        string dateTmp = query.getColumn(4).getText();
        Date newDate(dateTmp);
        //int returned = query.getColumn(5).getInt();
        string date2Tmp = query.getColumn(6).getText();
        Date newDate2(date2Tmp);
        cout << "Transaction #" << id << " : Article " << article << " emprunte par " << borrower << " le " << newDate << endl;
    }
}

void Transaction::displayAllTransactions()
{

}

void Transaction::displayTransactions(int day, int month, int year)
{

}

/*
Transaction Transaction::displayTransaction(int id)
{
    // TODO
}
*/

bool Transaction::save()
{
    int res = BaseModel::save("transactions", {
        {"id", {to_string(_id), "int"}},
        {"article_id", {to_string(_article->getId()), "int"}},
        {"borrower_id", {to_string(_user.getId()), "int"}},
        {"type", {_type, "string"}},
        {"date_borrowed", {_beginning.dateToDB(), "string"}},
        {"returned", {to_string(0), "int"}},
        {"date_returned", {_finish.dateToDB(), "string"}},
    });

    if(_id == 0){
        _id = res;
    }

    return (bool)res;
}

bool Transaction::remove()
{
    return BaseModel::remove(_dbTable, _id);
}

std::ostream& operator<<(std::ostream& os, const Transaction& transaction)
{
    os << "Transaction #" << transaction._id << " : Article  " << transaction._article << " emprunte par " << transaction._user << " le " << transaction._beginning << endl;
    return os;
}

std::istream& operator>>(std::istream& is, Transaction& transaction)
{
    cout << "Saisie d'une transaction" << endl;
    cout << "Utilisateur emprunteur:" << endl;
    is >> transaction._user; // TODO: sélection d'un utilisateur existant en DB
    return is;
}

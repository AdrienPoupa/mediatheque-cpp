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

Transaction::Transaction(const int articleId, const string type, const int userId){
    _articleId = articleId;
    _type = type;
    _userId = userId;
    _beginning = Date();
    _finish = Date(_beginning.getMonth()+1, _beginning.getDay(), _beginning.getYear()); // By default, allow a month
}

Transaction::Transaction(Article *article, const string type, const User user, const Date beginning, const Date finish) :
    _article(article), _type(type), _user(user), _beginning(beginning), _finish(finish)
{
    _articleId = article->getId();
    _userId = user.getId();
}

Transaction::Transaction(const int id, const int article_id, const string type, const int borrower_id,
                         const Date date_beginning, const Date date_returned, const bool returned)
{
    _id = id;
    _articleId = article_id;
    _type = type;
    _userId = borrower_id;
    _beginning = date_beginning;
    _finish = date_returned;
    _returned = returned;
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

string Transaction::getType() const
{
    return _type;
}

void Transaction::setType(string const type)
{
    _type = type;
}

// TODO: day/month/year
void Transaction::displayTransactions(const string current, const int day_borrowed, const int month_borrowed, const int year_borrowed,
                                      const int day_returned, const int month_returned, const int year_returned)
{
    string condition = (current == "current") ? "AND returned=0" : "";

    SQLite::Database dbTransaction("mediatheque.db3");

    SQLite::Statement query(dbTransaction, "SELECT id, article_id, type, borrower_id, date_borrowed, date_returned, returned FROM transactions WHERE id!=0 "+condition);

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
        Date beginning(dateTmp);
        string date2Tmp = query.getColumn(5).getText();
        Date finish(date2Tmp);
        int returned = query.getColumn(6).getInt();

        cout << "Transaction #" << id << " : Article  " << article->getTitle() << " emprunte par " << borrower << " le " << beginning << " a rendre le "  << finish << " ";
        (returned == 0) ? cout << "pas encore rendu" : cout << "rendu";
        cout << endl;
    }
}

list<Transaction> Transaction::byUser(const int userId, const bool active){

    string condition = active ? " AND returned is false" : "";
    SQLite::Database dbTransaction("mediatheque.db3");

    SQLite::Statement query(dbTransaction, "SELECT id, article_id, type, borrower_id, date_borrowed, date_returned, returned FROM transactions WHERE borrower_id =" + to_string(userId) + condition);

    list<Transaction> res;

    while (query.executeStep())
    {
        Transaction tmp(query.getColumn(0).getInt(), query.getColumn(1).getInt(), query.getColumn(2).getText(), query.getColumn(3).getInt(), Date(query.getColumn(4).getText()), Date(query.getColumn(5).getText()), (bool)query.getColumn(6).getInt());
        res.push_back(tmp);
    }

    return res;
}

/*
Transaction Transaction::displayTransaction(int id)
{
    // TODO
}
*/

bool Transaction::save()
{
    map<string, vector<string> > tmp = {
        {"id", {to_string(_id), "int"}},
        {"article_id", {to_string(_articleId), "int"}},
        {"borrower_id", {to_string(_userId), "int"}},
        {"type", {_type, "string"}},
        {"date_borrowed", {_beginning.dateToDB(), "string"}},
        {"returned", {to_string(_returned), "int"}},
    };

    if(_id != 0){
        tmp.insert({"date_returned", { _finish.dateToDB(), "string"}});
    }

    int res = BaseModel::save("transactions", tmp);

    if(_id == 0)
    {
        _id = res;
    }

    return (bool)res;
}

bool Transaction::remove()
{
    return BaseModel::remove(_dbTable, _id);
}

ostream& operator<<(ostream& os, const Transaction& transaction)
{
    os << "Transaction #" << transaction._id << " : Article  " << transaction._article->getTitle() << " emprunte par " << transaction._user << " le " << transaction._beginning << " a rendre le "  << transaction._finish << endl;
    return os;
}

istream& operator>>(istream& is, Transaction& transaction)
{
    cout << "Saisie d'une transaction" << endl;
    cout << "Utilisateur emprunteur:" << endl;
    //is >> transaction._user; // TODO: sélection d'un utilisateur existant en DB
    return is;
}

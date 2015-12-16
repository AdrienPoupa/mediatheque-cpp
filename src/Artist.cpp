#include <iostream>

#include "Artist.hpp"
#include "BaseModel.hpp"
#include "Position.hpp"

using namespace std;

/*
 # Database Model

 Table: artists

 Columns:
 - id: INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
 - name: TEXT,
 - surname: TEXT,
 - birthdate: DATE,
 - nationality: TEXT
 */

string Artist::_dbTable = "artists";

Artist::Artist(const std::string& firstName, const std::string& lastName, const std::string& nationality) :
    Person(firstName, lastName), _nationality(nationality)
{
    // empty
}

Artist::Artist(int id) // Get a person from an ID provided by DB
{
    map<string, string> data = BaseModel::getById(_dbTable, id);

    if(!data.empty())
    {
        _id = id;
        _firstName = data["name"];
        _lastName = data["surname"];
        _birthDate = Date(data["birthdate"]);
        _nationality = data["nationality"];
    }
    else
    {
        throw invalid_argument("Merci d'entrer un artiste valide");
    }
}

std::string Artist::getNationality() const
{
    return _nationality;
}

void Artist::setNationality(const std::string& nationality)
{
    _nationality = nationality;
}

std::set<Article*> Artist::getArticles() const
{
    return _articles;
}


void addArticles(const Article& article, const Position& position)
{
    // TODO?
}

void removeArticles(const Article& article)
{
    // TODO
}


std::ostream& operator<<(std::ostream& os, const Artist& me)
{
    os << me._firstName << " " << me._lastName <<" (" << me._nationality << "), ne(e) le " << me._birthDate << endl;
    return os;
}

std::istream& operator>>(std::istream& is, Artist& me)
{
    cout << "Saisie d'un artiste: " << endl;
    cout << "Saisie du prenom : " << endl;
    is.ignore(1, '\n');
    getline(is, me._firstName, '\n');
    cout << "Saisie du nom : ";
    getline(is, me._lastName, '\n');
    cout << "Saisie de la nationalite : ";
    getline(is, me._nationality, '\n');
    cout << "Saisie de la date de naissance : ";
    is >> me._birthDate;

    return is;
}

// DB method
bool Artist::save()
{
    int res = BaseModel::save(_dbTable, {

        {"id", {to_string(_id), "int"}},
        {"name", {_firstName, "string"}},
        {"surname", {_lastName, "string"}},
        {"birthdate", {_birthDate.dateToDB(), "string"}},
        {"nationality", {_nationality, "string"}}
    });

    if(_id == 0)
    {
        _id = res["id"];
    }

    return (bool)res;
}

bool Artist::remove()
{
    return BaseModel::remove(_dbTable, _id);
}

Artist::~Artist()
{

}



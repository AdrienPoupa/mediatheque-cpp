#include <iostream>

#include "Artist.hpp"

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

    if (!data.empty())
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

void Artist::deserialization(map<string, string> data)
{
    if (!data.empty())
    {
        _id = data.find("id")!= data.end() ? stoi(data["id"]): 0;
        _lastName = data["surname"];
        _firstName = data["name"];
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

void Artist::bibliography() const
{
    cout << "Bibliographie de " << getFirstName() << " " << getLastName() << endl;

    map<int, map<string, string>> bibliography = BaseModel::select("books", "id, title, author, release", "author=" + to_string(getId()));

    int totalCount = (int)bibliography.size();

    if (totalCount == 0)
    {
        cout << "Aucun livre dans la mediatheque" << endl;
        return;
    }

    for (int i = 1; i != totalCount + 1; i++)
    {
        Date release(bibliography[i]["release"]);
        cout << bibliography[i]["id"] << ". " << bibliography[i]["title"] << " (" << release << ")" << endl;
    }
}

void Artist::discography() const
{
    cout << "Discographie de " << getFirstName() << " " << getLastName() << endl;

    map<int, map<string, string>> cds = BaseModel::select("cds", "id, title, release", "artist=" + to_string(getId()));

    int totalCds = (int)cds.size();

    if (totalCds == 0)
    {
        cout << "Aucun cd dans la mediatheque" << endl;
        return;
    }

    for (int i = 1; i != totalCds + 1; i++)
    {
        Date release(cds[i]["release"]);
        cout << cds[i]["id"] << ". " << cds[i]["title"] << " (" << release << ")" << endl;
    }
}

void Artist::filmography() const
{
    cout << "Filmographie de " << getFirstName() << " " << getLastName() << endl;

    map<int, map<string, string>> dvds = BaseModel::select("dvds", "id, title, release", "director=" + to_string(getId()));

    int totalDvds = (int)dvds.size();

    if (totalDvds == 0)
    {
        cout << "Aucun dvd dans la mediatheque" << endl;
        return;
    }

    for (int i = 1; i != totalDvds + 1; i++)
    {
        Date release(dvds[i]["release"]);
        cout << dvds[i]["id"] << ". " << dvds[i]["title"] << " (" << release << ")" << endl;
    }
}

void Artist::edit()
{
    int choice;
    bool failInput = false;
    do
    {
        cout << "---------------------------------" << endl;
        cout << " -- Modification d'un artiste --" << endl;

        cout << "1. Modifier le prenom" << endl;
        cout << "2. Modifier le nom" << endl;
        cout << "3. Modifier la date de naissance" << endl;
        cout << "4. Modifier la nationalite" << endl;
        cout << "0. Annuler" << endl;
        cout << "Choix: " << endl;
        cin >> choice;
        if(cin.fail()){
            failInput = true;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while(failInput || choice < 0 || choice > 4);

    switch (choice)
    {
        case 1:
        {
            editFirstname();
            break;
        }
        case 2:
        {
            editLastname();
            break;
        }
        case 3:
        {
            editBirthdate();
            break;
        }
        case 4:
        {
            string newNationality;
            cin.ignore(1, '\n');
            getline(cin, newNationality, '\n');
            setNationality(newNationality);
            break;
        }
        default:
            return;
            break;
    }

    if (choice != 0)
    {
        cout << "Sauvegarde..." << endl;
        save();
    }

    return;
}


std::ostream& operator<<(std::ostream& os, const Artist& me)
{
    os << me._firstName << " " << me._lastName <<" (" << me._nationality << "), ne(e) le " << me._birthDate << endl;
    me.discography();
    me.filmography();
    me.bibliography();
    return os;
}

std::istream& operator>>(std::istream& is, Artist& me)
{
    cout << "Saisie d'un artiste: " << endl;

    cout << "Saisie du prenom : " << endl;
    is.ignore(1, '\n');
    getline(is, me._firstName, '\n');

    cout << "Saisie du nom : " << endl;
    getline(is, me._lastName, '\n');

    cout << "Saisie de la nationalite : " << endl;
    getline(is, me._nationality, '\n');

    cout << "Saisie de la date de naissance : " << endl;
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

    if (_id == 0)
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



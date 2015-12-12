#include "User.hpp"
#include "Address.hpp"
#include "BaseModel.hpp"
#include "sha256.h"

using namespace std;

/* Database Model
 Table: users

 Columns:
 - id: INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
 - name: TEXT NOT NULL,
 - surname: TEXT NOT NULL,
 - phone: TEXT,
 - birthdate: DATE,
 - country: TEXT,
 - house_number: INTEGER,
 - postal_code: TEXT,
 - town: TEXT,
 - street: TEXT

 */

string User::_dbTable = "users";

User::User(std::string firstName, std::string lastName, Date birthDate, string phone, int isAdmin, int quota, string password):
    Person(firstName, lastName, birthDate), _phone(phone), _isAdmin(isAdmin), _quota(quota), _password(password)
{

}

User::User()
{
    _firstName = "John";
    _lastName = "Doe";

    Date mock(1, 1, 1);
    _birthDate = mock;

    _phone = "Inconnu";
}

User::User(int id) // Get a person from an ID provided by DB
{
    map<string, string> data = BaseModel::getById(_dbTable, id);

    if(!data.empty())
    {
        _id = id;
        _firstName = data["name"];
        _lastName = data["surname"];
        _birthDate = data["birthdate"];
        _phone = data["phone"];
        _address = Address(stoi(data["house_number"]), data["street"], data["postal_code"], data["town"], data["country"]);
        _isAdmin = stoi(data["isadmin"]);
        _quota = stoi(data["quota"]);
        _password = data["password"];
    }
}

User::~User()
{

}

string User::getPhone()
{
    return _phone;
}

void User::setPhone(string phone)
{
    _phone = phone;
}

void User::setPassword(string password)
{
    _password = sha256(password);
}

bool User::checkPassword(string password)
{
    if (sha256(password) == _password)
    {
        return true;
    }

    return false;
}

Address User::getAddress()
{
    return _address;
}

void User::setAddress(Address address)
{
    _address = address;
}

bool User::isAdmin()
{
    return (bool) _isAdmin;
}

void User::setAdmin(int isAdmin)
{
    if (isAdmin == 0 || isAdmin == 1)
    {
        _isAdmin = isAdmin;
    }
}

int User::getQuota()
{
    return _quota;
}

void User::setQuota(int quota)
{
    _quota = quota;
}

bool User::save()
{
    int res = BaseModel::save(_dbTable, {
        {"id", {to_string(_id), "int"}},
        {"name", {_firstName, "string"}},
        {"surname", {_lastName, "string"}},
        {"phone", {_phone, "string"}},
        {"birthdate", {_birthDate.dateToDB(), "string"}},
        {"country", {_address.getCountry(), "string"}},
        {"house_number", {to_string(_address.getHouseNumber()), "int"}},
        {"postal_code", {_address.getPostalCode(), "string"}},
        {"town", {_address.getTown(), "string"}},
        {"street", {_address.getStreetName(), "string"}},
        {"isadmin", {to_string(_isAdmin), "int"}},
        {"quota", {to_string(_quota), "int"}},
        {"password", {_password, "string"}}
    });

    if(_id == 0)
    {
        _id = res["id"];
    }

    return (bool) res;
}

bool User::remove()
{
    return BaseModel::remove(_dbTable, _id);
}

ostream& operator<< (ostream& stream, const User& user)
{
    stream << "ID #" << user._id << " " << user._firstName << " " << user._lastName << endl;
    stream << "Anniversaire: " << user._birthDate << endl;
    stream << "Telephone: " << user._phone << endl;
    stream << "Adresse: " << user._address << endl;
    stream << "Est admin: " << user._isAdmin << endl;
    stream << "Nombre d'emprunts simultanes: " << user._quota << endl;

    return stream;
}

istream& operator>> (istream& stream, User& user)
{
    string passwordTmp;

    cout << "Saisie d'un user" << endl;
    cout << "Saisie du prenom" << endl;
    stream.ignore(1, '\n');
    getline(stream, user._firstName, '\n');
    cout << "Saisie du nom" << endl;
    getline(stream, user._lastName, '\n');
    cout << "Saisie de l'anniversaire" << endl;
    stream >> user._birthDate;
    cout << "Saisie du telephone" << endl;
    stream.ignore(1, '\n');
    getline(stream, user._phone, '\n');
    cout << "Saisie de l'adresse" << endl;
    stream >> user._address;
    cout << "Saisie du mot de passe" << endl;
    stream.ignore(1, '\n');
    getline(stream, passwordTmp, '\n');
    cout << "Tapez 1 si l'utilisateur est administrateur, 0 sinon" << endl;
    stream >> user._isAdmin;
    cout << "Saisie du nombre d'emprunts simultanes" << endl;
    stream >> user._quota;

    // Insert the hashed password
    user._password = sha256(passwordTmp);

    return stream;
}

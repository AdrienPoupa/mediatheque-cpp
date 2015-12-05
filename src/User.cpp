#include "User.hpp"
#include "Address.hpp"
#include "BaseModel.hpp"

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

User::User(std::string firstName, std::string lastName, Date birthDate, string phone):
    Person(firstName, lastName, birthDate), _phone(phone)
{

}

User::User(int id) // Get a person from an ID provided by DB
{
    map<string, string> data = BaseModel::getById(_dbTable, id);

    if(!data.empty()){
        _id = id;
        _firstName = data["name"];
        _lastName = data["surname"];
        _birthDate = data["birthdate"];
        _phone = data["phone"];
        _address = Address(stoi(data["house_number"]), data["street"], data["postal_code"], data["town"], data["country"]);
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

Address User::getAddress()
{
    return _address;
}

void User::setAddress(Address address)
{
    _address = address;
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
        {"street", {_address.getStreetName(), "string"}}
    });

    if(_id == 0){
        _id = res["id"];
    }

    return (bool) res;
}

bool User::remove()
{
    return BaseModel::remove(_dbTable, _id);
}

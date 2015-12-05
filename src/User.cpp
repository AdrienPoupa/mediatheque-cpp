#include "User.hpp"
#include "Address.hpp"
#include "BaseModel.hpp"

using namespace std;

User::User(std::string firstName, std::string lastName, Date birthDate, string phone):
    Person(firstName, lastName, birthDate), _phone(phone)
{

}

User::User(int id) // Get a person from an ID provided by DB
{
    map<string, string> data = BaseModel::getById("users", id);
    
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
    /*
     id: Integer
     name: Text
     surname: Text
     phone: Text
     birthdate: Date
     country: Text
     house_number: Integer
     postal_code: Text
     town: Text
     street: Text
     */
    
    int res = BaseModel::save("users", {
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
        _id = res;
    }
    
    return (bool)res;
}

bool User::remove()
{
    return BaseModel::remove("users", _id);
    
}

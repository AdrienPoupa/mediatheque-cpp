#include "Address.hpp"
#include <iostream>

using namespace std;

Address::Address(const int& houseNumber, const std::string& streetName, const std::string& postalCode, const std::string& town, const std::string& country):
    _houseNumber(houseNumber), _streetName(streetName), _postalCode(postalCode), _town(town), _country(country)
{
    // empty
}

string Address::getCountry() const
{
    return _country;
}

void Address::setCountry(const string& pays)
{
    _country = pays;
}

int Address::getHouseNumber() const
{
    return _houseNumber;
}

void Address::setHouseNumber(const int &numero)
{
    _houseNumber = numero;
}

string Address::getPostalCode() const
{
    return _postalCode;
}

void Address::setPostalCode(const string &postalCode)
{
    _postalCode = postalCode;
}

string Address::getTown() const
{
    return _town ;
}

void Address::setTown(const string& ville)
{
    _town = ville ;
}

string Address::getStreetName() const
{
    return _streetName;
}

void Address::setStreetName(const string& streetName)
{
    _streetName = streetName;
}

ostream& operator<< (ostream& stream, const Address& adresse)
{
    stream << adresse._houseNumber << endl << adresse._streetName << endl << adresse._postalCode << endl << adresse._town << endl << adresse._country;
    return stream;
}

istream& operator>> (std::istream& stream, Address& adresse)
{
    cout << "Numero de rue : " << endl;
    stream >> adresse._houseNumber;
    cout << "Rue : " << endl;
    stream.ignore(1, '\n');
    getline(stream, adresse._streetName, '\n');
    cout << "Code postal : " << endl;
    getline(stream, adresse._postalCode, '\n');
    cout <<"Ville : " << endl;
    getline(stream, adresse._town, '\n');
    cout << "Pays : " << endl;
    getline(stream, adresse._country, '\n');

    return stream;

}

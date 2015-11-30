//
//  Address.cpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//

#include "Address.hpp"
#include <iostream>

using namespace std;

Address::Address()
{

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

void Address::setPostalCode(const string &codePostal)
{
    _postalCode = codePostal;
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

void Address::setStreetName(const string& rue)
{
    _streetName = rue;
}

ostream& operator<< (ostream& stream, const Address& adresse)
{
    stream << adresse._houseNumber << endl << adresse._streetName << endl << adresse._postalCode << endl << adresse._town << endl << adresse._country << endl ;
    return stream;
}

string Address::addressDB()
{
    return _houseNumber + ", " + _streetName + ", " + _postalCode + ",  " + _town + ", " + _country;
}

istream& operator>> (std::istream& stream, Address& adresse)
{

    cout << "Saisie de l'adresse " << endl;;

    cout << "Numero de rue : ";
    stream >> adresse._houseNumber;
    cout << "Rue : ";
    stream >> adresse._streetName;
    cout << "Code postal : ";
    stream>> adresse._postalCode ;
    cout <<"Ville : ";
    stream>> adresse._town ;
    cout << "Pays : ";
    stream >> adresse._country ;

    return stream;

}










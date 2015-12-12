#ifndef Address_hpp
#define Address_hpp

#include <stdio.h>
#include <iostream>
#include <string>

class Address {
    unsigned int _houseNumber;
    std::string _streetName, _postalCode, _town, _country;

public:
    Address(const int& houseNumber = 30, const std::string& streetName = "Avenue de la Republique", const std::string& postalCode = "94800", const std::string& town = "Villejuif", const std::string& country = "France");

    std::string getCountry() const;
    void setCountry(const std::string& pays);

    int getHouseNumber() const;
    void setHouseNumber(const int& numero);

    std::string getPostalCode() const;
    void setPostalCode(const std::string& postalCode);

    std::string getTown() const;
    void setTown(const std::string& ville);

    std::string getStreetName() const;
    void setStreetName(const std::string& streetName);

    friend std::ostream& operator<< (std::ostream& stream, const Address& adresse);
    friend std::istream& operator>> (std::istream& stream, Address& addresse);
};

#endif /* Address_hpp */

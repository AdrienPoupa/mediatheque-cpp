#ifndef Address_hpp
#define Address_hpp

#include <stdio.h>
#include <iostream>
#include <string>

class Address {
    std::string _country;
    unsigned int _houseNumber = 30;
    std::string _postalCode ;// à cause de la corse et des départements commencant par 0
    std::string _streetName;
    std::string _town;

public:
    Address(const int& houseNumber = 30, const std::string& streetName = "Avenue de la Republique", const std::string& postalCode = "94800", const std::string& town = "Villejuif", const std::string& country = "France");

    std::string getCountry() const;
    void setCountry(const std::string& pays );

    int getHouseNumber() const;
    void setHouseNumber(const int& numero);

    std::string getPostalCode() const;
    void setPostalCode(const std::string& codePostal);

    std::string getTown() const;
    void setTown(const std::string& ville);

    std::string getStreetName() const;
    void setStreetName(const std::string& rue );

    friend std::ostream& operator<< (std::ostream& stream, const Address& adresse);
    friend std::istream& operator>> (std::istream& stream, Address& addresse);
};

#endif /* Address_hpp */

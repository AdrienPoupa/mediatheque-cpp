//
//  Address.hpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//

#ifndef Address_hpp
#define Address_hpp

#include <stdio.h>
#include <iostream>
#include <string>

class Address {
    std::string _country;
    unsigned int _houseNumber;
    std::string _postalCode;// à cause de la corse et des départements commencant par 0
    std::string _streetName;
    std::string _town;
    
public:
    Address();
    
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

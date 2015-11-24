//
//  Person.hpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//

#ifndef Person_hpp
#define Person_hpp

#include <stdio.h>
#include <iostream>

#include "Date.hpp"

class Person {
private:
    unsigned int _id;
    std::string _lastName;
    std::string _firstName;
    Date _birthDate;
public:
    Person(std::string lastName = "John", std::string firstName = "Doe");
    Person(std::string lastName, std::string firstName, Date birthDate);
    Person(int id); // Get a person from an ID provided by DB
    virtual ~Person();
    virtual unsigned int getId();
    virtual std::string getLastName();
    virtual void setLastName(std::string lastName);
    virtual std::string getFirstName();
    virtual void setFirstName(std::string firstName);
    virtual Date getBirthDate();
    virtual void setBirthDate(Date birthDate);
    virtual bool addToDB() = 0;
    virtual bool updateDB() = 0;
    virtual bool deleteDB() = 0;
    friend std::ostream& operator<< (std::ostream& stream, const Person& person);
    friend std::istream& operator>> (std::istream& stream, Person& person);
};

#endif /* Person_hpp */

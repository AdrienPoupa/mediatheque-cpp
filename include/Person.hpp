#ifndef Person_hpp
#define Person_hpp

#include <stdio.h>
#include <iostream>

#include "../sqlite/SQLiteCpp.h"
#include "Date.hpp"

class Person {
protected:
    unsigned int _id;
    std::string _lastName;
    std::string _firstName;
    Date _birthDate;

public:
    Person(const std::string lastName = "John", const std::string firstName = "Doe");
    Person(const std::string lastName, const std::string firstName, const Date birthDate);

    virtual void init(std::map<std::string, std::string> data);

    unsigned int getId() const;

    virtual void deserialization(std::map<std::string, std::string> data);

    std::string getLastName() const;
    void setLastName(const std::string lastName);

    std::string getFirstName() const;
    void setFirstName(const std::string firstName);

    Date getBirthDate() const;
    void setBirthDate(const Date birthDate);

    virtual void edit() = 0;

    // DB
    virtual bool save() = 0;
    virtual bool remove() = 0;

    void shortDisplay() const;

    friend std::ostream& operator<< (std::ostream& stream, const Person& person);
    friend std::istream& operator>> (std::istream& stream, Person& person);

    virtual ~Person();
};

#endif /* Person_hpp */

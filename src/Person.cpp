#include "Person.hpp"

using namespace std;

Person::Person(std::string lastName, std::string firstName) :
    _lastName(lastName), _firstName(firstName)
{
    Date(1, 1, 1900);
    _id = 0; // No ID for now
}

Person::Person(std::string lastName, std::string firstName, Date birthDate) :
    _lastName(lastName), _firstName(firstName), _birthDate(birthDate)
{
    _id = 0; // No ID for now
}

Person::~Person()
{
    // Nothing for now
}

unsigned int Person::getId() const
{
    return _id;
}

std::string Person::getLastName() const
{
    return _lastName;
}

void Person::setLastName(std::string lastName)
{
    _lastName = lastName;
}

void Person::setFirstName(std::string firstName)
{
    _firstName = firstName;
}

std::string Person::getFirstName() const
{
    return _firstName;
}

Date Person::getBirthDate() const
{
    return _birthDate;
}

void Person::setBirthDate(Date birthDate)
{
    _birthDate = birthDate;
}

ostream& operator<< (ostream& stream, const Person& person)
{
    stream << person._id << ' ' << person._firstName << ' ' << person._lastName;

    return stream;
}

istream& operator>> (istream& stream, Person& person)
{
    cout << "Saisie d'une personne" << endl;
    cout << "Saisie du prenom" << endl;
    stream.ignore(1, '\n');
    getline(stream, person._firstName, '\n');
    cout << "Saisie du nom" << endl;
    getline(stream, person._lastName, '\n');
    cout << "Saisie de l'anniversaire" << endl;
    stream >> person._birthDate;

    return stream;
}

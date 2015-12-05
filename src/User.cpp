#include "User.hpp"
#include "BaseModel.hpp"

using namespace std;

User::User(std::string firstName, std::string lastName, Date birthDate, string phone) :
    Person(firstName, lastName, birthDate), _phone(phone)
{

}

User::User(int id) // Get a person from an ID provided by DB
{
    SQLite::Database    dbUser("example.db3");

    SQLite::Statement query(dbUser, "SELECT name, surname, phone, birthdate, country, house_number, postal_code, town, street FROM users WHERE id=?");
    query.bind(1, id);

    while (query.executeStep())
    {
        _id = id;
        _firstName = query.getColumn(0).getText();
        _lastName = query.getColumn(1).getText();
        _phone = query.getColumn(2).getText();
        string birthDateTmp = query.getColumn(3).getText();
        Date newDate(birthDateTmp);
        _birthDate = newDate;
        _address.setCountry(query.getColumn(4).getText());
        _address.setHouseNumber(query.getColumn(5).getInt());
        _address.setPostalCode(query.getColumn(6).getText());
        _address.setTown(query.getColumn(7).getText());
        _address.setStreetName(query.getColumn(8).getText());
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
    /*// Update
    if (_id != 0) {
        try
        {
            SQLite::Database    dbUser("example.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
             // Insert query
            SQLite::Statement   query(dbUser, "UPDATE users SET name=?, surname=?, phone=?, birthdate=?, country=?, house_number=?, postal_code=?, town=?, street=? WHERE id=?");
            query.bind(1, _firstName);
            query.bind(2, _lastName);
            query.bind(3, _phone);
            query.bind(4, _birthDate.dateToDB());
            query.bind(5, _address.getCountry());
            query.bind(6, _address.getHouseNumber());
            query.bind(7, _address.getPostalCode());
            query.bind(8, _address.getTown());
            query.bind(9, _address.getStreetName());
            query.bind(10, (int) _id);
            query.exec();

            return true;
        }
        catch (std::exception& e)
        {
            std::cout << "SQLite exception: " << e.what() << std::endl;
            return false;
        }
    }
    // Insert
    else
    {
        try
        {
            SQLite::Database    dbUser("example.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
             // Insert query
            SQLite::Statement   query(dbUser, "INSERT INTO users VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
            query.bind(2, _firstName);
            query.bind(3, _lastName);
            query.bind(4, _phone);
            query.bind(6, _birthDate.dateToDB());
            query.bind(7, _address.getCountry());
            query.bind(8, _address.getHouseNumber());
            query.bind(9, _address.getPostalCode());
            query.bind(10, _address.getTown());
            query.bind(11, _address.getStreetName());
            query.exec();

            // Update current ID
            int tmp = dbUser.execAndGet("SELECT last_insert_rowid();");
            _id = tmp;

            return true;
        }
        catch (std::exception& e)
        {
            std::cout << "SQLite exception: " << e.what() << std::endl;
            return false;
        }
    }

    return true;
     */
    /*
     User:
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
    // If the user doesn't exist yet, we can't remove it
    if (_id == 0) {
        return false;
    }

    try
    {
        SQLite::Database    dbUser("example.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
         // Delete query
        SQLite::Statement   query(dbUser, "DELETE FROM users WHERE id=?");
        query.bind(1, (int) _id);
        query.exec();

        return true;
    }
    catch (std::exception& e)
    {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        return false;
    }

    return true;
}

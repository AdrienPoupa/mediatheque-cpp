#include "Genre.hpp"
#include "BaseModel.hpp"

using namespace std;

/*
 # Database Model

 Table: genres

 Columns:
 - id: INTEGER,
 - genre: TEXT
 */

Genre::Genre(const std::string name) : _name(name)
{

}

Genre::~Genre()
{

}

Genre::Genre(const int id)
{
    map<string, string> data = BaseModel::getById("genres", id);

    if(!data.empty())
    {
        _id = id;
        _name = data["genre"];
    }
    else
    {
        throw invalid_argument("Merci d'entrer un genre valide");
    }
}

int Genre::getId() const
{
    return _id;
}

void Genre::setName(const std::string name)
{
    _name = name;
}

std::string Genre::getName() const
{
    return _name;
}

bool Genre::save()
{
    int res = BaseModel::save("genres", {
        {"id", {to_string(_id), "int"}},
        {"genre", {_name, "string"}},
    });

    if(_id == 0)
    {
        _id = res["id"];
    }

    return (bool) res;
}

bool Genre::remove()
{
    return BaseModel::remove("genres", _id);
}

ostream& operator<< (ostream& stream, const Genre& genre)
{
    stream << genre._name;

    return stream;
}

istream& operator>> (istream& stream, Genre& genre)
{
    stream.ignore(1, '\n');
    getline(stream, genre._name, '\n');

    return stream;
}


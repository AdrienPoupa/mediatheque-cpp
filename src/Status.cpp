#include "Status.h"

using namespace std;

/*
 # Database Model

 Table: status

 Columns:
 - id: INTEGER,
 - status: TEXT
 */

Status::Status(const std::string name) : Genre(name)
{

}

Status::~Status()
{

}

Status::Status(int id)
{
    map<string, string> data = BaseModel::getById("status", id);

    if (!data.empty())
    {
        _id = id;
        _name = data["status"];
    }
    else
    {
        throw invalid_argument("Merci d'entrer un statuts valide");
    }
}

void Status::deserialization(map<string, string> data)
{
    if (!data.empty())
    {
        _id = data.find("id")!= data.end() ? stoi(data["id"]): 0;
        _name = data["status"];
    }
}

bool Status::save()
{
    int res = BaseModel::save("status", {
        {"id", {to_string(_id), "int"}},
        {"status", {_name, "string"}},
    });

    if (_id == 0)
    {
        _id = res["id"];
    }

    return (bool) res;
}

bool Status::remove()
{
    return BaseModel::remove("status", _id);
}

ostream& operator<< (ostream& stream, const Status& status)
{
    stream << status._name;

    return stream;
}

istream& operator>> (istream& stream, Status& status)
{
    stream.ignore(1, '\n');
    getline(stream, status._name, '\n');

    return stream;
}


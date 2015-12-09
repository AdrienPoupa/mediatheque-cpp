/*
 # Database Model

 Table: cds

 Columns:
 - id: INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL,
 - artist: INTEGER REFERENCES artists (id),
 - title: TEXT,
 - borrowable: BOOLEAN,
 - release: DATE,
 - length: INTEGER (10),
 - studio: TEXT,
 - genre1: INTEGER REFERENCES genres (id),
 - genre2: INTEGER REFERENCES genres (id)
 */

#include "Cd.hpp"
#include "BaseModel.hpp"

using namespace std;

string Cd::_dbTable = "cds";

Cd::Cd()
{
    //ctor
}

Cd::Cd(int id)
{
    map<string, string> data = BaseModel::getById(_dbTable, id);

    if(!data.empty()){
        _id = id;
        _authorId = stoi(data["author"]);
        _title = data["title"];
        _borrowable = data["borrowable"] != "0";
        _release = Date(data["release"]);
        _length = stoi(data["length"]);
        _studio = data["studio"];
    }
}

Cd::~Cd()
{
    //dtor
}

bool Cd::save()
{
    int res = BaseModel::save(_dbTable, {
        {"id", {to_string(_id), "int"}},
        {"artist", {to_string(_authorId), "int"}},
        {"title", {_title, "string"}},
        {"borrowable", {to_string(_borrowable), "boolean"}},
        {"release", {_release.dateToDB(), "string"}},
        {"length", {to_string(_length), "int"}},
        {"studio", {_studio, "string"}}
        // TODO: genres
    });

    if(_id == 0){
        _id = res["id"];
    }

    return (bool) res;
}

bool Cd::remove()
{
    return BaseModel::remove(_dbTable, _id);
}

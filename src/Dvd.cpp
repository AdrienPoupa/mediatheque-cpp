/*
 # Database Model

 Table: dvds

 Columns:
 - id: INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE,
 - borrowable: BOOLEAN,
 - title: TEXT NOT NULL,
 - director: INTEGER REFERENCES artists (id),
 - release: DATE,
 - length: INTEGER (10),
 - studio: TEXT,
 - genre1: INTEGER REFERENCES genres (id),
 - genre2: INTEGER REFERENCES genres (id)
 */

#include "Dvd.hpp"
#include "BaseModel.hpp"

using namespace std;

string Dvd::_dbTable = "dvds";

Dvd::Dvd()
{
    //ctor
}

Dvd::~Dvd()
{
    //dtor
}

Dvd::Dvd(int id)
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

void Dvd::addCasting(Artist* artist)
{
    _casting.insert(artist);
    save();
}

bool Dvd::save()
{
    int res = BaseModel::save(_dbTable, {
        {"id", {to_string(_id), "int"}},
        {"artist", {to_string(_authorId), "int"}},
        {"title", {_title, "string"}},
        {"borrowable", {to_string(_borrowable), "boolean"}},
        {"release", {_release.dateToDB(), "string"}},
        {"length", {to_string(_length), "int"}},
        {"studio", {_studio, "string"}}
        // genres
    });

    // TODO: save castings ...

    if(_id == 0){
        _id = res["id"];
    }

    return (bool) res;
}

bool Dvd::remove()
{
    return BaseModel::remove(_dbTable, _id);
}

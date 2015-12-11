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
        _authorId = stoi(data["director"]);
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
        {"director", {to_string(_authorId), "int"}},
        {"title", {_title, "string"}},
        {"borrowable", {to_string(_borrowable), "boolean"}},
        {"release", {_release.dateToDB(), "string"}},
        {"length", {to_string(_length), "int"}},
        {"studio", {_studio, "string"}}
        // TODO: genres
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

ostream& operator<< (ostream& stream, const Dvd& dvd)
{
    Artist director(dvd._authorId);

    stream << "ID #" << dvd._id << " : " << dvd._title << endl;
    stream << "Metteur en scene : " << director.getFirstName() << " "  << director.getLastName() << endl;
    stream << "Studio : " << dvd._studio << endl;
    stream << "Date de sortie : " << dvd._release << endl;
    stream << "Duree : " << dvd._length << endl;
    //TODO stream << "Genre : " << dvd._genre << endl;

    return stream;
}

istream& operator>> (istream& stream, Dvd& dvd)
{
    cout << "Saisie d'un dvd" << endl;
    cout << "Saisie du titre" << endl;
    stream >> dvd._title;
    cout << "ID du realisateur" << endl;
    stream >> dvd._authorId;
    cout << "Studio" << endl;
    stream >> dvd._studio;
    cout << "Date de sortie" << endl;
    stream >> dvd._release;
    cout << "Duree" << endl;
    stream >> dvd._length;
    /*cout << "Genres" << endl;
    stream >> dvd._genres;*/

    dvd._author = new Artist(dvd._authorId);

    return stream;
}

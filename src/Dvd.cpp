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

    if(!data.empty())
    {
        _id = id;
        _authorId = stoi(data["director"]);
        _title = data["title"];
        _borrowable = data["borrowable"] != "0";
        _release = Date(data["release"]);
        _length = stoi(data["length"]);
        _studio = data["studio"];
    }

    retrieveGenreFromDB(data);
}

void Dvd::addCasting(Artist* artist)
{
    // TODO
    _casting.insert(artist);
    save();
}

bool Dvd::save()
{
    map<string, vector<string>> data = {
        {"id", {to_string(_id), "int"}},
        {"director", {to_string(_authorId), "int"}},
        {"title", {_title, "string"}},
        {"borrowable", {to_string(_borrowable), "boolean"}},
        {"release", {_release.dateToDB(), "string"}},
        {"length", {to_string(_length), "int"}},
        {"studio", {_studio, "string"}}
    };

    addGenreToDB(data);

    int res = BaseModel::save(_dbTable, data);

    // TODO: save castings ...

    if(_id == 0)
    {
        _id = res["id"];
    }

    return (bool) res;
}

bool Dvd::remove()
{
    return BaseModel::remove(_dbTable, _id);
}

ostream& operator<< (ostream& stream, Dvd& dvd)
{
    Artist director(dvd._authorId);

    stream << "ID #" << dvd._id << " : " << dvd._title << endl;
    stream << "Metteur en scene : " << director.getFirstName() << " "  << director.getLastName() << endl;
    stream << "Studio : " << dvd._studio << endl;
    stream << "Date de sortie : " << dvd._release << endl;
    stream << "Duree : " << dvd._length << endl;
    dvd.displayGenres(stream);

    return stream;
}

istream& operator>> (istream& stream, Dvd& dvd)
{
    cout << "Saisie d'un dvd" << endl;
    cout << "Saisie du titre" << endl;
    stream.ignore(1, '\n');
    getline(stream, dvd._title, '\n');
    cout << "ID du realisateur" << endl;
    stream >> dvd._authorId;
    cout << "Studio" << endl;
    stream.ignore(1, '\n');
    getline(stream, dvd._studio, '\n');
    cout << "Date de sortie" << endl;
    stream >> dvd._release;
    cout << "Duree" << endl;
    stream >> dvd._length;
    dvd.displayGenreFromCli(stream);

    dvd._author = new Artist(dvd._authorId);

    return stream;
}

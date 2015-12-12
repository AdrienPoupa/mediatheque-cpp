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
        _authorId = stoi(data["artist"]);
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

ostream& operator<< (ostream& stream, const Cd& cd)
{
    Artist singer(cd._authorId);

    stream << "ID #" << cd._id << " : " << cd._title << endl;
    stream << "Artiste principal : " << singer.getFirstName() << " "  << singer.getLastName() << endl;
    stream << "Studio : " << cd._studio << endl;
    stream << "Date de sortie : " << cd._release << endl;
    stream << "Duree : " << cd._length << endl;
    //TODO stream << "Genre : " << cd._genre << endl;

    return stream;
}

istream& operator>> (istream& stream, Cd& cd)
{
    cout << "Saisie d'un CD" << endl;
    cout << "Saisie du titre" << endl;
    stream.ignore(1, '\n');
    getline(stream, cd._title, '\n');
    cout << "ID de l'artiste principal" << endl;
    stream >> cd._authorId;
    cout << "Studio" << endl;
    stream.ignore(1, '\n');
    getline(stream, cd._studio, '\n');
    cout << "Date de sortie" << endl;
    stream >> cd._release;
    cout << "Duree" << endl;
    stream >> cd._length;
    /*cout << "Genres" << endl;
    stream >> cd._genres;*/

    cd._author = new Artist(cd._authorId);

    return stream;
}


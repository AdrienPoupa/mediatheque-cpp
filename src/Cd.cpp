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

    if(!data.empty())
    {
        _id = id;
        _authorId = stoi(data["artist"]);
        _title = data["title"];
        _borrowable = data["borrowable"] != "0";
        _release = Date(data["release"]);
        _length = stoi(data["length"]);
        _studio = data["studio"];
        retrieveGenreFromDB(data);
    }
    else
    {
        throw invalid_argument("Merci d'entrer un cd valide");
    }
}

Cd::~Cd()
{
    //dtor
}

void Cd::deserialization(map<string, string> data){
    if(!data.empty())
    {
        _id = data.find("id")!= data.end() ? stoi(data["id"]): 0;
        _borrowable = data.find("borrowable")!= data.end() ? data["borrowable"] != "0" : true;
        _title = data["title"];
        _release = Date(data["release"]);
        if(data.find("artist")!= data.end()){
            _authorId = stoi(data["artist"]);
            _author = new Artist(stoi(data["artist"]));
        }
        else{
            _authorId = 0;
        }
        _studio = data["studio"];
        _length = data.find("length")!= data.end() ? stoi(data["length"]) : 0;
        retrieveGenreFromDB(data);
    }
}

string Cd::getStudio() const
{
    return _studio;
}

void Cd::setStudio(const std::string& studio)
{
    _studio = studio;
}

unsigned int Cd::getLength() const
{
    return _length;
}

void Cd::setLength(const unsigned int& length)
{
    _length = length;
}

bool Cd::save()
{
    map<string, vector<string>> data = {
        {"id", {to_string(_id), "int"}},
        {"artist", {to_string(_authorId), "int"}},
        {"title", {_title, "string"}},
        {"borrowable", {_borrowable ? "1" : "0", "int"}},
        {"release", {_release.dateToDB(), "string"}},
        {"length", {to_string(_length), "int"}},
        {"studio", {_studio, "string"}}
    };

    addGenreToDB(data);

    int res = BaseModel::save(_dbTable, data);

    if(_id == 0)
    {
        _id = res;
    }

    return (bool) res;
}

bool Cd::remove()
{
    return BaseModel::remove(_dbTable, _id);
}

ostream& operator<< (ostream& stream, Cd& cd)
{
    Artist singer(cd._authorId);

    stream << "ID #" << cd._id << " : " << cd._title << endl;
    stream << "Artiste principal : " << singer.getFirstName() << " "  << singer.getLastName() << endl;
    stream << "Studio : " << cd._studio << endl;
    stream << "Date de sortie : " << cd._release << endl;
    stream << "Duree : " << cd._length << endl;
    cd.displayGenres(stream);

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

    cd.displayGenreFromCli(stream);

    cd._author = new Artist(cd._authorId);

    return stream;
}


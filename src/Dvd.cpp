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
        _release = data["release"];
        _length = stoi(data["length"]);
        _studio = data["studio"];
        retrieveGenreFromDB(data);
    }
    else
    {
        throw invalid_argument("Merci d'entrer un dvd valide");
    }
}

void Dvd::deserialization(map<string, string> data){
    if(!data.empty())
    {
        _id = data.find("id")!= data.end() ? stoi(data["id"]): 0;
        _borrowable = data.find("borrowable")!= data.end() ? data["borrowable"] != "0" : true;
        _title = data["title"];
        _release = data["release"];
        if(data.find("director")!= data.end()){
            _authorId = stoi(data["director"]);
            _author = new Artist(stoi(data["director"]));
        }
        else{
            _authorId = 0;
        }
        _studio = data["studio"];
        _length = data.find("length")!= data.end() ? stoi(data["length"]) : 0;
        retrieveGenreFromDB(data);
    }
}

void Dvd::addCasting(const int artistId)
{
    _casting.push_back(artistId);
}

vector<int> Dvd::getCasting() const
{
    return _casting;
}

bool Dvd::save()
{
    map<string, vector<string>> data = {
        {"id", {to_string(_id), "int"}},
        {"director", {to_string(_authorId), "int"}},
        {"title", {_title, "string"}},
        {"borrowable", {_borrowable ? "1": "0", "int"}},
        {"release", {_release, "string"}},
        {"length", {to_string(_length), "int"}},
        {"studio", {_studio, "string"}}
    };

    addGenreToDB(data);

    int res = BaseModel::save(_dbTable, data);

    if(_id == 0)
    {
        _id = res["id"];
    }

    // Iterator, C++11 style :-)
    for (const auto& elem: _casting) {
        // Check if the entry is already in DB
        map<int, map<string, string>> casting = BaseModel::select("castings", "id", "artist_id=" + to_string(elem) + " AND dvd_id=" + to_string(_id));

        // Insert if not
        if (casting.empty())
        {
            BaseModel::save("castings", {
                {"id", {to_string(0), "int"}},
                {"artist_id", {to_string(elem), "int"}},
                {"dvd_id", {to_string(_id), "int"}}
            });
        }
    }

    return (bool) res;
}

void Dvd::deleteCasting()
{
    _casting.clear();

    SQLite::Database db("mediatheque.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
    SQLite::Statement   query(db, "DELETE FROM castings WHERE dvd_id=?");
    query.bind(1, (int) _id);
    query.exec();
}

bool Dvd::remove()
{
    return BaseModel::remove(_dbTable, _id);
}

void Dvd::displayCasting() const
{
    map<int, map<string, string>> casting = BaseModel::select("castings", "artist_id", "dvd_id=" + to_string(_id));

    if (!casting.empty())
    {
        cout << "Casting : ";
        int totalCasting = (int)casting.size();
        for (int i = 1; i != totalCasting + 1; i++)
        {
            Artist actor(stoi(casting[i]["artist_id"]));
            cout << actor.getFirstName() << " " << actor.getLastName();

            // Add a comma as long as we didn't reach the last item
            if (i != totalCasting)
            {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

ostream& operator<< (ostream& stream, Dvd& dvd)
{
    Artist director(dvd._authorId);

    stream << "ID #" << dvd._id << " : " << dvd._title << endl;
    stream << "Metteur en scene : " << director.getFirstName() << " "  << director.getLastName() << endl;
    dvd.displayCasting();
    stream << "Studio : " << dvd._studio << endl;
    stream << "Date de sortie : " << dvd._release << endl;
    stream << "Duree : " << dvd._length << " minutes" << endl;
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
    cout << "Duree en minutes" << endl;
    stream >> dvd._length;
    dvd.displayGenreFromCli(stream);

    int artistId = 0;

    cout << "ID de l'artiste a rajouter au casting, 0 pour ne pas rentrer de casting" << endl;
    stream >> artistId;

    while (artistId != 0)
    {
        dvd._casting.push_back(artistId);

        cout << "ID de l'artiste a rajouter au casting, 0 pour arreter" << endl;
        stream >> artistId;
    }

    dvd._author = new Artist(dvd._authorId);

    return stream;
}

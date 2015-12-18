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
#include "Util.hpp"

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

    if (!data.empty())
    {
        deserialization(data);
    }
    else
    {
        throw invalid_argument("Merci d'entrer un dvd valide");
    }
}

void Dvd::deserialization(map<string, string> data)
{
    if (!data.empty())
    {
        _id = data.find("id")!= data.end() ? stoi(data["id"]): 0;
        _borrowable = data.find("borrowable")!= data.end() ? data["borrowable"] != "0" : true;
        _title = data["title"];
        _release = data["release"];

        if(data.find("director")!= data.end())
        {
            _authorId = stoi(data["director"]);
            _author = new Artist(stoi(data["director"]));
        }
        else
        {
            _authorId = 0;
        }

        _studio = data["studio"];
        _length = data.find("length")!= data.end() ? stoi(data["length"]) : 0;
        retrieveGenreFromDB(data);
        retrieveStatusFromDB("dvd");
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

void Dvd::edit()
{
    int choice;
    bool failInput = false;
    do
    {
        cout << "Modification d'un DVD" << endl;

        cout << "1. Modifier le realisateur" << endl;
        cout << "2. Modifier le titre" << endl;
        cout << "3. Modifier la date de sortie" << endl;
        cout << "4. Modifier la duree" << endl;
        cout << "5. Modifier le studio" << endl;
        cout << "6. Modifier les genres" << endl;
        cout << "7. Modifier le casting" << endl;
        cout << "8. Modifier les statuts" << endl;
        cout << "0. Annuler" << endl;
        cout << "Choix: ";
        cin >> choice;
        if(cin.fail()){
            failInput = true;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while(failInput || choice < 0 || choice > 7);

    switch (choice)
    {
        case 1:
        {
            int newArtist = Util::displayIdList<Artist>("artists");
            if (newArtist != 0)
            {
                setAuthorId(newArtist);
            }
            break;
        }
        case 2:
        {
            string newTitle;
            cin.ignore(1, '\n');
            getline(cin, newTitle, '\n');
            setTitle(newTitle);
            break;
        }
        case 3:
        {
            Date newReleaseDate;
            cin >> newReleaseDate;
            setRelease(newReleaseDate);
            break;
        }
        case 4:
        {
            int newLength = -1;
            bool failInput;
            do{
                failInput = false;
                cout << "Saisir nouvel duree: ";
                cin >> newLength;
                if(cin.fail()){
                    failInput = true;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }while(failInput || newLength <= 0);

            setLength(newLength);
            break;
        }
        case 5:
        {
            string newStudio;
            cin.ignore(1, '\n');
            getline(cin, newStudio, '\n');
            setStudio(newStudio);
            break;
        }
        case 6:
        {
            cout << "Les genres actuels sont supprimes et remplaces par ceux que vous allez rentrer" << endl;
            deleteGenre();

            int genre1 = 0, genre2 = 0;

            cout << "ID genre 1" << endl;

            genre1 = Util::displayIdList<Genre>("genres");

            addGenre(genre1);

            cout << "ID genre 2" << endl;

            genre1 = Util::displayIdList<Genre>("genres");

            addGenre(genre2);

            break;
        }
        case 7:
        {
            cout << "Le casting actuel est supprime et remplace par celui que vous allez rentrer" << endl;
            deleteCasting();

            int artistId = 0;

            cout << "ID de l'artiste a rajouter au casting" << endl;
            artistId = Util::displayIdList<Artist>("artists");

            do {
                if (artistId != 0)
                {
                    addCasting(artistId);
                }

                cout << "ID de l'artiste a rajouter au casting, 0 pour arreter" << endl;
                artistId = Util::displayIdList<Artist>("artists");
            } while (artistId != 0);

            break;
        }
        case 8:
        {
            cout << "Les statuts actuels sont supprimes et remplaces par ceux que vous allez rentrer" << endl;
            deleteStatus();

            int artistId = 0, positionId = 0;

            cout << "ID de l'artiste a rajouter au status" << endl;
            artistId = Util::displayIdList<Artist>("artists");

            cout << "ID de la position de l'artiste" << endl;
            positionId = Util::displayIdList<Status>("status");

            do {
                if (positionId != 0 && artistId != 0)
                {
                    addStatus(positionId, artistId);
                }

                cout << "ID de l'artiste a rajouter au status" << endl;
                artistId = Util::displayIdList<Artist>("artists");

                if (artistId != 0)
                {
                    cout << "ID de la position de l'artiste" << endl;
                    positionId = Util::displayIdList<Status>("status");
                }
            } while (artistId != 0);

            break;
        }
        default:
            return;
            break;
    }

    cout << "Sauvegarde..." << endl;
    save();
    return;
}

bool Dvd::save()
{
    map<string, vector<string>> data = {
        {"id", {to_string(_id), "int"}},
        {"director", {to_string(_authorId), "int"}},
        {"title", {_title, "string"}},
        {"borrowable", {_borrowable ? "1": "0", "int"}},
        {"release", {_release.dateToDB(), "string"}},
        {"length", {to_string(_length), "int"}},
        {"studio", {_studio, "string"}}
    };

    addGenreToDB(data);
    addStatusToDB();

    int res = BaseModel::save(_dbTable, data);

    if (_id == 0)
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

    cout << "Saisie du titre : " << endl;
    stream.ignore(1, '\n');
    getline(stream, dvd._title, '\n');

    cout << "ID du realisateur : " << endl;
    int authorId;
    do {
        authorId = Util::displayIdList<Artist>("artists");
    }while(authorId == 0);
    dvd._authorId = authorId;

    cout << "Studio : " << endl;
    stream.ignore(1, '\n');
    getline(stream, dvd._studio, '\n');

    cout << "Date de sortie : " << endl;
    stream >> dvd._release;

    cout << "Duree en minutes : " << endl;
    stream >> dvd._length;

    dvd.displayGenreFromCli(stream);

    int artistId = 0;

    cout << "ID de l'artiste a rajouter au casting : " << endl;
    artistId = Util::displayIdList<Artist>("artists");

    while (artistId != 0)
    {
        dvd._casting.push_back(artistId);

        cout << "ID de l'artiste a rajouter au casting : " << endl;
        artistId = Util::displayIdList<Artist>("artists");
    }

    dvd._author = new Artist(dvd._authorId);

    return stream;
}

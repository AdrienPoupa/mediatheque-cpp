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
#include "Util.hpp"

using namespace std;

string Cd::_dbTable = "cds";

Cd::Cd()
{
    //ctor
}

Cd::Cd(int id)
{
    map<string, string> data = BaseModel::getById(_dbTable, id);

    if (!data.empty())
    {
        deserialization(data);
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

void Cd::deserialization(map<string, string> data)
{
    if (!data.empty())
    {
        _id = data.find("id")!= data.end() ? stoi(data["id"]): 0;
        _borrowable = data.find("borrowable")!= data.end() ? data["borrowable"] != "0" : true;
        _title = data["title"];
        _release = data["release"];

        if(data.find("artist")!= data.end())
        {
            _authorId = stoi(data["artist"]);
            _author = new Artist(stoi(data["artist"]));
        }
        else
        {
            _authorId = 0;
        }

        _studio = data["studio"];
        _length = data.find("length")!= data.end() ? stoi(data["length"]) : 0;
        retrieveGenreFromDB(data);
        retrieveStatusFromDB("cd");
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

void Cd::edit()
{
    int choice;
    bool failInput = false;
    do
    {
        cout << "Modification d'un CD" << endl;

        cout << "1. Modifier l'artiste" << endl;
        cout << "2. Modifier le titre" << endl;
        cout << "3. Modifier la date de sortie" << endl;
        cout << "4. Modifier la duree" << endl;
        cout << "5. Modifier le studio" << endl;
        cout << "6. Modifier les genres" << endl;
        cout << "7. Modifier les statuts" << endl;
        cout << "0. Annuler" << endl;
        cout << "Choix: ";
        cin >> choice;
        if(cin.fail()){
            failInput = false;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while(failInput || choice < 0 || choice > 6);

    switch (choice)
    {
        case 1:
        {
            int newArtist = Util::displayIdList<Artist>("artists");
            setAuthorId(newArtist);
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
            int genre1 = 0, genre2 = 0;

            cout << "ID genre 1" << endl;
            cin >> genre1;

            Util::checkInput(cin, genre1, 1);

            addGenre(genre1);

            cout << "ID genre 2" << endl;
            cin >> genre2;

            Util::checkInput(cin, genre2, 1);

            addGenre(genre2);

            break;
        }
        case 7:
        {
            cout << "Les statuts actuels sont supprimes et remplaces par ceux que vous allez rentrer" << endl;
            deleteStatus();

            int artistId = 0, positionId = 0;

            cout << "ID de l'artiste a rajouter au status" << endl;
            cin >> artistId;

            cout << "ID de la position de l'artiste" << endl;
            cin >> positionId;

            do {
                Util::checkInput(cin, artistId, 1);
                Util::checkInput(cin, positionId, 1);

                addStatus(positionId, artistId);

                cout << "ID de l'artiste a rajouter au status, 0 pour arreter" << endl;
                cin >> artistId;

                if (artistId != 0)
                {
                    cout << "ID de la position de l'artiste" << endl;
                    cin >> positionId;
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
    addStatusToDB();

    int res = BaseModel::save(_dbTable, data);

    if (_id == 0)
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


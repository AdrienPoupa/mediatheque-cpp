/*
 # Database Model

 Table: books

 Columns:
 - id: INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
 - borrowable: BOOLEAN,
 - title: TEXT,
 - release: DATE,
 - author: INTEGER REFERENCES artists (id),
 - editor: TEXT,
 - pages: INTEGER,
 - genre1: INTEGER REFERENCES genres (id),
 - genre2: INTEGER REFERENCES genres (id)
 */

#include "Book.hpp"
#include "Util.hpp"

using namespace std;

string Book::_dbTable = "books";

Book::Book()
{

}

Book::Book(const int id)
{
    map<string, string> data = BaseModel::getById(_dbTable, id);

    if (!data.empty())
    {
        deserialization(data);
    }
    else
    {
        throw invalid_argument("Merci d'entrer un livre valide");
    }
}

Book::~Book()
{

}

void Book::deserialization(map<string, string> data)
{
    if (!data.empty())
    {
        _id = data.find("id")!= data.end() ? stoi(data["id"]): 0;
        _borrowable = data.find("borrowable")!= data.end() ? data["borrowable"] != "0" : true;
        _title = data["title"];
        _release = data["release"];

        if(data.find("author")!= data.end())
        {
            _authorId = stoi(data["author"]);
            _author = new Artist(stoi(data["author"]));
        }
        else
        {
            _authorId = 0;
        }

        _editor = data["editor"];
        _pages = data.find("pages")!= data.end() ? stoi(data["pages"]) : 0;
        retrieveGenreFromDB(data);
        retrieveStatusFromDB("book");
    }
}

int Book::getPages() const
{
    return _pages;
}

void Book::setPages(const int& pages)
{
    _pages = pages;
}

string Book::getEditor() const
{
    return _editor;
}

void Book::setEditor(const string& editor)
{
    _editor = editor;
}

void Book::edit()
{
    int choice;
    bool failInput = false;
    do
    {
        cout << "Modification d'un livre" << endl;

        cout << "1. Modifier l'auteur" << endl;
        cout << "2. Modifier le titre" << endl;
        cout << "3. Modifier la date de sortie" << endl;
        cout << "4. Modifier le nombre de pages" << endl;
        cout << "5. Modifier l'editeur" << endl;
        cout << "6. Modifier les genres" << endl;
        cout << "7. Modifier les statuts" << endl;
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
            string newReleaseDate;
            cin >> newReleaseDate;
            setRelease(newReleaseDate);
            break;
        }
        case 4:
        {
            int newPages;
            cin >> newPages;

            Util::checkInput(cin, newPages, 1);

            setPages(newPages);
            break;
        }
        case 5:
        {
            string newEditor;
            cin.ignore(1, '\n');
            getline(cin, newEditor, '\n');
            setEditor(newEditor);
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

bool Book::save()
{
    map<string, vector<string>> data = {
        {"id", {to_string(_id), "int"}},
        {"borrowable", {_borrowable ? "1" : "0", "int"}},
        {"title", {_title, "string"}},
        {"release", {_release.dateToDB(), "string"}},
        {"author", {to_string(_authorId), "int"}},
        {"editor", {_editor, "string"}},
        {"pages", {to_string(_pages), "int"}},
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

bool Book::remove()
{
    return BaseModel::remove(_dbTable, _id);
}

ostream& operator<< (ostream& stream, Book& book)
{
    Artist author(book._authorId);

    stream << "ID #" << book._id << " : " << book._title << endl;
    stream << "Auteur : " << author.getFirstName() << " "  << author.getLastName() << endl;
    stream << "Editeur : " << book._editor << endl;
    stream << "Date de sortie : " << book._release << endl;
    stream << "Nombre de pages : " << book._pages << endl;
    book.displayGenres(stream);
    book.displayStatus(stream);

    return stream;
}

istream& operator>> (istream& stream, Book& book)
{
    cout << "Saisie d'un livre" << endl;

    cout << "Saisie du titre :" << endl;
    stream.ignore(1, '\n');
    getline(stream, book._title, '\n');

    cout << "ID de l'auteur :" << endl;

    int authorId;

    do {
        authorId = Util::displayIdList<Artist>("artists");
    } while (authorId == 0);

    book._authorId = authorId;

    cout << "Editeur :" << endl;
    stream.ignore(1, '\n');
    getline(stream, book._editor, '\n');

    cout << "Date de sortie :" << endl;
    stream >> book._release;

    cout << "Nombre de pages :" << endl;
    stream >> book._pages;

    book.displayGenreFromCli(stream);

    book._author = new Artist(book._authorId);

    return stream;
}

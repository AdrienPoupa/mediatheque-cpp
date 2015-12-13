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
#include "BaseModel.hpp"
#include "Artist.hpp"

using namespace std;

string Book::_dbTable = "books";

Book::Book()
{

}

Book::Book(int id)
{
    map<string, string> data = BaseModel::getById(_dbTable, id);

    if(!data.empty())
    {
        _id = id;
        _borrowable = data["borrowable"] != "0";
        _title = data["title"];
        _release = Date(data["release"]);
        _authorId = stoi(data["author"]);
        _editor = data["editor"];
        _pages = stoi(data["pages"]);
        retrieveGenreFromDB(data);
    }
    else
    {
        throw invalid_argument("Merci d'entrer un livre valide");
    }
}

Book::~Book()
{

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

bool Book::save()
{
    map<string, vector<string>> data = {
        {"id", {to_string(_id), "int"}},
        {"borrowable", {to_string(_borrowable), "boolean"}},
        {"title", {_title, "string"}},
        {"release", {_release.dateToDB(), "string"}},
        {"author", {to_string(_authorId), "int"}},
        {"editor", {_editor, "string"}},
        {"pages", {to_string(_pages), "int"}},
    };

    addGenreToDB(data);

    int res = BaseModel::save(_dbTable, data);

    if(_id == 0)
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

    return stream;
}

istream& operator>> (istream& stream, Book& book)
{
    cout << "Saisie d'un livre" << endl;
    cout << "Saisie du titre" << endl;
    stream.ignore(1, '\n');
    getline(stream, book._title, '\n');
    cout << "ID de l'auteur" << endl;
    stream >> book._authorId;
    cout << "Editeur" << endl;
    stream.ignore(1, '\n');
    getline(stream, book._editor, '\n');
    cout << "Date de sortie" << endl;
    stream >> book._release;
    cout << "Nombre de pages" << endl;
    stream >> book._pages;

    book.displayGenreFromCli(stream);

    book._author = new Artist(book._authorId);

    return stream;
}

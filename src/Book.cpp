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

    int genre1 = 0;
    int genre2 = 0;

    if(!data.empty()){
        _id = id;
        _borrowable = data["borrowable"] != "0";
        _title = data["title"];
        _release = Date(data["release"]);
        _authorId = stoi(data["author"]);
        _editor = data["editor"];
        _pages = stoi(data["pages"]);
        genre1 = stoi(data["genre1"]);
        genre2 = stoi(data["genre2"]);
    }

    if (genre1 != 0)
    {
        _genres.push_back(stoi(data["genre1"]));
    }

    if (genre2 != 0)
    {
        _genres.push_back(stoi(data["genre2"]));
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
    int genre1, genre2;

    if (_genres.empty())
    {
        genre1 = genre2 = 0;
    }
    else
    {
        if (_genres.front() == _genres.back())
        {
            genre1 = _genres.front();
            genre2 = 0;
        }

        Genre testGenre1(_genres.front());
        string testGenre1Name = testGenre1.getName();
        if (testGenre1Name == "Inconnu")
        {
            genre1 = 0;
        }

        Genre testGenre2(_genres.back());
        string testGenre2Name = testGenre2.getName();
        if (testGenre2Name == "Inconnu")
        {
            genre2 = 0;
        }

        genre1 = _genres.front();
        genre2 = _genres.back();
    }

    int res = BaseModel::save(_dbTable, {
        {"id", {to_string(_id), "int"}},
        {"borrowable", {to_string(_borrowable), "boolean"}},
        {"title", {_title, "string"}},
        {"release", {_release.dateToDB(), "string"}},
        {"author", {to_string(_authorId), "int"}},
        {"editor", {_editor, "string"}},
        {"pages", {to_string(_pages), "int"}},
        {"genre1", {to_string(genre1), "int"}},
        {"genre2", {to_string(genre2), "int"}},
    });

    if(_id == 0){
        _id = res;
    }

    return (bool) res;
}

bool Book::remove()
{
    return BaseModel::remove(_dbTable, _id);
}

ostream& operator<< (ostream& stream, const Book& book)
{
    Artist author(book._authorId);

    stream << "ID #" << book._id << " : " << book._title << endl;
    stream << "Auteur : " << author.getFirstName() << " "  << author.getLastName() << endl;
    stream << "Editeur : " << book._editor << endl;
    stream << "Date de sortie : " << book._release << endl;
    stream << "Nombre de pages : " << book._pages << endl;
    if (!(book._genres.empty()))
    {
        Genre genre1(book._genres.front());
        Genre genre2(book._genres.back());
        stream << "Genre 1 : " << genre1 << endl;
        stream << "Genre 2 : " << genre2 << endl;
    }

    return stream;
}

istream& operator>> (istream& stream, Book& book)
{
    int idGenre1, idGenre2;

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
    cout << "ID Genre 1 (0 pour genre inconnu)" << endl;
    stream >> idGenre1;
    cout << "ID Genre 2 (0 pour genre inconnu)" << endl;
    stream >> idGenre2;

    book._genres.push_back(idGenre1);
    book._genres.push_back(idGenre2);

    book._author = new Artist(book._authorId);

    return stream;
}

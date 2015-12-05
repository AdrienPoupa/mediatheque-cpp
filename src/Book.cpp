#include "Book.hpp"

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

using namespace std;

string Book::_dbTable = "books";

Book::Book()
{

}

Book::Book(int id)
{
    map<string, string> data = BaseModel::getById(_dbTable, id);

    if(!data.empty()){
        _id = id;
        _borrowable = data["borrowable"] != "0";
        _title = data["title"];
        _release = Date(data["release"]);
        _authorId = stoi(data["author"]);
        _editor = data["editor"];
        _pages = stoi(data["pages"]);
        // TODO: genres
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
    return true;
}

bool Book::remove()
{
    return BaseModel::remove(_dbTable, _id);
}

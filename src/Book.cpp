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

Book::Book()
{

}

Book::Book(int id)
{

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

std::string Book::getEditor() const
{
    return _editor;
}

void Book::setEditor(const std::string& editor)
{
    _editor = editor;
}

bool Book::save()
{
    return true;
}

bool Book::remove()
{
    // If the genre doesn't exist yet, we can't remove it
    if (_id == 0) {
        return false;
    }

    try
    {
        SQLite::Database    dbGenre("example.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
         // Delete query
        SQLite::Statement   query(dbGenre, "DELETE FROM books WHERE id=?");
        query.bind(1, (int) _id);
        query.exec();

        return true;
    }
    catch (std::exception& e)
    {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        return false;
    }

    return true;
}

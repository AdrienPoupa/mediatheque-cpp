#include "Article.hpp"

using namespace std;

Article::~Article()
{

}

void Article::addGenre(int genreId)
{
    if (_genres.size() < 2)
    {
        _genres.push_back(genreId);
    }
    else
    {
        cout << "Il y a deja deux genres pour cet article" << endl;
    }
}

void Article::deleteGenre()
{
    _genres.clear();
}

bool Article::getBorrowable() const
{
    return _borrowable;
}

unsigned int Article::getId() const
{
    return _id;
}

unsigned int Article::getAuthorId() const
{
    return _authorId;
}

void Article::setAuthorId(const int& newAuthorId)
{
    _authorId = newAuthorId;
}

Person* Article::getAuthor() const
{
    return _author;
}

void Article::setBorrowable(const bool& newBorrowable)
{
    _borrowable = newBorrowable;
}

vector<int> Article::getGenres() const
{
    return _genres;
}

Date Article::getRelease() const
{
    return _release;
}

void Article::setRelease(const Date& newRelease)
{
    _release = newRelease;
}

string Article::getTitle() const
{
    return _title;
}

void Article::setTitle(const string& newTitle)
{
    _title = newTitle;
}

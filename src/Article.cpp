#include "Article.hpp"

using namespace std;

//set<Genre*>Article::_genres = set<Genre*>();

Article::~Article()
{

}

void Article::addGenre(Genre* genre)
{
    if (_genres.size() < 2)
        _genres.insert(genre);
    else
        cout<<"Il y a déjà deux genres pour cet article"<<endl;
    save();
}

bool Article::getBorrowable() const
{
    return _borrowable;
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

std::set<Genre*> Article::getGenres() const
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

std::string Article::getTitle() const
{
    return _title;
}

void Article::setTitle(const std::string& newTitle)
{
    _title = newTitle;
}
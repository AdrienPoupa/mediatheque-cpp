#include "Article.hpp"

using namespace std;

Article::~Article()
{

}

void Article::deserialization(map<string, string> data){
    //empty
}

void Article::init(map<string, string> data){
    this->deserialization(data);
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

void Article::retrieveGenreFromDB(map<string, string> data)
{
    int genre1 = 0, genre2 = 0;

    if(!data.empty())
    {
        genre1 = data.find("genre1")!= data.end() ? stoi(data["genre1"]) : 0;
        genre2 = data.find("genre2")!= data.end() ? stoi(data["genre2"]) : 0;
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

void Article::addGenreToDB(map<string, vector<string>>& data)
{
    int genre1, genre2;

    if (_genres.empty())
    {
        genre1 = genre2 = 0;
    }
    else
    {
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

        if (genre1 == genre2)
        {
            genre1 = _genres.front();
            genre2 = 0;
        }
    }

    data["genre1"] = {to_string(genre1), "int"};
    data["genre2"] = {to_string(genre2), "int"};
}

void Article::shortDisplay() const{
    cout << _id << ". " << _title << " (" << _release << ")";
    if(_authorId){
        cout <<  " par " << _author->getFirstName() << " " << _author->getLastName();
    }
    cout << endl;
}

ostream& Article::displayGenres(ostream& stream)
{
    if (!(_genres.empty()))
    {
        Genre genre1(_genres.front());
        Genre genre2(_genres.back());
        if (genre1.getName() != "Inconnu")
        {
            stream << "Genre 1 : " << genre1 << endl;
        }
        if (genre2.getName() != "Inconnu" && genre1.getName() != genre2.getName())
        {
            stream << "Genre 2 : " << genre2 << endl;
        }
    }

    return stream;
}

istream& Article::displayGenreFromCli(istream& stream)
{
    int idGenre1, idGenre2;
    cout << "ID Genre 1 (0 pour genre inconnu)" << endl;
    stream >> idGenre1;
    cout << "ID Genre 2 (0 pour genre inconnu)" << endl;
    stream >> idGenre2;

    _genres.push_back(idGenre1);
    _genres.push_back(idGenre2);

    return stream;
}

#ifndef Article_hpp
#define Article_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "Date.hpp"
#include "Genre.hpp"
#include "Person.hpp"

class Article {
protected:
    unsigned int _id = 0; // save
    unsigned int _authorId; // save
    Person* _author; // do not save
    bool _borrowable; // save
    std::vector<int> _genres; // contains genres IDs
    Date _release; // save
    std::string _title; // save

    //std::map<int, std::string> _content;

public:
    virtual ~Article();

    unsigned int getId() const;

    bool getBorrowable() const;
    void setBorrowable(const bool& newBorrowable);

    unsigned int getAuthorId() const;
    Person* getAuthor() const;
    void setAuthorId(const int& newAuthorId);

    std::vector<int> getGenres() const;
    void addGenre(int genreId);
    void deleteGenre();

    Date getRelease() const;
    void setRelease(const Date& newRelease);

    std::string getTitle() const;
    void setTitle(const std::string& newTitle);

    void retrieveGenreFromDB(std::map<std::string, std::string> data);
    void addGenreToDB(std::map<std::string, std::vector<std::string>>& data);
    std::ostream& displayGenres(std::ostream& stream);
    std::istream& displayGenreFromCli(std::istream& stream);

    virtual bool save() = 0;
    virtual bool remove() = 0;

};

#endif /* Article_hpp */

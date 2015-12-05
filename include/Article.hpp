#ifndef Article_hpp
#define Article_hpp

#include <stdio.h>
#include <iostream>

#include "Date.hpp"
#include "Genre.hpp"
#include "Person.hpp"

#include <set>

class Article {
protected:
    unsigned int _id = 0; // save
    unsigned int _authorId; // save
    Person* _author; // do not save
    bool _borrowable; // save
    std::set<Genre*> _genres; // do not save
    Date _release; // save
    std::string _title; // save

    //std::map<int, std::string> _content;

public:
    virtual ~Article();

    unsigned int getId() const;
    bool getBorrowable() const;
    unsigned int getAuthorId() const;
    void setAuthorId(const int& newAuthorId);
    Person* getAuthor() const;
    void setBorrowable(const bool& newBorrowable);
    std::set<Genre*> getGenres() const;
    void addGenre(Genre* genre);
    Date getRelease() const;
    void setRelease(const Date& newRelease);
    std::string getTitle() const;
    void setTitle(const std::string& newTitle);

    virtual bool save() = 0;
    virtual bool remove() = 0;

};

#endif /* Article_hpp */

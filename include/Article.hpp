#ifndef Article_hpp
#define Article_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>

#include "BaseModel.hpp"
#include "Date.hpp"
#include "Genre.hpp"
#include "Person.hpp"
#include "Status.h"

class Article {
protected:
    unsigned int _id = 0; // save
    unsigned int _authorId; // save
    Person* _author; // do not save
    bool _borrowable = true; // save
    std::vector<int> _genres;
    std::map<int, int> _status;
    Date _release;
    std::string _title, _type = "book";

public:
    virtual ~Article();

    virtual void init(std::map<std::string, std::string> data);

    unsigned int getId() const;

    virtual void deserialization(std::map<std::string, std::string> data);

    bool getBorrowable() const;
    void setBorrowable(const bool& newBorrowable);

    unsigned int getAuthorId() const;
    Person* getAuthor() const;
    void setAuthorId(const int& newAuthorId);

    std::vector<int> getGenres() const;
    void addGenre(const int genreId);
    void deleteGenre();

    std::map<int, int> getStatus() const;
    void addStatus(const int statusId, const int artistId);
    void deleteStatus();
    std::ostream& displayStatus(std::ostream& stream);
    void addStatusToDB();
    void retrieveStatusFromDB(std::string type);

    Date getRelease() const;
    void setRelease(const Date newRelease);

    std::string getTitle() const;
    void setTitle(const std::string& newTitle);

    void retrieveGenreFromDB(std::map<std::string, std::string> data);
    void addGenreToDB(std::map<std::string, std::vector<std::string>>& data);

    void shortDisplay() const;
    std::ostream& displayGenres(std::ostream& stream);
    std::istream& displayGenreFromCli(std::istream& stream);

    virtual void edit() = 0;

    virtual bool save() = 0;
    virtual bool remove() = 0;

};

#endif /* Article_hpp */

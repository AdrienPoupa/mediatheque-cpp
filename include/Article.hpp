//
//  Article.hpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//

#ifndef Article_hpp
#define Article_hpp

#include <stdio.h>
#include <iostream>

#include "Date.hpp"
#include "Genre.hpp"
#include "Person.hpp"

class Article {
    
    unsigned int _id; // save
    
    unsigned int _authorId; // save
    Person* _author; // do not save
    bool _borrowable; // save
    unsigned int * _genreIdList; // save (modified)
    unsigned int _genreIdListLength; // do not save
    std::set<Genre*> _genreList; // do not save
    Date _release; // save
    std::string _studio; // save
    std::string _title; // save
    unsigned int _length; // save
    
    static unsigned int _lastIdUsed;
    
public:
    Article();
    ~Article();
    
    unsigned int getId() const;
    bool getBorrowable() const;
    unsigned int getAuthorId() const;
    void setAuthorId(const int& newAuthorId);
    Person* getAuthor() const;
    void setBorrowable(const bool& newBorrowable);
    unsigned int * getGenreIdList() const;
    unsigned int getGenreIdListLength() const;
    std::set<Genre*> getGenreList() const;
    Date getRelease() const;
    void setRelease(const Date& newRelease);
    std::string getStudio() const;
    void setStudio(const std::string& newStudio);
    std::string getTitle() const;
    void setTitle(const std::string& newTitle);
    unsigned int getLength() const;
    void setLength(const unsigned int& newLength);
    
    
    
    
    
    
    
};

#endif /* Article_hpp */

//
//  Artist.hpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//

#ifndef Artist_hpp
#define Artist_hpp

#include <stdio.h>
#include <iostream>
#include <set>

#include "Article.hpp"
#include "Position.hpp"
#include "Person.hpp"

class Artist: public Person {
    std::string _nationality;
    std::set<Position*> _positions;
    std::set<Article*> _articles;
    
public:
    Artist(std::string nationality = "");
    
    std::string getNationality() const;
    void setNationality(const std::string& nationality);
    
    std::set<Position*> getPositions() const;
    std::set<Article*> getArticles() const;
    
    void addArticles(const Article& article, const Position& position);
    void removeArticles(const Article& article);
    
    friend std::ostream& operator<<(std::ostream& os, const Artist& me);
    friend std::istream& operator>>(std::istream& is, Artist& me);
    
    // DB method
    bool save();
    bool update();
    bool remove();
    
    
    ~Artist();
};

#endif /* Artist_hpp */

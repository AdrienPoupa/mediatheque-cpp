#ifndef Artist_hpp
#define Artist_hpp

#include <stdio.h>
#include <iostream>
#include <set>
#include <map>

#include "Article.hpp"
#include "Person.hpp"

class Artist: public Person {

    static std::string _dbTable;
    std::string _nationality;

    //std::set<Position*> _positions;
    std::set<Article*> _articles;
    //std::map<Position*, std::set<Article*>> _realisations;

public:
    Artist(const std::string& firstName = "John", const std::string& lastName = "Doe", const std::string& nationality = "Inconnu");
    Artist(int id);

    std::string getNationality() const;
    void setNationality(const std::string& nationality);

    std::set<Article*> getArticles() const;

    void addArticles(const Article& article);
    void removeArticles(const Article& article);

    friend std::ostream& operator<<(std::ostream& os, const Artist& me);
    friend std::istream& operator>>(std::istream& is, Artist& me);

    // DB method
    bool save();
    bool remove();


    ~Artist();
};

#endif /* Artist_hpp */

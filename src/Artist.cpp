//
//  Artist.cpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//
#include <iostream>

#include "Artist.hpp"

using namespace std;

Artist::Artist(const std::string& firstName, const std::string& lastName, const std::string& nationality):Person(firstName, lastName), _nationality(nationality)
{
    // empty
}

std::string Artist::getNationality() const{
    return _nationality;
}
void Artist::setNationality(const std::string& nationality){
    _nationality = nationality;
}

std::set<Position*> Artist::getPositions() const{
    return _positions;
}
std::set<Article*> Artist::getArticles() const{
    return _articles;
}

void addArticles(const Article& article, const Position& position){
    // TODO
}
void removeArticles(const Article& article){
    // TODO
}


std::ostream& operator<<(std::ostream& os, const Artist& me){
    os << me.getFirstName() << me.getLastName() <<" (" << me.getNationality() << "), née le " << me.getBirthDate() << endl;
    return os;
}

std::istream& operator>>(std::istream& is, Artist& me){
    cout << "Saisie d'un artiste: " << endl;
    cout << " - prénom : ";
    is >> me._firstName;
    cout << " - nom : ";
    is >> me._lastName;
    cout << " - nationalité : ";
    is >> me._nationality;
    cout << " - date de Naissance : ";
    is >> me._birthDate;

    return is;
}

// DB method
bool Artist::save(){
    return true;
}
bool Artist::update(){
    return true;
}
bool Artist::remove(){
    return true;
}

Artist::~Artist(){
}



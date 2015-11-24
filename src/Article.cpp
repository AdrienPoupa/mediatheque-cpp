//
//  Article.cpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//

#include "Article.hpp"

using namespace std;

//set<Genre*>Article::_genres = set<Genre*>();

Article::~Article()
{

}

void Article::addGenre(Genre* genre)
{
    _genres.insert(genre);
    update();
}

bool Article::save()
{
    return true;
}

bool Article::update()
{
    return true;
}

bool Article::remove()
{
    return true;
}

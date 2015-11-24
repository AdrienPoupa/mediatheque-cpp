//
//  Genre.cpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//

#include "Genre.hpp"

Genre::Genre(const std::string name) : _name(name)
{

}

int Genre::getId()
{
    return _id;
}

void Genre::setName(const std::string name)
{
    _name = name;
}

std::string Genre::getName() const
{
    return _name;
}

bool Genre::save()
{
    return true;
}

bool Genre::update()
{
    return true;
}

bool Genre::remove()
{
    return true;
}

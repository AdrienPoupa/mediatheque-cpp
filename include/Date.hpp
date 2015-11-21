//
//  Date.hpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//  D'après la classe Date: http://www.ece.uc.edu/~franco/C321/html/date.html
//

#ifndef Date_hpp
#define Date_hpp

#include <stdio.h>


class Date
{
 public:
    Date (int day = 1, int month = 1, int year = 1);
    void display();
    int getMonth();
    void setMonth(int month);
    int daysSoFar();
 private:
    int _month, _day, _year;
};


#endif /* Date_hpp */

//
//  Date.hpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//  Source de la classe Date: http://www.ece.uc.edu/~franco/C321/html/date.html
//

#ifndef Date_hpp
#define Date_hpp

#include <stdio.h>


class Date
{
 public:
    Date ( int mn = 1, int day = 1, int yr = 1);  // constructor
    void display();                   // function to display date
    int GetMonth();
    void SetMonth(int mn);
 private:
    int month, day, year;
    int DaysSoFar();
};


#endif /* Date_hpp */

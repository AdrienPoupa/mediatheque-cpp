//
//  Date.cpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//  Source de la classe Date: http://www.ece.uc.edu/~franco/C321/html/date.html
//

#include "Date.hpp"
#include <iostream>

using namespace std;

int max (int a, int b)
{
   if (a>b) return(a) ; else return (b);
}

int min (int a, int b)
{
   if (a>b) return(b); else return (a);
}

Date::Date (int mn, int dy, int yr)
{
   static int length[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

   month = max(1, mn);
   month = min(month,12);

   day = max(1,dy);
   day = min(day, length[month]);

   year = max(1, yr);
}

void Date::display()
{
   static char const *name[] = {"nothing", "January", "February", "March", "April",
            "May", "June", "July", "August", "September", "October",
            "November", "December" };

   cout << '\n' << name[month] << ' ' << day << "," << year << '\n';
   cout << "Days so far: " << DaysSoFar() << '\n';
}

int Date::DaysSoFar()
{
   int total = 0;
   static int length[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

   for (int i=1; i < month; i++) total += length[i];
   total += day;
   return (total);
}

int Date::GetMonth()
{
   return month;
}

void Date::SetMonth(int mn)
{
   month = max(1, mn);
   month = min(month, 12);
}

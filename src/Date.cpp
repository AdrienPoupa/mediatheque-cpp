//
//  Date.cpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//  D'après la classe Date: http://www.ece.uc.edu/~franco/C321/html/date.html
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

Date::Date (int month, int day, int year)
{
   static int length[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

   _month = max(1, month);
   _month = min(_month,12);

   _day = max(1,day);
   _day = min(_day, length[_month]);

   _year = max(1, year);
}

void Date::display()
{
   static char const *name[] =
   {"inconnu", "Janvier", "Fevrier", "Mars", "Avril",
    "Mai", "Juin", "Juillet", "Aout", "Septembre",
    "Octobre", "Novembre", "Decembre"};

   cout << endl << _day << ' ' << name[_month] << ' ' << _year << endl;
   //cout << "Jours jusqu'à présent: " << DaysSoFar() << '\n';
}

int Date::daysSoFar()
{
   int total = 0;
   static int length[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

   for (int i=1; i < _month; i++)total += length[i];
   total += _day;
   return (total);
}

int Date::getMonth()
{
   return _month;
}

void Date::setMonth(int month)
{
   _month = max(1, month);
   _month = min(month, 12);
}

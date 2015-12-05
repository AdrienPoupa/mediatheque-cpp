//  D'après la classe Date: http://www.ece.uc.edu/~franco/C321/html/date.html
//

#ifndef Date_hpp
#define Date_hpp

#include <stdio.h>
#include <iostream>


class Date
{
 public:
    Date (int day = 1, int month = 1, int year = 1);
    Date (std::string dateDB);
    int getMonth();
    void setMonth(int month);
    int daysSoFar();
    friend std::ostream& operator<< (std::ostream& stream, const Date& date);
    friend std::istream& operator>> (std::istream& stream, Date& date);
    std::string dateToDB();
 private:
    int _month, _day, _year;
};


#endif /* Date_hpp */

//  D'après la classe Date: http://www.ece.uc.edu/~franco/C321/html/date.html
//

#include "Date.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <chrono>
#include <map>

using namespace std;

Date::Date (int month, int day, int year)
{
    static int length[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    if(month != -1 && day != -1 && year != -1){
        _month = max(1, month);
        _month = min(_month,12);
        
        _day = max(1, day);
        _day = min(_day, length[_month]);
        
        _year = max(1, year);
    }
    else{
        
        map<string, int> months = {{"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4}, {"Mai", 5}, {"Jun", 6}, {"Jul", 7}, {"Aug", 8}, {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}};
    
        std::chrono::time_point<std::chrono::system_clock> end;
        end = std::chrono::system_clock::now();
        
        time_t end_time = std::chrono::system_clock::to_time_t(end);
        
        string timeStr = std::ctime(&end_time);
        
        _month = months.at(timeStr.substr(4, 3));
        _day = stoi(timeStr.substr(7, 3));
        _year =  stoi(timeStr.substr(20, 4));
    }

    
}

Date::Date (string dateDB)
{
    static int length[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Too much redundant code here...

    ostringstream ss1;
    ss1 << dateDB.substr(0,4);
    string _yearString = ss1.str();
    _yearString.erase(0, _yearString.find_first_not_of('0')); // Delete leading zeros
    stringstream ss11(_yearString); // Convert string back to int
    ss11 >> _year;
    _year = max(1, _year);

    ostringstream ss2;
    ss2 << dateDB.substr(5,2);
    string _monthString = ss2.str();
    _monthString.erase(0, _monthString.find_first_not_of('0'));
    istringstream ss22(_monthString);
    ss22 >> _month;
    _month = max(1, _month);
    _month = min(_month,12);

    ostringstream ss3;
    ss3 << dateDB.substr(8,2);
    string _dayString = ss3.str();
    _dayString.erase(0, _dayString.find_first_not_of('0'));
    istringstream ss33(_dayString);
    ss33 >> _day;
    _day = max(1, _day);
    _day = min(_day, length[_month]);
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

// Returns YEAR-MM-DAY to store in DB
string Date::dateToDB()
{
    /*
       Convert int to string and add leading zeros
       http://stackoverflow.com/questions/26486419/c-save-int-with-leading-zeros-to-string-not-displaying-them
    */
    ostringstream ss1;
    ss1 << setw(4) << setfill('0') << _year;
    string year = ss1.str();

    ostringstream ss2;
    ss2 << setw(2) << setfill('0') << _month;
    string month = ss2.str();

    ostringstream ss3;
    ss3 << setw(2) << setfill('0') << _day;
    string day = ss3.str();

    return year + "-" + month + "-" + day;
}

ostream& operator<< (ostream& stream, const Date& date)
{
   static char const *name[] =
   {"inconnu", "Janvier", "Fevrier", "Mars", "Avril",
    "Mai", "Juin", "Juillet", "Aout", "Septembre",
    "Octobre", "Novembre", "Decembre"};

    cout << date._day << ' ' << name[date._month] << ' ' << date._year;

    return stream;
}

istream& operator>> (istream& stream, Date& date)
{
    int day, month, year;

    cout << "Saisissez d'abord le jour (de 1 a 31) : " << endl;
    stream >> day;
    cout << "Saisissez ensuite le mois (de 1 a 12) : " << endl;
    stream >> month;
    cout << "Saisissez enfin l'annee : " << endl;
    stream >> year;

    // Redundant with constructor, should we do something about it ?
    static int length[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    date._month = max(1, month);
    date._month = min(date._month,12);

    date._day = max(1, day);
    date._day = min(date._day, length[date._month]);

    date._year = max(1, year);

    return stream;
}

//  D'après la classe Date: http://www.ece.uc.edu/~franco/C321/html/date.html
//

#include "Date.hpp"

using namespace std;

Date::Date (const int month, const int day, const int year)
{
    static int length[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (month != -1 && day != -1 && year != -1)
    {
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

int getYearFromStr(string date){
    ostringstream ss1;
    ss1 << date.substr(0,4);
    string yearString = ss1.str();
    yearString.erase(0, yearString.find_first_not_of('0')); // Delete leading zeros
    stringstream ss11(yearString); // Convert string back to int
    int year;
    ss11 >> year;
    year = max(1, year);
    return year;
}

int getMonthFromStr(string date){
    ostringstream ss2;
    ss2 << date.substr(5,2);
    string monthString = ss2.str();
    monthString.erase(0, monthString.find_first_not_of('0'));
    istringstream ss22(monthString);
    int month;
    ss22 >> month;
    month = max(1, month);
    month = min(month,12);
    
    return month;
}

int getDayFromStr(string date, int month){
    static int length[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    ostringstream ss3;
    ss3 << date.substr(8,2);
    string dayString = ss3.str();
    dayString.erase(0, dayString.find_first_not_of('0'));
    istringstream ss33(dayString);
    int day;
    ss33 >> day;
    day = max(1, day);
    day = min(day, length[month]);
    return day;
}


Date::Date (const string dateDB)
{
    if(dateDB.length() >= 4){
        _year = getYearFromStr(dateDB);
    }
    else{
        _year = -1;
    }
    
    if(dateDB.length() >= 7){
        _month = getMonthFromStr(dateDB);
    }
    else{
        _month = -1;
    }
    
    if(dateDB.length() >= 10){
        _day = getDayFromStr(dateDB, _month == -1 ? 0 : _month);
    }
    else{
        _day = -1;
    }

    
}

int Date::daysSoFar() const
{
   int total = 0;
   static int length[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

   for (int i = 1; i < _month; i++)
   {
       total += length[i];
   }

   total += _day;

   return total;
}

int Date::getMonth() const
{
   return _month;
}

void Date::setMonth(const int month)
{
   _month = max(1, month);
   _month = min(month, 12);
}

void Date::setDay(const int day)
{
   _day = day;
}

int Date::getDay() const
{
   return _day;
}

void Date::setYear(const int year)
{
   _year = year;
}

int Date::getYear() const
{
   return _year;
}

// Returns YEAR-MM-DAY to store in DB
string Date::dateToDB() const
{
    /*
       Convert int to string and add leading zeros
       http://stackoverflow.com/questions/26486419/c-save-int-with-leading-zeros-to-string-not-displaying-them
    */
    ostringstream ss1;
    ss1 << setw(4) << setfill('0') << (_year == -1 ? 0 : _year);
    string year = ss1.str();

    ostringstream ss2;
    ss2 << setw(2) << setfill('0') << (_month == -1 ? 0 : _month);
    string month = ss2.str();

    ostringstream ss3;
    ss3 << setw(2) << setfill('0') << (_day == -1 ? 0 : _day);
    string day = ss3.str();

    return year + "-" + month + "-" + day;
}

ostream& operator<< (ostream& stream, const Date& date)
{
   static char const *name[] =
   {"inconnu", "Janvier", "Fevrier", "Mars", "Avril",
    "Mai", "Juin", "Juillet", "Aout", "Septembre",
    "Octobre", "Novembre", "Decembre"};

    cout << (date._day != -1 ? date._day : stoi("")) << ' ' << (date._month != -1 ? name[date._month] : "") << ' ' << (date._year != -1 ? date._year : stoi(""));

    return stream;
}

istream& operator>> (istream& stream, Date& date)
{
    int day, month, year;

    do {
        cout << "Saisissez d'abord le jour (de 1 a 31) : " << endl;
        stream >> day;
    }while(day < 1 && day > 31);
    
    do {
        cout << "Saisissez ensuite le mois (de 1 a 12) : " << endl;
        stream >> month;
    }while(month < 1 && month > 12);
    
    do{
        cout << "Saisissez enfin l'annee : " << endl;
        stream >> year;
    }while(year < 0 && year > 9000);
    

    // Redundant with constructor, should we do something about it ?
    static int length[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    date._month = max(1, month);
    date._month = min(date._month,12);

    date._day = max(1, day);
    date._day = min(date._day, length[date._month]);

    date._year = max(1, year);

    return stream;
}

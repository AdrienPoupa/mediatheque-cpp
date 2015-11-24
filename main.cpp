#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "sqlite/SQLiteCpp.h"
#include "Date.hpp"

using namespace std;

int main()
{
    try
    {
        // Open a database file
        SQLite::Database    db("example.db3");

        // Compile a SQL query, containing one parameter (index 1)
        SQLite::Statement   query(db, "SELECT * FROM test WHERE id > ?");

        // Bind the integer value 6 to the first parameter of the SQL query
        query.bind(1, 1);

        // Loop to execute the query step by step, to get rows of result
        while (query.executeStep())
        {
            // Demonstrate how to get some typed column value
            int         id      = query.getColumn(0);
            const char* value   = query.getColumn(1);

            cout << "row: " << id << ", " << value << endl;
        }
    }
    catch (exception& e)
    {
        cout << "exception: " << e.what() << endl;
    }


   // Tests Date
   /*
   Date mydate(1, 2, 1993);
   Date date2(12,4,1994);
   Date date4;
   Date *date3;
   Date *date6;
   Date date5(1,1,1);

   date3 = new Date(45,45,44545);

   cout << mydate << endl;
   cout << date2 << endl;
   cout << *date3 << endl;


   cout << "OK: " << date3->getMonth() << endl;
   date3->setMonth(4);
   cout << "OK: " << date3->getMonth() << endl;

   delete(date3);
   date6 = new Date(1,1,1);

   cout << "OK: " << date3->getMonth() << endl;
   date3->setMonth(4);
   cout << "OK: " << date3->getMonth() << endl;

   cout << date3 << endl;

   cout << date4 << endl;

   date5.setMonth(3);
   delete(date6);

   Date yourDate;
   cout << "Vous allez saisir Jour Mois Annee" << endl;
   cin >> yourDate;
   cout << yourDate << endl;

   cout << "Format BDD:" << yourDate.dateToDB() << endl;

   Date dateDB("2015-03-04");
   cout << dateDB << endl;
   */

   // Tests Artiste
}

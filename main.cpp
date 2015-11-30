#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "sqlite/SQLiteCpp.h"
#include "Date.hpp"
#include "Address.hpp"
#include "User.hpp"

using namespace std;

int main()
{
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

    /*Date dateDB("1970-03-04");

    Address addPOTUS;
    addPOTUS.setCountry("USA");
    addPOTUS.setTown("Washington DC");
    addPOTUS.setStreetName("White House");
    //cout << addPOTUS;
    cout << addPOTUS.addressDB() << endl;

    User POTUS("Obama", "Barack", dateDB, "911");
    POTUS.setAddress(addPOTUS);
    POTUS.save();
    cout << POTUS;
    POTUS.setLastName("Jackson");
    //POTUS.save();
    //POTUS.remove();*/

    User userFromID(1);
    cout << userFromID << endl;
}

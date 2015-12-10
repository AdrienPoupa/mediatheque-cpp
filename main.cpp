#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "sqlite/SQLiteCpp.h"
#include "BaseModel.hpp"
#include "Book.hpp"
#include "Cd.hpp"
#include "Dvd.hpp"
#include "Date.hpp"
#include "Address.hpp"
#include "Artist.hpp"
#include "User.hpp"
#include "User.hpp"
#include "Transaction.hpp"
#include "sha256.h"
#include "Library.hpp"

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

    /*
    Date dateDB("1970-03-04");

    Address addPOTUS;
    addPOTUS.setCountry("USA");
    addPOTUS.setTown("Washington DC");
    addPOTUS.setStreetName("White House");
    cout << addPOTUS;

    User POTUS("Obama", "Barack", dateDB, "911");
    POTUS.setAddress(addPOTUS);

    POTUS.save();
    cout << POTUS;
    POTUS.setLastName("Jackson");
    POTUS.save();
    cout << POTUS;
    cout << POTUS.remove();
     */

    /*User test1(8);
    cout << test1 << endl;

    User test2(900);
    cout << test2 << endl;*/

//    User userFromID(1);
//    cout << userFromID << endl;

    /*Genre nouveauGenre;
    cin >> nouveauGenre;
    nouveauGenre.save();
    cout << nouveauGenre << endl;*/

//    Genre nouveauGenre(7);
//    cout << nouveauGenre << endl;

    /*Artist monArtiste;
    cin >> monArtiste;
    cout << monArtiste;
    monArtiste.save();*/

//    Artist monArtiste(2);
//    cout << monArtiste << endl;



    /*Address addPOTUS;
    addPOTUS.setCountry("USA");
    addPOTUS.setTown("Washington DC");
    addPOTUS.setStreetName("White House");
    addPOTUS.setHouseNumber(1);
    addPOTUS.setPostalCode("911");
    //cout << addPOTUS;
    cout << addPOTUS.addressDB() << endl;

    Date dateDB("1970-03-04");
    User POTUS("Obama", "Barack", dateDB, "911");
    POTUS.setAddress(addPOTUS);
    POTUS.save();
    cout << POTUS;*/

    /*User POTUS(8);
    cout << POTUS << endl;
    Address test = POTUS.getAddress();
    cout << test;
    test.setCountry("France");
    POTUS.setAddress(test);
    POTUS.save();*/

    /*Book *GoT = new Book(1);
    User POTUS(8);
    string type = "book";
    Transaction testT(GoT, type, POTUS, Date("2015-12-05"), Date("2015-12-15"));
    cout << testT;
    //testT.save();
    Transaction::displayTransactions("current");
    Transaction::displayTransactions();

    string input = "grape";
    string output1 = sha256(input);

    cout << "sha256('"<< input << "'):" << output1 << endl;*/

    /*User POTUS(8);
    POTUS.setPassword("president");
    cout << POTUS.checkPassword("bad_pwd") << endl;
    cout << POTUS.checkPassword("president") << endl;
    POTUS.setAdmin(1);
    POTUS.setQuota(10);
    POTUS.save();*/

    /*User toBeInserted;
    cin >> toBeInserted;
    cout << toBeInserted;*/
    //toBeInserted.save();

    Library *l = Library::getSingleton();
    Library *l2 = Library::getSingleton();
    l->open();
}

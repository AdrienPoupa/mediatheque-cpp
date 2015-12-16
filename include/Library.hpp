#ifndef Library_hpp
#define Library_hpp

#include <iostream>
#include <stdio.h>
#include <set>

#include "BaseModel.hpp"
#include "Article.hpp"
#include "Book.hpp"
#include "Dvd.hpp"
#include "Cd.hpp"
#include "Person.hpp"
#include "Artist.hpp"
#include "User.hpp"
#include "../sqlite/SQLiteCpp.h"

class Library {
    User _currentUser;

    public:
        static Library *getSingleton();
        ~Library();

        void open();

    private:
        Library();

        bool isAdmin();

        void checkInput(std::istream& stream, int intToCheck, int minValue);

        void displayMenu();
        void redirectChoice(int choice);
    
        void searchList();

        void bookList();
        void seeBook(int bookId);
        void editBook(Book& book);

        void dvdList();
        void seeDvd(int dvdId);
        void editDvd(Dvd& dvd);

        void cdList();
        void seeCd(int cdId);
        void editCd(Cd& cd);

        void userList();
        void editUser(int userId);
        void deleteUser();

        void artistList();
        void seeArtist(int artistId);
        void editArtist(Artist& artist);

        void bibliography(Artist& artist);
        void discography(Artist& artist);
        void filmography(Artist& artist);

        template <class T>
        void addThing();

        void borrowArticle(Article* art = nullptr, std::string type = NULL);
        void returnArticle();
        void listTransactions();

        static Library* singleton;
};

#endif /* Library_hpp */

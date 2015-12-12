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

        void displayMenu();
        void redirectChoice(int choice);

        void bookList();
        void seeBook(int bookId);
        void addBook();
        void editBook(Book& book);

        void dvdList();
        void seeDvd(int dvdId);
        void addDvd();
        void editDvd(Dvd& dvd);

        void cdList();
        void seeCd(int cdId);
        void addCd();
        void editCd(Cd& cd);

        void userList();
        void addUser();
        void editUser(int userId);
        void deleteUser();

        void artistList();
        void addArtist();
        void editArtist(int artistId);
        void deleteArtist();

        void borrowArticle();
        void returnArticle();
        void listTransactions();

        static Library* singleton;
};

#endif /* Library_hpp */

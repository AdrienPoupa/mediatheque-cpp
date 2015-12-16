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

        void checkInput(std::istream& stream, const int intToCheck, const int minValue) const;

        void displayMenu();
        void redirectChoice(int choice);
    
        template <class T>
        void seeArticle(int id);
    
        template <class T>
        void getListArticle();
    
        bool affichageChoixSee(std::string typeChoix, std::string typeArticle) const;
    
        void searchList() const;

        void bookList();
        void editBook(Book& book);

        void dvdList();
        void editDvd(Dvd& dvd);

        void cdList();
        void editCd(Cd& cd);

        void userList();
        void editUser(const int userId);
        void deleteUser();

        void artistList();
        void seeArtist(const int artistId);
        void editArtist(Artist& artist);

        void bibliography(Artist& artist) const;
        void discography(Artist& artist) const;
        void filmography(Artist& artist) const;

        template <class T>
        void addThing();

        void borrowArticle(Article* art = nullptr, const std::string type = NULL);
        void returnArticle();
        void listTransactions();

        static Library* singleton;
};

#endif /* Library_hpp */

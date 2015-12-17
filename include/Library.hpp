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

        void run();

    private:
        Library();

        bool isAdmin();
    
        bool connect();

        bool checkInput(std::istream& stream, const int intToCheck, const int minValue) const;

        int displayMenu();
        void redirectChoice(int choice);
    
        template <class T>
        void seeArticle(int id);
    
        template <class T>
        void getListArticle();
    
        bool affichageChoixSee(std::string typeChoix, std::string typeArticle) const;
    
        void searchList();

        void editBook(Book& book);

        void editDvd(Dvd& dvd);

        void editCd(Cd& cd);

        void userList();
        void editUser(const int userId);
        void deleteUser(int userId);

        void artistList();
        void seeArtist(const int artistId);
        void editArtist(Artist& artist);

        void bibliography(Artist& artist) const;
        void discography(Artist& artist) const;
        void filmography(Artist& artist) const;

        template <class T>
        void addThing();

        void borrowedMenu();
        void seeEmprunt(Transaction tr);
        void borrowArticle(Article* art = nullptr, const int type = 0);
        void returnArticle(Transaction *t = nullptr);
        void listTransactions();

        static Library* singleton;
};

class Util{
public:
    enum Types{Book, Cd, Dvd};
    static std::string getTypesString(Types type){
        switch(type){
            case Types::Book:
                return "livre";
                break;
            case Types::Cd:
                return "Cd";
                break;
            default:
                return "Dvd";
        }
    }
};



#endif /* Library_hpp */

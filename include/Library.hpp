#ifndef Library_hpp
#define Library_hpp

#include <iostream>
#include <fstream>
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
#include "Util.hpp"
#include "../sqlite/SQLiteCpp.h"
#include "Transaction.hpp"

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

        int displayMenu();
        void redirectChoice(const int choice);

        template <class T>
        void seeEntity(const int id);

        template <class T>
        void getListEntity(bool askEdit = true);
    
        bool affichageChoixSee(std::string typeChoix, std::string typeArticle) const;

        void searchList();

        void userList();

        void artistList();
        void seeArtist(const int artistId);

        template <class T>
        void addThing();

        void borrowedMenu();
        void seeEmprunt(Transaction tr, bool adminMode = false);
        void borrowArticle(Article* art = nullptr, const int type = 0);
        void returnArticle(Transaction *t = nullptr);
        void listTransactions();

        static Library* singleton;
};


#endif /* Library_hpp */

#ifndef Library_hpp
#define Library_hpp

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <set>


#ifdef _WIN32
#define CLEAN_SCREEN "CLS"
#include "mingw.thread.hpp"
#else
#define CLEAN_SCREEN "clear"
#include <thread>
#endif

#include "BaseModel.hpp"
#include "Article.hpp"
#include "Book.hpp"
#include "Dvd.hpp"
#include "Cd.hpp"
#include "Genre.hpp"
#include "Person.hpp"
#include "Artist.hpp"
#include "User.hpp"
#include "Util.hpp"
#include "../sqlite/SQLiteCpp.h"
#include "Transaction.hpp"
#include "Status.h"

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
        void seeEntity(const int id, bool isTrWithAdmin = false);

        template <class T>
        void getListEntity(bool askEdit = true, int artistFilter = 0);

        bool affichageChoixSee(std::string typeChoix, std::string typeArticle) const;

        void searchList();

        template <class T>
        void addThing();

        void borrowedMenu();
        void borrowArticle(Article* art = nullptr, const int type = 0);
        void returnArticle(Transaction *t = nullptr);

        static Library* singleton;
};


#endif /* Library_hpp */

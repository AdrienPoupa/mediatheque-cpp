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
    std::set<Article*> _articleSet;
    std::set<Person*> _personSet;
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

    void borrowArticle();
    void returnArticle();

    void userList();
    void addUser();
    void editUser();
    void deleteUser();

    void listTransactions();

    static Library* singleton;

};

#endif /* Library_hpp */

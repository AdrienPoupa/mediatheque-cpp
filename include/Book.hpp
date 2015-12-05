
#ifndef Book_hpp
#define Book_hpp

#include <stdio.h>

#include <string>

#include "Article.hpp"

class Book : public Article {
protected:
    int _pages;
    std::string _editor;
public:
    Book();
    Book(int id);
    ~Book();

    int getPages() const;
    void setPages(const int& pages);

    std::string getEditor() const;
    void setEditor(const std::string& editor);

    bool save();
    bool remove();
};

#endif /* Book_hpp */

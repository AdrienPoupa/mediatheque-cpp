
#ifndef Book_hpp
#define Book_hpp

#include <stdio.h>

#include <string>

#include "BaseModel.hpp"
#include "Artist.hpp"
#include "Article.hpp"

class Book : public Article {
private:
    static std::string _dbTable;
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

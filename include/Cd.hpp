#ifndef CD_HPP
#define CD_HPP

#include "Article.hpp"

class Cd : public Article
{
public:
    Cd();
    Cd(int id);
    virtual ~Cd();
    std::string getStudio() const;
    void setStudio(const std::string& newStudio);
    unsigned int getLength() const;
    void setLength(const unsigned int& newLength);
    bool save();
    bool remove();
    
protected:
    std::string _studio; // save
    unsigned int _length; // save
    
private:
    static std::string _dbTable;
};

#endif // CD_HPP

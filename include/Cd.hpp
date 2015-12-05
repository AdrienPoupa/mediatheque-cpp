#ifndef CD_HPP
#define CD_HPP

#include "Article.hpp"

class Cd : public Article
{
    public:
        Cd();
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
};

#endif // CD_HPP
#ifndef CD_H
#define CD_H

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

#endif // CD_H
unsigned int _id;
bool _etat;
std::string _titre;
std::string _artiste;
std::string _studioDeDistriburtion;
std::map<int, std::string> _chansons;
Date _dateDeSortie;
unsigned int _duree;
Genre _genre;
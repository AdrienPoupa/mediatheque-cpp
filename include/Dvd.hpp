#ifndef DVD_H
#define DVD_H

#include "Cd.h"
#include "Artist.hpp"

class Dvd : public Cd
{
    public:
        Dvd();
        Dvd(int id);
        virtual ~Dvd();
        std::set<Artist*> getCasting() const;
        void addCasting(Artist* artist);
        bool save();
        bool remove();
    protected:
        std::set<Artist*> _casting; // do not save
    private:
        
};

#endif // DVD_H

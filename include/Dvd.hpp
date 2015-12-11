#ifndef DVD_H
#define DVD_H

#include "Cd.hpp"
#include "Artist.hpp"

class Dvd : public Cd
{
    private:
        static std::string _dbTable;

    protected:
        std::set<Artist*> _casting; // do not save

    public:
        Dvd();
        Dvd(int id);
        virtual ~Dvd();

        std::set<Artist*> getCasting() const; // TODO
        void addCasting(Artist* artist);

        bool save();
        bool remove();

        friend std::ostream& operator<< (std::ostream& stream, const Dvd& dvd);
        friend std::istream& operator>> (std::istream& stream, Dvd& dvd);
};

#endif // DVD_H

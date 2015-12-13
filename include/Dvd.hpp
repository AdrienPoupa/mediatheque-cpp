#ifndef DVD_H
#define DVD_H

#include <vector>

#include "Cd.hpp"
#include "Artist.hpp"

class Dvd : public Cd
{
    private:
        static std::string _dbTable;

    protected:
        std::vector<int> _casting; // do not save

    public:
        Dvd();
        Dvd(int id);
        virtual ~Dvd();

        std::vector<int> getCasting() const;
        void addCasting(int artistId);
        void deleteCasting();

        bool save();
        bool remove();

        friend std::ostream& operator<< (std::ostream& stream, Dvd& dvd);
        friend std::istream& operator>> (std::istream& stream, Dvd& dvd);
};

#endif // DVD_H

#ifndef CD_HPP
#define CD_HPP

#include "Artist.hpp"
#include "Article.hpp"

class Cd : public Article
{
    private:
        static std::string _dbTable;

    protected:
        std::string _studio; // save
        unsigned int _length; // save

    public:
        Cd();
        Cd(int id);
        virtual ~Cd();

        std::string getStudio() const;
        void setStudio(const std::string& studio);

        unsigned int getLength() const;
        void setLength(const unsigned int& length);

        bool save();
        bool remove();

        friend std::ostream& operator<< (std::ostream& stream, const Cd& cd);
        friend std::istream& operator>> (std::istream& stream, Cd& cd);
};

#endif // CD_HPP

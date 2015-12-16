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
    
        void deserialization(std::map<std::string, std::string> data);

        std::string getStudio() const;
        void setStudio(const std::string& studio);

        unsigned int getLength() const;
        void setLength(const unsigned int& length);

        bool save();
        bool remove();

        friend std::ostream& operator<< (std::ostream& stream, Cd& cd);
        friend std::istream& operator>> (std::istream& stream, Cd& cd);
};

#endif // CD_HPP

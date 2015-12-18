#include "Util.hpp"

using namespace std;

bool Util::checkInput(istream& stream, const int intToCheck, const int minValue)
{
    return !(stream.fail() || intToCheck < minValue); //"Merci d'entrer un choix valide"
}

bool Util::isFilterableType(int type)
{
    return type == Util::Types::Book || type == Util::Types::Cd || type == Util::Types::Dvd || type == Util::Types::Transaction;
}

string Util::fillWithDash(unsigned long length){
    string dash = "";
    for(unsigned long i = 0; i < length; i++){
        dash += "-";
    }
    return dash;
}

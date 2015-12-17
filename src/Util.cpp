#include "Util.hpp"

using namespace std;

bool Util::checkInput(istream& stream, const int intToCheck, const int minValue)
{
    return !(stream.fail() || intToCheck < minValue); //"Merci d'entrer un choix valide"
}

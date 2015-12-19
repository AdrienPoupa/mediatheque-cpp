#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "Library.hpp"

using namespace std;

int main()
{
    try
    {
        Library * libraryOfAlexandria = Library::getSingleton();

        libraryOfAlexandria->run();

        delete libraryOfAlexandria;
    }
    catch (const exception& e)
    {
        cout << e.what() << endl;
    }
}

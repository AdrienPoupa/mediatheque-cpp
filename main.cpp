#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "Library.hpp"

using namespace std;

int main()
{
    Library *towerOfBabel = Library::getSingleton();

    try
    {
        towerOfBabel->open();
    }
    catch (const std::invalid_argument& e)
    {
        cout << e.what() << endl;
    }

    delete towerOfBabel;
}

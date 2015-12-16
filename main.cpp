#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "Library.hpp"

using namespace std;

int main()
{
    
    try{
        Library * towerOfBabel = Library::getSingleton();
        
        towerOfBabel->open();
        
        delete towerOfBabel;
    }
    catch (const exception& e)
    {
        cout << e.what() << endl;
    }
}

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "sqlite/SQLiteCpp.h"
#include "BaseModel.hpp"
#include "Book.hpp"
#include "Cd.hpp"
#include "Dvd.hpp"
#include "Date.hpp"
#include "Address.hpp"
#include "Artist.hpp"
#include "User.hpp"
#include "User.hpp"
#include "Transaction.hpp"
#include "sha256.h"
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

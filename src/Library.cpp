#include "Library.hpp"

using namespace std;

Library* Library::singleton = NULL;

Library* Library::getSingleton()
{
    if (singleton == NULL) {
        singleton = new Library();
    }

    return singleton;
}

Library::Library()
{
    cout << "Initializing Library ..." << endl;
    cout << "Loading data ..." << endl;
    cout << "Generating Articles ..." << endl;
    cout << "Generating Person ..." << endl;
}

Library::~Library()
{
    singleton = NULL;
}

void Library::open()
{
    cout << "Ouverture de la mediatheque." << endl;
    cout << "Liste des comptes disponibles pour l'ouverture:" << endl;

    map<int, map<string, string>> users = BaseModel::select("users", "id, name, surname");

    // Iterator, C++11 style :-)
    // http://stackoverflow.com/questions/4844886/how-to-loop-through-a-c-map
    for(auto const &ent1 : users)
    {
        for(auto const &ent2 : ent1.second)
        {
            cout << ent2.second << " ";
        }
        cout << endl;
    }

    cout << "Saisissez le numero du compte a ouvrir" << endl;
    int accountToOpen;
    cin >> accountToOpen;

    User test(accountToOpen);
    cout << test;
}

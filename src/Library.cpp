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
    int idToOpen;
    cin >> idToOpen;

    User accountToOpen(idToOpen);
    _currentUser = accountToOpen;

    cout << "Identification: rentrez votre mot de passe" << endl;
    string inputPassword;
    cin >> inputPassword;

    if (_currentUser.checkPassword(inputPassword))
    {
        cout << "Identification reussie!" << endl;
        displayMenu();
    }
    else
    {
        cout << "Identification ratee" << endl;
    }
}

void Library::displayMenu()
{
    int choice;

    cout << endl;
    cout << "Menu : tapez le numero de l'action choisie" << endl;
    cout << "1. Liste des livres" << endl;
    cout << "2. Liste des dvds" << endl;
    cout << "3. Liste des cds" << endl;
    cout << "4. Restituer un emprunt" << endl;

    if (_currentUser.isAdmin())
    {
        cout << endl << "Menu Administrateur" << endl;
        cout << "5. Liste des utilisateurs" << endl;
        cout << "6. Emprunts en cours" << endl;
    }

    cin >> choice;
    redirectChoice(choice);
}

void Library::redirectChoice(int choice)
{

}

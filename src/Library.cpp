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

bool Library::isAdmin()
{
    return _currentUser.isAdmin();
}

void Library::open()
{
    cout << "Ouverture de la mediatheque." << endl;
    cout << "Liste des comptes disponibles pour l'ouverture:" << endl;

    map<int, map<string, string>> users = BaseModel::select("users", "id, name, surname");

    int totalUsers = users.size();

    for (int i = 1; i != totalUsers + 1; i++)
    {
        cout << users[i]["id"] << ". " << users[i]["name"] << " " << users[i]["surname"] << endl;
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
    cout << "4. Emprunter un article" << endl;
    cout << "5. Restituer un emprunt" << endl;

    if (isAdmin())
    {
        cout << endl << "Menu Administrateur" << endl;
        cout << "6. Liste des utilisateurs" << endl;
        cout << "7. Ajouter un utilisateur" << endl;
        cout << "8. Supprimer un utilisateur" << endl;
        cout << "9. Emprunts en cours" << endl;
    }

    cin >> choice;
    redirectChoice(choice);
}

void Library::redirectChoice(int choice)
{
    switch (choice)
    {
        // User action
        case 1:
            bookList();
            break;
        case 2:
            dvdList();
            break;
        case 3:
            cdList();
            break;
        case 4:
            borrowArticle();
            break;
        case 5:
            returnArticle();
            break;
        // Admin action - we need an extra check
        case 6:
            (isAdmin()) ? userList() : displayMenu();
            break;
        case 7:
            (isAdmin()) ? addUser() : displayMenu();
            break;
        case 8:
            (isAdmin()) ? deleteUser() : displayMenu();
            break;
        case 9:
            (isAdmin()) ? listTransactions() : displayMenu();
            break;
        default:
            (isAdmin()) ? displayMenu() : displayMenu();
            break;
    }
}

void Library::bookList()
{
    cout << "Liste des livres dans la mediatheque:" << endl;

    map<int, map<string, string>> books = BaseModel::select("books", "id, title, author, release");

    int totalBooks = books.size();

    if (totalBooks == 0)
    {
        cout << "Aucun livre dans la mediatheque" << endl;
        return;
    }

    for (int i = 1; i != totalBooks + 1; i++)
    {
        Artist writer(stoi(books[i]["author"]));
        Date release(books[i]["release"]);
        cout << books[i]["id"] << ". " << books[i]["title"] << " (" << release << ") par " << writer.getFirstName() << " " << writer.getLastName() << endl;
    }
}

void Library::dvdList()
{
    cout << "Liste des dvds dans la mediatheque:" << endl;

    map<int, map<string, string>> dvds = BaseModel::select("dvds", "id, title, director, release");

    int totalDvds = dvds.size();

    if (totalDvds == 0)
    {
        cout << "Aucun dvd dans la mediatheque" << endl;
        return;
    }

    for (int i = 1; i != totalDvds + 1; i++)
    {
        Artist director(stoi(dvds[i]["director"]));
        Date release(dvds[i]["release"]);
        cout << dvds[i]["id"] << ". " << dvds[i]["title"] << " (" << release << ") par " << director.getFirstName() << " " << director.getLastName() << endl;
    }
}

void Library::cdList()
{
    cout << "Liste des cds dans la mediatheque:" << endl;

    map<int, map<string, string>> cds = BaseModel::select("cds", "id, title, artist, release");

    int totalCds = cds.size();

    if (totalCds == 0)
    {
        cout << "Aucun cd dans la mediatheque" << endl;
        return;
    }

    for (int i = 1; i != totalCds + 1; i++)
    {
        Artist singer(stoi(cds[i]["artist"]));
        Date release(cds[i]["release"]);
        cout << cds[i]["id"] << ". " << cds[i]["title"] << " (" << release << ") par " << singer.getFirstName() << " " << singer.getLastName() << endl;
    }
}

void Library::borrowArticle()
{

}

void Library::returnArticle()
{

}

void Library::userList()
{

}

void Library::addUser()
{

}

void Library::deleteUser()
{

}

void Library::listTransactions()
{

}


#include "Library.hpp"

using namespace std;

Library* Library::singleton = NULL;

Library* Library::getSingleton()
{
    if (singleton == NULL)
    {
        singleton = new Library();
    }

    return singleton;
}

Library::Library()
{
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
        cout << "9. Ajouter un livre" << endl;
        cout << "10. Ajouter un cd" << endl;
        cout << "11. Ajouter un dvd" << endl;
        cout << "12. Emprunts en cours" << endl;
    }

    cout << "42. Quitter" << endl;

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
            (isAdmin()) ? addBook() : displayMenu();
            break;
        case 10:
            (isAdmin()) ? addCd() : displayMenu();
            break;
        case 11:
            (isAdmin()) ? addDvd() : displayMenu();
            break;
        case 12:
            (isAdmin()) ? listTransactions() : displayMenu();
            break;
        case 42:
            return;
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

    int articleId;
    cout << "Pour voir un livre, puis le modifier ou le supprimer, tapez son ID, et 0 pour revenir au menu" << endl;
    cin >> articleId;
    seeBook(articleId);
}

void Library::seeBook(int bookId)
{
    if (bookId == 0)
    {
        displayMenu();
    }

    Book bookToDisplay(bookId);
    cout << bookToDisplay << endl;

    cout << "Voulez-vous modifier ce livre ? Tapez 'Oui' le cas echeant, 'Non' sinon" << endl;
    string choice;
    cin >> choice;

    if (choice == "Oui")
    {
        editBook(bookToDisplay);
    }

    cout << "Voulez-vous supprimer ce livre ? Tapez 'Oui' le cas echeant, 'Non' sinon" << endl;
    string choice2;
    cin >> choice2;

    if (choice2 == "Oui")
    {
        bookToDisplay.remove();
    }

    displayMenu();
}

void Library::addBook()
{
    Book myNewBook;
    cin >> myNewBook;
    myNewBook.save();

    displayMenu();
}

void Library::editBook(Book& book)
{
    // TODO
    displayMenu();
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

    int articleId;
    cout << "Pour voir un dvd, puis le modifier ou le supprimer, tapez son ID, et 0 pour revenir au menu" << endl;
    cin >> articleId;
    seeDvd(articleId);
}

void Library::seeDvd(int dvdId)
{
    if (dvdId == 0)
    {
        displayMenu();
    }

    Dvd dvdToDisplay(dvdId);
    cout << dvdToDisplay << endl;

    cout << "Voulez-vous modifier ce DVD ? Tapez 'Oui' le cas echeant, 'Non' sinon" << endl;
    string choice;
    cin >> choice;

    if (choice == "Oui")
    {
        editDvd(dvdToDisplay);
    }

    cout << "Voulez-vous supprimer ce DVD ? Tapez 'Oui' le cas echeant, 'Non' sinon" << endl;
    string choice2;
    cin >> choice2;

    if (choice2 == "Oui")
    {
        dvdToDisplay.remove();
    }

    displayMenu();
}

void Library::addDvd()
{
    Dvd myNewDvd;
    cin >> myNewDvd;
    myNewDvd.save();

    displayMenu();
}

void Library::editDvd(Dvd& dvd)
{
    // TODO
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

    int articleId;
    cout << "Pour voir un cd, puis le modifier ou le supprimer, tapez son ID, et 0 pour revenir au menu" << endl;
    cin >> articleId;
    seeCd(articleId);
}

void Library::seeCd(int cdId)
{
    if (cdId == 0)
    {
        displayMenu();
    }

    Cd cdToDisplay(cdId);
    cout << cdToDisplay << endl;

    cout << "Voulez-vous modifier ce CD ? Tapez 'Oui' le cas echeant, 'Non' sinon" << endl;
    string choice;
    cin >> choice;

    if (choice == "Oui")
    {
        editCd(cdToDisplay);
    }

    cout << "Voulez-vous supprimer ce CD ? Tapez 'Oui' le cas echeant, 'Non' sinon" << endl;
    string choice2;
    cin >> choice2;

    if (choice2 == "Oui")
    {
        cdToDisplay.remove();
    }

    displayMenu();
}

void Library::addCd()
{
    Cd myNewCd;
    cin >> myNewCd;
    myNewCd.save();

    displayMenu();
}

void Library::editCd(Cd& cd)
{
    // TODO
}

void Library::borrowArticle()
{
    displayMenu();
}

void Library::returnArticle()
{
    displayMenu();
}

void Library::userList()
{
    cout << "Liste des utilisateurs :" << endl << endl;

    map<int, map<string, string>> users = BaseModel::select("users");

    int i = 1;

    // Iterator, C++11 style :-)
    // http://stackoverflow.com/questions/4844886/how-to-loop-through-a-c-map
    for(auto const &ent1 : users)
    {
        cout << "Utilisateur " << i << endl;
        for(auto const &ent2 : ent1.second)
        {
            cout << ent2.first << " : " << ent2.second << " " << endl;
        }
        cout << endl;
        i++;
    }

    displayMenu();
}

void Library::addUser()
{
    User newUser;
    cin >> newUser;
    newUser.save();

    displayMenu();
}

void Library::editUser()
{
    // TODO
}

void Library::deleteUser()
{
    int userId;

    cout << "Rentrez l'ID de l'utilisateur a supprimer" << endl;
    cin >> userId;

    User userToDelete(userId);
    userToDelete.remove();

    displayMenu();
}

void Library::listTransactions()
{
    displayMenu();
}


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

    if (cin.fail() || idToOpen < 1)
    {
        cout << "Merci d'entrer un ID valide" << endl;
        return;
    }

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
        open();
    }
}

void Library::displayMenu()
{
    int choice;

    cout << endl;
    cout << "Menu : tapez le numero de l'action choisie" << endl;
    cout << "0. Quitter" << endl;
    cout << "1. Liste des livres" << endl;
    cout << "2. Liste des dvds" << endl;
    cout << "3. Liste des cds" << endl;
    cout << "4. Liste des artistes" << endl;
    cout << "5. Emprunter un article" << endl;
    cout << "6. Restituer un emprunt" << endl;

    if (isAdmin())
    {
        cout << endl << "Menu Administrateur" << endl;
        cout << "7. Liste des utilisateurs" << endl;
        cout << "8. Ajouter un utilisateur" << endl;
        cout << "9. Supprimer un utilisateur" << endl;
        cout << "10. Ajouter un livre" << endl;
        cout << "11. Ajouter un cd" << endl;
        cout << "12. Ajouter un dvd" << endl;
        cout << "13. Ajouter un artiste" << endl;
        cout << "14. Emprunts en cours" << endl;
    }

    cin >> choice;

    if (cin.fail() || choice < 0)
    {
        cout << "Merci d'entrer un choix valide" << endl;
        return;
    }

    redirectChoice(choice);
}

void Library::redirectChoice(int choice)
{
    switch (choice)
    {
        // User action
        case 0:
            return;
            break;
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
            artistList();
            break;
        case 5:
            borrowArticle();
            break;
        case 6:
            returnArticle();
            break;
        // Admin action - we need an extra check
        case 7:
            (isAdmin()) ? userList() : displayMenu();
            break;
        case 8:
            (isAdmin()) ? addThing<User>() : displayMenu();
            break;
        case 9:
            (isAdmin()) ? deleteUser() : displayMenu();
            break;
        case 10:
            (isAdmin()) ? addThing<Book>() : displayMenu();
            break;
        case 11:
            (isAdmin()) ? addThing<Cd>() : displayMenu();
            break;
        case 12:
            (isAdmin()) ? addThing<Dvd>() : displayMenu();
            break;
        case 13:
            (isAdmin()) ? addThing<Artist>() : displayMenu();
            break;
        case 14:
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

    int articleId;
    cout << "Pour voir un livre, puis le modifier ou le supprimer, tapez son ID, et 0 pour revenir au menu" << endl;
    cin >> articleId;

    if (cin.fail() || articleId < 0)
    {
        cout << "Merci d'entrer un ID valide" << endl;
        return;
    }

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

    if (isAdmin())
    {
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
    }

    displayMenu();
}

void Library::editBook(Book& book)
{
    cout << "Modification d'un livre" << endl;

    cout << "1. Modifier l'auteur" << endl;
    cout << "2. Modifier le titre" << endl;
    cout << "3. Modifier la date de sortie" << endl;
    cout << "4. Modifier le nombre de pages" << endl;
    cout << "5. Modifier l'editeur" << endl;
    cout << "6. Modifier les genres" << endl;

    int choice;
    cin >> choice;

    if (cin.fail() || choice < 1)
    {
        cout << "Merci d'entrer un choix valide" << endl;
        return;
    }

    switch (choice)
    {
        case 1:
        {
            int newArtist;
            cin >> newArtist;

            if (cin.fail() || newArtist < 1)
            {
                cout << "Merci d'entrer un ID valide" << endl;
                return;
            }

            book.setAuthorId(newArtist);
            break;
        }
        case 2:
        {
            string newTitle;
            cin.ignore(1, '\n');
            getline(cin, newTitle, '\n');
            book.setTitle(newTitle);
            break;
        }
        case 3:
        {
            Date newReleaseDate;
            cin >> newReleaseDate;
            book.setRelease(newReleaseDate);
            break;
        }
        case 4:
        {
            int newPages;
            cin >> newPages;

            if (cin.fail() || newPages < 1)
            {
                cout << "Merci d'entrer un nombre de pages valide" << endl;
                return;
            }

            book.setPages(newPages);
            break;
        }
        case 5:
        {
            string newEditor;
            cin.ignore(1, '\n');
            getline(cin, newEditor, '\n');
            book.setEditor(newEditor);
            break;
        }
        case 6:
        {
            int genre1 = 0, genre2 = 0;

            cout << "ID genre 1" << endl;
            cin >> genre1;
            if (cin.fail() || genre1 < 1)
            {
                cout << "Merci d'entrer un ID" << endl;
                return;
            }

            book.addGenre(genre1);

            cout << "ID genre 2" << endl;
            cin >> genre2;
            if (cin.fail() || genre1 < 1)
            {
                cout << "Merci d'entrer un ID" << endl;
                return;
            }

            book.addGenre(genre2);

            break;
        }
        default:
            editBook(book);
            break;
    }

    cout << "Sauvegarde..." << endl;
    book.save();
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

    if (cin.fail() || articleId < 0)
    {
        cout << "Merci d'entrer un ID valide" << endl;
        return;
    }

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

    if (isAdmin())
    {
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
    }

    displayMenu();
}

void Library::editDvd(Dvd& dvd)
{
    cout << "Modification d'un DVD" << endl;

    cout << "1. Modifier le realisateur" << endl;
    cout << "2. Modifier le titre" << endl;
    cout << "3. Modifier la date de sortie" << endl;
    cout << "4. Modifier la duree" << endl;
    cout << "5. Modifier le studio" << endl;
    cout << "6. Modifier les genres" << endl;

    int choice;
    cin >> choice;

    if (cin.fail() || choice < 1)
    {
        cout << "Merci d'entrer un choix valide" << endl;
        return;
    }

    switch (choice)
    {
        case 1:
        {
            int newArtist;
            cin >> newArtist;

            if (cin.fail() || newArtist < 1)
            {
                cout << "Merci d'entrer un ID valide" << endl;
                return;
            }

            dvd.setAuthorId(newArtist);
            break;
        }
        case 2:
        {
            string newTitle;
            cin.ignore(1, '\n');
            getline(cin, newTitle, '\n');
            dvd.setTitle(newTitle);
            break;
        }
        case 3:
        {
            Date newReleaseDate;
            cin >> newReleaseDate;
            dvd.setRelease(newReleaseDate);
            break;
        }
        case 4:
        {
            int newLength;
            cin >> newLength;

            if (cin.fail() || newLength < 1)
            {
                cout << "Merci d'entrer une duree valide" << endl;
                return;
            }

            dvd.setLength(newLength);
            break;
        }
        case 5:
        {
            string newStudio;
            cin.ignore(1, '\n');
            getline(cin, newStudio, '\n');
            dvd.setStudio(newStudio);
            break;
        }
        case 6:
        {
            int genre1 = 0, genre2 = 0;

            cout << "ID genre 1" << endl;
            cin >> genre1;
            if (cin.fail() || genre1 < 1)
            {
                cout << "Merci d'entrer un ID" << endl;
                return;
            }

            dvd.addGenre(genre1);

            cout << "ID genre 2" << endl;
            cin >> genre2;
            if (cin.fail() || genre1 < 1)
            {
                cout << "Merci d'entrer un ID" << endl;
                return;
            }

            dvd.addGenre(genre2);

            break;
        }
        default:
            editDvd(dvd);
            break;
    }

    cout << "Sauvegarde..." << endl;
    dvd.save();
    displayMenu();
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

    if (cin.fail() || articleId < 0)
    {
        cout << "Merci d'entrer un ID valide" << endl;
        return;
    }

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

    if (isAdmin())
    {
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
    }

    displayMenu();
}

void Library::editCd(Cd& cd)
{
    cout << "Modification d'un CD" << endl;

    cout << "1. Modifier l'artiste" << endl;
    cout << "2. Modifier le titre" << endl;
    cout << "3. Modifier la date de sortie" << endl;
    cout << "4. Modifier la duree" << endl;
    cout << "5. Modifier le studio" << endl;
    cout << "6. Modifier les genres" << endl;

    int choice;
    cin >> choice;

    if (cin.fail() || choice < 1)
    {
        cout << "Merci d'entrer un choix valide" << endl;
        return;
    }

    switch (choice)
    {
        case 1:
        {
            int newArtist;
            cin >> newArtist;

            if (cin.fail() || newArtist < 1)
            {
                cout << "Merci d'entrer un ID valide" << endl;
                return;
            }

            cd.setAuthorId(newArtist);
            break;
        }
        case 2:
        {
            string newTitle;
            cin.ignore(1, '\n');
            getline(cin, newTitle, '\n');
            cd.setTitle(newTitle);
            break;
        }
        case 3:
        {
            Date newReleaseDate;
            cin >> newReleaseDate;
            cd.setRelease(newReleaseDate);
            break;
        }
        case 4:
        {
            int newLength;
            cin >> newLength;

            if (cin.fail() || newLength < 1)
            {
                cout << "Merci d'entrer une duree valide" << endl;
                return;
            }

            cd.setLength(newLength);
            break;
        }
        case 5:
        {
            string newStudio;
            cin.ignore(1, '\n');
            getline(cin, newStudio, '\n');
            cd.setStudio(newStudio);
            break;
        }
        case 6:
        {
            int genre1 = 0, genre2 = 0;

            cout << "ID genre 1" << endl;
            cin >> genre1;
            if (cin.fail() || genre1 < 1)
            {
                cout << "Merci d'entrer un ID" << endl;
                return;
            }

            cd.addGenre(genre1);

            cout << "ID genre 2" << endl;
            cin >> genre2;
            if (cin.fail() || genre1 < 1)
            {
                cout << "Merci d'entrer un ID" << endl;
                return;
            }

            cd.addGenre(genre2);

            break;
        }
        default:
            editCd(cd);
            break;
    }

    cout << "Sauvegarde..." << endl;
    cd.save();
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

    int userId;
    cout << "Pour modifier un utilisateur, tapez son ID, et 0 pour revenir au menu" << endl;
    cin >> userId;

    if (cin.fail() || userId < 0)
    {
        cout << "Merci d'entrer un ID valide" << endl;
        return;
    }

    editUser(userId);
}

template <class T>
void Library::addThing()
{
    T newThing;
    cin >> newThing;
    newThing.save();

    displayMenu();
}

void Library::editUser(int userId)
{
    if (userId == 0)
    {
        displayMenu();
    }

    User userToEdit(userId);

    cout << "Modification d'un utilisateur" << endl;

    cout << "1. Modifier le prenom" << endl;
    cout << "2. Modifier le nom" << endl;
    cout << "3. Modifier le telephone" << endl;
    cout << "4. Modifier la date de naissance" << endl;
    cout << "5. Modifier l'adresse" << endl;
    cout << "6. Modifier le type de compte" << endl;
    cout << "7. Modifier le nombre d'emprunts simultanes" << endl;
    cout << "8. Modifier le mot de passe" << endl;

    int choice;
    cin >> choice;

    if (cin.fail() || choice < 1)
    {
        cout << "Merci d'entrer un choix valide" << endl;
        return;
    }

    switch (choice)
    {
        case 1:
        {
            string newName;
            cin.ignore(1, '\n');
            getline(cin, newName, '\n');
            userToEdit.setFirstName(newName);
            break;
        }
        case 2:
        {
            string newLastName;
            cin.ignore(1, '\n');
            getline(cin, newLastName, '\n');
            userToEdit.setLastName(newLastName);
            break;
        }
        case 3:
        {
            string newPhone;
            cin.ignore(1, '\n');
            getline(cin, newPhone, '\n');
            userToEdit.setPhone(newPhone);
            break;
        }
        case 4:
        {
            Date newBirthDate;
            cin >> newBirthDate;
            userToEdit.setBirthDate(newBirthDate);
            break;
        }
        case 5:
        {
            Address newAddress;
            cin >> newAddress;
            userToEdit.setAddress(newAddress);
            break;
        }
        case 6:
        {
            int newIsAdmin;
            cout << "Tapez 0 pour un utilisateur lambda, 1 pour un administrateur" << endl;
            cin >> newIsAdmin;
            userToEdit.setAdmin(newIsAdmin);
            break;
        }
        case 7:
        {
            int newQuota;
            cin >> newQuota;
            if (cin.fail() || newQuota < 0)
            {
                cout << "Merci d'entrer un choix valide" << endl;
                return;
            }
            userToEdit.setQuota(newQuota);
            break;
        }
        case 8:
        {
            string newPassword;
            cin.ignore(1, '\n');
            getline(cin, newPassword, '\n');
            userToEdit.setPassword(newPassword);
            break;
        }
        default:
            editUser(userId);
            break;
    }

    cout << "Sauvegarde..." << endl;
    userToEdit.save();
    displayMenu();
}

void Library::deleteUser()
{
    unsigned int userId;

    cout << "Rentrez l'ID de l'utilisateur a supprimer" << endl;
    cin >> userId;

    if (cin.fail() || userId < 1)
    {
        cout << "Merci d'entrer un ID valide" << endl;
        return;
    }

    if (userId != _currentUser.getId())
    {
        User userToDelete(userId);
        userToDelete.remove();
    }
    else
    {
        cout << "Vous ne pouvez pas vous supprimer vous-meme !" << endl;
    }

    displayMenu();
}

void Library::artistList()
{
    cout << "Liste des artistes de la mediatheque:" << endl;

    map<int, map<string, string>> artists = BaseModel::select("artists", "id, name, surname");

    int totalArtists = artists.size();

    if (totalArtists == 0)
    {
        cout << "Aucun artiste dans la mediatheque" << endl;
        return;
    }

    for (int i = 1; i != totalArtists + 1; i++)
    {
        cout << artists[i]["id"] << ". " << artists[i]["name"] << " " << artists[i]["surname"] << endl;
    }

    int artistId;
    cout << "Pour voir un artiste, puis le modifier ou le supprimer, tapez son ID, et 0 pour revenir au menu" << endl;
    cin >> artistId;

    if (cin.fail() || artistId < 0)
    {
        cout << "Merci d'entrer un ID valide" << endl;
        return;
    }

    seeArtist(artistId);
}

void Library::seeArtist(int artistId)
{
    if (artistId == 0)
    {
        displayMenu();
    }

    Artist artistToDisplay(artistId);
    cout << artistToDisplay << endl;

    if (isAdmin())
    {
        cout << "Voulez-vous modifier cet artiste ? Tapez 'Oui' le cas echeant, 'Non' sinon" << endl;
        string choice;
        cin >> choice;

        if (choice == "Oui")
        {
            editArtist(artistToDisplay);
        }

        cout << "Voulez-vous supprimer cet artiste ? Tapez 'Oui' le cas echeant, 'Non' sinon" << endl;
        string choice2;
        cin >> choice2;

        if (choice2 == "Oui")
        {
            artistToDisplay.remove();
        }
    }

    biography(artistToDisplay);
    discography(artistToDisplay);
    filmography(artistToDisplay);

    displayMenu();
}

void Library::biography(Artist& artist)
{
    cout << "Biographie de " << artist.getFirstName() << " " << artist.getLastName() << endl;

    map<int, map<string, string>> bibliography = BaseModel::select("books", "id, title, author, release", "WHERE author=" + to_string(artist.getId()));

    int totalBooks = bibliography.size();

    if (totalBooks == 0)
    {
        cout << "Aucun livre dans la mediatheque" << endl;
        return;
    }

    for (int i = 1; i != totalBooks + 1; i++)
    {
        Artist writer(stoi(bibliography[i]["author"]));
        Date release(bibliography[i]["release"]);
        cout << bibliography[i]["id"] << ". " << bibliography[i]["title"] << " (" << release << ")" << endl;
    }
}

void Library::discography(Artist& artist)
{
    cout << "Discographie de " << artist.getFirstName() << " " << artist.getLastName() << endl;

    map<int, map<string, string>> cds = BaseModel::select("cds", "id, title, release", "WHERE artist=" + to_string(artist.getId()));

    int totalCds = cds.size();

    if (totalCds == 0)
    {
        cout << "Aucun cd dans la mediatheque" << endl;
        return;
    }

    for (int i = 1; i != totalCds + 1; i++)
    {
        Date release(cds[i]["release"]);
        cout << cds[i]["id"] << ". " << cds[i]["title"] << " (" << release << ")" << endl;
    }
}

void Library::filmography(Artist& artist)
{
    cout << "Filmographie de " << artist.getFirstName() << " " << artist.getLastName() << endl;

    map<int, map<string, string>> dvds = BaseModel::select("dvds", "id, title, release", "WHERE director=" + to_string(artist.getId()));

    int totalDvds = dvds.size();

    if (totalDvds == 0)
    {
        cout << "Aucun dvd dans la mediatheque" << endl;
        return;
    }

    for (int i = 1; i != totalDvds + 1; i++)
    {
        Date release(dvds[i]["release"]);
        cout << dvds[i]["id"] << ". " << dvds[i]["title"] << " (" << release << ")" << endl;
    }
}

void Library::editArtist(Artist& artist)
{
    cout << "Modification d'un artiste" << endl;

    cout << "1. Modifier le prenom" << endl;
    cout << "2. Modifier le nom" << endl;
    cout << "3. Modifier la date de naissance" << endl;
    cout << "4. Modifier la nationalite" << endl;

    int choice;
    cin >> choice;

    if (cin.fail() || choice < 1)
    {
        cout << "Merci d'entrer un choix valide" << endl;
        return;
    }

    switch (choice)
    {
        case 1:
        {
            string newName;
            cin.ignore(1, '\n');
            getline(cin, newName, '\n');
            artist.setFirstName(newName);
            break;
        }
        case 2:
        {
            string newLastName;
            cin.ignore(1, '\n');
            getline(cin, newLastName, '\n');
            artist.setLastName(newLastName);
            break;
        }
        case 3:
        {
            Date newBirthDate;
            cin >> newBirthDate;
            artist.setBirthDate(newBirthDate);
            break;
        }
        case 4:
        {
            string newNationality;
            cin.ignore(1, '\n');
            getline(cin, newNationality, '\n');
            artist.setNationality(newNationality);
            break;
        }
        default:
            editArtist(artist);
            break;
    }

    cout << "Sauvegarde..." << endl;
    artist.save();
    displayMenu();
}

void Library::borrowArticle()
{
    // TODO
    displayMenu();
}

void Library::returnArticle()
{
    // TODO
    displayMenu();
}

void Library::listTransactions()
{
    // TODO
    displayMenu();
}


#include "Library.hpp"

using namespace std;

class NoDbException: public exception
{
    virtual const char* what() const throw()
    {
        return "No DB file available.";
    }
} NoDb;

Library* Library::singleton = NULL;

Library* Library::getSingleton()
{
    if (singleton == NULL)
    {
        // check if mediatheque.db3 exist
        ifstream mfile("mediatheque.db3");
        if (mfile)
        {
            singleton = new Library();
            mfile.close();
        }
        else
        {
            throw NoDb;
        }
    }

    return singleton;
}

Library::Library()
{
    cout << "Bienvenue dans votre mediatheque !" << endl;
}

Library::~Library()
{
    singleton = NULL;
}

bool Library::isAdmin()
{
    return _currentUser.isAdmin();
}

void Library::run()
{

    // connection
    bool connected = connect();

    if (!connected)
    {
        cout << "L'authentification a echoue." << endl;
        return;
    }
    // boucle tant que l'utilisateur ne quitte pas le programme
    bool quit = false;

    while(!quit)
    {
        int choice = displayMenu();
        if (choice)
            redirectChoice(choice);
        else
            quit = true;
    }

    cout << "A bientot !" << endl;
}

bool Library::connect()
{
    map<int, map<string, string>> users = BaseModel::select("users", "id, name, surname");

    int totalUsers = (int)users.size();

    int idToOpen;
    set<int> userIds = set<int>();
    bool correctId = false;

    do{
        cout << "Liste des comptes disponibles pour l'ouverture:" << endl;
        for (int i = 1; i != totalUsers + 1; i++)
        {
            cout << users[i]["id"] << ". " << users[i]["name"] << " " << users[i]["surname"] << endl;
            userIds.insert(stoi(users[i]["id"]));
        }

        cout << "Saisissez le numero du compte a ouvrir" << endl;
        cin >> idToOpen;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            correctId = userIds.find(idToOpen) != userIds.end();
        }
        
        if (!correctId)
        {
            cout << "Identifiant inconnu ..." << endl;
        }

    } while(!correctId);

    User accountToOpen(idToOpen);
    _currentUser = accountToOpen;

    int essai = 3;
    bool correctPass = false;
    while(!correctPass && essai > 0)
    {
        cout << "Identification: rentrez votre mot de passe" << endl;
        string inputPassword;
        cin >> inputPassword;

        correctPass = _currentUser.checkPassword(inputPassword);
        essai--;

        if (correctPass)
        {
            cout << "Identification reussie!" << endl;
        }
        else
        {
            cout << "Erreur dans votre mot de passe." << endl;
        }
    }
    return correctPass;
}

int Library::displayMenu()
{

    int choice;
    bool failInput = false;
    do
    {
        cout << endl;
        cout << "Menu : tapez le numero de l'action choisie" << endl;
        cout << "0. Quitter" << endl;
        cout << "1. Liste des livres" << endl;
        cout << "2. Liste des dvds" << endl;
        cout << "3. Liste des cds" << endl;
        cout << "4. Liste des artistes" << endl;
        cout << "5. Mes emprunts" << endl;
        cout << "6. Chercher un article" << endl;

        if (isAdmin())
        {
            cout << endl << "Menu Administrateur" << endl;
            cout << "7. Liste des utilisateurs" << endl;
            cout << "8. Ajouter un utilisateur" << endl;
            cout << "9. Ajouter un livre" << endl;
            cout << "10. Ajouter un cd" << endl;
            cout << "11. Ajouter un dvd" << endl;
            cout << "12. Ajouter un artiste" << endl;
            cout << "13. Emprunts en cours" << endl;
        }

        cout << "Choix: " << endl;
        cin >> choice;
        if(cin.fail()){
            failInput = true;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
    } while(failInput || choice < 0 || (!isAdmin() && choice > 6) || choice > 13);

    return choice;
}

void Library::redirectChoice(const int choice)
{
    switch (choice)
    {
        // User action
        case 0:
            return;
            break;
        case 1:
            getListEntity<Book>();
            break;
        case 2:
            getListEntity<Dvd>();
            break;
        case 3:
            getListEntity<Cd>();
            break;
        case 4:
            getListArticle<Artist>();
            break;
        case 5:
            borrowedMenu();
            break;
        case 6:
            searchList();
            break;
        // Admin action
        case 7:
            getListEntity<User>();
            break;
        case 8:
            addThing<User>();
            break;
        case 9:
            addThing<Book>();
            break;
        case 10:
            addThing<Cd>();
            break;
        case 11:
            addThing<Dvd>();
            break;
        case 12:
            addThing<Artist>();
            break;
        case 13:
            listTransactions();
            break;
        default:
            return;
            break;
    }
}

void Library::searchList()
{
    cout << "Rechercher dans la mediatheque : rentrez le titre de l'article recherche" << endl;
    string query;
    cin.ignore(1, '\n');
    getline(cin, query, '\n');

    cout << "Livres trouves" << endl;

    map<int, map<string, string>> bibliography = BaseModel::select("books", "id, title, author, release", "title LIKE '%" + query + "%'");

    int totalBooks = (int)bibliography.size();

    if (totalBooks == 0)
    {
        cout << "Aucun livre dans la mediatheque" << endl;
    }

    for (int i = 1; i != totalBooks + 1; i++)
    {
        Artist writer(stoi(bibliography[i]["author"]));
        Date release(bibliography[i]["release"]);
        cout << bibliography[i]["id"] << ". " << bibliography[i]["title"] << " (" << release << ")" << endl;
    }

    cout << "CDs trouves" << endl;

    map<int, map<string, string>> cds = BaseModel::select("cds", "id, title, release", "title LIKE '%" + query + "%'");

    int totalCds = (int)cds.size();

    if (totalCds == 0)
    {
        cout << "Aucun cd dans la mediatheque" << endl;
    }

    for (int i = 1; i != totalCds + 1; i++)
    {
        Date release(cds[i]["release"]);
        cout << cds[i]["id"] << ". " << cds[i]["title"] << " (" << release << ")" << endl;
    }

    cout << "DVDs trouves" << endl;

    map<int, map<string, string>> dvds = BaseModel::select("dvds", "id, title, release", "title LIKE '%" + query + "%'");

    int totalDvds = (int)dvds.size();

    if (totalDvds == 0)
    {
        cout << "Aucun dvd dans la mediatheque" << endl;
    }

    for (int i = 1; i != totalDvds + 1; i++)
    {
        Date release(dvds[i]["release"]);
        cout << dvds[i]["id"] << ". " << dvds[i]["title"] << " (" << release << ")" << endl;
    }

    // Action a proposer avec les resultats.
    /*
     On peut aussi demander les filtres avant, et faire differente fonction qui traite chaque table de la DB
     */
     return;
}

template <class T>
void Library::getListEntity(bool askEdit)
{
    map<int, vector<string>> liaison = {
        {Util::Types::Book, {"books", "id, title, author, release"}},
        {Util::Types::Cd, {"cds", "*"}},
        {Util::Types::Dvd, {"dvds", "*"}},
        {Util::Types::Artist, {"artists", "id, name, surname"}},
        {Util::Types::User, {"users", "*"}}
    };

    int type = 0;
    string typeStr;

    if (is_same<T, Cd>::value)
    {
        type = Util::Types::Cd;
        typeStr = Util::getTypesString(Util::Types::Cd);
    }
    else if (is_same<T, Dvd>::value)
    {
        type = Util::Types::Dvd;
        typeStr = Util::getTypesString(Util::Types::Dvd);
    }
    else if (is_same<T, Book>::value)
    {
        type = Util::Types::Book;
        typeStr = Util::getTypesString(Util::Types::Book);
    }
    else if(is_same<T, User>::value){
        type = Util::Types::User;
        typeStr = Util::getTypesString(Util::Types::User);
    }
    else if (is_same<T, Artist>::value)
    {
        type = Util::Types::Artist;
        typeStr = Util::getTypesString(Util::Types::Artist);
    }

    
    string filter = "borrowable=1";
    
    if(isAdmin() && type >= 0 && type <= 2){
        int choice;
        bool failInput = false;
        do {
            cout << "Filtres possibles:" << endl;
            cout << "1.Empruntables" << endl;
            cout << "2.Empruntes" << endl;
            cout << "3.Tous" << endl;
            cout << "0.Annuler" << endl;
            cout << "Choix: " << endl;
            cin >> choice;
            if(cin.fail()){
                failInput = true;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }while(failInput || choice < 0 || choice > 3);
        
        if(choice == 0) return;
        
        switch(choice){
            case 2:
                filter = "borrowable=0";
                break;
            case 3:
                filter = "";
                break;
            default:
                filter = "borrowable=1";
                break;
        }
    }
    
    cout << "Liste des " + typeStr + "s" + " dans la mediatheque:" << endl;

    map<int, map<string, string>> response = BaseModel::select(liaison.at(type)[0], liaison.at(type)[1], type < 3? filter : "");

    int totalCount = (int)response.size();

    if (totalCount == 0)
    {
        cout << "Aucun " + typeStr + " dans la mediatheque" << endl;
        return;
    }

    set<int> ids = set<int>();
    for (int i = 1; i != totalCount + 1; i++)
    {
        T tmp= T();
        tmp.init(response[i]);
        tmp.shortDisplay();
        ids.insert(stoi(response[i]["id"]));
    }

    int responseId;
    do{
        cout << "Pour voir un " + typeStr + ", puis le modifier ou le supprimer, tapez son ID, et 0 pour revenir au menu." << endl << "Choix: " << endl;
        cin >> responseId;
    } while(responseId != 0 && !(ids.find(responseId) != ids.end()));

    if(type != 4)
        seeArticle<T>(responseId);
    else
        editUser(responseId);
}

template <class T>
void Library::seeArticle(int id)
{
    void * art = nullptr;
    Article * artCast = nullptr;

    if (id == 0)
    {
        return;
    }

    Util::Types type = Util::Types::Book;

    if (is_same<T, Cd>::value)
    {
        type = Util::Types::Cd;
        artCast = static_cast<Cd*>(art);
        artCast = new Cd(id);
    }
    else if (is_same<T, Dvd>::value)
    {
        type = Util::Types::Dvd;
        artCast = static_cast<Dvd*>(art);
        artCast = new Dvd(id);
    }
    else if (is_same<T, Book>::value)
    {
        type = Util::Types::Book;
        artCast = static_cast<Book*>(art);
        artCast = new Book(id);
    }
    
    cout << art << endl;

    T tmp(id);
    cout << tmp << endl;

    if (artCast != nullptr && artCast->getBorrowable())
    {
        if (affichageChoixSee("emprunter", Util::getTypesString(type)))
        {
            borrowArticle(artCast, type);
        }
    }

    if (isAdmin())
    {
        if (affichageChoixSee("modifier", Util::getTypesString(type)))
        {
            tmp.edit();
        }

        if (affichageChoixSee("supprimer", Util::getTypesString(type)))
        {
            tmp.remove();
        }
    }
    return;
}

template <class T>
void Library::addThing()
{
    T newThing;
    cin >> newThing;
    newThing.save();

    return;
}

bool Library::affichageChoixSee(const string typeChoix, const string typeArticle) const
{

    string choice = "";
    do {
        cout << "Voulez-vous " + typeChoix + " ce " + typeArticle + " ? Tapez 'o' le si oui, 'n' sinon" << endl;
        cin >> choice;
    } while(choice != "o" && choice !="n");

    return choice == "o";
}

void Library::userList()
{
    cout << "Liste des utilisateurs :" << endl << endl;

    map<int, map<string, string>> users = BaseModel::select("users", "id");

    int totalUsers = (int)users.size();

    map<int, User> userIds = map<int, User>();
    for (int i = 1; i != totalUsers + 1; i++)
    {
        User tmp(stoi(users[i]["id"]));
        cout << tmp << endl;
        userIds.insert(pair<int, User>(tmp.getId(), tmp));
    }

    int userId;
    do {
        cout << "Pour modifier un utilisateur, tapez son ID, et 0 pour revenir au menu: " << endl;
        cin >> userId;
    } while(userIds.find(userId) == userIds.end() && userId != 0);

    if (userId == 0) return;

    editUser(userId);
}

void Library::editUser(int userId)
{
    if (userId == 0)
    {
        return;
    }

    User userToEdit(userId);

    int choice;
    bool failInput = false;
    do {
        cout << "Modification d'un utilisateur" << endl;

        cout << "1. Modifier le prenom" << endl;
        cout << "2. Modifier le nom" << endl;
        cout << "3. Modifier le telephone" << endl;
        cout << "4. Modifier la date de naissance" << endl;
        cout << "5. Modifier l'adresse" << endl;
        cout << "6. Modifier le type de compte" << endl;
        cout << "7. Modifier le nombre d'emprunts simultanes" << endl;
        cout << "8. Modifier le mot de passe" << endl;
        cout << "9. Supprimer l'utilisateur" << endl;
        cout << "0. Annuler" << endl;

        cout << "Choix: ";
        cin >> choice;
        if(cin.fail()){
            failInput = true;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while(failInput || choice < 0 || choice > 9);

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
            Util::checkInput(cin, newIsAdmin, 0);
            userToEdit.setAdmin(newIsAdmin);
            break;
        }
        case 7:
        {
            int newQuota;
            cin >> newQuota;
            Util::checkInput(cin, newQuota, 0);
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
        case 9:{
            deleteUser(userId);
            break;
        }
        default:
            return;
            break;
    }

    if (choice != 9 && choice != 0 )
    {
        cout << "Sauvegarde..." << endl;
        userToEdit.save();
    }

    return;
}

void Library::deleteUser(const unsigned int userId)
{

    if (userId != _currentUser.getId())
    {
        User userToDelete(userId);
        userToDelete.remove();
    }
    else
    {
        cout << "Vous ne pouvez pas vous supprimer vous-meme !" << endl;
    }
    return;
}

void Library::borrowedMenu()
{
    cout << "Mes emprunts en cours" << endl;

    map<int, map<string, string>> transactions = BaseModel::select("transactions", "*", "borrower_id=" + to_string(_currentUser.getId()) +" AND returned=0");

    int totalCount = (int)transactions.size();

    if (totalCount == 0)
    {
        cout << "Aucun emprunt en cours" << endl;
        return;
    }

    set<int> ids = set<int>();
    map<int, Transaction> trs = map<int, Transaction>();
    for (int i = 1; i != totalCount + 1; i++)
    {
        Transaction tmp = Transaction();
        tmp.init(transactions[i]);
        tmp.shortDisplay();
        trs.insert(pair<int, Transaction>(tmp.getId(), tmp));
        ids.insert(tmp.getId());
    }

    int empruntId;
    do
    {
        cout << "Pour voir un emprunt, puis le modifier ou le supprimer, tapez son ID, et 0 pour revenir au menu." << endl << "Choix: " << endl;
        cin >> empruntId;
    } while(empruntId != 0 && !(ids.find(empruntId) != ids.end()));

    if (empruntId == 0) return;

    seeEmprunt(trs.at(empruntId));
}

void Library::seeEmprunt(Transaction tr, bool adminMode)
{
    if (adminMode)
    {
        // editTransaction
        cout << "fonctionnalite d'edition non disponible ..." << endl;
    }
    else if (affichageChoixSee("rendre", Util::getTypesString(Util::Types(tr.getType()))))
    {
        returnArticle(&tr);
    }
}

void Library::borrowArticle(Article* art, const int type)
{
    _currentUser.borrow(art, type);

    return;
}

void Library::returnArticle(Transaction *t)
{
    _currentUser.returnArticle(t);

    return;
}

void Library::listTransactions()
{
    /*
     recherche d'emprunts :
     # filtre:
        - fini/en cours/tous;
        - date
     */
    int choice;
    bool failInput = false;
    do{
        cout << "Emprunts: choix du filtre" << endl;
        cout << "1. En cours" << endl;
        cout << "2. Termines" << endl;
        cout << "3. Tous" << endl;
        cout << "0. Annuler" << endl;
        cout << "Choix: " << endl;
        cin >> choice;
        if(cin.fail()){
            failInput = true;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while(failInput || choice < 0 || choice > 3);

    if (choice == 0) return;

    string filter = "";
    switch(choice)
    {
        case 1:
            // En cours
            filter = "returned=0";
            break;
        case 2:
            // Termines
            filter = "returned=1";
            break;
        default:
            // Tous = No filter
            break;
    }

    map<int, map<string, string>> transactions = BaseModel::select("transactions", "*", filter);

    int totalCount = (int)transactions.size();

    if (totalCount == 0)
    {
        cout << "Aucun emprunt en cours" << endl;
        return;
    }

    set<int> ids = set<int>();
    map<int, Transaction> trs = map<int, Transaction>();
    for (int i = 1; i != totalCount + 1; i++)
    {
        Transaction tmp = Transaction();
        tmp.init(transactions[i]);
        tmp.shortDisplay();
        trs.insert(pair<int, Transaction>(tmp.getId(), tmp));
        ids.insert(tmp.getId());
    }

    int empruntId;
    do
    {
        cout << "Pour voir un emprunt, puis le modifier ou le supprimer, tapez son ID, et 0 pour revenir au menu." << endl << "Choix: " << endl;
        cin >> empruntId;
    } while(empruntId != 0 && !(ids.find(empruntId) != ids.end()));

    seeEmprunt(trs.at(empruntId), true);
}


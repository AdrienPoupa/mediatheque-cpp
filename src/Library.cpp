#include "Library.hpp"

using namespace std;

class NoDbException: public exception
{
    virtual const char* what() const throw()
    {
        return "Le fichier mediatheque.db3 n'est pas accessible.";
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
    system(CLEAN_SCREEN);
    cout << "######################################" << endl;
    cout << "#                                    #" << endl;
    cout << "# Bienvenue dans votre mediatheque ! #" << endl;
    cout << "#                                    #" << endl;
    cout << "#  Realise par:                      #" << endl;
    cout << "#          - Timothee Barbot         #" << endl;
    cout << "#          - Adrien Poupa            #" << endl;
    cout << "#          - Edgar Buob              #" << endl;
    cout << "#                                    #" << endl;
    cout << "#         Efrei L'3 2018             #" << endl;
    cout << "#                                    #" << endl;
    cout << "######################################" << endl;
    cout << endl;
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
    cout << endl << "Chargement en cours (2 sec)" << endl;
    std::this_thread::sleep_for(chrono::seconds(2));

    system(CLEAN_SCREEN);

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
        cout << "-------------------------------------------------------" << endl;
        cout << " -- Liste des comptes disponibles pour la connexion --" << endl;
        cout << " Identifiant | Prenom Nom " << endl;
        cout << "-------------|-------------------" << endl;
        for (int i = 1; i != totalUsers + 1; i++)
        {
            string space;
            for(unsigned int i = 0; i < (11 - users[i]["id"].length()); i++){
                space += " ";
            }
            cout <<  space << users[i]["id"] << " | " << users[i]["name"] << " " << users[i]["surname"] << endl;
            userIds.insert(stoi(users[i]["id"]));
        }

        cout << endl << "Identifiant de connexion : " << endl;
        cin >> idToOpen;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
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
        cout << "Mot de passe de connexion : " << endl;
        string inputPassword;
        cin >> inputPassword;

        correctPass = _currentUser.checkPassword(inputPassword);
        essai--;

        if (correctPass)
        {
            cout << "Identification reussie ! " << endl << endl;
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
    system(CLEAN_SCREEN);
    int choice;
    bool failInput = false;
    do
    {
        cout << endl;
        cout << "##############################" << endl;
        cout << "#                            #" << endl;
        cout << "#  -- Menu principal --      #" << endl;
        cout << "#  1. Liste des livres       #" << endl;
        cout << "#  2. Liste des dvds         #" << endl;
        cout << "#  3. Liste des cds          #" << endl;
        cout << "#  4. Liste des artistes     #" << endl;
        cout << "#  5. Mes emprunts           #" << endl;
        cout << "#  6. Chercher un article    #" << endl;

        if (isAdmin())
        {
            cout << "#                            #" << endl;
            cout << "# -- Menu Administrateur --  #" << endl;
            cout << "#  7. Liste des utilisateurs #" << endl;
            cout << "#  8. Liste des genres       #" << endl;
            cout << "#  9. Liste des statuts      #" << endl;
            cout << "# 10. Liste des emprunts     #" << endl;
            cout << "# 11. Ajouter un utilisateur #" << endl;
            cout << "# 12. Ajouter un livre       #" << endl;
            cout << "# 13. Ajouter un cd          #" << endl;
            cout << "# 14. Ajouter un dvd         #" << endl;
            cout << "# 15. Ajouter un artiste     #" << endl;
            cout << "# 16. Ajouter un genre       #" << endl;
            cout << "# 17. Ajouter un statuts     #" << endl;
        }

        cout << "#  -----------------------   #" << endl;
        cout << "#  0. Annuler                #" << endl;
        cout << "##############################" << endl;

        cout << "\tChoix: " << endl;
        cin >> choice;
        if(cin.fail()){
            failInput = true;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    } while(failInput || choice < 0 || (!isAdmin() && choice > 6) || choice > 17);

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
            getListEntity<Artist>();
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
            getListEntity<Genre>();
            break;
        case 9:
            getListEntity<Status>();
            break;
        case 10:
            getListEntity<Transaction>();
            break;
        case 11:
            addThing<User>();
            break;
        case 12:
            addThing<Book>();
            break;
        case 13:
            addThing<Cd>();
            break;
        case 14:
            addThing<Dvd>();
            break;
        case 15:
            addThing<Artist>();
            break;
        case 16:
            addThing<Genre>();
            break;
        case 17:
            addThing<Status>();
            break;
        default:
            return;
            break;
    }
}

void Library::searchList()
{
    system(CLEAN_SCREEN);
    cout << "--------------------------------------" << endl;
    cout << " -- Rechercher dans la mediatheque -- " << endl;
    cout << endl;

    cout << "Saisisser le titre de l'element que vous cherche : " << endl;
    string query;
    cin.ignore(1, '\n');
    getline(cin, query, '\n');

    cout << endl << "Traitement de la recherche en cours ." << flush;
    for(int i = 0; i < 10; i++){
        std::this_thread::sleep_for(chrono::milliseconds(100));
        cout << "." << flush;
    }
    cout << endl << endl;

    int totalCount = 0;

    map<int, map<string, string>> bibliography = BaseModel::select("books", "id, title, author, release", "title LIKE '%" + query + "%'");

    int totalBooks = (int)bibliography.size();

    map<int, map<string, string>> dvds = BaseModel::select("dvds", "id, title, release", "title LIKE '%" + query + "%'");

    int totalDvds = (int)dvds.size();

    map<int, map<string, string>> cds = BaseModel::select("cds", "id, title, release", "title LIKE '%" + query + "%'");

    int totalCds = (int)cds.size();

    totalCount = totalBooks + totalCds + totalDvds;
    int n = 1;

    vector<Book> bookSet = vector<Book>();

    cout << "----------------------" << endl;
    cout << " -- Livres trouves -- " << endl;
    if (totalBooks == 0)
    {
        cout << "Aucun livre dans la mediatheque" << endl;
    }
    for (int i = 1; i != totalBooks + 1; i++)
    {
        Book tmp = Book();
        tmp.init(bibliography[i]);
        cout << n << ". " << tmp.getTitle() << " (" << tmp.getRelease() << ")" << endl;
        bookSet.push_back(tmp);
        n++;
    }


    vector<Cd> cdSet = vector<Cd>();

    cout << "-------------------" << endl;
    cout << " -- CDs trouves -- " << endl;
    if (totalCds == 0)
    {
        cout << "Aucun cd dans la mediatheque" << endl;
    }
    for (int i = 1; i != totalCds + 1; i++)
    {
        Cd tmp = Cd();
        tmp.init(cds[i]);
        cout << n << ". " << tmp.getTitle() << " (" << tmp.getRelease() << ")" << endl;
        cdSet.push_back(tmp);
        n++;
    }

    vector<Dvd> dvdSet = vector<Dvd>();

    cout << "--------------------" << endl;
    cout << " -- DVDs trouves -- " << endl;
    if (totalDvds == 0)
    {
        cout << "Aucun dvd dans la mediatheque" << endl;
    }
    for (int i = 1; i != totalDvds + 1; i++)
    {
        Dvd tmp = Dvd();
        tmp.init(dvds[i]);
        cout << n << ". " << tmp.getTitle() << " (" << tmp.getRelease() << ")" << endl;
        dvdSet.push_back(tmp);
        n++;
    }

    if(totalCount == 0){
        cout << " ---------- " << endl;
        cout << "Retour au menu principal ..." << endl;
        std::this_thread::sleep_for(chrono::seconds(2));
        return;
    }

    int responseId;
    bool failInput;
    do{
        failInput = false;
        cout << "Saisissez l'identifiant d'un article pour y acceder, ou 0 pour revenir au menu precedent : " << endl;
        cin >> responseId;
        if(cin.fail()){
            failInput = true;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while(failInput || responseId < 0 || responseId > n );

    if(responseId == 0) return;

    responseId -= 1;

    if(responseId >= 0 && responseId < totalBooks){
        seeEntity<Book>(bookSet[responseId].getId());
    }
    else if(responseId >= totalBooks && responseId < totalBooks + totalCds){
        seeEntity<Cd>(cdSet[responseId - totalBooks].getId());
    }
    else if(responseId >= totalBooks + totalCds && responseId < n){
        seeEntity<Dvd>(dvdSet[responseId - (totalBooks + totalCds) ].getId());
    }

}

template <class T>
void Library::getListEntity(bool askEdit, int artistFilter)
{
    system(CLEAN_SCREEN);
    map<int, vector<string>> liaison = {
        {Util::Types::Book, {"books", "id, title, author, release"}},
        {Util::Types::Cd, {"cds", "*"}},
        {Util::Types::Dvd, {"dvds", "*"}},
        {Util::Types::Artist, {"artists", "id, name, surname"}},
        {Util::Types::User, {"users", "*"}},
        {Util::Types::Genre, {"genres", "*"}},
        {Util::Types::Status, {"status", "*"}},
        {Util::Types::Transaction, {"transactions", "*"}}
    };

    int type = 0;
    string typeStr;
    string artistArticleStr;

    if (is_same<T, Cd>::value)
    {
        type = Util::Types::Cd;
        typeStr = Util::getTypesString(Util::Types::Cd);
        artistArticleStr = "Discographie";
    }
    else if (is_same<T, Dvd>::value)
    {
        type = Util::Types::Dvd;
        typeStr = Util::getTypesString(Util::Types::Dvd);
        artistArticleStr = "Filmographie";
    }
    else if (is_same<T, Book>::value)
    {
        type = Util::Types::Book;
        typeStr = Util::getTypesString(Util::Types::Book);
        artistArticleStr = "Bibliographie";
    }
    else if(is_same<T, User>::value)
    {
        type = Util::Types::User;
        typeStr = Util::getTypesString(Util::Types::User);
    }
    else if (is_same<T, Artist>::value)
    {
        type = Util::Types::Artist;
        typeStr = Util::getTypesString(Util::Types::Artist);
    }
    else if (is_same<T, Genre>::value)
    {
        type = Util::Types::Genre;
        typeStr = Util::getTypesString(Util::Types::Genre);
    }
    else if (is_same<T, Status>::value)
    {
        type = Util::Types::Status;
        typeStr = Util::getTypesString(Util::Types::Status);
    }
    else if (is_same<T, Transaction>::value){
        type = Util::Types::Transaction;
        typeStr = Util::getTypesString(Util::Types::Transaction);
    }


    string filter = "";
    string filterStr = "";

    if(isAdmin() && askEdit){
        if(type>= 0 && type <= 2){
            int choice;
            bool failInput = false;
            do {
                cout << "----------------------------- " << endl;
                cout << "| -- Filtres disponibles -- |" << endl;
                cout << "| 1. Empruntables           |" << endl;
                cout << "| 2. Empruntes              |" << endl;
                cout << "| 3. Tous                   |" << endl;
                cout << "| 0. Annuler                |" << endl;
                cout << "----------------------------- " << endl;
                cout << "\tChoix: " << endl;
                cin >> choice;
                if(cin.fail())
                {
                    failInput = true;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }while(failInput || choice < 0 || choice > 3);

            if(choice == 0) return;

            switch(choice){
                case 2:
                    filter = "borrowable=0";
                    filterStr = " emprunte";
                    break;
                case 3:
                    filter = "";
                    filterStr = "";
                    break;
                default:
                    filter = "borrowable=1";
                    filterStr = " empruntable";
                    break;
            }
        }
        else if(type == Util::Types::Transaction){
            int choice;
            bool failInput = false;
            do{
                cout << "-----------------------------" << endl;
                cout << "| -- Filtres disponibles -- |" << endl;
                cout << "| 1. En cours               |" << endl;
                cout << "| 2. Termines               |" << endl;
                cout << "| 3. Tous                   |" << endl;
                cout << "| 0. Annuler                |" << endl;
                cout << "-----------------------------" << endl;
                cout << "\tChoix: " << endl;
                cin >> choice;
                if(cin.fail()){
                    failInput = true;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while(failInput || choice < 0 || choice > 3);

            if (choice == 0) return;

            switch(choice)
            {
                case 1:
                    // En cours
                    filter = "returned=0";
                    filterStr = " en cours";
                    break;
                case 2:
                    // Termines
                    filter = "returned=1";
                    filterStr = " termine";
                    break;
                default:
                    // Tous = No filter
                    filterStr = "";
                    filter = "";
                    break;
            }
        }
    }
    else{
        filter = "borrowable=1";
    }

    cout << endl << "Traitement de la recherche en cours ." << flush;
    for(int i = 0; i < 10; i++){
        std::this_thread::sleep_for(chrono::milliseconds(100));
        cout << "." << flush;
    }
    
    cout << endl << endl;

    bool needS = typeStr.substr(typeStr.length()-1, 1) == "s";

    if(!artistFilter){
        cout << "--------------" << Util::fillWithDash(typeStr.length()) << (needS ? "-" : "") << "------------------------"<< endl;
        cout << " -- Liste des " + (needS ? typeStr + "s" : typeStr) + " dans la mediatheque --" << endl << endl;
    }
    else{
                
        cout << "----" << Util::fillWithDash(artistArticleStr.length()) << "----" << endl;
        cout << " -- " << artistArticleStr << " -- " << endl;
    }
    

    map<int, map<string, string>> response = BaseModel::select(liaison.at(type)[0], liaison.at(type)[1], (!artistFilter ? ((Util::isFilterableType(type))? filter : "") : "artist_id=" + to_string(artistFilter)));

    int totalCount = (int)response.size();

    if (totalCount == 0)
    {
        cout << "Aucun " + typeStr + filterStr + " dans la mediatheque" << endl;
        return;
    }

    set<int> ids = set<int>();
    for (int i = 1; i != totalCount + 1; i++)
    {
        T tmp = T();
        tmp.init(response[i]);
        tmp.shortDisplay();
        ids.insert(stoi(response[i]["id"]));
    }

    cout << " ---------- " << endl;
    if(askEdit){
        int responseId;
        do{
            cout << "Saisissez l'identifiant d'un " + typeStr + " pour y accéder ou 0 pour revenir au menu precedent :" << endl;
            cin >> responseId;
        } while(responseId != 0 && !(ids.find(responseId) != ids.end()));

        seeEntity<T>(responseId, is_same<T, Transaction>::value);
    }

}

template <class T>
void Library::seeEntity(int id, bool isTrWithAdmin)
{
    system(CLEAN_SCREEN);
    void * art = nullptr;
    Article * artCast = nullptr;
    Artist * artistCast = nullptr;
    Transaction * trCast = nullptr;
    string typeStr;

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
        typeStr = Util::getTypesString(Util::Types::Cd);

    }
    else if (is_same<T, Dvd>::value)
    {
        type = Util::Types::Dvd;
        artCast = static_cast<Dvd*>(art);
        artCast = new Dvd(id);
        typeStr = Util::getTypesString(Util::Types::Dvd);
    }
    else if (is_same<T, Book>::value)
    {
        type = Util::Types::Book;
        artCast = static_cast<Book*>(art);
        artCast = new Book(id);
    }
    else if (is_same<T, User>::value)
    {
        type = Util::Types::User;
    }
    else if (is_same<T, Artist>::value)
    {
        type = Util::Types::Artist;
    }
    else if (is_same<T, Genre>::value)
    {
        type = Util::Types::Genre;
    }
    else if (is_same<T, Status>::value)
    {
        type = Util::Types::Status;
    }
    else if (is_same<T, Transaction>::value){
        type = Util::Types::Transaction;
        trCast = static_cast<Transaction*>(art);
        trCast = new Transaction(id);
    }

    typeStr = Util::getTypesString(type);

    string firstL = typeStr.substr(0, 1);
    set<string> voyelles = {"a", "e", "i", "o", "u", "y"};
    bool needE = voyelles.find(firstL) == voyelles.end();

    T tmp(id);
    cout << "----------------------" << (needE ? "--" : "-") << Util::fillWithDash(typeStr.length()) << "----" << endl ;
    cout << " -- Informations sur l" << (needE ? "e " : "'") << typeStr << " -- "<< endl;
    cout << tmp << endl;
    
    // todo : artist -> selection article depuis filmo, biblio, disco

    if (artCast != nullptr && artCast->getBorrowable())
    {
        if (affichageChoixSee("emprunter", Util::getTypesString(type)))
        {
            borrowArticle(artCast, type);
        }
    }
    else if (trCast != nullptr && !isTrWithAdmin){
        if (affichageChoixSee("rendre", Util::getTypesString(type)))
        {
            returnArticle(trCast);
        }
    }
    else if(artistCast != nullptr){
        int choice;
        bool failInput;
        do {
            failInput = false;
            cout << "--------------------" << endl;
            cout << " -- Realisations --" << endl;
            cout << " 1. Bibliographie " << endl;
            cout << " 2. Discographie " << endl;
            cout << " 3. Filmographie " << endl;
            cout << " 0. Annuler" << endl;
            cout << "Saisir un choix : " << endl;
            cin >> choice;
            if(cin.fail()){
                failInput = true;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }while(failInput || choice < 0 || choice > 3);
        
        if(choice != 0){
            switch(choice){
                case 1:
                    getListEntity<Book>(false, artistCast->getId());
                    break;
                case 2:
                    getListEntity<Cd>(false, artistCast->getId());
                    break;
                case 3:
                    getListEntity<Dvd>(false, artistCast->getId());
                    break;
            }
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

    cout << " ---------- " << endl;
    cout << "Retour au menu principal ..." << endl;
    std::this_thread::sleep_for(chrono::seconds(2));

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
        cout << "Voulez-vous " + typeChoix + " ce " + typeArticle + " ? Tapez 'o' si oui, 'n' sinon" << endl;
        cin >> choice;
    } while(choice != "o" && choice !="n");

    return choice == "o";
}

void Library::borrowedMenu()
{
    system(CLEAN_SCREEN);
    cout << " --------------------------- " << endl;
    cout << " -- Mes emprunts en cours -- " << endl;

    map<int, map<string, string>> transactions = BaseModel::select("transactions", "*", "borrower_id=" + to_string(_currentUser.getId()) +" AND returned=0");

    int totalCount = (int)transactions.size();

    if (totalCount == 0)
    {
        if(totalCount == 0){
            cout << "Aucun emprunt en cours" << endl << endl;
            cout << " ---------- " << endl;
            cout << "Retour au menu principal ..." << endl;
            std::this_thread::sleep_for(chrono::seconds(2));
            return;
        }
        return;
    }

    set<int> ids = set<int>();
    for (int i = 1; i != totalCount + 1; i++)
    {
        Transaction tmp = Transaction();
        tmp.init(transactions[i]);
        tmp.shortDisplay();
        ids.insert(tmp.getId());
    }

    int empruntId;
    do
    {
        cout << "Saisissez l'identifiant d'un emprunt pour y acceder ou 0 pour revenir au menu: " << endl;
        cin >> empruntId;
    } while(empruntId != 0 && !(ids.find(empruntId) != ids.end()));

    if (empruntId == 0) return;

    seeEntity<Transaction>(empruntId);
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

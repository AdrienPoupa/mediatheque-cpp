#include "BaseModel.hpp"

BaseModel::BaseModel(){
    
}

BaseModel::~BaseModel(){
    
}

bool BaseModel::save(){
    
    
    
    // Update
//    if (_id != 0) {
//        try
//        {
//            SQLite::Database    db("example.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
//            // Insert query
//            SQLite::Statement   query(db, "UPDATE artists SET name=?, surname=?, birthdate=?, nationality=? WHERE id=?");
//            query.bind(1, _firstName);
//            query.bind(2, _lastName);
//            query.bind(3, _birthDate.dateToDB());
//            query.bind(4, _nationality);
//            query.bind(5, (int) _id);
//            query.exec();
//            
//            return true;
//        }
//        catch (std::exception& e)
//        {
//            std::cout << "SQLite exception: " << e.what() << std::endl;
//            return false;
//        }
//    }
//    // Insert
//    else
//    {
//        try
//        {
//            SQLite::Database    dbArtist("example.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
//            // Insert query
//            SQLite::Statement   query(dbArtist, "INSERT INTO artists VALUES (?, ?, ?, ?, ?, ?)");
//            query.bind(2, _firstName);
//            query.bind(3, _lastName);
//            query.bind(4, _birthDate.dateToDB());
//            query.bind(5, _nationality);
//            query.exec();
//            
//            // Update current ID
//            int tmp = dbArtist.execAndGet("SELECT last_insert_rowid();");
//            _id = tmp;
//            
//            return true;
//        }
//        catch (std::exception& e)
//        {
//            std::cout << "SQLite exception: " << e.what() << std::endl;
//            return false;
//        }
//    }
    return true;
}
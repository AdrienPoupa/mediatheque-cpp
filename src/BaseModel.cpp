#include "BaseModel.hpp"

#include <iostream>

using namespace std;

int BaseModel::save(const string& table, map<string, vector<string>> data){
    
    /*
     data : {
        {"_id", {"15", "int"}},
        {"attr1", {"jean", "string"}},
        ...
     }
     */
    
    // Update
    if (stoi(data["id"][0]) != 0) {
        //cout << "Updating ..." << endl;
        try
        {
            SQLite::Database db("example.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
            
            string queryString = "UPDATE " + table + " SET ";
            
            for(auto const& elem : data){
                if(elem.first != "id"){
                    queryString += elem.first.c_str();
                    queryString += "=?, ";
                }
            }
            
            queryString = queryString.substr(0, queryString.size() - 2);
            
            queryString += "WHERE id=" + data["id"][0] + ";";
            
            // queryString : UPDATE table SET attr1=?, attr2=?, attr3=? WHERE id=?

            SQLite::Statement query(db, queryString);
            
            int n = 1;
            for(auto const& elem : data){
                if(elem.first != "id"){
                    if(elem.second[1] == "string"){
                        query.bind(n, elem.second[0]);
                    }
                    else if(elem.second[1] == "int"){
                        query.bind(n, stoi(elem.second[0]));
                    }
                    n++;
                }
                
            }
            
            // queryString: UPDATE table SET attr1=val1, attr2=val2, attr3=val3 WHERE id=_idval
            
            query.exec();
            
            return true;
        }
        catch (std::exception& e)
        {
            std::cout << "SQLite exception: " << e.what() << std::endl;
            return false;
        }
    }
    
    // Insert
    else
    {
        //cout << "Inserting ..." << endl;
        try
        {
            SQLite::Database db("example.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
            
            string queryString = "INSERT INTO " + table + "(";
            
            for(auto const& elem: data){
                if(elem.first != "id"){
                    queryString += elem.first + ", ";
                }
            }
            
            queryString = queryString.substr(0, queryString.size() - 2);
            queryString += ") ";
            
            queryString += "VALUES( ";
            
            for(auto const& elem: data){
                if(elem.first != "id"){
                    queryString += "?, ";
                }
            }
            
            queryString = queryString.substr(0, queryString.size()-2);
            
            queryString += ");";
            
            // Insert query
            SQLite::Statement query(db, queryString);
            
            int n = 1;
            for(auto const& elem : data){
                if(elem.first != "id"){
                    if(elem.second[1] == "string"){
                        query.bind(n, elem.second[0]);
                    }
                    else if(elem.second[1] == "int"){
                        query.bind(n, stoi(elem.second[0]));
                    }
                    n++;
                }
            }
            
            query.exec();
            
            // Update current ID
            int tmp = db.execAndGet("SELECT last_insert_rowid();");
            return tmp;
        }
        catch (std::exception& e)
        {
            std::cout << "SQLite exception: " << e.what() << std::endl;
            return false;
        }
    }
}

bool BaseModel::remove(const std::string& table, const int& id){
    return true;
}
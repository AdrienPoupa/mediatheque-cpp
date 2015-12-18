#include "BaseModel.hpp"

using namespace std;

map<string, string> BaseModel::getById(const string& table, const int& id)
{

    map<string, string> data = map<string, string>();

    try
    {
        SQLite::Database db("mediatheque.db3");

        SQLite::Statement query(db, "SELECT * FROM " + table + " WHERE id=?");
        query.bind(1, id);

        int resultCount = 0;
        while (query.executeStep())
        {
            resultCount++;
            for(int i = 0; i < query.getColumnCount(); i ++)
            {
                data.insert({query.getColumnName(i), query.getColumn(i).getText()});
            }
        }

        return data;

    } catch (exception& e) {
        cout << "exception: " << e.what() << endl;
        return data;
    }
}

map<int, map<string, string>> BaseModel::select(const string& table, const string& fields, const string& where)
{

    map<int, map<string, string>> data = map<int, map<string, string>>();

    try
    {
        SQLite::Database db("mediatheque.db3");

        //cout << "SELECT " + fields + " FROM " + table + (where.length() != 0 ? " WHERE " + where : "") << endl;

        SQLite::Statement query(db, "SELECT " + fields + " FROM " + table + (where.length() != 0 ? " WHERE " + where : ""));

        int resultCount = 0;
        while (query.executeStep())
        {
            resultCount++;
            for(int i = 0; i < query.getColumnCount(); i ++)
            {
                data[resultCount].insert({query.getColumnName(i), query.getColumn(i).getText()});
            }
        }

        return data;

    } catch (exception& e) {
        cout << "exception: " << e.what() << endl;
        return data;
    }
}

int BaseModel::save(const string& table, map<string, vector<string>> data)
{

    /*
     data : {
        {"_id", {"15", "int"}},
        {"attr1", {"jean", "string"}},
        ...
     }
     */

    // Update
    if (stoi(data["id"][0]) != 0) {
        try
        {
            SQLite::Database db("mediatheque.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);

            string queryString = "UPDATE " + table + " SET ";

            for(auto const& elem : data)
            {
                if (elem.first != "id")
                {
                    queryString += elem.first.c_str();
                    queryString += "=?, ";
                }
            }

            queryString = queryString.substr(0, queryString.size() - 2);

            queryString += "WHERE id=" + data["id"][0] + ";";

            // queryString : UPDATE table SET attr1=?, attr2=?, attr3=? WHERE id=?

            SQLite::Statement query(db, queryString);

            int n = 1;
            for(auto const& elem : data)
            {
                if (elem.first != "id")
                {
                    if (elem.second[1] == "string")
                    {
                        query.bind(n, elem.second[0]);
                    }
                    else if (elem.second[1] == "int")
                    {
                        query.bind(n, stoi(elem.second[0]));
                    }
                    n++;
                }
            }

            // queryString: UPDATE table SET attr1=val1, attr2=val2, attr3=val3 WHERE id=_idval

            query.exec();

            return true;
        }
        catch (exception& e)
        {
            cout << "SQLite exception: " << e.what() << endl;
            return false;
        }
    }

    // Insert
    else
    {
        try
        {
            SQLite::Database db("mediatheque.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);

            string queryString = "INSERT OR IGNORE INTO " + table + "(";

            for(auto const& elem: data)
            {
                if (elem.first != "id")
                {
                    queryString += elem.first + ", ";
                }
            }

            queryString = queryString.substr(0, queryString.size() - 2);
            queryString += ") ";

            queryString += "VALUES( ";

            for(auto const& elem: data)
            {
                if (elem.first != "id")
                {
                    queryString += "?, ";
                }
            }

            queryString = queryString.substr(0, queryString.size()-2);

            queryString += ");";

            // Insert query
            SQLite::Statement query(db, queryString);

            int n = 1;
            for(auto const& elem : data)
            {
                if (elem.first != "id")
                {
                    if (elem.second[1] == "string")
                    {
                        query.bind(n, elem.second[0]);
                    }
                    else if (elem.second[1] == "int")
                    {
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
        catch (exception& e)
        {
            cout << "SQLite exception: " << e.what() << endl;
            return false;
        }
    }
}

int BaseModel::getCount(const string& table, string filter){
    
    if (filter != ""){
        filter = " WHERE " + filter;
    }
    try
    {
        SQLite::Database db("mediatheque.db3");
        
        SQLite::Statement query(db, "SELECT count(*) FROM " + table + filter);
        
        while (query.executeStep())
        {
            return query.getColumn(0);
        }
        
        
    } catch (exception& e) {
        cout << "exception: " << e.what() << endl;
    }
    return 0;
}

bool BaseModel::remove(const string& table, const int& id)
{

    // We cannot delete a non-existing field
    if (id == 0)
    {
        return false;
    }

    try
    {
        SQLite::Database db("mediatheque.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
        // Delete query
        SQLite::Statement   query(db, "DELETE FROM " + table + " WHERE id=?");
        query.bind(1, (int) id);
        query.exec();

        return true;
    }
    catch (exception& e)
    {
        cout << "SQLite exception: " << e.what() << endl;
        return false;
    }
    return true;
}

#include <iostream>

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "sqlite/SQLiteCpp.h"

using namespace std;

int main()
{
    try
    {
        // Open a database file
        SQLite::Database    db("example.db3");

        // Compile a SQL query, containing one parameter (index 1)
        SQLite::Statement   query(db, "SELECT * FROM test WHERE id > ?");

        // Bind the integer value 6 to the first parameter of the SQL query
        query.bind(1, 1);

        // Loop to execute the query step by step, to get rows of result
        while (query.executeStep())
        {
            // Demonstrate how to get some typed column value
            int         id      = query.getColumn(0);
            const char* value   = query.getColumn(1);

            std::cout << "row: " << id << ", " << value << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }
}
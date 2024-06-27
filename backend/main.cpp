#include "crow.h"
#include <string>
#include <cstring>
#include <vector> 
#include <iostream> 
#include <SQLiteCpp/SQLiteCpp.h>


const int PORT = 9999;
const std::string TODO_TABLE_NAME = "Todo";
const std::string DB_DIR = "/app/todosDB.db";

std::vector<std::string> todos;

void create_table(SQLite::Database &db){
    db.exec("CREATE TABLE IF NOT EXISTS todos (name TEXT)");
    CROW_LOG_INFO << "Table created...";
}

void insert_into_table(SQLite::Database &db, std::string name){
    CROW_LOG_INFO << "Adding " + name + " to DB";
    db.exec("INSERT into todos (name) VALUES ('" + name + "')");
    CROW_LOG_INFO << name  << " added to DB";
}

void delete_from_table(SQLite::Database& db, std::string name) {
    CROW_LOG_INFO << "Removing " + name + " from DB";
    db.exec("DELETE FROM todos WHERE name = '" + name + "'");
    CROW_LOG_INFO << name << " removed from DB";
}

int main() {

    crow::SimpleApp app;
    app.loglevel(crow::LogLevel::Info);

    SQLite::Database db(DB_DIR, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    create_table(db);

    CROW_ROUTE(app, "/todos/<string>").methods(crow::HTTPMethod::GET, crow::HTTPMethod::POST, crow::HTTPMethod::DELETE)([&db](const crow::request &req, const std::string &name)
                                                                                                                        {
     if (req.method == crow::HTTPMethod::GET) {
            return crow::response(200, "Get Response: " + name);

        } else if (req.method == crow::HTTPMethod::POST) {

            // Add Object
            insert_into_table(db, name);
            return crow::response(200, "Post Response: " + name);
        } else if (req.method == crow::HTTPMethod::DELETE) {

            // Delete Object
            delete_from_table(db, name);
            return crow::response(200, "Delete Response: " + name);
        }
        return crow::response(405); });

    CROW_ROUTE(app, "/todos/").methods(crow::HTTPMethod::GET)([&db](){
        crow::json::wvalue result;

        SQLite::Statement query(db, "SELECT name FROM todos");

        int count = 0;
        while(query.executeStep()) {
            result[count] = query.getColumn("name").getText();
            count++;
        }
        return crow::response{result};
    });

    app.port(PORT).multithreaded().run();
}


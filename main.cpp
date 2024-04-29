#include "crow.h"


const int port = 9999;

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return "Hello world!";
    });

    app.port(port).multithreaded().run();
}

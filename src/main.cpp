#include "chat_server.hpp"

int main() {
    try {
        boost::asio::io_context ioc;
        tcp::endpoint endpoint(tcp::v4(), 8080); // Listen on port 8080
        ChatServer server(ioc, endpoint);
        server.run();
        ioc.run();
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}


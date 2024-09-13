#include <iostream>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include "chat_server.hpp"

int main() {
    try {
        boost::asio::io_context ioc;
        tcp::endpoint endpoint(boost::asio::ip::make_address("127.0.0.1"), 8080);
        ChatServer server(ioc, endpoint);
        server.run();
        ioc.run();  // Start the I/O context
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}


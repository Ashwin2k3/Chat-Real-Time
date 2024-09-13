#include "chat_server.hpp"
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/placeholders.hpp>
#include <iostream>
#include <vector>
#include <memory>

using tcp = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;

// ChatSession Implementation
ChatSession::ChatSession(tcp::socket socket)
    : ws_(std::move(socket)) {}

void ChatSession::start() {
    ws_.async_accept(
        [self = shared_from_this()](boost::beast::error_code ec) {
            if (!ec) {
                self->do_read();
            }
        });
}

void ChatSession::send_message(const std::string& message) {
    ws_.async_write(
        boost::asio::buffer(message),
        [self = shared_from_this()](boost::beast::error_code ec, std::size_t bytes_transferred) {
            if (ec) {
                std::cerr << "Write error: " << ec.message() << std::endl;
            }
        });
}

void ChatSession::do_read() {
    ws_.async_read(buffer_,
        [self = shared_from_this()](boost::beast::error_code ec, std::size_t bytes_transferred) {
            if (!ec) {
                std::string message = boost::beast::buffers_to_string(self->buffer_.data());
                self->buffer_.consume(bytes_transferred);
                self->send_message(message);
                self->do_read();
            } else {
                std::cerr << "Read error: " << ec.message() << std::endl;
            }
        });
}

// ChatServer Implementation
ChatServer::ChatServer(boost::asio::io_context& ioc, tcp::endpoint endpoint)
    : acceptor_(ioc, endpoint), ioc_(ioc) {}

void ChatServer::run() {
    do_accept();
}

void ChatServer::do_accept() {
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket) {
            if (!ec) {
                std::make_shared<ChatSession>(std::move(socket))->start();
            } else {
                std::cerr << "Accept error: " << ec.message() << std::endl;
            }
            do_accept();
        });
}


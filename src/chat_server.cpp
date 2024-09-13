#include "chat_server.hpp"
#include <iostream>

ChatSession::ChatSession(tcp::socket socket)
    : ws_(std::move(socket)) {}

void ChatSession::start() {
    ws_.async_accept([self = shared_from_this()](boost::system::error_code ec) {
        if (!ec) {
            self->do_read();
        }
    });
}

void ChatSession::do_read() {
    ws_.async_read(buffer_, [self = shared_from_this()](boost::system::error_code ec, std::size_t bytes_transferred) {
        if (!ec) {
            std::string message = boost::beast::buffers_to_string(self->buffer_.data());
            std::cout << "Received: " << message << std::endl;
            self->do_write(message);
            self->buffer_.consume(bytes_transferred);
        }
    });
}

void ChatSession::do_write(const std::string& message) {
    ws_.text(ws_.got_text());
    ws_.async_write(boost::asio::buffer(message), [self = shared_from_this()](boost::system::error_code ec, std::size_t bytes_transferred) {
        if (!ec) {
            self->do_read();
        }
    });
}

ChatServer::ChatServer(boost::asio::io_context& ioc, tcp::endpoint endpoint)
    : acceptor_(ioc, endpoint), ioc_(ioc) {}

void ChatServer::run() {
    do_accept();
}

void ChatServer::do_accept() {
    acceptor_.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
        if (!ec) {
            std::make_shared<ChatSession>(std::move(socket))->start();
        }
        do_accept();
    });
}


#ifndef CHAT_SERVER_HPP
#define CHAT_SERVER_HPP

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <string>
#include <memory>

using tcp = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;

class ChatSession : public std::enable_shared_from_this<ChatSession> {
public:
    ChatSession(tcp::socket socket);
    void start();
    void send_message(const std::string& message);
private:
    void do_read();
    void do_write(const std::string& message);

    websocket::stream<tcp::socket> ws_;
    boost::beast::flat_buffer buffer_;
};

class ChatServer {
public:
    ChatServer(boost::asio::io_context& ioc, tcp::endpoint endpoint);
    void run();
private:
    void do_accept();

    tcp::acceptor acceptor_;
    boost::asio::io_context& ioc_;
    std::vector<std::shared_ptr<ChatSession>> sessions_;
};

#endif


#include <iostream>
#include <boost/asio.hpp>
#include <chrono>
#include <thread>

using namespace boost::asio;
using ip::tcp;

void startServer() {
    io_service ioService;

    // Create an acceptor to listen for incoming connections
    tcp::acceptor acceptor(ioService, tcp::endpoint(tcp::v4(), 50000));

    // Accept a connection
    tcp::socket socket(ioService);
    acceptor.accept(socket);

    // Write "42" once every second
    std::chrono::seconds sleep_duration(1);
    while (true) {
        const char* msg = "42";
        socket.write_some(buffer(msg, std::strlen(msg)));
        std::this_thread::sleep_for(sleep_duration);
    }
}

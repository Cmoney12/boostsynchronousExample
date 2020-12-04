//Server

#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <string>
#include "Server.h"

using namespace boost::asio;

int main() {
    try {
        io_context io_context;
        tcp_server server(io_context);
        io_context.run();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

#ifndef BOOSTNOTESAGAIN_SERVER_H
#define BOOSTNOTESAGAIN_SERVER_H

#endif //BOOSTNOTESAGAIN_SERVER_H

using namespace boost::asio;

class tcp_server {
public:
    tcp_server(io_context& io_context) :
            acceptor_(io_context, ip::tcp::endpoint(ip::tcp::v4(), 1234))
    {
        createSocket(io_context);
    }
private:
    std::string getData(ip::tcp::socket& socket)  {
        boost::asio::streambuf buf;
        read_until(socket, buf, "\n");
        std::string data = buffer_cast<const char*>(buf.data());
        return data;
    }

    void sendData(ip::tcp::socket& socket, const std::string& message) {
        write(socket, buffer(message + "\n"));
    }

    void createSocket(io_service& ioService) {
        //create a socket
        ip::tcp::socket server_socket(ioService);
        //wait for connection
        acceptor_.accept(server_socket);
        //get username
        user_name = getData(server_socket);
        initiateChat(server_socket);
    }
    void initiateChat(ip::tcp::socket& socket) {
        std::string response;
        reply = "Hello " + user_name + "!";
        std::cout << "Server: " << reply << std::endl;
        sendData(socket, reply);
        chat(socket);
    }
    void chat(ip::tcp::socket& socket) {
        while (true) {
            std::string response = getData(socket);
            response.pop_back();
            std::cout << user_name << ": " << response << std::endl;
            //reading a new message from input stream.
            std::cout << "Server" << ": ";
            std::getline(std::cin, reply);
            sendData(socket, reply);
            if (reply == "exit")
                break;
        }
    }
public:
    ip::tcp::acceptor acceptor_;
    std::string user_name;
    std::string reply;
};

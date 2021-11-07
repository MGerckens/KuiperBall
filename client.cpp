#include <iostream>
#include <boost/asio.hpp>
#include <boost/algorithm/string/trim.hpp>

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

string read_(tcp::socket& socket) {
    boost::asio::streambuf buf;
    boost::asio::read_until(socket, buf, "\0");
    string data = boost::asio::buffer_cast<const char*>(buf.data());
    return data;
}
void send_(tcp::socket& socket, const string& message) {
    const string msg = message + "\0";
    boost::asio::write(socket, boost::asio::buffer(message));
}


bool first = true;
int main() {
    string ip;
    cout << "Enter server IP: ";
    std::getline(std::cin, ip);
    //boost::algorithm::trim(ip);
    boost::asio::io_service io_service;
    //socket creation
    tcp::socket socket(io_service);
    //connection
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string(ip.c_str()), 1234));
    string message, senddata;
    boost::system::error_code error;
    //boost::asio::streambuf receive_buffer;
    while (true) {
        message = read_(socket);
        if (error && error != boost::asio::error::eof) {
            cout << "receive failed: " << error.message() << endl;
        }
        else {
            if (message.at(0) == 'I' && !first) {
                continue;
            }
            else {
                system("cls");
                cout << message;
                if (first) { 
                    system("cls");
                    cout << "Enter coordinates as \"x y\": ";
                }
                if (message.at(0) == 'Y' || message.at(0) == 'G') {
                    system("pause");
                    return 0;
                }
            }
        }
        

        std::getline(std::cin, senddata);
        send_(socket, senddata);
        if (error) {
            cout << "send failed: " << error.message() << endl;
        }
        first = false;
    }
}
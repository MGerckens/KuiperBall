#include <iostream>
#include <boost/asio.hpp>

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

std::string buffer_to_string(const boost::asio::streambuf& buffer)
{
    using boost::asio::buffers_begin;

    auto bufs = buffer.data();
    std::string result(buffers_begin(bufs), buffers_begin(bufs) + buffer.size());
    return result;
}
bool first = true;
int main() {
    boost::asio::io_service io_service;
    //socket creation
    tcp::socket socket(io_service);
    //connection
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));
    string message, senddata;
    boost::system::error_code error;
    //boost::asio::streambuf receive_buffer;
    while (true) {
        message = read_(socket);
        if (error && error != boost::asio::error::eof) {
            cout << "receive failed: " << error.message() << endl;
        }
        else {
            if (!message.compare("I") && !first) {
                continue;
            }
            if (!message.compare("L")) {
                cout << "Game Over!" << endl;
                goto fail;
            }
            else {
                system("cls");
                cout << message;
            }
        }
        

        std::getline(std::cin, senddata);
        send_(socket, senddata);
        if (error) {
            cout << "send failed: " << error.message() << endl;
        }
        first = false;
    }
fail:
    cout << "Game Over!" << endl;
    system("pause");
    return 0;
}
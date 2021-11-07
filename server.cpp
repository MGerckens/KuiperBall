#include <iostream>
#include <boost/asio.hpp>
#include "minesweeper.h"

#define GET_IO_SERVICE(s) ((boost::asio::io_context&)(s).get_executor().context())

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

Minesweeper* minesweeper;

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

int main() {
    minesweeper = new Minesweeper();
    boost::asio::io_service io_service;
    //listen for new connection
    tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), 1234));
    //socket creation 
    tcp::socket socket_(io_service);
    //waiting for connection
    acceptor_.accept(socket_);
    stringstream* s;
    int x, y, p;
    send_(socket_, minesweeper->getResult());
    while (true) {
        string message = read_(socket_);
        s = new stringstream(message);
        *s >> y >> x;
        minesweeper->process(x, y);

        system("cls");
        cout << minesweeper->getResult() ;
        input:
        cin >> y >> x;
        minesweeper->process(x, y);
        string res = minesweeper->getResult();
        if (!res.compare("L")) {
            goto fail;
        }
        else if (!res.compare("I")) {
            cout << "Already picked, try again\n";
            goto input;
        }
        else {
            send_(socket_, res);
        }
    }
    fail:
    cout << "Game Over!" << endl;
    system("pause");
    return 0;
}
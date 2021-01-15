#include <iostream>
#include <boost\asio.hpp>
#include <boost\thread.hpp>

using namespace std;

int main()
{
	boost::asio::io_service ioS;
	boost::asio::io_service  ioS2;
	
	boost::asio::steady_timer tm1(ioS, std::chrono::seconds(3));
	tm1.async_wait([](const  boost::system::error_code &ec) {cout << "[1]3sec" << endl; });

	boost::asio::steady_timer tm2(ioS2, std::chrono::seconds(3));
	tm2.async_wait([](const  boost::system::error_code &ec) {cout << "[2]3sec" << endl; });

	boost::thread t1{ [&ioS]() {ioS.run(); } };
	boost::thread t2{ [&ioS2]() {ioS2.run(); } };

	t1.join();
	t2.join();

	return 0;
}
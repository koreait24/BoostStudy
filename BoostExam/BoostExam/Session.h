#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <list>
#include <boost\bind.hpp>
#include <boost\asio.hpp>

using namespace std;
using namespace boost;
using namespace boost::asio;
using namespace asio::ip;

class Session
{
public:
	Session(io_service &io_service)
	{

	}

	tcp::socket& Socket()
	{
		return m_Socket;
	}
};
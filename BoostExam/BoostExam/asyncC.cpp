#include <iostream>
#include <algorithm>
#include <string>
#include <list>
#include <boost\asio.hpp>
#include <boost\bind.hpp>

using namespace std;

const char SERVER_IP[] = "127.0.0.1";
const unsigned short PORT_NUMBER = 31400;

class TCP_Client
{
public:
	TCP_Client(boost::asio::io_service &io_service) :m_io_service(io_service), m_Socket(io_service), m_SeqNumber(0)	{}
	
public:
	void Connect(boost::asio::ip::tcp::endpoint &endpoint)
	{
		m_Socket.async_connect(endpoint, boost::bind(&TCP_Client::handle_connect, this, boost::asio::placeholders::error));
	}
	
private:
	boost::asio::io_service& m_io_service;
	boost::asio::ip::tcp::socket m_Socket;
	int m_SeqNumber;
	array<char, 128> m_ReceiveBuffer;
	string m_WriteMessage;

private:
	void PostWrite()
	{
		if (m_Socket.is_open() == false)
		{
			return;
		}

		if (m_SeqNumber > 7)
		{
			m_Socket.close();
			return;
		}

		++m_SeqNumber;

		char szMessage[128] = { 0, };
		sprintf_s(szMessage, 128-1, "%d - Send Message", m_SeqNumber);


		m_WriteMessage = szMessage;

		boost::asio::async_write(m_Socket, boost::asio::buffer(m_WriteMessage),
			boost::bind(&TCP_Client::handle_write, this,  
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		
		PostRecieve();
	}

	void PostRecieve()
	{
		memset(&m_ReceiveBuffer, '\0', sizeof(m_ReceiveBuffer));

		m_Socket.async_read_some(boost::asio::buffer(m_ReceiveBuffer),
			boost::bind(&TCP_Client::handle_receive, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}

	void handle_connect(const boost::system::error_code &error)
	{
		if (error)
		{
			cout << "connect failed : " << error.message() << endl;
		}
		else
		{
			cout << "Connected" << endl;
			PostWrite();
		}
	}

	void handle_write(const boost::system::error_code &, size_t)
	{
	}

	void handle_receive(const boost::system::error_code &error, size_t bytes_transferred)
	{
		if (error)
		{
			if (error == boost::asio::error::eof)
			{
				cout << "서버와 연결이 끊어졌습니다." << endl;
			}
			else
			{
				cout << "error No : " << error.value() << "error Message : " << error.message() << endl;
			}
		}
		else
		{
			const string strRecvMessage = m_ReceiveBuffer.data();
			cout << "서버에서 받은 메시지 : " << strRecvMessage << ", 받은 크기 : " << bytes_transferred << endl;
			PostWrite();
		}
	}
};

int main()
{
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(SERVER_IP), PORT_NUMBER);
	TCP_Client client(io_service);
	client.Connect(endpoint);
	io_service.run();
	cout << "네트워크 접속 종료" << endl;
	getchar();
	return 0;
}
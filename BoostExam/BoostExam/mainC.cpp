#include <boost\asio.hpp>
#include <iostream>

using namespace std;
using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

const char SERVER_IP[] = "127.0.0.1";
const unsigned short PORT_NUMBER = 31400;

int main()
{
	io_service io_service;
	tcp::endpoint endpoint(address::from_string(SERVER_IP), PORT_NUMBER);			// address::from_string 클래스를
																					// 사용해 문자열로 된 IP주소를
																					// Boost.Asio에서 사용하는 IP주소로 변환
	system::error_code connect_error;
	tcp::socket socket(io_service);
	socket.connect(endpoint, connect_error);										// socket 클래스의 connect 맴버 함수를 사용해 접속 시도

	if (connect_error)																// error_code의 값을 조사해 연결 성공 실패 여부 확인
	{
		cout << "연결 실패. error No: " << connect_error.value()
			<< ", Message: " << connect_error.message() << endl;
		getchar();
		return 0;
	}

	else 
	{
		cout << "서버에 연결 성공" << endl;
	}

	for (int i = 0; i < 7; ++i)
	{
		char szMessage[128] = { 0, };
		sprintf_s(szMessage, 128 - 1, "%d - Send Message", i);
		int nMsgLen = strnlen_s(szMessage, 128 - 1);

		system::error_code ignored_error;
		socket.write_some(buffer(szMessage, nMsgLen), ignored_error);					// write some

		cout << "서버에 보낸 메시지: " << szMessage << endl;

		std::array<char, 128>buf;
		buf.assign(0);
		system::error_code error;
		size_t len = socket.read_some(buffer(buf), error);								// read some을 이용해 서버와 데이터를 주고받음

		if (error)
		{
			if (error == error::eof)
			{
				cout << "서버와 연결이 끊어졌습니다." << endl;
			}
			else
			{
				cout << "error No: " << error.value() << "error Message: "
					<< error.message().c_str() << endl;
			}
			break;
		}
		cout << "서버로부터 받은 메시지: " << &buf[0] << std::endl;
	}

	if (socket.is_open())
	{
		socket.close();																	// 서버와 연결된 상태에서 연결을 끊을 때 사용
	}

	getchar();
	return 0;
}
#include <boost\asio.hpp>
#include <iostream>

using namespace std;
using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

const unsigned short PORT_NUMBER = 31400;

int main()
{
	io_service io_service;										// I/O 이벤트를 디스패치 해주는 클래스 네트워크상 접속 받기, 데이터 받기/보내기 등의 이벤트 감지 가능
	tcp::endpoint endpoint(tcp::v4(), PORT_NUMBER);				// endpoint는 네트워크 주소를 설정
	tcp::acceptor accepter(io_service, endpoint);				// ecceptor 클래스는 클라이언트의 접속을 받는 역할

	tcp::socket socket(io_service);								// tcp 소켓을 만들기 위해 io_service를 할당
	accepter.accept(socket);									// acceptor 가 accept를 통해 소켓을 받을 준비를 한다. (완료 될 때 까지 대기상태)

	cout << "클라이언트 접속" << endl;

	for (;;)
	{
		std::array<char, 128> buf;												// STL의 array 컨테이너 사용 
		buf.assign(0);
		system::error_code error;												// error_code 클래스는 시스템에서 발생하는 에러코드를 랩핑한 클래스 애러 발생시 에러코드와 메시지 획득
		size_t len = socket.read_some(buffer(buf), error);						// socket 클래스의 read_some을 통해 클라이언트가 보낸 데이터를 받음.
																				// 매개변수는 버퍼와 error_code를 사용한다.
																				// read_some을 통해 에러캐치도 가능, 에러인지, 접속끊김인지 확인 해야함.

		if (error)																// 위에서 에러 발생시 조건문 실행 / error에 저장
		{
			if (error == error::eof)
			{
				cout << "클라이언트와 연결이 끊어졌습니다" << endl;
			}
			
			else
			{
				cout << "error No: " << error.value() << "error Message"
					<< error.message() << endl;
			}
			break;
		}
		cout << "클라이언트에서 받은 메시지: " << &buf[0] << endl;

		char szMessage[128] = { 0, };
		sprintf_s(szMessage, 128 - 1, "Re:%s", &buf[0]);
		int nMsgLen = strnlen_s(szMessage, 128 - 1);

		system::error_code ignored_error;
		socket.write_some(buffer(szMessage, nMsgLen), ignored_error);
		cout << "클라이언트에 보낸 메시지:" << szMessage << endl;

	}
	getchar();
	return 0;
}
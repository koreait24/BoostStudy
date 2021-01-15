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
	tcp::endpoint endpoint(address::from_string(SERVER_IP), PORT_NUMBER);			// address::from_string Ŭ������
																					// ����� ���ڿ��� �� IP�ּҸ�
																					// Boost.Asio���� ����ϴ� IP�ּҷ� ��ȯ
	system::error_code connect_error;
	tcp::socket socket(io_service);
	socket.connect(endpoint, connect_error);										// socket Ŭ������ connect �ɹ� �Լ��� ����� ���� �õ�

	if (connect_error)																// error_code�� ���� ������ ���� ���� ���� ���� Ȯ��
	{
		cout << "���� ����. error No: " << connect_error.value()
			<< ", Message: " << connect_error.message() << endl;
		getchar();
		return 0;
	}

	else 
	{
		cout << "������ ���� ����" << endl;
	}

	for (int i = 0; i < 7; ++i)
	{
		char szMessage[128] = { 0, };
		sprintf_s(szMessage, 128 - 1, "%d - Send Message", i);
		int nMsgLen = strnlen_s(szMessage, 128 - 1);

		system::error_code ignored_error;
		socket.write_some(buffer(szMessage, nMsgLen), ignored_error);					// write some

		cout << "������ ���� �޽���: " << szMessage << endl;

		std::array<char, 128>buf;
		buf.assign(0);
		system::error_code error;
		size_t len = socket.read_some(buffer(buf), error);								// read some�� �̿��� ������ �����͸� �ְ����

		if (error)
		{
			if (error == error::eof)
			{
				cout << "������ ������ ���������ϴ�." << endl;
			}
			else
			{
				cout << "error No: " << error.value() << "error Message: "
					<< error.message().c_str() << endl;
			}
			break;
		}
		cout << "�����κ��� ���� �޽���: " << &buf[0] << std::endl;
	}

	if (socket.is_open())
	{
		socket.close();																	// ������ ����� ���¿��� ������ ���� �� ���
	}

	getchar();
	return 0;
}
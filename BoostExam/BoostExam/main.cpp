#include <boost\asio.hpp>
#include <iostream>

using namespace std;
using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

const unsigned short PORT_NUMBER = 31400;

int main()
{
	io_service io_service;										// I/O �̺�Ʈ�� ����ġ ���ִ� Ŭ���� ��Ʈ��ũ�� ���� �ޱ�, ������ �ޱ�/������ ���� �̺�Ʈ ���� ����
	tcp::endpoint endpoint(tcp::v4(), PORT_NUMBER);				// endpoint�� ��Ʈ��ũ �ּҸ� ����
	tcp::acceptor accepter(io_service, endpoint);				// ecceptor Ŭ������ Ŭ���̾�Ʈ�� ������ �޴� ����

	tcp::socket socket(io_service);								// tcp ������ ����� ���� io_service�� �Ҵ�
	accepter.accept(socket);									// acceptor �� accept�� ���� ������ ���� �غ� �Ѵ�. (�Ϸ� �� �� ���� ������)

	cout << "Ŭ���̾�Ʈ ����" << endl;

	for (;;)
	{
		std::array<char, 128> buf;												// STL�� array �����̳� ��� 
		buf.assign(0);
		system::error_code error;												// error_code Ŭ������ �ý��ۿ��� �߻��ϴ� �����ڵ带 ������ Ŭ���� �ַ� �߻��� �����ڵ�� �޽��� ȹ��
		size_t len = socket.read_some(buffer(buf), error);						// socket Ŭ������ read_some�� ���� Ŭ���̾�Ʈ�� ���� �����͸� ����.
																				// �Ű������� ���ۿ� error_code�� ����Ѵ�.
																				// read_some�� ���� ����ĳġ�� ����, ��������, ���Ӳ������� Ȯ�� �ؾ���.

		if (error)																// ������ ���� �߻��� ���ǹ� ���� / error�� ����
		{
			if (error == error::eof)
			{
				cout << "Ŭ���̾�Ʈ�� ������ ���������ϴ�" << endl;
			}
			
			else
			{
				cout << "error No: " << error.value() << "error Message"
					<< error.message() << endl;
			}
			break;
		}
		cout << "Ŭ���̾�Ʈ���� ���� �޽���: " << &buf[0] << endl;

		char szMessage[128] = { 0, };
		sprintf_s(szMessage, 128 - 1, "Re:%s", &buf[0]);
		int nMsgLen = strnlen_s(szMessage, 128 - 1);

		system::error_code ignored_error;
		socket.write_some(buffer(szMessage, nMsgLen), ignored_error);
		cout << "Ŭ���̾�Ʈ�� ���� �޽���:" << szMessage << endl;

	}
	getchar();
	return 0;
}
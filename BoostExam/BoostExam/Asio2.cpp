#include <iostream>
#include <boost\asio.hpp>
#include <boost\function.hpp>
#include <boost\bind.hpp>
#include <boost\thread.hpp>

using namespace std;

class Test
{
public:
	void Print(int x)
	{
		boost::function<void(int)> printHandler = [](int x)
		{
			for (int i = 0; i <= x; i++)
			{
				cout << __FUNCTION__ << " : called and loop : " << i << endl;
				boost::this_thread::sleep_for(boost::chrono::seconds(1));
			}
		};
		is.post(boost::bind(printHandler, x)); // is 내부에 intHandler 의 핸들러 추가
	}

	void Start()
	{ 
		is.run();
	}

	void stop()
	{
		is.stop();
	}

private:
	boost::asio::io_service is;
};

int main()
{
	Test test;
	test.Print(10);
	test.Start();
	cout << "end of main" << endl;
	cin.get();
	test.stop();

	return 0;
}
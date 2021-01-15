#include <iostream>
#include <boost\timer\timer.hpp>
#include <boost\chrono.hpp>
#include <boost\thread.hpp>
#include <boost\bind.hpp>
#include <boost\asio.hpp>

using namespace std;

class timers
{
public:
	timers(boost::asio::io_context& io, int gettime):strand_(io), dt(io, boost::posix_time::milliseconds(0))
	{
		this->gettime = gettime;
		dt.async_wait(boost::asio::bind_executor(strand_, boost::bind(&timers::timer1, this)));
	}

	void timer1()
	{

		boost::function<void(int, const boost::system::error_code&)> lambda = [](int timerID, const boost::system::error_code& error) { // 타이머 실행
			cout << "handle timer" << endl;
		};

		boost::function<void(int)> jobRun = [=](int n)
		{	
			boost::this_thread::sleep(boost::posix_time::milliseconds(n));

			dt.expires_from_now(boost::posix_time::milliseconds(0));
			dt.async_wait(boost::asio::bind_executor(strand_, boost::bind(lambda, 1, boost::asio::placeholders::error)));
		};

		strand_.post(boost::bind(jobRun, this->gettime));
	}

private:
	boost::asio::deadline_timer dt;  // 데드라인 타이머
	boost::asio::io_context::strand strand_;
	int gettime;
};

int main()
{
	boost::asio::io_context io;
	timers tms(io, 10000);
	boost::thread th1 = boost::thread(boost::bind(&boost::asio::io_context::run, &io));
	io.run();
	th1.join();

	return 0;
}
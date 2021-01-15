#include <iostream>
#include <boost\asio\deadline_timer.hpp>
#include <boost\asio.hpp>
#include <boost\thread\thread.hpp>

using namespace std;

class threadset
{
public:
	threadset(boost::asio::io_context &io):strand_(io), 
		dt1(io, boost::posix_time::seconds(1)),
		dt2(io, boost::posix_time::seconds(1)), count(0)
	{
		dt1.async_wait(boost::asio::bind_executor(strand_, boost::bind(&threadset::thread1, this)));
		dt2.async_wait(boost::asio::bind_executor(strand_, boost::bind(&threadset::thread2, this)));
	}

	~threadset()
	{
		cout << "End Thread: " << count <<  endl;
	}

	void thread1()
	{
		if (count < 10)
		{  
			cout << "thread1: " << count << endl;
			count++;
			dt1.expires_at(dt1.expires_at() + boost::posix_time::seconds(1));
			dt1.async_wait(boost::asio::bind_executor(strand_, boost::bind(&threadset::thread1, this)));
		}
	}

	void thread2()
	{
		if (count < 10)
		{
			cout << "thread2: " << count << endl;
			count++;
			dt2.expires_at(dt2.expires_at() + boost::posix_time::seconds(1));
			dt2.async_wait(boost::asio::bind_executor(strand_, boost::bind(&threadset::thread2, this)));
		}
	}

private:
	boost::asio::io_context::strand strand_;
	boost::asio::deadline_timer dt1;
	boost::asio::deadline_timer dt2;
	int count;
};

int main()
{
	boost::asio::io_context io;
	threadset ts(io);
	boost::thread t(boost::bind(&boost::asio::io_context::run, &io));
	io.run();
	t.join();

	return 0;
}
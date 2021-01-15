#include <iostream>
#include <boost\thread.hpp>

using namespace std;

class JobTimeChecker					// 작업의 시간을 측정하기 위해 작업을 모아놓은 클래스
{
public:

	void TimeChecker()					// 일하는 시간을 측정하는 멤버함수 (쓰레드 1)
	{
		while (status)
		{
			count++;
			cout << count << endl;		// 디버깅
			boost::this_thread::sleep(boost::posix_time::millisec(10));
		}
		cout << "Jobs Done! 까지 : " << count << endl;
	}

	void ExecuteJob(int num)			// 연산작업을 시키나 중간에 sleep을 발생시켜 작업에 공백을 발생시킴 (쓰레드 2)
	{
		for (int i = 0; i < num ; i++)
		{
			cout << "Job Done!" << endl;
			boost::this_thread::sleep(boost::posix_time::millisec(50));
		}
		status = false;
	}
private:
	int count = 0;
	bool status = true;
};

int main()
{
	JobTimeChecker jtc;

	int input = 0;

	cin >> input;

	boost::thread th1 = boost::thread(boost::bind(&JobTimeChecker::TimeChecker, &jtc));
	boost::thread th2 = boost::thread(boost::bind(&JobTimeChecker::ExecuteJob, &jtc, input));

	th2.join();
	th1.join();

	return 0;
}
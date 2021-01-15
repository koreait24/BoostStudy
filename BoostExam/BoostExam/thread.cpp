#include <iostream>
#include <boost\thread.hpp>

using namespace std;

class JobTimeChecker					// �۾��� �ð��� �����ϱ� ���� �۾��� ��Ƴ��� Ŭ����
{
public:

	void TimeChecker()					// ���ϴ� �ð��� �����ϴ� ����Լ� (������ 1)
	{
		while (status)
		{
			count++;
			cout << count << endl;		// �����
			boost::this_thread::sleep(boost::posix_time::millisec(10));
		}
		cout << "Jobs Done! ���� : " << count << endl;
	}

	void ExecuteJob(int num)			// �����۾��� ��Ű�� �߰��� sleep�� �߻����� �۾��� ������ �߻���Ŵ (������ 2)
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
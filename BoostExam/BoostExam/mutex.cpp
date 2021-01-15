#include <iostream>
#include <boost\thread\mutex.hpp>
#include <boost\thread\locks.hpp>
#include <boost\thread.hpp>

using namespace std;

struct Job
{
	int jobnum;
	bool isSolved;
};

class JobTable
{
public:
	void Admin(Job job[])
	{
		while (1)
		{
			job[this->Aindex].isSolved = false;
			job[this->Aindex].jobnum = this->Aindex;
			cout << "Admin : " << job[this->Aindex].jobnum << "��° ���� �����Ǿ����ϴ�." << endl;
			this->Aindex++;
			boost::this_thread::sleep(boost::posix_time::millisec(600));
		}
	}

	void Worker1(Job job[]) // Work2�� �ڵ� ����
	{
		while (1)
		{
			boost::this_thread::sleep(boost::posix_time::millisec(10)); // ���� �������� ���� �۵��ϱ� ���� ������
			boost::lock_guard<boost::mutex> lock(i_mutex);				// Worker2 �� ���ÿ� ��������� ������ ������� �ʱ� ���� lock
			if (job[this->Sindex].isSolved == false)					// ���� �������� �Ǵ�
			{


				job[this->Sindex].isSolved = true;
				cout << "Worker1 : " << job[this->Sindex].jobnum << "��° ���� �ذ�Ǿ����ϴ�." << endl;
				this->Sindex++;
				boost::this_thread::sleep(boost::posix_time::millisec(400));
			}
			else
			{
				cout << "Worker1 : ���� ���� �������� �ʾҽ��ϴ�." << endl;
				boost::this_thread::sleep(boost::posix_time::millisec(400));
			}
		}
	}
	void Worker2(Job job[])
	{
		while (1)
		{
			boost::this_thread::sleep(boost::posix_time::millisec(10));
			boost::lock_guard<boost::mutex> lock(i_mutex);
			if (job[this->Sindex].isSolved == false)
			{


				job[this->Sindex].isSolved = true;
				cout << "Worker2 : " << job[this->Sindex].jobnum << "��° ���� �ذ�Ǿ����ϴ�." << endl;
				this->Sindex++;
				boost::this_thread::sleep(boost::posix_time::millisec(400));
			}
			else
			{
				cout << "Worker2 : ���� ���� �������� �ʾҽ��ϴ�." << endl;
				boost::this_thread::sleep(boost::posix_time::millisec(400));
			}
		}
	}
private:
	int Sindex = 0;
	int Aindex = 0;
	boost::mutex i_mutex;
};

int main()
{
	JobTable jt;
	Job j[1000];


	bool isWork = false;

	boost::thread makeJob(boost::bind(&JobTable::Admin, &jt, j));
	boost::thread solveJob1(boost::bind(&JobTable::Worker1, &jt, j));
	boost::thread solveJob2(boost::bind(&JobTable::Worker2, &jt, j));

	makeJob.join();
	solveJob1.join();
	solveJob2.join();
	

	//solveJob.join();
}
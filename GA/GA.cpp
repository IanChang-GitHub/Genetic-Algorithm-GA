// GA.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <vector>
#include <time.h>
#include <numeric> 
using namespace std;


void cross_over(vector<vector<int>>& solution, double cross_rate)
{
	int middle = solution.size() / 2;
	for (int i = 0;i < middle;i++)
	{
		double random = (double)rand() / RAND_MAX;
		if (random < cross_rate)
		{
			int cross_point = (int)rand() % solution[0].size();
			for (int j = cross_point;j < solution[0].size();j++)
			{
				swap(solution[i][j], solution[middle + i][j]);
			}
		}
	}
}

void mutation(vector<vector<int>>& solution, double mutation_rate)
{
	for (int i = 0;i < solution.size();i++)
		for (int j = 0;j <100;j++)
		{
			double random = (double)rand() / RAND_MAX;
			if (random < mutation_rate)
			{
				solution[i][j] = !solution[i][j];
			}
		}
}

vector<vector<int>> wheel_select(vector<vector<int>>& solution, vector<double>& value) //輪盤選擇法
{
	int total= accumulate(value.begin(), value.end(), 0);//機率分母
	vector<double> probability(solution.size(),0);
	vector<vector<int>> seletion(solution.size());
	seletion = solution;
	for (int i = 0;i < solution.size();i++) //計算每個解機率
	{
		probability[i] =(value[i] / total);
	}
	for (int i = 0;i < solution.size();i++)
	{
		double random =(double) rand() / RAND_MAX;
		for (int j = 0;j < solution.size();j++)
		{
			if ((random - probability[j]) <= 0)
			{
				seletion[i] = solution[j];
				break;
			}
		}
	}
	return seletion;

}

vector<vector<int>> tournament_select(vector<vector<int>>& solution, vector<double>& value) //競爭選擇法
{
	vector<vector<int>> seletion(solution.size());
	for (int i = 0;i < solution.size();i++)
	{
		int condidate = rand() % solution.size();
		double condidate_value = value[condidate];
		for (int j = 1;j < 20;j++)
		{
			int random = rand() % solution.size();
			if (value[random] > condidate)
			{
				condidate = random;
				condidate_value = value[random];
			}
		}
		seletion[i] = solution[condidate];
	}
	return seletion;
}


vector<double> evaluation(vector<vector<int>>& solution)
{
	vector<double> value(solution.size(), 0);
	for (int i = 0;i < solution.size();i++)
	{
		value[i] = accumulate(solution[i].begin(), solution[i].end(), 0);
	}
	return value;
}
int main()
{
	int sol_num = 100;//解個數
	vector<vector<int>> solution(sol_num, vector<int>(100)); //各個解
	vector<double> value(sol_num);
	vector<int> best_solution(100);
	int iterator = 2000;
	vector<int> average(iterator, 0);
	srand(time(NULL));
	for (int i = 0;i < 30;i++)
	{
		int best_value = 0; //最佳值
		int times = 0;

		for (int i = 0;i < sol_num;i++)
			for (int j = 0;j < 100;j++)
			{
				solution[i][j] = (int)rand() % 2;
			}

		while (times < iterator)
		{
			value = evaluation(solution);
			for (int i = 0;i < value.size();i++)
			{
				if (value[i] > best_value)
				{
					best_value = value[i];
					best_solution = solution[i];
				}
			}
			solution = tournament_select(solution, value);
			cross_over(solution, 0.9);
			mutation(solution, 0.01);
			average[times] = average[times] + best_value;
			times++;
		}

		for (int i = 0;i < 100;i++)
		{
			cout << best_solution[i];
		}
		cout << endl;
		cout << "最佳值: " << best_value << endl;
	}
	cout << "30次平均: ";
	for (int i = 0;i < iterator;i++)
	{
		cout << average[i]/30 << " ";
	}
	
}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案

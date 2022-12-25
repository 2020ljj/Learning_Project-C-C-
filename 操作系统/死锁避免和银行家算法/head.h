#pragma once
#include<iostream>
#include <iomanip>
#include<stack>
#include<queue>
constexpr int Num = 20;		//常量
int request[Num];
std::queue<int*> requestSeq;//请求队列
bool Safe(int n, int m, int* available, int** allocation, int** need);
void DisplayProcess(int m) {
	std::cout << "过去进程申请表:" << '\n';
	while (!requestSeq.empty()) {
		std::cout << "P" << requestSeq.front()[0]<<" ";
		for(int i =1;i<m+1;i++)
			std::cout << std::setw(2) << requestSeq.front()[i];
		if (requestSeq.front()[m + 1])
			std::cout << "   suceess";
		else
			std::cout << "   fail";
		std::cout << std::endl;
		requestSeq.pop();
	}
}
void DisplayResult(int n, int m, int* available, int** max, int** allocation, int** need) {
	std::cout << "当前资源分配表:" << '\n';
	std::cout << std::left << std::setw(2 * m) << "P"
		<< std::left << std::setw(2 * m) << "M"
		<< std::left << std::setw(2 * m) << "AL"
		<< std::left << std::setw(2 * m) << "N"
		<< std::left << std::setw(2 * m) << "Av"<<'\n';
	for (int i = 0; i < n; i++) {
		std::cout << "P" << std::left << std::setw(m)  << i;
		for (int j = 0; j < m; j++) {
			std::cout << std::left << std::setw(2) << max[i][j];
		}
		for (int j = 0; j < m; j++) {
			std::cout << std::left << std::setw(2) << allocation[i][j];
		}
		for (int j = 0; j < m; j++) {
			std::cout << std::left << std::setw(2) << need[i][j];
		}
		if (0 == i) {
			for (int j = 0; j < m; j++) {
				std::cout << std::left << std::setw(2) <<available[j];
			}
		}
		std::cout << '\n';
	}
	
}
void update(int i,int n, int m, int*& available, int** max, int**& allocation, int**& need) {
	for (int j = 0; j < m; j++) {
		available[j] = available[j] - request[j];
		allocation[i][j] = allocation[i][j] + request[j];
		need[i][j] = need[i][j] - request[j];
	}
}
void recover(int i, int n, int m, int*& available, int** max, int**& allocation, int**& need) {
	for (int j = 0; j < m; j++) {
		available[j] = available[j] + request[j];
		allocation[i][j] = allocation[i][j] - request[j];
		need[i][j] = need[i][j] + request[j];
	}
}
int Banker(int n,int m,int*&available, int** max, int**& allocation, int**& need) {
	int i;									//进程下标
	bool flag = true;						//申请是否成功
	int* temp = new int[m + 2] {0};			//记录请求信息：下标0表示请求进程，后m位代表资源申请大小，最后一位表示申请结果（0/1）
	std::cout << "请输入需要申请资源的进程号：(P0~P" << n - 1 << ",输入-1结束申请资源并显示结果)\n";
	std::cin >> i;
	if (-1 == i)
		return -1;
	if (i<0 || i>n)
		std::cout << "输入越界！" << '\n';
	std::cout << "请输入需要申请的资源数，当前最大资源数为"<< m <<"（例 0 1 0）：\n";
	for (int j = 0; j < m; j++) 
		std::cin >> request[j];
	for (int j = 0; j < m; j++) {
		if (request[j] > need[i][j]) {
			std::cout << "申请失败！\n";
			flag = 0;
			break;
		}
		else {
			if (request[j] > available[j]) {
				std::cout << "资源不足！\n";
				flag = 0;
				break;
			}
		}
	}
	temp[0] = i;
	for (int k = 1; k < m + 1; k++)
		temp[k] = request[k - 1];
	temp[m + 1] = flag;
	requestSeq.push(temp);			//申请情况存入申请序列
	if (flag == true) {
		update(i, n, m, available, max, allocation, need);
		if (Safe(n, m, available, allocation, need)) {
			return 1;
		}
		else {
			std::cout << "找不到安全序列！\n";
			recover(i, n, m, available, max, allocation, need);
			return 0;
		}
	}
	else
		return 0;
}
int noBanker(int n, int m, int*& available, int** max, int**& allocation, int**& need) {
	int i;
	bool flag = true;
	int *temp = new int[m + 2]{0};			//记录请求信息：下标0表示请求进程，后m位代表资源申请大小，最后一位表示申请结果（0/1）
	std::cout << "请输入需要申请资源的进程号：(P0~P" << n - 1 << ",输入-1结束申请资源并显示结果)\n";
	std::cin >> i;
	if (-1 == i)
		return -1;
	if (i<0 || i>n)
		std::cout << "输入越界！" << '\n';
	for (int j = 0; j < m; j++)
		std::cin >> request[j];
	for (int j = 0; j < m; j++) {
		if (request[j] > need[i][j]) {
			std::cout << "申请失败！\n";
			flag = 0;
			break;
		}
		else {
			if (request[j] > available[j]) {
				std::cout << "资源不足！\n";
				flag = 0;
				break;
			}
		}
	}
	temp[0] = i;
	for (int k = 1; k < m+1; k++)
		temp[k] = request[k - 1];
	temp[m + 1] = flag;
	requestSeq.push(temp);			//申请情况存入申请序列
	if (flag == true) {
		update(i, n, m, available, max, allocation, need);
		return 1;	
	}
	else
		return 0;
}
bool Safe(int n,int m, int* available, int** allocation,int **need) {
	int* finish = new int[n]{0};
	int* work = new int[m] {0};
	std::queue<int> s;
	int i = 0, t = 0,sum = 0;
	for (int j = 0; j < m; j++) {
		work[j] = available[j];
	}
	while (i<n) {
		if (finish[i] == 0) {
			while (t < m) {
				if (work[t] >= need[i][t])
					t++;
				else
					break;
			}
			if (t == m) {
				for(int j = 0;j<m;j++)
					work[j] = work[j] + allocation[i][j];
				finish[i] = 1;
				s.push(i);
				sum++;
				i = -1;
			}
			t = 0;
		}
		i++;
	}
	if (sum == n) {
		delete []work;
		delete []finish;
		std::cout << "安全序列：P" << s.front();
		s.pop();
		for (int i = 0; i < n-1; i++) {
			std::cout << "-->P" << s.front();
			s.pop();
		}
		return true;//安全
	}
	else {
		delete []work;
		delete []finish;
		return false;
	}
}
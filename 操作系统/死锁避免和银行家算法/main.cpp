#include<iostream>
#include"head.h"
/*
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

7 5 3
3 2 2
9 0 2
2 2 2
4 3 3



*/
int main() {
	int n = 0, m = 0;
	char ch;
	std::cout << "请输入进程数和资源种类数：" << std::endl;
	std::cin >> n >> m;
	///******1.定义关键数组******///
	int* Available = (int*)malloc(sizeof(int) * m);
	int** Max = new int*[n] {0};
	int** Allocation = new int* [n] {0};
	//int Allocation1[5][3] = {{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
	int** Need = new int* [n] {0};
	for (int i = 0; i < n; i++) {
		Max[i] = new int[m] {0};
	}
	for (int i = 0; i < n; i++) {
		Allocation[i] = new int[m] {0};
	}
	for (int i = 0; i < n; i++) {
		Need[i] = new int[m] {0};
	}
	///******2.初始化数组******///
	std::cout << "请依次输入资源M0~M" << m - 1 << "的可用数目：" << std::endl;
	for (int j = 0; j < m; j++) {
		std::cin>>Available[j];
	}
	std::cout << "请依次输入进程P0~P" << n - 1 << "进程占有的资源数：" << std::endl;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			std::cin >> Allocation[i][j];
		}
	std::cout << "请依次输入进程P0~P"<<n-1<<"进程所需的最大资源数：" << std::endl;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			std::cin >> Max[i][j];
			Need[i][j] = Max[i][j] - Allocation[i][j];
		}
	DisplayResult(n, m, Available, Max, Allocation, Need);
	while (1) {
		std::cout << "请选择是否采用银行家算法：(y/n)\n";
		std::cout << "结束测试并释放资源：(0)\n";
		std::cin >> ch;
		if (ch == 'y' || ch == 'Y') {
			while (1) {
				int temp = Banker(n, m, Available, Max, Allocation, Need);
				if (-1 == temp) {
					DisplayResult(n, m, Available, Max, Allocation, Need);
					DisplayProcess(m);
					break;
				}
				else if (0 == temp)
					std::cout << "申请资源失败！" << '\n';
				else if (1 == temp)
					std::cout << "申请资源成功！" << '\n';
			}
		}
		else if (ch == 'n' || ch == 'N') {
			while (1) {
				int temp = noBanker(n, m, Available, Max, Allocation, Need);
				if (-1 == temp) {
					DisplayResult(n, m, Available, Max, Allocation, Need);
					DisplayProcess(m);
					break;
				}
				else if (0 == temp)
					std::cout << "申请资源失败！" << '\n';
				else if (1 == temp)
					std::cout << "申请资源成功！" << '\n';
			}
		}
		else if(ch=='0') {
			delete[]Allocation;
			delete[]Max;
			delete[]Need;
			break;
		}
		else {
			std::cout << "输入异常！\n";
		}
	}
	return 0;
}

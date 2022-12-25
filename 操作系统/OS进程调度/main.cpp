#include"head.h"
#include<iostream>
#include<random>
void prinf(std::vector<PCB>& pcbs) {
	int n = pcbs.size();
	for (auto item : pcbs) {
		item.Display();
	}
}
void SortbyArrive(std::vector<PCB>& pcbs) {					//按照进程的到来先后进行排列
	int min = 0;
	int n = pcbs.size();
	for (int i = 0; i < n-1; i++) {
		min = i;
		for (int j = i + 1; j < n; j++) {
			if (pcbs[j].Arrival() < pcbs[min].Arrival()) {
				min = j;
			}
		}
		if (min != i) {
			PCB temp;
			temp = pcbs[i];
			pcbs[i] = pcbs[min];
			pcbs[min] = temp;
		}
	}

}
void SortbyPriority(std::vector<PCB>& pcbs) {					//按照进程的优先级进行排列
	

}
int main() {
	while (1) {
		int temp,alltime,num;
		char id;				//进程ID号
		int at_time;			//到达时间
		int piece;				//时间片
		std::cout << "请输入进程数目：" << '\n';
 		std::cin >> num;
		std::vector<PCB> pcbs(num);
		std::default_random_engine e(time(0));
		std::uniform_int_distribution<int> u1(1, 9);
		std::uniform_int_distribution<int> u2(1, 4);
		piece = u2(e);			//时间片取随机数
		std::cout << "请依次输入PCB ID号 和 到达时间" << '\n';
		
		for (int i = 0; i < num; i++) {
			std::cin >> id >> at_time;
			alltime = u1(e);					//进程时间片随机
			pcbs[i] = PCB(id, at_time, alltime);
			 
		}
		
		int choice;
		std::cout << "多级反馈队列调度算法:1" << '\n';
		std::cout << "轮转调度法:2" << '\n';
		std::cout << "选择对应的调度算法:" << '\n';
		std::cin >> choice;
		if (choice < 1 || choice>2)
			std::cout<<"INPUT EXCEPTION！" << '\n';
		else if (1 == choice) {
			SortbyArrive(pcbs);
			prinf(pcbs);
			MFQ(pcbs);
		}
		else if (2 == choice) {
			SortbyArrive(pcbs);
			prinf(pcbs);
			RR(pcbs,piece);
			
		}
	}
	return 0;
}
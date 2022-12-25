#pragma once
#ifndef HEAD_H
#define HEAD_H
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<deque>
enum status{R,W,F};

class PCB {
	friend void RR(std::vector<PCB>& pcbs, int piece);
	friend void MFQ(std::vector<PCB>& pcbs);
public:
	PCB() = default;
	PCB(char id, int at_time, int all_time);
	int Arrival();
	int Priority();
	void Display();
	void SetPriority(int pri);
	void SetState(status st);

private:
	int priority;
	int cputime;
	int alltime;
	int arrivaltime;
	int remainingtime;
	status state;
	char ID;
	PCB* next;
};
PCB::PCB(char id, int at_time, int all_time) {
	priority = 0;
	cputime = 0;
	alltime = all_time;
	arrivaltime = at_time;
	remainingtime = all_time;
	state = R;
	ID = id;
	next = NULL;
}
int PCB::Arrival() {
	return arrivaltime;
}
int PCB::Priority() {
	return priority;
}
void PCB::Display() {
	std::cout << "进程ID:" << ID << "   " << "进程占用时间：" << alltime << "进程到达时间："<<"   " << arrivaltime << '\n';
}
void PCB::SetPriority(int pri) {
	priority = pri;
}
void PCB::SetState(status st) {
	state = st;
}
 void RR(std::vector<PCB>& pcbs,int piece) {
	 int time = 0;
	 int i = 1;
	 int n = pcbs.size();
	 PCB temp;
	 std::deque<PCB> readyqueue;
	 readyqueue.push_back(pcbs[0]);
	 pcbs[0].SetState(R);
	 time += pcbs[0].Arrival();
	 std::cout << "时间片:" << piece<< '\n';
	 std::cout << "time:" << time << "进程" << pcbs[0].ID << "加入队列" << '\n';
	 while (n!=0) {
		 while (i < pcbs.size() && pcbs[i].Arrival() <= time) {
			 readyqueue.push_back(pcbs[i]);
			 std::cout << "time:" << time << "进程" << pcbs[i].ID << "加入队列" << '\n';
			 i++;
		 }
		 if (!readyqueue.empty()) {
			 readyqueue[0].SetState(R);
			 std::cout << "time:" << time << "  执行进程" << readyqueue[0].ID  << '\n';
			 if (readyqueue[0].remainingtime <= piece) {
				 readyqueue[0].SetState(R);
				 time += readyqueue[0].remainingtime;
				 readyqueue[0].remainingtime = 0;
				 std::cout << "time:" << time << "进程" << readyqueue[0].ID << "弹出队列" << "   进程" << readyqueue[0].ID << "完成" << '\n';
				 readyqueue.pop_front();					//弹出已完成的进程
				 n--;
			 }
			 else {
				 time += piece;
				 readyqueue[0].remainingtime -= piece;
				 readyqueue[0].SetState(W);
				 temp = readyqueue[0];
				 readyqueue.pop_front();
				 readyqueue.push_back(temp);
			 }
		 }
		 else if(time < pcbs[i].arrivaltime) {
			 std::cout << "等待" << pcbs[i].arrivaltime - time << "s" << '\n';
			 time = pcbs[i].arrivaltime;
		 }
		 
	 }
	 std::cout << "耗时：" << time<<'\n';
}
 void MFQ(std::vector<PCB>& pcbs) {
	 std::deque<PCB> queue1,queue2, queue3,queue4;
	 int piece1 = 2;			//就绪队列1:FCFS
	 int piece2 = 4;			//就绪队列2：RR
	 int piece3 = 8;
	 int piece4 = 16;
	 int time = 0;
	 int n = pcbs.size();
	 int i = 1;
	 queue1.push_back(pcbs[0]);
	 pcbs[0].SetState(R);
	 time += pcbs[0].Arrival();
	 std::cout << "time:" << time << "进程" << pcbs[0].ID << "加入队列①" << '\n';
	 while (n != 0) {
		 if (time >= pcbs[i].arrivaltime) {							//2.3.4队列执行完成后也要检查依次是否有新进程到达
			 while (i < pcbs.size() && pcbs[i].Arrival() <= time) {
				 queue1.push_back(pcbs[i]);
				 std::cout << "进程" << pcbs[i].ID << "加入队列①" << '\n';
				 i++;
			 }
		 }
		 if (!queue1.empty()) {
				 std::cout << "time:" << time << "  在队列①执行进程" << queue1[0].ID << '\n';
				 if (queue1[0].remainingtime <= piece1) {
					 time += queue1[0].remainingtime;
					 queue1[0].remainingtime = 0;
					 std::cout << "time:" << time << "进程" << queue1[0].ID << "弹出队列①" << "   进程" << queue1[0].ID << "完成" << '\n';
					 queue1.pop_front();					//弹出已完成的进程
					 n--;
				 }
				 else {
					 time += piece1;
					 queue1[0].remainingtime -= piece1;
					 PCB temp = queue1[0];
					 queue1.pop_front();
					 queue2.push_back(temp);
					 std::cout << "time:" << time << "进程" << temp.ID << "加入队列②" << '\n';

				 }
		 }
		 else if (!queue2.empty()) {
			 std::cout << "time:" << time << "  在队列②执行进程" << queue2[0].ID << '\n';
			 if (queue2[0].remainingtime <= piece2) {
				 time += queue2[0].remainingtime;
				 queue2[0].remainingtime = 0;
				 std::cout << "time:" << time << "进程" << queue2[0].ID << "弹出队列②" << "   进程" << queue2[0].ID << "完成" << '\n';
				 queue2.pop_front();					//弹出已完成的进程
				 n--;
			 }
			 else {
				 time += piece2;
				 queue2[0].remainingtime -= piece2;
				 PCB temp = queue2[0];
				 queue2.pop_front();
				 queue3.push_back(temp);
				 std::cout << "time:" << time << "进程" << temp.ID << "加入队列③" << '\n';

			 }
		 }
		 else if (!queue3.empty()) {
			 std::cout << "time:" << time << "  在队列③执行进程" << queue3[0].ID << '\n';
			 if (queue3[0].remainingtime <= piece3) {
				 time += queue3[0].remainingtime;
				 queue3[0].remainingtime = 0;
				 std::cout << "time:" << time << "进程" << queue3[0].ID << "弹出队列③" << "   进程" << queue3[0].ID << "完成" << '\n';
				 queue3.pop_front();					//弹出已完成的进程
				 n--;
			 }
			 else {
				 time += piece3;
				 queue3[0].remainingtime -= piece3;
				 PCB temp = queue3[0];
				 queue3.pop_front();
				 queue4.push_back(temp);
				 std::cout << "time:" << time << "进程" << temp.ID << "加入队列④" << '\n';

			 }
		 }
		 else if (!queue4.empty()) {
			 std::cout << "time:" << time << "  在队列4执行进程" << queue4[0].ID << '\n';
			 if (queue4[0].remainingtime <= piece4) {
				 time += queue4[0].remainingtime;
				 queue4[0].remainingtime = 0;
				 std::cout << "time:" << time << "进程" << queue4[0].ID << "弹出队列④" << "   进程" << queue4[0].ID <<"完成"<<'\n';
				 queue4.pop_front();					//弹出已完成的进程
				 n--;
			 }
			 else {
				 time += piece4;
				 queue4[0].remainingtime -= piece4;
				 PCB temp = queue4[0];
				 queue4.pop_front();
				 queue4.push_back(temp);
				 std::cout << "time:" << time << "进程" << temp.ID << "加入队列④" << '\n';

			 }
		 }
		 else if (time < pcbs[i].arrivaltime) {										//队列全为空的话把时间调到下一个进程的到来时刻
			 std::cout << "等待" << pcbs[i].arrivaltime - time <<"s" << '\n';
			 time = pcbs[i].arrivaltime;

		 }
	 }
	 std::cout << "耗时：" << time << '\n';
 }
#endif // !HEAD_H

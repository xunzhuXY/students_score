#include<stdio.h>
#include<string.h>

#include "tool.h"

//结构体定义

//生日（年月日）
struct birth{
	int year;
	int month;
	int day;
}birth;

//学生信息
struct stu{
	char name[30];
	char id[8];
	char sex[2];
	struct birth bir;
	char addr[100];
	char phone[15];
	char email[50];
}stu;

//课程信息
struct class {
	char class_id[50];
	char class_name[50];
	int score;
};

//成绩信息
struct score {
	struct class cls;
	struct stu stu;
	int mark;
	int avg;
	int sum;
};


void main() {
	while (1) {
		menu1();
		if(m1_start1()) return;
		}
}
#include<stdio.h>
#include<string.h>

#include "tool.h"

//结构体定义

//生日（年月日）
typedef struct{
	int year;
	int month;
	int day;
}birth;

//学生信息
typedef struct{
	char name[30];
	char id[8];
	char sex[2];
	birth bir;
	char addr[100];
	char phone[15];
	char email[50];
}stu;

//课程信息
typedef struct{
	char class_id[50];
	char class_name[50];
	int score;
}class;

//成绩信息
typedef struct{
    class cls;
	stu stu;
	int mark;
	int avg;
	int sum;
}score;


void main() {
	while (1) {
		menu1();
		if(m1_start1()) return;
		}
}
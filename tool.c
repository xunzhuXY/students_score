#include "tool.h"
#include<stdio.h>
#include<string.h>

void menu1(){
	printf("0.退出\n");
	printf("1.录取学生信息\n");
	printf("2.录取课程信息\n");
	printf("3.录取成绩信息\n");
	printf("4.读取学生信息\n");
	printf("5.读取课程信息\n");
	printf("6.读取成绩信息\n");
	printf("7.输出学生所有课程成绩以及平均分\n");
	printf("8.输出学生所有课程成绩以及总学分\n");
	printf("9.按课程成绩排名\n");
	printf("10.按学生平均分排名\n");
	return;
}

int m1_start1(){
	int c;
	scanf("%d", &c);
	switch (c){
	case 0:
		printf("quit\n");
		return 1;
		break;
	}
}
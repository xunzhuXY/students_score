#include "common.h"

#include<stdio.h>
#include<string.h>

void menu1(){
	printf("\n");
	printf("0.退出\n");
	printf("1.录取信息\n");
	printf("2.修改信息\n");
	printf("3.读取信息\n");
	printf("4.输出学生所有课程成绩以及平均分\n");
	printf("5.输出学生所有课程成绩以及总学分\n");
	printf("6.按课程成绩排名\n");
	printf("7.按学生平均分排名\n");
	printf("\n");
	return;
}

void menu11() {
	printf("\n");
	printf("0.返回上一级菜单\n");
	printf("1.录入学生信息\n");
	printf("2.录入课程信息\n");
	printf("3.录入成绩信息\n");
	printf("\n");
	m11_choose();
	return;
}

void menu21() {
	printf("\n");
	printf("0.返回上一级菜单\n");
	printf("1.修改学生信息\n");
	printf("2.删除学生信息\n");
	printf("3.修改课程信息\n");
	printf("4.删除课程信息\n");
	printf("5.修改成绩信息\n");
	printf("6.删除成绩信息\n");
	printf("\n");
	m21_choose();
	return;
}

void menu31() {
	printf("\n");
	printf("0.返回上一级菜单\n");
	printf("1.读取学生信息\n");
	printf("2.读取所有学生信息\n");
	printf("3.读取课程信息\n");
	printf("4.读取所有课程信息\n");
	printf("5.读取成绩信息\n");
	printf("6.读取所有成绩信息\n");
	printf("\n");
	m31_choose();
	return;
}

int m1_choose(){
	int c;
	scanf("%d", &c);
	switch (c){
	case 0:
		printf("已退出\n");
		return 1;
		break;
	case 1:
		menu11();
		return 0;
		break;
	case 2:
		menu21();
		return 0;
		break;
	case 3:
		menu31();
		return 0;
		break;
	default:
		return 0;
	}
}

void m11_choose(){
	int c1;
	scanf("%d", &c1);
	switch (c1)
	{
	case 0:
		break;
	case 1:
		stu new_stu = input_stu();
		add_stu(new_stu, "students.txt");
		break;
	}
	return;
}

void m21_choose(){
	int c2;
	scanf("%d", &c2);
	switch (c2)
	{
	case 0:
		break;
	case 1:
		modify_stu("students.txt");
		break;
	case 2:
		delete_stu("students.txt");
		break;
	}
	return;
}

void m31_choose(){
	int c3;
	scanf("%d", &c3);
	switch (c3)
	{
	case 0:
		break;
	case 1:
		input_search();
		break;
	case 2:
		display_all_stu("students.txt");
		break;
	}
	return;
}



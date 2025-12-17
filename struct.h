#ifndef struct_h
#define struct_h

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
	char sex[20];
	birth bir;
	char addr[100];
	char phone[15];
	char email[50];
}stu;

//课程信息
typedef struct {
	char class_id[50];
	char class_name[50];
	int score;
}class;

//成绩信息
typedef struct {
	char id[8];
	char class_id[50];
	int score;
}score;

#endif // !struct_h

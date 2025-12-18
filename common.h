#ifndef common_h
#define common_h
#include "struct.h"

void menu1();
void menu11(); 
void menu21();
void menu31();

int m1_choose();
void m11_choose();
void m21_choose();
void m31_choose();

//学生信息功能
stu input_stu();
void add_stu(stu stus, const char* filename);
void modify_stu(const char* filename);
void delete_stu(const char* filename);
void input_search();
void search_stu(const char* filename, char* name, char* id);
void display_all_stu(const char* filename);

//课程信息功能
class input_class();
void add_class(class clses, const char* filename);
void modify_class(const char* filename);
void delete_class(const char* filename);
void input_class_search();
void search_class(const char* filename, char* id);
void display_all_class(const char* filename);

//成绩信息功能
score input_score();
void add_score(score scores, const char* filename);
void modify_score(const char* filename);
void delete_score(const char* filename);
void input_score_search();
void search_score(const char* filename, char* id, char* class_id);
void display_all_score(const char* filename);

#endif // !common_h

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

stu input_stu();
void add_stu(stu stus, const char* filename);
void modify_stu(const char* filename);
void delete_stu(const char* filename);
void input_search();
void search_stu(const char* filename, char* name, char* id);
void display_all_stu(const char* filename);


#endif // !common_h

#include "common.h"

#include <stdio.h>
#include <string.h>

stu input_stu() {
	stu stu0;
	getchar();

    printf("\n");
    printf("---开始输入---\n");

	printf("学号：");
	fgets(stu0.id, sizeof(stu0.id), stdin);
	stu0.id[strcspn(stu0.id, "\n")] = 0;  // 去除换行符

	printf("姓名：");
	fgets(stu0.name, sizeof(stu0.name), stdin);
	stu0.name[strcspn(stu0.name, "\n")] = 0;  // 去除换行符

	printf("性别：");
	fgets(stu0.sex, sizeof(stu0.sex), stdin);
	stu0.sex[strcspn(stu0.sex, "\n")] = 0;

	printf("出生日期（年 月 日）：");
	scanf("%d %d %d", &stu0.bir.year, &stu0.bir.month, &stu0.bir.day);
	getchar();  // 清除缓冲区的换行符

	printf("地址：");
	fgets(stu0.addr, sizeof(stu0.addr), stdin);
	stu0.addr[strcspn(stu0.addr, "\n")] = 0;

	printf("电话：");
	fgets(stu0.phone, sizeof(stu0.phone), stdin);
	stu0.phone[strcspn(stu0.phone, "\n")] = 0;

	printf("邮箱：");
	fgets(stu0.email, sizeof(stu0.email), stdin);
	stu0.email[strcspn(stu0.email, "\n")] = 0;

	printf("\n");
	return stu0;
}

void add_stu(stu stus,const char* filename) {
    FILE* file = fopen(filename, "a");  // 追加模式
    if (file == NULL) {
        printf("无法打开文件 %s！\n", filename);
        return;
    }

    fprintf(file, "学号：%s\n", stus.id);
	fprintf(file, "姓名：%s\n", stus.name);
    fprintf(file, "性别：%s\n", stus.sex);
	fprintf(file, "出生日期：%d-%d-%d\n", stus.bir.year, stus.bir.month, stus.bir.day);
	fprintf(file, "地址：%s\n", stus.addr);
	fprintf(file, "电话：%s\n", stus.phone);
	fprintf(file, "邮箱：%s\n", stus.email);
	fprintf(file, "---");

    fclose(file);
}

void input_search() {
	char name[30];
	char id[8];
	getchar();

	printf("姓名：");
	fgets(name, sizeof(name), stdin);
	name[strcspn(name, "\n")] = 0;

	printf("学号：");
	fgets(id, sizeof(id), stdin);
	id[strcspn(id, "\n")] = 0;

	search_stu("students.txt",name,id);
}

void search_stu(const char* filename,char* name,char* id) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("无法打开文件 %s！\n", filename);
		return;
	}

	char line[256];
	stu current_stu;
	int found = 0;
	int in_record = 0;  // 标记是否在读取一个学生记录中
	int lines_in_record = 0;  // 记录当前学生信息的行数

	// 初始化结构体
	memset(&current_stu, 0, sizeof(current_stu));

	while (fgets(line, sizeof(line), file)) {
		// 去除行尾的换行符
		line[strcspn(line, "\n")] = 0;
		

		// 检查是否是分隔符
		if (strcmp(line, "---") == 0) {
			if (in_record) {
				if (strcmp(current_stu.id, id) == 0 && strcmp(current_stu.name, name) == 0) {
					found = 1;
					printf("\n找到匹配的学生信息：\n");
					printf("学号:%s\n", current_stu.id);
					printf("名字:%s\n", current_stu.name);
					printf("性别:%s\n", current_stu.sex);
					printf("生日:%d-%d-%d\n", current_stu.bir.year,
						current_stu.bir.month, current_stu.bir.day);
					printf("地址:%s\n", current_stu.addr);
					printf("电话:%s\n", current_stu.phone);
					printf("邮箱:%s\n", current_stu.email);
				}
				in_record = 0;
				lines_in_record = 0;
				memset(&current_stu, 0, sizeof(current_stu));
			}
			continue;
		}

		char* colon = strchr(line, ':');
		if (colon != NULL) {
			*colon = '\0';  // 分割键和值
			char* key = line;
			char* value = colon + 1;

			if (!in_record) in_record = 1;

			// 根据key存储到对应的字段
			if (strcmp(key, "学号") == 0) {
				strcpy(current_stu.id, value);
			}
			else if (strcmp(key, "姓名") == 0) {
				strcpy(current_stu.name, value);
			}
			else if (strcmp(key, "性别") == 0) {
				strcpy(current_stu.sex, value);
			}
			else if (strcmp(key, "生日") == 0) {
				sscanf(value, "%d-%d-%d", &current_stu.bir.year,
					&current_stu.bir.month, &current_stu.bir.day);
			}
			else if (strcmp(key, "地址") == 0) {
				strcpy(current_stu.addr, value);
			}
			else if (strcmp(key, "电话") == 0) {
				strcpy(current_stu.phone, value);
			}
			else if (strcmp(key, "邮箱") == 0) {
				strcpy(current_stu.email, value);
			}
			lines_in_record++;
		}
	}

	if (!found) {
		printf("查无此人");
	}

	fclose(file);
}
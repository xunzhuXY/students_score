#include "common.h"

#include <stdio.h>
#include <string.h>

class input_class() {
	class cls;
	getchar();
	
	printf("\n");
	printf("---开始输入课程信息---\n");

	printf("课程编号：");
	fgets(cls.class_id, sizeof(cls.class_id), stdin);
	cls.class_id[strcspn(cls.class_id, "\n")] = 0;  // 去除换行符

	printf("课程名称：");
	fgets(cls.class_name, sizeof(cls.class_name), stdin);
	cls.class_name[strcspn(cls.class_name, "\n")] = 0;  // 去除换行符

	printf("学分：");
	scanf("%d", &cls.score);
	printf("\n");

	return cls;
}

void add_class(class clses, const char* filename) {
	FILE* file = fopen(filename, "a");  // 追加模式
	if (file == NULL) {
		printf("无法打开文件 %s！\n", filename);
		return;
	}

	fprintf(file, "课程编号:%s\n", clses.class_id);
	fprintf(file, "课程名称:%s\n", clses.class_name);
	fprintf(file, "学分:%d\n", clses.score);
	fprintf(file, "---\n");

	fclose(file);
}

void modify_class(const char* filename) {
	FILE* file = fopen(filename, "r");  // 阅读模式
	if (file == NULL) {
		printf("无法打开文件 %s！\n", filename);
		return;
	}

	char id[50];
	printf("请输入要修改的课程编号：");
	getchar();
	fgets(id, sizeof(id), stdin);
	id[strcspn(id, "\n")] = 0;

	FILE* temp_file = fopen("temp.txt", "w");
	if (temp_file == NULL) {
		printf("无法创建临时文件！\n");
		fclose(file);
		return;
	}

	char line[256];
	int found = 0;
	int skip_count = 0;

	while (fgets(line, sizeof(line), file)) {
		// 检查是否是课程编号行
		if (strstr(line, "课程编号:") != NULL) {

			char id_in_file[50];
			sscanf(line, "课程编号:%s", id_in_file);

			if (strcmp(id_in_file, id) == 0) {
				found = 1;
				printf("找到课程信息，开始修改：\n");

				// 输入修改后的信息
				class modified_class;

				printf("课程编号：");
				fgets(modified_class.class_id, sizeof(modified_class.class_id), stdin);
				modified_class.class_id[strcspn(modified_class.class_id, "\n")] = 0;

				printf("课程名称：");
				fgets(modified_class.class_name, sizeof(modified_class.class_name), stdin);
				modified_class.class_name[strcspn(modified_class.class_name, "\n")] = 0;

				printf("学分：");
				scanf("%d", &modified_class.score);
				getchar();

				// 写入修改后的信息到临时文件
				fprintf(temp_file, "课程编号:%s\n", modified_class.class_id);
				fprintf(temp_file, "课程名称:%s\n", modified_class.class_name);
				fprintf(temp_file, "学分:%d\n", modified_class.score);

				// 跳过这个课程的所有信息（2行）
				skip_count = 2;
				continue;
			}
		}

		if (skip_count > 0) {
			skip_count--;
			continue;  // 跳过该行
		}

		fputs(line, temp_file);  // 复制未修改的行
	}

	fclose(file);
	fclose(temp_file);

	// 删除原文件，重命名临时文件
	remove(filename);
	rename("temp.txt", filename);

	if (found) {
		printf("课程信息修改成功！\n");
	}
	else {
		printf("未找到课程编号为 %s 的课程信息！\n", id);
		remove("temp.txt");  // 删除临时文件
	}
}

void delete_class(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("无法打开文件 %s！\n", filename);
		return;
	}

	char id[50];
	printf("请输入要删除的课程编号：");
	getchar();
	fgets(id, sizeof(id), stdin);
	id[strcspn(id, "\n")] = 0;

	// 创建临时文件
	FILE* temp_file = fopen("temp.txt", "w");
	if (temp_file == NULL) {
		printf("无法创建临时文件！\n");
		fclose(file);
		return;
	}

	char line[256];
	int found = 0;
	int skip_count = 0;  // 跳过后续行数

	while (fgets(line, sizeof(line), file)) {
		// 检查是否是课程编号行
		if (strstr(line, "课程编号:") != NULL) {
			char id_in_file[50];
			sscanf(line, "课程编号:%s", id_in_file);
			if (strcmp(id_in_file, id) == 0) {
				found = 1;
				printf("找到课程信息，正在删除...\n");
				// 跳过这个课程的所有信息（3行）
				skip_count = 3;
				continue;
			}
		}
		if (skip_count > 0) {
			skip_count--;
			continue;
		}
		// 写入其他行到临时文件
		fputs(line, temp_file);
	}
	fclose(file);
	fclose(temp_file);

	// 删除原文件，重命名临时文件
	remove(filename);
	rename("temp.txt", filename);

	if (found) {
		printf("课程信息删除成功！\n");
	}
	else {
		printf("未找到课程编号为 %s 的课程信息！\n", id);
		remove("temp.txt");  // 删除临时文件
	}
}

void input_class_search() {
	char id[50];
	getchar();

	printf("课程编号：");
	fgets(id, sizeof(id), stdin);
	id[strcspn(id, "\n")] = 0;

	search_class("classes.txt", id);
}

void search_class(const char* filename, char* id) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("无法打开文件 %s！\n", filename);
		return;
	}

	char line[256];
	class current_class;
	int found = 0;
	int in_record = 0;  // 标记是否在读取一个课程记录中
	int lines_in_record = 0;  // 记录当前课程信息的行数

	memset(&current_class, 0, sizeof(current_class));

	while (fgets(line, sizeof(line), file)) {
		// 去除行尾的换行符
		line[strcspn(line, "\n")] = 0;

		// 检查是否是分隔符
		if (strcmp(line, "---") == 0) {
			if (in_record) {
				if (strcmp(current_class.class_id, id) == 0) {
					found = 1;
					printf("\n找到匹配的课程信息：\n");
					printf("---\n");
					printf("课程编号:%s\n", current_class.class_id);
					printf("课程名称:%s\n", current_class.class_name);
					printf("学分:%d\n", current_class.score);
					printf("---\n");
				}
				in_record = 0;
				lines_in_record = 0;
				memset(&current_class, 0, sizeof(current_class));
			}
			continue;
		}

		// 读取课程信息
		char* colon = strchr(line, ':');
		if (colon != NULL) {
			char key[50];
			strncpy(key, line, colon - line);
			key[colon - line] = 0;
			char* value = colon + 1;
			if (!in_record) in_record = 1;
			// 根据key存储到对应的字段
			if (strcmp(key, "课程编号") == 0) {
				strcpy(current_class.class_id, value);
			}
			else if (strcmp(key, "课程名称") == 0) {
				strcpy(current_class.class_name, value);
			}
			else if (strcmp(key, "学分") == 0) {
				current_class.score = atoi(value);
			}
			lines_in_record++;
		}
	}

	if (!found)
	{
		printf("查无此课\n");
	}

	fclose(file);
}

void display_all_class(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("无法打开文件 %s！\n", filename);
		return;
	}

	char line[256];
	int count = 0;

	printf("\n========== 所有课程档案 ==========\n");
	while (fgets(line, sizeof(line), file)) {
		printf("%s", line);
		if (strstr(line, "---") != NULL) {
			printf("\n");
			count++;
		}
	}

	printf("========== 共 %d 节课 ==========\n", count);
	fclose(file);
}
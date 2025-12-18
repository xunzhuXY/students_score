#include "common.h"

#include <stdio.h>
#include <string.h>
//typedef struct {
//	char class_id[50];
//	char class_name[50];
//	char id[8];
//	char name[30];
//	int mark;
//}score;

score input_score() {
	score scr;
	getchar();

	printf("\n");
	printf("---开始输入成绩信息---\n");

	printf("课程编号：");
	fgets(scr.class_id, sizeof(scr.class_id), stdin);
	scr.class_id[strcspn(scr.class_id, "\n")] = 0;  // 去除换行符

	printf("课程名称：");
	fgets(scr.class_name, sizeof(scr.class_name), stdin);
	scr.class_name[strcspn(scr.class_name, "\n")] = 0;  // 去除换行符

	printf("学生学号：");
	fgets(scr.id, sizeof(scr.id), stdin);
	scr.id[strcspn(scr.id, "\n")] = 0;  // 去除换行符

	printf("学生姓名：");
	fgets(scr.name, sizeof(scr.name), stdin);
	scr.name[strcspn(scr.name, "\n")] = 0;  // 去除换行符

	printf("成绩：");
	scanf("%d", &scr.mark);
	getchar();  // 清除缓冲区的换行符
	printf("\n");

	return scr;
}

void add_score(score scores, const char* filename) {
	FILE* file = fopen(filename, "a");  // 追加模式
	if (file == NULL) {
		printf("无法打开文件 %s！\n", filename);
		return;
	}
	fprintf(file, "---\n");
	fprintf(file, "课程编号:%s\n", scores.class_id);
	fprintf(file, "课程名称:%s\n", scores.class_name);
	fprintf(file, "学生学号:%s\n", scores.id);
	fprintf(file, "学生姓名:%s\n", scores.name);
	fprintf(file, "成绩:%d\n", scores.mark);
	fprintf(file, "---\n");

	fclose(file);
}

void modify_score(const char* filename) {
	FILE* file = fopen(filename, "r");  // 阅读模式
	if (file == NULL) {
		printf("无法打开文件 %s！\n", filename);
		return;
	}
	getchar();

	char cls_id[50];
	char stu_id[8];
	score current_score;
	int found = 0;
	int in_record = 0;
	int lines_in_record = 0;

	printf("请输入要修改的课程编号：");
	fgets(cls_id, sizeof(cls_id), stdin);
	cls_id[strcspn(cls_id, "\n")] = 0;
	printf("请输入要修改的学生学号：");
	fgets(stu_id, sizeof(stu_id), stdin);
	stu_id[strcspn(stu_id, "\n")] = 0;

	FILE* temp_file = fopen("temp.txt", "w");
	if (temp_file == NULL) {
		printf("无法创建临时文件！\n");
		fclose(file);
		return;
	}

	char line[256];
	

	while (fgets(line, sizeof(line), file)) {
		// 去除行尾的换行符
		line[strcspn(line, "\n")] = 0;


		// 检查是否是分隔符
		if (strcmp(line, "---") == 0) {
			if (in_record) {
				if (strcmp(current_score.class_id, cls_id) == 0 &&
					strcmp(current_score.id, stu_id) == 0) {
					found = 1;
					printf("\n找到匹配的成绩信息，开始修改：\n");

					// 输入修改后的信息
					score modified_score;
					printf("课程编号：");
					fgets(modified_score.class_id, sizeof(modified_score.class_id), stdin);
					modified_score.class_id[strcspn(modified_score.class_id, "\n")] = 0;

					printf("课程名称：");
					fgets(modified_score.class_name, sizeof(modified_score.class_name), stdin);
					modified_score.class_name[strcspn(modified_score.class_name, "\n")] = 0;

					printf("学生学号：");
					fgets(modified_score.id, sizeof(modified_score.id), stdin);
					modified_score.id[strcspn(modified_score.id, "\n")] = 0;

					printf("学生姓名：");
					fgets(modified_score.name, sizeof(modified_score.name), stdin);
					modified_score.name[strcspn(modified_score.name, "\n")] = 0;

					printf("成绩：");
					scanf("%d", &modified_score.mark);
					getchar();

					// 写入修改后的信息到临时文件
					fprintf(temp_file, "---\n");
					fprintf(temp_file, "课程编号:%s\n", modified_score.class_id);
					fprintf(temp_file, "课程名称:%s\n", modified_score.class_name);
					fprintf(temp_file, "学生学号:%s\n", modified_score.id);
					fprintf(temp_file, "学生姓名:%s\n", modified_score.name);
					fprintf(temp_file, "成绩:%d\n", modified_score.mark);
					fprintf(temp_file, "---\n");
					
				}else{
					// 写入未修改的信息到临时文件
					fprintf(temp_file, "---\n");
					fprintf(temp_file, "课程编号:%s\n", current_score.class_id);
					fprintf(temp_file, "课程名称:%s\n", current_score.class_name);
					fprintf(temp_file, "学生学号:%s\n", current_score.id);
					fprintf(temp_file, "学生姓名:%s\n", current_score.name);
					fprintf(temp_file, "成绩:%d\n", current_score.mark);
					fprintf(temp_file, "---\n");
				}
				in_record = 0;
				lines_in_record = 0;
				memset(&current_score, 0, sizeof(current_score));
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
			if (strcmp(key, "课程编号") == 0) {
				strcpy(current_score.class_id, value);
			}
			else if (strcmp(key, "课程名称") == 0) {
				strcpy(current_score.class_name, value);
			}
			else if (strcmp(key, "学生学号") == 0) {
				strcpy(current_score.id, value);
			}
			else if (strcmp(key, "学生姓名") == 0) {
				strcpy(current_score.name, value);
			}
			else if (strcmp(key, "成绩") == 0) {
				current_score.mark = atoi(value);
			}
			lines_in_record++;
		}
	}


	fclose(file);
	fclose(temp_file);

	// 删除原文件，重命名临时文件
	remove(filename);
	rename("temp.txt", filename);

	if (found) {
		printf("成绩信息修改成功！\n");
	}
	else {
		printf("未找到信息！\n");
		remove("temp.txt");  // 删除临时文件
	}
}

void delete_score(const char* filename) {
	FILE* file = fopen(filename, "r");  // 阅读模式
	if (file == NULL) {
		printf("无法打开文件 %s！\n", filename);
		return;
	}
	getchar();

	char cls_id[50];
	char stu_id[8];
	score current_score;
	int found = 0;
	int in_record = 0;
	int lines_in_record = 0;

	printf("请输入要删除的课程编号：");
	fgets(cls_id, sizeof(cls_id), stdin);
	cls_id[strcspn(cls_id, "\n")] = 0;
	printf("请输入要删除的学生学号：");
	fgets(stu_id, sizeof(stu_id), stdin);
	stu_id[strcspn(stu_id, "\n")] = 0;

	FILE* temp_file = fopen("temp.txt", "w");
	if (temp_file == NULL) {
		printf("无法创建临时文件！\n");
		fclose(file);
		return;
	}

	char line[256];
	int skip_count = 0;


	while (fgets(line, sizeof(line), file)) {
		// 去除行尾的换行符
		line[strcspn(line, "\n")] = 0;


		// 检查是否是分隔符
		if (strcmp(line, "---") == 0) {
			if (in_record) {
				if (strcmp(current_score.class_id, cls_id) != 0 &&
					strcmp(current_score.id, stu_id) != 0) {
					found = 1;
					fprintf(temp_file, "---\n");
					fprintf(temp_file, "课程编号:%s\n", current_score.class_id);
					fprintf(temp_file, "课程名称:%s\n", current_score.class_name);
					fprintf(temp_file, "学生学号:%s\n", current_score.id);
					fprintf(temp_file, "学生姓名:%s\n", current_score.name);
					fprintf(temp_file, "成绩:%d\n", current_score.mark);
					fprintf(temp_file, "---\n");
				}
				in_record = 0;
				memset(&current_score, 0, sizeof(current_score));
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
			if (strcmp(key, "课程编号") == 0) {
				strcpy(current_score.class_id, value);
			}
			else if (strcmp(key, "课程名称") == 0) {
				strcpy(current_score.class_name, value);
			}
			else if (strcmp(key, "学生学号") == 0) {
				strcpy(current_score.id, value);
			}
			else if (strcmp(key, "学生姓名") == 0) {
				strcpy(current_score.name, value);
			}
			else if (strcmp(key, "成绩") == 0) {
				current_score.mark = atoi(value);
			}
			lines_in_record++;
		}
	}

	fclose(file);
	fclose(temp_file);

	// 删除原文件，重命名临时文件
	remove(filename);
	rename("temp.txt", filename);

	if (found) {
		printf("成绩信息删除成功！\n");
	}
	else {
		printf("未找到信息！\n");
		remove("temp.txt");  // 删除临时文件
	}
}

void input_score_search() {
	char cls_id[50];
	char stu_id[8];
	getchar();

	printf("课程编号：");
	fgets(cls_id, sizeof(cls_id), stdin);
	cls_id[strcspn(cls_id, "\n")] = 0;

	printf("学生学号：");
	fgets(stu_id, sizeof(stu_id), stdin);
	stu_id[strcspn(stu_id, "\n")] = 0;

	search_score("scores.txt", stu_id, cls_id);
}

void search_score(const char* filename, char* stu_id, char* cls_id) {
	FILE* file = fopen(filename, "r");  // 阅读模式
	if (file == NULL) {
		printf("无法打开文件 %s！\n", filename);
		return;
	}

	score current_score;
	int found = 0;
	int in_record = 0;
	int lines_in_record = 0;

	memset(&current_score, 0, sizeof(current_score));

	char line[256];
	int skip_count = 0;


	while (fgets(line, sizeof(line), file)) {
		// 去除行尾的换行符
		line[strcspn(line, "\n")] = 0;
		


		// 检查是否是分隔符
		if (strcmp(line, "---") == 0) {
			if (in_record) {
				if (strcmp(current_score.class_id, cls_id) == 0 &&
					strcmp(current_score.id, stu_id) == 0) {
					found = 1;
					printf("\n找到匹配的成绩信息：\n");
					printf("---\n");
					printf("课程编号:%s\n", current_score.class_id);
					printf("课程名称:%s\n", current_score.class_name);
					printf("学生学号:%s\n", current_score.id);
					printf("学生姓名:%s\n", current_score.name);
					printf("成绩:%d\n", current_score.mark);
					printf("---\n");
				}
				in_record = 0;
				lines_in_record = 0;
				memset(&current_score, 0, sizeof(current_score));
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
			if (strcmp(key, "课程编号") == 0) {
				strcpy(current_score.class_id, value);
			}
			else if (strcmp(key, "课程名称") == 0) {
				strcpy(current_score.class_name, value);
			}
			else if (strcmp(key, "学生学号") == 0) {
				strcpy(current_score.id, value);
			}
			else if (strcmp(key, "学生姓名") == 0) {
				strcpy(current_score.name, value);
			}
			else if (strcmp(key, "成绩") == 0) {
				current_score.mark = atoi(value);
			}
			lines_in_record++;
		}
	}

	if (!found) {
		printf("查无此成绩\n");
	}

	fclose(file);
}

void display_all_score(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("无法打开文件 %s！\n", filename);
		return;
	}

	char line[256];
	int count = 0;

	printf("\n========== 所有成绩档案 ==========\n");
	while (fgets(line, sizeof(line), file)) {
		printf("%s", line);
		if (strstr(line, "---") != NULL) {
			printf("\n");
			count++;
		}
	}

	printf("========== 共 %d 个成绩 ==========\n", count/2);
	fclose(file);
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>
#include<locale.h>
#include<wchar.h>
#include<io.h>
#include<fcntl.h>

typedef struct {
    char xh[10];
    char xm[60];
    char xb[10];
    int nl;
} Student;

typedef struct {
    char kh[10];
    char km[60];
    float xf;
} Course;

typedef struct {
    char xh[10];
    char kh[10];
    float cj;
} Select;

typedef struct {
    char xh[10];
    char xm[60];
    float cj[30];
    float zpj;
    float zxf;
} Score;

void clear_screen() {
    printf("按任意键继续...\n");
    getchar();
    getchar();
    system("cls");
}

void sort_stud(Student slist[], int scount) {
    for (int i = 0; i < scount - 1; i++) {
        for (int j = 0; j < scount - 1 - i; j++) {
            if (strcmp(slist[j].xh, slist[j + 1].xh) > 0) {
                Student temp = slist[j];
                slist[j] = slist[j + 1];
                slist[j + 1] = temp;
            }
        }
    }
}

void sort_course(Course clist[], int ccount) {
    for (int i = 0; i < ccount - 1; i++) {
        for (int j = 0; j < ccount - 1 - i; j++) {
            if (strcmp(clist[j].kh, clist[j + 1].kh) > 0) {
                Course temp = clist[j];
                clist[j] = clist[j + 1];
                clist[j + 1] = temp;
            }
        }
    }
}

void sort_cjlist(Score cjlist[], int cjcount) {
    for (int i = 0; i < cjcount - 1; i++) {
        for (int j = 0; j < cjcount - 1 - i; j++) {
            if (cjlist[j].zpj < cjlist[j + 1].zpj) {
                Score temp = cjlist[j];
                cjlist[j] = cjlist[j + 1];
                cjlist[j + 1] = temp;
            }
        }
    }
}

void disp_stud(Student slist[], int scount) {
    sort_stud(slist, scount);
    for (int i = 0; i < scount; i++) {
        printf("学号: %s, 姓名: %s, 性别: %s, 年龄: %d\n", slist[i].xh, slist[i].xm, slist[i].xb, slist[i].nl);
        if ((i + 1) % 10 == 0) {
            printf("按任意键继续...\n");
            getchar();
            getchar();
        }
    }
}

void disp_course(Course clist[], int ccount) {
    sort_course(clist, ccount);
    for (int i = 0; i < ccount; i++) {
        printf("课程号: %s, 课程名: %s, 学分: %.2f\n", clist[i].kh, clist[i].km, clist[i].xf);
        if ((i + 1) % 10 == 0) {
            printf("按任意键继续...\n");
            getchar();
            getchar();
        }
    }
}

void disp_cjlist(Score cjlist[], int cjcount, Course clist[], int ccount, Student slist[], int scount, Select sclist[], int sccount) {
    sort_cjlist(cjlist, cjcount);
    for (int i = 0; i < cjcount; i++) {
        printf("学号: %s, 姓名: %s, 平均成绩: %.2f, 总学分: %.2f\n", cjlist[i].xh, cjlist[i].xm, cjlist[i].zpj, cjlist[i].zxf);
        printf("课程成绩: ");
        for (int j = 0; j < sccount; j++) {
            if (strcmp(sclist[j].xh, cjlist[i].xh) == 0) {
                for (int k = 0; k < ccount; k++) {
                    if (strcmp(sclist[j].kh, clist[k].kh) == 0) {
                        printf("%s:", clist[k].km);
                        printf("%.2f\n", sclist[j].cj);
                    }
                }

            }
        }
        printf("\n");
        if ((i + 1) % 10 == 0) {
            printf("按任意键继续...\n");
            getchar();
            getchar();
        }
    }
}

void loadStudents(const char* filename, Student slist[], int* scount) {
    //setlocale(LC_ALL, "");
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open student file: %s\n", filename);
        exit(1);
    }

    *scount = 0;
    while (fscanf(file, "%9s %59s %9s %d\n", &slist[*scount].xh, slist[*scount].xm, &slist[*scount].xb, &slist[*scount].nl) != EOF) {
        (*scount)++;
    }

    fclose(file);
}

void loadCourses(const char* filename, Course clist[], int* ccount) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open course file: %s\n", filename);
        exit(1);
    }

    *ccount = 0;
    while (fscanf(file, "%9s %59s %f", &clist[*ccount].kh, clist[*ccount].km, &clist[*ccount].xf) != EOF) {
        (*ccount)++;
    }

    fclose(file);
}

void loadSelect(const char* filename, Select sclist[], int* sccount) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open score file: %s\n", filename);
        exit(1);
    }

    *sccount = 0;
    while (fscanf(file, "%9s %9s %f", &sclist[*sccount].xh, &sclist[*sccount].kh, &sclist[*sccount].cj) != EOF) {
        (*sccount)++;
    }

    fclose(file);
}

void init(Student slist[], int* scount, Course clist[], int* ccount, Select sclist[], int* sccount) {
    const char* studentFile = "student.txt";
    const char* courseFile = "course.txt";
    const char* scoreFile = "select.txt";

    loadStudents(studentFile, slist, scount);
    loadCourses(courseFile, clist, ccount);
    loadSelect(scoreFile, sclist, sccount);
}
int create_cjlist(Student slist[100], int* scount, Course clist[100], int* ccount, Select sclist[100], int* sccount, Score cjlist[100], int* cjcount) {
    *cjcount = *scount; // 设置成绩单中的学生数量
    for (int i = 0; i < *scount; i++) {
        strcpy(cjlist[i].xh, slist[i].xh);
        strcpy(cjlist[i].xm, slist[i].xm);
        cjlist[i].zxf = 0;
        cjlist[i].zpj = 0;
        int course_count = 0;

        for (int j = 0; j < *sccount; j++) {
            if (strcmp(cjlist[i].xh, sclist[j].xh) == 0) {
                for (int k = 0; k < *ccount; k++) {
                    if (strcmp(sclist[j].kh, clist[k].kh) == 0) {
                        cjlist[i].cj[course_count] = sclist[j].cj;
                        cjlist[i].zxf += clist[k].xf;
                        cjlist[i].zpj += sclist[j].cj * clist[k].xf;
                        course_count++;
                        break;
                    }
                }
            }
        }

        if (cjlist[i].zxf > 0) {
            cjlist[i].zpj /= cjlist[i].zxf;
        }
    }

    return 0;
}

int input_stud(Student slist[], int* scount) {
    while (1) {
        Student temp;
        printf("输入学号: ");
        scanf("%s", temp.xh);
        int exists = 0;
        for (int i = 0; i < *scount; i++) {
            if (strcmp(slist[i].xh, temp.xh) == 0) {
                exists = 1;
                printf("学号已存在，是否替换? (y/n): ");
                char choice;
                getchar(); // 清除缓冲区
                scanf("%c", &choice);
                if (choice == 'y' || choice == 'Y') {
                    printf("输入姓名: ");
                    scanf("%s", temp.xm);
                    printf("输入性别: ");
                    scanf("%s", temp.xb);
                    printf("输入年龄: ");
                    scanf("%d", &temp.nl);
                    slist[i] = temp;
                }
                break;
            }
        }
        if (!exists) {
            printf("输入姓名: ");
            scanf("%s", temp.xm);
            printf("输入性别: ");
            scanf("%s", temp.xb);
            printf("输入年龄: ");
            scanf("%d", &temp.nl);
            slist[*scount] = temp;
            (*scount)++;
        }
        printf("是否输入下一条记录? (y/n): ");
        char cont;
        getchar(); // 清除缓冲区
        scanf("%c", &cont);
        if (cont == 'n' || cont == 'N') {
            break;
        }
    }
    return *scount;
}

int input_course(Course clist[], int* ccount) {
    while (1) {
        Course temp;
        printf("输入课程号: ");
        scanf("%s", temp.kh);
        int exists = 0;
        for (int i = 0; i < *ccount; i++) {
            if (strcmp(clist[i].kh, temp.kh) == 0) {
                exists = 1;
                printf("课程号已存在，是否替换? (y/n): ");
                char choice;
                getchar(); // 清除缓冲区
                scanf("%c", &choice);
                if (choice == 'y' || choice == 'Y') {
                    printf("输入课程名: ");
                    scanf("%s", temp.km);
                    printf("输入学分: ");
                    scanf("%f", &temp.xf);
                    clist[i] = temp;
                }
                break;
            }
        }
        if (!exists) {
            printf("输入课程名: ");
            scanf("%s", temp.km);
            printf("输入学分: ");
            scanf("%f", &temp.xf);
            clist[*ccount] = temp;
            (*ccount)++;
        }
        printf("是否输入下一条记录? (y/n): ");
        char cont;
        getchar(); // 清除缓冲区
        scanf("%c", &cont);
        if (cont == 'n' || cont == 'N') {
            break;
        }
    }
    return *ccount;
}

int input_select(Select sclist[], int* sccount, Student slist[], int scount, Course clist[], int ccount) {
    while (1) {
        Select temp;
        printf("输入学生学号: ");
        scanf("%s", temp.xh);
        int student_exists = 0;
        for (int i = 0; i < scount; i++) {
            if (strcmp(slist[i].xh, temp.xh) == 0) {
                student_exists = 1;
                break;
            }
        }
        if (!student_exists) {
            printf("学生学号不存在，请重新输入。\n");
            continue;
        }

        printf("输入课程号: ");
        scanf("%s", temp.kh);
        int course_exists = 0;
        for (int i = 0; i < ccount; i++) {
            if (strcmp(clist[i].kh, temp.kh) == 0) {
                course_exists = 1;
                break;
            }
        }
        if (!course_exists) {
            printf("课程号不存在，请重新输入。\n");
            continue;
        }

        printf("输入成绩: ");
        scanf("%f", &temp.cj);
        if (temp.cj < -1 || temp.cj > 120) {
            printf("成绩无效，请重新输入。\n");
            continue;
        }

        int exists = 0;
        for (int i = 0; i < *sccount; i++) {
            if (strcmp(sclist[i].xh, temp.xh) == 0 && strcmp(sclist[i].kh, temp.kh) == 0) {
                exists = 1;
                printf("该学生的该课程成绩已存在，是否替换? (y/n): ");
                char choice;
                getchar(); // 清除缓冲区
                scanf("%c", &choice);
                if (choice == 'y' || choice == 'Y') {
                    sclist[i] = temp;
                }
                break;
            }
        }
        if (!exists) {
            sclist[*sccount] = temp;
            (*sccount)++;
        }

        printf("是否输入下一条记录? (y/n): ");
        char cont;
        getchar(); // 清除缓冲区
        scanf("%c", &cont);
        if (cont == 'n' || cont == 'N') {
            break;
        }
    }
    return *sccount;
}

int delete_stud(Student slist[], int* scount, const char* identifier) {
    int i, j, count = 0;
    for (i = 0; i < *scount; i++) {
        if (strcmp(slist[i].xh, identifier) == 0 || strcmp(slist[i].xm, identifier) == 0) {
            for (j = i; j < *scount - 1; j++) {
                slist[j] = slist[j + 1];
            }
            (*scount)--;
            count++;
            i--;
        }
    }
    return *scount;
}

int delete_course(Course clist[], int* ccount, const char* identifier) {
    int i, j, count = 0;
    for (i = 0; i < *ccount; i++) {
        if (strcmp(clist[i].kh, identifier) == 0 || strcmp(clist[i].km, identifier) == 0) {
            for (j = i; j < *ccount - 1; j++) {
                clist[j] = clist[j + 1];
            }
            (*ccount)--;
            count++;
            i--;
        }
    }
    return *ccount;
}

int delete_select(Select sclist[], int* sccount, const char* student_id) {
    int i, j, count = 0;
    for (i = 0; i < *sccount; i++) {
        if (strcmp(sclist[i].xh, student_id) == 0) {
            for (j = i; j < *sccount - 1; j++) {
                sclist[j] = sclist[j + 1];
            }
            (*sccount)--;
            count++;
            i--;
        }
    }
    return *sccount;
}

void query_stud(Student slist[], int* scount) {
    char identifier[20];
    printf("请输入要查找的学生学号或姓名：");
    scanf("%s", identifier);
    for (int i = 0; i < *scount; i++) {
        if (strcmp(slist[i].xh, identifier) == 0 || strcmp(slist[i].xm, identifier) == 0) {
            printf("学号: %s, 姓名: %s, 性别: %s, 年龄: %d\n", slist[i].xh, slist[i].xm, slist[i].xb, slist[i].nl);
            return;
        }
    }
    printf("未找到该学生信息。\n");
}

void query_course(Course clist[], int* ccount) {
    char identifier[20];
    printf("请输入要查找的课程号或课程名：");
    scanf("%s", identifier);
    for (int i = 0; i < *ccount; i++) {
        if (strcmp(clist[i].kh, identifier) == 0 || strcmp(clist[i].km, identifier) == 0) {
            printf("课程号: %s, 课程名: %s, 学分: %.2f\n", clist[i].kh, clist[i].km, clist[i].xf);
            return;
        }
    }
    printf("未找到该课程信息。\n");
}

void query_cjlist(Select sclist[], int* sccount, Course clist[], int ccount, Score cjlist[], int scount) {
    char student_id[10];
    printf("请输入要查找成绩的学生学号：");
    scanf("%s", student_id);
    for (int i = 0; i < scount; i++) {
        if (strcmp(cjlist[i].xh, student_id) == 0) {
            printf("学号: %s, 姓名: %s\n", cjlist[i].xh, cjlist[i].xm);
            printf("排名：%d,平均分：%.2f,学分：%.2f", i + 1, cjlist[i].zpj, cjlist[i].zxf);
            printf("课程成绩: ");
            for (int j = 0; j < *sccount; j++) {
                if (strcmp(sclist[j].xh, student_id) == 0) {
                    for (int k = 0; k < ccount; k++) {
                        if (strcmp(sclist[j].kh, clist[k].kh) == 0)
                            printf("%s:%.2f ", clist[k].km, sclist[j].cj);
                    }
                }
            }
            printf("\n");
            return;
        }
    }
    printf("未找到该学生的成绩信息。\n");
}
void get_current_time_str(char* buffer, int size) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(buffer, size, "%04d%02d%02d_%02d%02d%02d",
        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
        tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void export_students(Student students[], int size, const char* filename_prefix) {
    char filename[100];
    char time_str[20];
    get_current_time_str(time_str, sizeof(time_str));
    snprintf(filename, sizeof(filename), "%s_students_%s.txt", filename_prefix, time_str);

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Unable to open file %s\n", filename);
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "学号: %s, 姓名: %s, 性别: %s, 年龄: %d\n",
            students[i].xh, students[i].xm, students[i].xb, students[i].nl);
    }

    fclose(file);
}

void export_courses(Course courses[], int size, const char* filename_prefix) {
    char filename[100];
    char time_str[20];
    get_current_time_str(time_str, sizeof(time_str));
    snprintf(filename, sizeof(filename), "%s_courses_%s.txt", filename_prefix, time_str);

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Unable to open file %s\n", filename);
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "课程号: %s, 课程名: %s, 学分: %.2f\n",
            courses[i].kh, courses[i].km, courses[i].xf);
    }

    fclose(file);
}

void export_selects(Select selects[], int size, const char* filename_prefix) {
    char filename[100];
    char time_str[20];
    get_current_time_str(time_str, sizeof(time_str));
    snprintf(filename, sizeof(filename), "%s_selects_%s.txt", filename_prefix, time_str);

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Unable to open file %s\n", filename);
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "学号: %s, 课程号: %s, 成绩: %.2f\n",
            selects[i].xh, selects[i].kh, selects[i].cj);
    }

    fclose(file);
}

void export_scores(Score scores[], int size, const char* filename_prefix, Course clist[], int ccount, Select sclist[], int sccount) {
    char filename[100];
    char time_str[20];
    get_current_time_str(time_str, sizeof(time_str));
    snprintf(filename, sizeof(filename), "%s_scores_%s.txt", filename_prefix, time_str);

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Unable to open file %s\n", filename);
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "学号: %s, 姓名: %s, 加权平均分: %.2f, 总学分: %.2f\n",
            scores[i].xh, scores[i].xm, scores[i].zpj, scores[i].zxf);
        fprintf(file, "课程成绩: ");
        for (int j = 0; j < sccount; j++) {
            if (strcmp(sclist[j].xh, scores[i].xh) == 0) {
                for (int k = 0; k < ccount; k++) {
                    if (strcmp(sclist[j].kh, clist[k].kh) == 0)
                        fprintf(file, "%s:%.2f ", clist[k].km, sclist[j].cj);
                }
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int main() {
   /* _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);*/

    Student slist[100];
    Course clist[100];
    Select sclist[100];
    Score cjlist[100];
    int xuan;
    int scount = 0;
    int ccount = 0;
    int sccount = 0;
    int cjcount = 0;

    while (1) {
        printf("1.导入初始数据\n");
        printf("2.显示信息\n");
        printf("3.输入记录\n");
        printf("4.删除记录\n");
        printf("5.查询信息\n");
        printf("6.批量导出数据\n");
        printf("0.退出\n");
        printf("请给出你的选择：");
        scanf("%d", &xuan);
        switch (xuan) {
        case 1:
            init(slist, &scount, clist, &ccount, sclist, &sccount);
            create_cjlist(slist, &scount, clist, &ccount, sclist, &sccount, cjlist, &cjcount);
            break;
        case 2:
            printf("1. 显示学生信息\n");
            printf("2. 显示课程信息\n");
            printf("3. 显示成绩信息\n");
            printf("请选择要显示的信息：");
            int disp_choice;
            scanf("%d", &disp_choice);
            if (disp_choice == 1) {
                disp_stud(slist, scount);
            }
            else if (disp_choice == 2) {
                disp_course(clist, ccount);
            }
            else if (disp_choice == 3) {
                create_cjlist(slist, &scount, clist, &ccount, sclist, &sccount, cjlist, &cjcount);
                disp_cjlist(cjlist, cjcount, clist, ccount, slist, scount, sclist, sccount);
            }
            else {
                printf("无效的选择，请重新输入。\n");
            }
            break;
        case 3:
            printf("1. 输入学生信息\n");
            printf("2. 输入课程信息\n");
            printf("3. 输入选课信息\n");
            printf("请选择要输入的类型：");
            int input_choice;
            scanf("%d", &input_choice);
            if (input_choice == 1) {
                int count = input_stud(slist, &scount);
                printf("一共%d条学生信息记录\n", count);
            }
            else if (input_choice == 2) {
                int count = input_course(clist, &ccount);
                printf("一共%d条课程信息记录\n", count);
            }
            else if (input_choice == 3) {
                int count = input_select(sclist, &sccount, slist, scount, clist, ccount);
                printf("一共%d条选课成绩记录\n", count);
                create_cjlist(slist, &scount, clist, &ccount, sclist, &sccount, cjlist, &cjcount);
            }
            else {
                printf("无效的选择，请重新输入。\\n");
            }
            break;
        case 4:
            printf("1. 输入要删除的学生信息\n");
            printf("2. 输入要删除的课程信息\n");
            printf("3. 输入要删除的选课信息\n");
            printf("请选择要删除的类型：");
            int delete_choice;
            scanf("%d", &delete_choice);
            if (delete_choice == 1) {
                char identifier[20];
                printf("请输入要删除的学生的学号或姓名：");
                scanf("%s", identifier);
                int count = delete_stud(slist, &scount, identifier);
                printf("还剩了%d条学生信息记录\n", count);
            }
            else if (delete_choice == 2) {
                char identifier[20];
                printf("请输入要删除的课程号或课程名：");
                scanf("%s", identifier);
                int count = delete_course(clist, &ccount, identifier);
                printf("还剩%d条课程信息记录\n", count);
            }
            else if (delete_choice == 3) {
                char student_id[10], course_id[10];
                printf("请输入要删除的选课记录的学号：");
                scanf("%s", student_id);
                int count = delete_select(sclist, &sccount, student_id);
                printf("还剩了%d条选课成绩记录\n", count);
                // create_cjlist(slist, &scount, clist, &ccount, sclist, &sccount, cjlist, &cjcount);
            }
            else {
                printf("无效的选择，请重新输入。\n");
            }
            break;
        case 5:
            printf("1. 查找学生信息\n");
            printf("2. 查找课程信息\n");
            printf("3. 查找学生成绩\n");
            printf("请选择要查找的类型：");
            int query_choice;
            scanf("%d", &query_choice);
            if (query_choice == 1) {
                query_stud(slist, &scount);
            }
            else if (query_choice == 2) {
                query_course(clist, &ccount);
            }
            else if (query_choice == 3) {
                sort_cjlist(cjlist, cjcount);
                query_cjlist(sclist, &sccount, clist, ccount, cjlist, cjcount);
            }
            else {
                printf("无效的选择，请重新输入。\n");
            }
            break;
        case 6:
            printf("1. 导出学生信息\n");
            printf("2. 导出学生成绩\n");
            printf("请选择要导出的类型：");
            int write_choice;
            scanf("%d", &write_choice);
            if (write_choice == 1) {
                export_students(slist, scount, "date");
                export_courses(clist, ccount, "date");
                export_selects(sclist, sccount, "date");
            }
            else if (write_choice == 2) {
                export_scores(cjlist, cjcount, "date", clist, ccount, sclist, sccount);
            }
            else {
                printf("无效的选择，请重新输入。\n");
            }
            break;
        case 0:
            exit(0);
        default:
            printf("无效的选择，请重新输入。\n");
            break;
        }
        clear_screen();
    }

    return 0;
}

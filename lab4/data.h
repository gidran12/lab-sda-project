#ifndef DATA_H
#define DATA_H

// Описание структуры
typedef struct {
    char name[50];
    char teacher[50];
    int duration;
    int students;
} Course;

// список того, что умеет программа
Course* manualResize(Course* old_ptr, int count, int new_capacity);
Course inputCourse();
void addCourse(Course** courses, int* count, int* capacity);
void printCourses(Course* courses, int count);
void sortCourses(Course* courses, int count);
void insertCourse(Course** courses, int* count, int* capacity);
void deleteCourse(Course** courses, int* count, int* capacity);

// Функции для работы с файлами
void saveToFile(Course* courses, int count, const char* filename);
void loadFromFile(Course** courses, int* count, int* capacity, const char* filename);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

// изменение размера из2 лабы
Course* manualResize(Course* old_ptr, int count, int new_capacity) {
    Course* new_ptr = (Course*)malloc(new_capacity * sizeof(Course));
    if (new_ptr == NULL) exit(1);
    if (old_ptr != NULL) {
        for (int i = 0; i < count; i++) new_ptr[i] = old_ptr[i];
        free(old_ptr);
    }
    return new_ptr;
}

// Ввод данных
Course inputCourse() {
    Course c;
    printf("Название: "); scanf("%49s", c.name);
    printf("Преподаватель: "); scanf("%49s", c.teacher);
    printf("Часы: "); scanf("%d", &c.duration);
    printf("Студенты: "); scanf("%d", &c.students);
    return c;
}

// Добавление (2-я лаба)
void addCourse(Course** courses, int* count, int* capacity) {
    if (*count == *capacity) {
        *capacity += 1;
        *courses = manualResize(*courses, *count, *capacity);
    }
    (*courses)[*count] = inputCourse();
    (*count)++;
}

// Вывод 
void printCourses(Course* courses, int count) {
    if (count == 0) { printf("Пусто.\n"); return; }
    for (int i = 0; i < count; i++) {
        printf("[%d] %s | %s | %d ч. | %d чел.\n", i, courses[i].name, courses[i].teacher, courses[i].duration, courses[i].students);
    }
}

// сортировка  Пузырек
void sortCourses(Course* courses, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(courses[j].name, courses[j+1].name) > 0) {
                Course temp = courses[j];
                courses[j] = courses[j+1];
                courses[j+1] = temp;
            }
        }
    }
}

// вставка сдвиг вправо)
void insertCourse(Course** courses, int* count, int* capacity) {
    int index;
    printf("Индекс для вставки: "); scanf("%d", &index);
    if (index < 0 || index > *count) return;
    if (*count == *capacity) {
        *capacity += 1;
        *courses = manualResize(*courses, *count, *capacity);
    }
    for (int i = *count; i > index; i--) (*courses)[i] = (*courses)[i - 1];
    (*courses)[index] = inputCourse();
    (*count)++;
}

// удаление сдвиг влево
void deleteCourse(Course** courses, int* count, int* capacity) {
    int index;
    printf("Индекс для удаления: "); scanf("%d", &index);
    if (index < 0 || index >= *count) return;
    for (int i = index; i < *count - 1; i++) (*courses)[i] = (*courses)[i + 1];
    (*count)--;
    *capacity = *count;
    *courses = manualResize(*courses, *count, *capacity);
}

//РАБОТА С ФАЙЛАМИ

void saveToFile(Course* courses, int count, const char* filename) {
    FILE *f = fopen(filename, "wb"); // Бинарная запись
    if (!f) return;
    fwrite(&count, sizeof(int), 1, f); 
    if (count > 0) fwrite(courses, sizeof(Course), count, f); //весь массив
    fclose(f);
    printf("Данные сохранены.\n");
}

void loadFromFile(Course** courses, int* count, int* capacity, const char* filename) {
    FILE *f = fopen(filename, "rb"); // бинарное чтение
    if (!f) return;
    fread(count, sizeof(int), 1, f); 
    *capacity = *count;
    if (*count > 0) {
        *courses = (Course*)malloc(*capacity * sizeof(Course));
        fread(*courses, sizeof(Course), *count, f); // читаем массив
    }
    fclose(f);
    printf("Данные загружены.\n");
}

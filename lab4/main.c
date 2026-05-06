#include <stdio.h>
#include <stdlib.h>
#include "data.h"

int main() {
    Course* courses = NULL;
    int count = 0;
    int capacity = 0;
    int choice;
    const char* file = "data.bin"; 

    // згрузка при старте 
    loadFromFile(&courses, &count, &capacity, file);

    do {
        printf("\n1.Добавить 2.Показать 3.Сортировка 4.Вставить 5.Удалить 0.Выход: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addCourse(&courses, &count, &capacity); break;
            case 2: printCourses(courses, count); break;
            case 3: sortCourses(courses, count); break;
            case 4: insertCourse(&courses, &count, &capacity); break;
            case 5: deleteCourse(&courses, &count, &capacity); break;
            case 0:
                saveToFile(courses, count, file); // сохранение при выходе
                break;
        }
    } while (choice != 0);

    if (courses) free(courses);
    return 0;
}

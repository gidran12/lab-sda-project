#include <stdio.h>
#include <string.h>

#define SIZE 10

// Структура "Курсы обучения"
struct Course {
    char name[50];
    char teacher[50];
    char duration[50];
    int students;
};

// Функция заполнения массива
void fillCourses(struct Course courses[]) {
    for(int i = 0; i < SIZE; i++) {
        printf("\nКурс %d\n", i);

        printf("Название курса: ");
        scanf("%s", courses[i].name);

        printf("Преподаватель: ");
        scanf("%s", courses[i].teacher);

        printf("Длительность: ");
        scanf("%s", courses[i].duration);

        printf("Количество студентов: ");
        scanf("%d", &courses[i].students);
    }
}

// Функция вывода
void printCourses(struct Course courses[]) {
    for(int i = 0; i < SIZE; i++) {
        printf("\n----- Курс %d -----\n", i);
        printf("Название: %s\n", courses[i].name);
        printf("Преподаватель: %s\n", courses[i].teacher);
        printf("Длительность: %s\n", courses[i].duration);
        printf("Студентов: %d\n", courses[i].students);
    }
}

// Функция редактирования по индексу
void editCourse(struct Course courses[]) {
    int index;
    printf("Введите индекс курса для редактирования (0-9): ");
    scanf("%d", &index);

    if(index >= 0 && index < SIZE) {
        printf("Новое название: ");
        scanf("%s", courses[index].name);

        printf("Новый преподаватель: ");
        scanf("%s", courses[index].teacher);

        printf("Новая длительность: ");
        scanf("%s", courses[index].duration);

        printf("Новое количество студентов: ");
        scanf("%d", &courses[index].students);

        printf("Курс изменён!\n");
    } else {
        printf("Неверный индекс!\n");
    }
}

// Поиск по названию курса
void searchCourse(struct Course courses[]) {
    char searchName[50];
    int found = 0;

    printf("Введите название курса для поиска: ");
    scanf("%s", searchName);

    for(int i = 0; i < SIZE; i++) {
        if(strcmp(courses[i].name, searchName) == 0) {
            printf("\nНайден курс:\n");
            printf("Название: %s\n", courses[i].name);
            printf("Преподаватель: %s\n", courses[i].teacher);
            printf("Длительность: %s\n", courses[i].duration);
            printf("Студентов: %d\n", courses[i].students);
            found = 1;
        }
    }

    if(found == 0) {
        printf("Курс не найден.\n");
    }
}

int main() {
    struct Course courses[SIZE];

    int choice;

    do {
        printf("\n1 - Заполнить массив\n");
        printf("2 - Показать все курсы\n");
        printf("3 - Редактировать курс\n");
        printf("4 - Найти курс по названию\n");
        printf("0 - Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        if(choice == 1) {
            fillCourses(courses);
        }
        else if(choice == 2) {
            printCourses(courses);
        }
        else if(choice == 3) {
            editCourse(courses);
        }
        else if(choice == 4) {
            searchCourse(courses);
        }

    } while(choice != 0);
return 0;
}add
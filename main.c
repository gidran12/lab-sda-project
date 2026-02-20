#include <stdio.h>
#include <string.h>

#define SIZE 10

struct Course {
    char name[50];   // ключевое поле
    char teacher[50];
    char duration[50];
    int students;
};

void fillCourses(struct Course courses[]) {
    for(int i = 0; i < SIZE; i++) {
        printf("\nКурс %d\n", i);

        printf("Название: ");
        scanf("%s", courses[i].name);

        printf("Преподаватель: ");
        scanf("%s", courses[i].teacher);

        printf("Длительность: ");
        scanf("%s", courses[i].duration);

        printf("Студентов: ");
        scanf("%d", &courses[i].students);
    }
}

void printCourses(struct Course courses[]) {
    for(int i = 0; i < SIZE; i++) {
        printf("\n--- %d ---\n", i);
        printf("Название: %s\n", courses[i].name);
        printf("Преподаватель: %s\n", courses[i].teacher);
        printf("Длительность: %s\n", courses[i].duration);
        printf("Студентов: %d\n", courses[i].students);
    }
}

void searchCourse(struct Course courses[]) {
    char key[50];
    int found = 0;

    printf("Введите название курса: ");
    scanf("%s", key);

    for(int i = 0; i < SIZE; i++) {
        if(strcmp(courses[i].name, key) == 0) {
            printf("\nНайден курс:\n");
            printf("Название: %s\n", courses[i].name);
            printf("Преподаватель: %s\n", courses[i].teacher);
            printf("Длительность: %s\n", courses[i].duration);
            printf("Студентов: %d\n", courses[i].students);
            found = 1;
        }
    }

    if(found == 0) {
        printf("Курс не найден\n");
    }
}

int main() {
    struct Course courses[SIZE];
    int choice;

    do {
        printf("\n1 - Заполнить\n");
        printf("2 - Показать\n");
        printf("3 - Найти по названию\n");
        printf("0 - Выход\n");
        printf("Выбор: ");
        scanf("%d", &choice);

        if(choice == 1)
            fillCourses(courses);
        else if(choice == 2)
            printCourses(courses);
        else if(choice == 3)
            searchCourse(courses);

    } while(choice != 0);

    return 0;
}

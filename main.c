#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

struct Course {
    char name[50];
    char teacher[50];
    char duration[50];
    int students;
};

// расширение-сужение памяти 
struct Course* resize(struct Course* old_ptr, int old_count, int new_capacity) {
    if (new_capacity <= 0) {
        free(old_ptr);
        return NULL;
    }

    // выделяю новую область памяти
    struct Course* new_ptr = (struct Course*)malloc(new_capacity * sizeof(struct Course));
    if (new_ptr == NULL) {
        printf("Ошибка выделения памяти!\n");
        return old_ptr;
    }

    // копирую данные из старой памяти в новую
    int elements_to_copy = (old_count < new_capacity) ? old_count : new_capacity;
    for (int i = 0; i < elements_to_copy; i++) {
        new_ptr[i] = old_ptr[i];
    }

    // освобождаю старую память
    free(old_ptr);

    printf("--- Память перераспределена. Новый объем: %d ---\n", new_capacity);
    return new_ptr;
}

// добавляю один элемент в конец 
void addCourse(struct Course** courses, int* count, int* capacity) {
    // если места нет — расширяем на 1 слот
    if (*count >= *capacity) {
        *courses = resize(*courses, *count, (*capacity) + 1);
        (*capacity)++;
    }

    int i = *count;
    printf("\nДобавление курса (индекс %d):\n", i);
    printf("Название курса: ");
    scanf("%s", (*courses)[i].name);
    printf("Преподаватель: ");
    scanf("%s", (*courses)[i].teacher);
    printf("Длительность: ");
    scanf("%s", (*courses)[i].duration);
    printf("Количество студентов: ");
    scanf("%d", &(*courses)[i].students);

    (*count)++;
}

// удаление последнего элемента 
void removeLastCourse(struct Course** courses, int* count, int* capacity) {
    if (*count > 0) {
        (*count)--;
        // уменьшение физического размера памяти
        *courses = resize(*courses, *count, *count);
        *capacity = *count;
        printf("Последний элемент удален. Размер массива уменьшен.\n");
    } else {
        printf("Массив и так пуст!\n");
    }
}

// вывод
void printCourses(struct Course* courses, int count) {
    if (count == 0) {
        printf("Список пуст.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        printf("\n----- Курс %d -----\n", i);
        printf("Название: %s\n", courses[i].name);
        printf("Преподаватель: %s\n", courses[i].teacher);
        printf("Длительность: %s\n", courses[i].duration);
        printf("Студентов: %d\n", courses[i].students);
    }
}

int main() {
    struct Course* courses = NULL; // указатель на динамический массив
    int count = 0;                 // реальное кол-во элементов
    int capacity = 0;              // емкость
    int choice;

    do {
        printf("\n--- Меню (Динамический массив) ---\n");
        printf("1 - Добавить курс в конец\n");
        printf("2 - Показать все курсы\n");
        printf("3 - Удалить последний курс\n");
        printf("4 - Очистить всё и выйти\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        if (choice == 1) {
            addCourse(&courses, &count, &capacity);
        }
        else if (choice == 2) {
            printCourses(courses, count);
        }
        else if (choice == 3) {
            removeLastCourse(&courses, &count, &capacity);
        }
        else if (choice == 4) {
            //очистка 
            free(courses);
            courses = NULL;
            count = 0;
            capacity = 0;
            printf("Память очищена. Выход...\n");
            break; 
        }

    } while (choice != 4);

    return 0;
}

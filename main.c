#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Описание структуры курса
typedef struct {
    char name[50];
    char teacher[50];
    int duration;
    int students;
} Course;

// Функция перераспределения памяти (твоя блок-схема Resize)
Course* manualResize(Course* old_ptr, int count, int new_capacity) {
    Course* new_ptr = (Course*)malloc(new_capacity * sizeof(Course));
    if (new_ptr == NULL) {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
    
    // Копируем старые данные в новый массив
    if (old_ptr != NULL) {
        for (int i = 0; i < count; i++) {
            new_ptr[i] = old_ptr[i];
        }
        free(old_ptr); // Освобождаем старую память
    }
    return new_ptr;
}

// 1. Ввод данных для одного курса (вспомогательная функция)
Course inputCourse() {
    Course c;
    printf("Введите название курса: ");
    scanf("%49s", c.name);
    printf("Введите имя преподавателя: ");
    scanf("%49s", c.teacher);
    printf("Введите длительность (часы): ");
    scanf("%d", &c.duration);
    printf("Введите количество студентов: ");
    scanf("%d", &c.students);
    return c;
}

// 2. Функция добавления в конец (из Лабы 2)
void addCourse(Course** courses, int* count, int* capacity) {
    if (*count == *capacity) {
        *capacity += 1; // Увеличиваем вместимость
        *courses = manualResize(*courses, *count, *capacity);
    }
    (*courses)[*count] = inputCourse();
    (*count)++;
    printf("Курс успешно добавлен в конец!\n");
}

// 3. Функция вывода всех курсов
void printCourses(Course* courses, int count) {
    if (count == 0) {
        printf("Список курсов пуст.\n");
        return;
    }
    printf("\n--- Список курсов ---\n");
    for (int i = 0; i < count; i++) {
        printf("[%d] Курс: %s | Преподаватель: %s | Часы: %d | Студенты: %d\n", 
               i, courses[i].name, courses[i].teacher, courses[i].duration, courses[i].students);
    }
    printf("---------------------\n");
}

// 4. Функция сортировки (Пузырек по названию)
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
    printf("Массив отсортирован по алфавиту!\n");
}

// 5. Функция вставки по индексу со сдвигом вправо
void insertCourse(Course** courses, int* count, int* capacity) {
    int index;
    printf("Введите индекс для вставки (0 - %d): ", *count);
    scanf("%d", &index);

    if (index < 0 || index > *count) {
        printf("Ошибка: Неверный индекс!\n");
        return;
    }

    // Проверка вместимости
    if (*count == *capacity) {
        *capacity += 1;
        *courses = manualResize(*courses, *count, *capacity);
    }

    // Сдвиг элементов вправо (начиная с конца)
    for (int i = *count; i > index; i--) {
        (*courses)[i] = (*courses)[i - 1];
    }

    printf("Ввод данных для нового курса:\n");
    (*courses)[index] = inputCourse();
    (*count)++;
    printf("Курс успешно вставлен!\n");
}

// 6. Функция удаления по индексу со сдвигом влево
void deleteCourse(Course** courses, int* count, int* capacity) {
    int index;
    printf("Введите индекс для удаления (0 - %d): ", *count - 1);
    scanf("%d", &index);

    if (index < 0 || index >= *count) {
        printf("Ошибка: Неверный индекс!\n");
        return;
    }

    // Сдвиг элементов влево
    for (int i = index; i < *count - 1; i++) {
        (*courses)[i] = (*courses)[i + 1];
    }
    (*count)--;

    // Уменьшение памяти (если нужно по заданию)
    if (*count > 0) {
        *capacity = *count;
        *courses = manualResize(*courses, *count, *capacity);
    } else if (*count == 0) {
        free(*courses);
        *courses = NULL;
        *capacity = 0;
    }
    printf("Курс успешно удален!\n");
}

// Основная функция с меню
int main() {
    Course* courses = NULL;
    int count = 0;
    int capacity = 0;
    int choice;

    do {
        printf("\n=== МЕНЮ УПРАВЛЕНИЯ КУРСАМИ ===\n");
        printf("1. Добавить курс в конец\n");
        printf("2. Вывести все курсы\n");
        printf("3. Отсортировать курсы\n");
        printf("4. Вставить курс по индексу\n");
        printf("5. Удалить курс по индексу\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода. Ожидается число.\n");
            break;
        }

        switch (choice) {
            case 1:
                addCourse(&courses, &count, &capacity);
                break;
            case 2:
                printCourses(courses, count);
                break;
            case 3:
                sortCourses(courses, count);
                break;
            case 4:
                insertCourse(&courses, &count, &capacity);
                break;
            case 5:
                deleteCourse(&courses, &count, &capacity);
                break;
            case 0:
                printf("Завершение работы...\n");
                break;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 0);

    // Очистка памяти перед выходом
    if (courses != NULL) {
        free(courses);
    }

    return 0;
}

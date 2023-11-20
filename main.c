/*
Написать программу абонентский справочник. Список абонентов представляет собой
статический массив (100) элементов из структур следующего вида:

struct abonent {
    char name[10];
    char second_name[10];
    char tel[10];
}

При запуске на экран выводится текстовое меню:
    1) Добавить абонента
    2) Удалить абонента 
    3) Поиск абонентов по имени
    4) Вывод всех записей
    5) Выход

и пользователю предлагается ввести пункт меню с клавиатуре. Добавление абонента
в массив реализуется простым заполнением свободной структуры, при выходе за 100
абонентов уведомить пользователя о переполнении справочника и не позволять
больше добавлять элементов. При удалении структура заполняется нулями. При 
поиске пользователь вводит с клавиатуры имя абонентов и на экран выводится список
всех абонентов с таким же именем. Программа продолжает выполняться пока 
пользователь не введёт пункт 5.
*/
#include <stdio.h>

struct abonent {
    char name[10];
    char second_name[10];
    char tel[10];
};

enum SUBDIR_COMMAND_LIST {
    SUBDIR_CMD_NONE,
    SUBDIR_CMD_ADD_SUBSCRIBER,
    SUBDIR_CMD_REMOVE_SUBSCRIBER,
    SUBDIR_CMD_FIND_SUBSCRIBER_BY_NAME,
    SUBDIR_CMD_PRINT_ALL_ENTRIES,
    SUBDIR_CMD_EXIT
};

int main(){
    struct abonent subdir[100];
    enum SUBDIR_COMMAND_LIST cmd = SUBDIR_CMD_NONE;

    printf("--- Command menu ---\n");
    printf("Code/Command\n");
    printf(" -%d- Add subscriber\n", (unsigned int)SUBDIR_CMD_ADD_SUBSCRIBER);
    printf(" -%d- Remove subscriber\n", (unsigned int)SUBDIR_CMD_REMOVE_SUBSCRIBER);
    printf(" -%d- Find subscriber by name\n", (unsigned int)SUBDIR_CMD_FIND_SUBSCRIBER_BY_NAME);
    printf(" -%d- Print all entries\n", (unsigned int)SUBDIR_CMD_PRINT_ALL_ENTRIES);
    printf(" -%d- Exit\n", (unsigned int)SUBDIR_CMD_EXIT);

    unsigned int input_commad = 0;
    while (1){
        printf("Enter command code: ");
        scanf("%u", &input_commad);
        getchar();
        cmd = input_commad;

        switch (cmd)
        {
        case SUBDIR_CMD_ADD_SUBSCRIBER:
            printf("SUBDIR_CMD_ADD_SUBSCRIBER\n");
            break;
        case SUBDIR_CMD_REMOVE_SUBSCRIBER:
            printf("SUBDIR_CMD_REMOVE_SUBSCRIBER\n");
            break;
        case SUBDIR_CMD_FIND_SUBSCRIBER_BY_NAME:
            printf("SUBDIR_CMD_FIND_SUBSCRIBER_BY_NAME\n");
            break;
        case SUBDIR_CMD_PRINT_ALL_ENTRIES:
            printf("SUBDIR_CMD_PRINT_ALL_ENTRIES\n");
            break;
        case SUBDIR_CMD_EXIT:
            printf("SUBDIR_CMD_EXIT\n");
            break;
        default:
            printf("Error: Unknown command code\n");
            break;
        }
    }

    return 0;
}
















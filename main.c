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

#define SUBSCRIBER_FIELD_SIZE 10
#define SUBDIR_SIZE 5

struct Subscriber {
    char name[SUBSCRIBER_FIELD_SIZE];
    char second_name[SUBSCRIBER_FIELD_SIZE];
    char tel[SUBSCRIBER_FIELD_SIZE];
};

enum Subdir_command_list {
    SUBDIR_CMD_NONE,
    SUBDIR_CMD_ADD_SUBSCRIBER,
    SUBDIR_CMD_REMOVE_SUBSCRIBER,
    SUBDIR_CMD_FIND_SUBSCRIBER_BY_NAME,
    SUBDIR_CMD_PRINT_ALL_ENTRIES,
    SUBDIR_CMD_EXIT
};

int main(){
    struct Subscriber subdir_base[SUBDIR_SIZE];
    for (int i = 0; i < SUBDIR_SIZE; i++){
        for (int j = 0; j < SUBSCRIBER_FIELD_SIZE; j++){
            subdir_base[i].name[j] = 0;
            subdir_base[i].second_name[j] = 0;
            subdir_base[i].tel[j] = 0;
        }
    }
    
    unsigned int last_empty = 0;
    unsigned int count_free = SUBDIR_SIZE;
    unsigned int subdir_list[SUBDIR_SIZE] = {0};

    enum Subdir_command_list cmd = SUBDIR_CMD_NONE;

    printf("--- Command menu ---\n");
    printf("Code/Command\n");
    printf(" -%d- Add subscriber\n", (unsigned int)SUBDIR_CMD_ADD_SUBSCRIBER);
    printf(" -%d- Remove subscriber\n", (unsigned int)SUBDIR_CMD_REMOVE_SUBSCRIBER);
    printf(" -%d- Find subscriber by name\n", (unsigned int)SUBDIR_CMD_FIND_SUBSCRIBER_BY_NAME);
    printf(" -%d- Print all entries\n", (unsigned int)SUBDIR_CMD_PRINT_ALL_ENTRIES);
    printf(" -%d- Exit\n", (unsigned int)SUBDIR_CMD_EXIT);

    unsigned int input_commad = 0;

    char work = 1;
    while (work){
        printf("\nEnter command code > ");
        scanf("%u", &input_commad);
        getchar();
        cmd = input_commad;

        switch (cmd)
        {
        case SUBDIR_CMD_ADD_SUBSCRIBER:
            if (last_empty < SUBDIR_SIZE){
                // Данные абонента
                printf("(Max field size: %u symbols)\n", (unsigned)SUBSCRIBER_FIELD_SIZE - 1);
                printf("Name: ");
                fgets(subdir_base[last_empty].name, SUBSCRIBER_FIELD_SIZE + 1, stdin);
                printf("Second name: ");
                fgets(subdir_base[last_empty].second_name, SUBSCRIBER_FIELD_SIZE + 1, stdin);
                printf("Tel: ");
                fgets(subdir_base[last_empty].tel, SUBSCRIBER_FIELD_SIZE + 1, stdin);
                printf("Subscriber code: %u\n", last_empty);
                // Пометить запись как не пустую
                subdir_list[last_empty] = 1;
                count_free--;
                // Если элемент был последний, прекратить добавлять
                if (count_free == 0){
                    last_empty = SUBDIR_SIZE;
                // Если элемент был не последний, найти пустой справа
                }else{
                    for (int i = last_empty + 1; i < SUBDIR_SIZE; i++){
                        if (subdir_list[i] == 0){
                            last_empty = i;
                            break;
                        }
                    }
                }
            }else{
                printf("Subscriber directory is full\n");
            }
            break;
        case SUBDIR_CMD_REMOVE_SUBSCRIBER:
            // Ввести код удаляемой записи 
            int index = -1;
            printf("Enter abonent code: ");
            scanf("%d", &index);
            getchar();

            // Проверить границы введённой величины
            if ( (index < 0) || (index >= SUBDIR_SIZE) ){
                printf("Subscriber code out of bounds\n");
                break;
            }

            // Если запись пуста, уведомить пользователя и выйти
            if (subdir_list[index] == 0){
                printf("Subscriber entry is already empty\n");
                break;
            // Если запись не пуста, удалить
            }else{
                // Пометить запись как пустую
                subdir_list[index] = 0;

                // Занулить структуру
                char* ptrByte = &(subdir_base[index]);
                for (int i = 0; i < sizeof(struct Subscriber); i++){
                    *(ptrByte + i) = 0;
                }
                // Сдвинуть минимальный пустой индекс если нужно
                if (index < last_empty)
                    last_empty = index;
                count_free++;
                printf("Entry removed\n");
            }
            break;
        case SUBDIR_CMD_FIND_SUBSCRIBER_BY_NAME:
            char name[SUBSCRIBER_FIELD_SIZE] = {0};
            printf("Name: ");
            fgets(name, SUBSCRIBER_FIELD_SIZE + 1, stdin);

            // unsigned int name_field_value = 0;
            // unsigned int name_value = 0;
            // for (int i = 0; i < SUBSCRIBER_FIELD_SIZE; i++){
            //     name_value = (name_value << 8) | name[i];
            // }
            char match = 0;
            for (int i = 0; i < SUBDIR_SIZE; i++){
                if (subdir_list[i] != 0){
                    char find = 1;
                    // for (int j = 0; j < SUBSCRIBER_FIELD_SIZE; j++){
                    //     name_field_value = (name_field_value << 8) | subdir_base[i].name[j];
                    // }
                    //if (name_value == name_field_value){
                    for (int j = 0; j < SUBSCRIBER_FIELD_SIZE; j++){
                        if (name[j] != subdir_base[i].name[j]){
                            find = 0;
                            break;
                        }
                    }

                    if (find){
                        match = 1;
                        printf("\tSubscriber/ code [%-3u]\t", i);
                        // Если дальше идут символы новой строки, заменить пробелами
                        printf("Name: [");
                        for (int j = 0; j < SUBSCRIBER_FIELD_SIZE - 1; j++)
                            if ((subdir_base[i].name[j] == '\n') || (subdir_base[i].name[j] == '\0'))
                                printf(" ");
                            else
                                printf("%c", subdir_base[i].name[j]);
                        printf("]\t");

                        printf("Second name: [");
                        for (int j = 0; j < SUBSCRIBER_FIELD_SIZE - 1; j++)
                            if ((subdir_base[i].second_name[j] == '\n') || (subdir_base[i].second_name[j] == '\0'))
                                printf(" ");
                            else
                                printf("%c", subdir_base[i].second_name[j]);
                        printf("]\t");

                        printf("Tel: [");
                        for (int j = 0; j < SUBSCRIBER_FIELD_SIZE - 1; j++)
                            if ((subdir_base[i].tel[j] == '\n') || (subdir_base[i].tel[j] == '\0'))
                                printf(" ");
                            else
                                printf("%c", subdir_base[i].tel[j]);
                        printf("]\n");
                    }
                    
                }
            }
            if (!match)
                printf("Subscriber not found\n");
            break;
        case SUBDIR_CMD_PRINT_ALL_ENTRIES:
            for (int i = 0; i < SUBDIR_SIZE; i++){
                // Выводим данные в одну строку существующие записи
                if (subdir_list[i] != 0){
                    printf("\tSubscriber code [%-3u]\t", i);
                    // Если дальше идут символы новой строки, заменить пробелами
                    printf("Name: [");
                    for (int j = 0; j < SUBSCRIBER_FIELD_SIZE - 1; j++)
                        if ((subdir_base[i].name[j] == '\n') || (subdir_base[i].name[j] == '\0'))
                            printf(" ");
                        else
                            printf("%c", subdir_base[i].name[j]);
                    printf("]\t");

                    printf("Second name: [");
                    for (int j = 0; j < SUBSCRIBER_FIELD_SIZE - 1; j++)
                        if ((subdir_base[i].second_name[j] == '\n') || (subdir_base[i].second_name[j] == '\0'))
                            printf(" ");
                        else
                            printf("%c", subdir_base[i].second_name[j]);
                    printf("]\t");

                    printf("Tel: [");
                    for (int j = 0; j < SUBSCRIBER_FIELD_SIZE - 1; j++)
                        if ((subdir_base[i].tel[j] == '\n') || (subdir_base[i].tel[j] == '\0'))
                            printf(" ");
                        else
                            printf("%c", subdir_base[i].tel[j]);
                    printf("]\n");
                }
            }
            break;
        case SUBDIR_CMD_EXIT:
            work = 0;
            break;
        default:
            printf("Error: Unknown command code\n");
            break;
        }
    }

    return 0;
}
















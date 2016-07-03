#include <stdlib.h>
#include <string.h>
#include "lineinteperter.h"
#include "find-apt.h"
#include "add-apt.h"
#include "buy-apt.h"
#include "delete-apt.h"

void start(ApartmentTable *db, History *hist) {
    /*
     * Processing the program, Routing the output, trigger exitSigal
     */
    BOOL isEOF = FALSE;
    char line[INPUT_MAX];
    COMMAND *currCommand = NULL;

    printf("Please enter one of the following commands: \n");
    printf("add-apt, find-apt, buy-apt or delete-apt\n");
    printf("For reconstruction commands, please enter:\n");
    printf("!!, !num, history, short_history or !num^str1^str2\n");

    while (isEOF == FALSE) {
        gets(line);
        if (line[0] != '\0') {
            if (strcmp(line, "exit") == 0) {
                exitHandler(db, hist);
                printf("Good Bye!");
                break;
            } else {
                currCommand = commandLineParser(line);
                //debugCommand(*currCommand);
                routerHandler(currCommand, db, hist);
            }
        }
    }

}

void invoke_from_history(COMMAND *currCommand, ApartmentTable *db, History *hist) {
    /*
     * Invoking A command form the history
     */
    BOOL is_replace_required = FALSE;
    char *find_str = NULL;
    char *replace_str = NULL;
    char *found_str = splitFirst(currCommand->raw_command, '^');
    int history_command_number = 0;

    if (found_str == NULL) {
        // invoke command without replacing string
        if (currCommand->command[1] == '!') {
            history_command_number = -1;
        } else {
            history_command_number = atoi(currCommand->raw_command + 1);
        }
    } else {
        // invoke command with replacing some string in it
        history_command_number = atoi(found_str + 1);
        find_str = splitFirst(currCommand->raw_command + strlen(found_str) + 1, '^');
        replace_str = strdup(currCommand->raw_command + strlen(find_str) + strlen(found_str) + 2);
        is_replace_required = TRUE;
    }

    char *command_from_hist = get_command_by_index(history_command_number, hist);
    char *command_to_run = strdup(command_from_hist);

    if (find_str != NULL && replace_str != NULL) {
        // replacing string
        command_to_run = str_replace(command_to_run, find_str, replace_str);
    }

    currCommand = commandLineParser(command_to_run);
    // invoking the command again
    routerHandler(currCommand, db, hist);
}

void routerHandler(COMMAND *currCommand, ApartmentTable *db, History *hist) {
    /*
     * Factory Pattern function -
     * routing the COMMAND to the right function
     */
    if (strcmp(currCommand->command, "find-apt") == 0) {
        append_last_search(hist, currCommand->raw_command);
        find_apt(*currCommand, *db);
    } else if (strcmp(currCommand->command, "buy-apt") == 0) {
        append_last_search(hist, currCommand->raw_command);
        buy_apt(*currCommand, db);
    } else if (strcmp(currCommand->command, "delete-apt") == 0) {
        append_last_search(hist, currCommand->raw_command);
        delete_apt(*currCommand, db);
    } else if (strcmp(currCommand->command, "add-apt") == 0) {
        append_last_search(hist, currCommand->raw_command);
        add_apt(*currCommand, db);
    } else if (strcmp(currCommand->command, "history") == 0) {
        history(*hist);
    } else if (strcmp(currCommand->command, "short_history") == 0) {
        short_history(*hist);
    } else if (currCommand->command[0] == '!') {
        invoke_from_history(currCommand, db, hist);
    }
}

void exitHandler(ApartmentTable *table, History *hist) {
    /*
     * Exit function handler
     */
    save_history_to_file(*hist);
    save_apartment_table_to_file(table);
}

ApartmentTable *initialProgramState(History *hist) {
    /*
     * initializer for the all project, suppose to initial all data structures and
     * load pre-saved data
     */
    ApartmentTable *table;
    table = load_apartment_table_from_file();
    load_from_history_file(hist);
    return table;
}

COMMAND *commandLineParser(char *str) {
    /*
     * Command line parser
     */
    COMMAND *cmd = malloc(sizeof(Dict));
    char *args = NULL, *command_name = NULL;

    // parsing command name
    cmd->raw_command = strdup(str);
    command_name = strtok(str, " ");
    cmd->command = strdup(command_name);
    cmd->args = NULL;
    cmd->kwargs = NULL;

    /*
     * There only option to have args or extractKwargs (key value arg)
     */
    // lets try to get args
    args = str + strlen(command_name) + 1;
    if (args[0] != '-' && args[0] != '–') {
        cmd->args = extractArgs(args);
    } else {
        cmd->kwargs = extractKwargs(args);
    }

    return cmd;
}

Dict *extractKwargs(char *str) {
    /*
     * extracting kwargs (key value args)
     */
    int pySize = 2, size = 0;
    KeyValue *arr;
    Dict *pt = malloc(sizeof(Dict));

    arr = malloc(sizeof(KeyValue) * 2);
    str = strtok(str, "-");

    while (str != NULL) {
        if (size == pySize) {
            pySize *= 2;
            arr = realloc(arr, sizeof(Dict) * pySize);
        }
        arr[size].key = splitFirst(str, ' ');
        arr[size].value = NULL;
        if (arr[size].key == NULL) {
            arr[size].key = strdup(str);
        } else {
            if (strlen(str) > strlen(arr[size].key)) {
                arr[size].value = trim(strdup(str + strlen(arr[size].key)));
            }
        }
        str = strtok(NULL, "-");
        size++;
    }

    pt->size = size;
    pt->arr = arr;
    return pt;
}

List *extractArgs(char *args) {
    /*
     * extracting args from command line
     */
    List *pList = malloc(sizeof(List));
    char *tmp, *last;

    makeEmptyList(pList);

    while (args != NULL) {
        if (args[0] == '"') {
            args++;
            tmp = splitFirst(args, '"');
            args++;
        } else {
            tmp = splitFirst(args, ' ');
            if (tmp == NULL) {
                tmp = strdup(args);
                args = NULL;
            }
        }
        insertDataToEndList(pList, tmp);
        if (args != NULL)
            args += strlen(tmp) + 1;
    }
    return pList;
}


void debugCommand(COMMAND command1) {
    /*
     * internal use only, for debbuging reasons
     */
    printf("the command name is %s \n", command1.command);

    if (isEmptyList(command1.args)) {
        printf("command dont have args values \n");
    } else {
        printf("command have args values, they are: \n");
        printList(command1.args);
    }

    if (command1.kwargs == NULL) {
        printf("command dont have kwargs values \n");
    } else {
        printf("command have kwargs values \n");
        printDict(command1.kwargs);
    }
    printf("\n \n");

}

void printDict(Dict *kwargs) {
    for (int i = 0; i < kwargs->size; i++) {
        printf("Key : %s \n", kwargs->arr[i].key);
        if (kwargs->arr[i].value != NULL) {
            printf("Value : %s \n", kwargs->arr[i].value);
        }
    }

}

char *getValueByKey(char *key, Dict *kwargs) {
    for (int i = 0; i < kwargs->size; i++) {
        if (strcmp(kwargs->arr[i].key, key) == 0) {
            return kwargs->arr[i].value;
        }
    }
    return NULL;
}

BOOL isKeyExists(char *key, Dict *kwargs) {
    for (int i = 0; i < kwargs->size; i++) {
        if (strcmp(kwargs->arr[i].key, key) == 0) {
            return TRUE;
        }
    }
    return FALSE;
}


void insertNodeToEndList(List *pList, ListNode *newNode) {
    if (isEmptyList(pList)) {
        pList->head = pList->tail = newNode;
    }
    else {
        pList->tail->next = newNode;
        pList->tail = newNode;
    }
}


void makeEmptyList(List *pList) {
    pList->head = pList->tail = NULL;
}

BOOL isEmptyList(List *lst) {
    return (lst == NULL) || (lst->head == NULL);
}

void freeList(List *lst) {
    ListNode *curr = lst->head, *saver;
    while (curr != NULL) {
        saver = curr->next;
        free(curr);
        curr = saver;
    }
}

void insertDataToEndList(List *pList, char *str) {
    ListNode *lNode;
    lNode = createNodeElement(str, NULL);
    insertNodeToEndList(pList, lNode);
}

ListNode *createNodeElement(char *str, ListNode *next) {
    ListNode *pNode;
    pNode = malloc(sizeof(ListNode));
    pNode->data = str;
    pNode->next = next;
    return pNode;
}

void printList(List *pList) {
    ListNode *curr;
    curr = pList->head;
    while (curr != NULL) {
        printf("%s \n", curr->data);
        curr = curr->next;
    }

}

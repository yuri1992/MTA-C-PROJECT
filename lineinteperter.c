#include <stdlib.h>
#include <string.h>
#include "lineinteperter.h"
#include "history.h"
#include "find-apt.h"
#include "add-apt.h"
#include "utils.h"

void start(ApartmentTable *db) {
    /*
     * waiting for input program, kind of router function
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
                exitHandler(db);
                printf("Good Bye!");
                break;
            } else {
                currCommand = commandLineParser(line);
                debugCommand(*currCommand);
                routerHandler(currCommand, db);
            }
        }
    }

}

void routerHandler(COMMAND *currCommand, ApartmentTable *db) {
    if (strcmp(currCommand->command, "find-apt") == 0) {
        find_apt(*currCommand, *db);
    } else if (strcmp(currCommand->command, "buy-apt") == 0) {

    } else if (strcmp(currCommand->command, "delete-apt") == 0) {

    } else if (strcmp(currCommand->command, "add-apt") == 0) {
        add_apt(*currCommand, db);
    } else if (strcmp(currCommand->command, "history") == 0) {

    } else if (strcmp(currCommand->command, "short_history") == 0) {

    }
}

void exitHandler(ApartmentTable *table) {
    /*
     * Exit function handler
     */
    // Todo: save all necessary data to disk

}

ApartmentTable *initialProgramState() {
    /*
     * initializer for the all project, suppose to initial all data structures and
     * load pre-saved data
     */

    // !!!!! only for now i initial the table with "dump" data for tests and debug
    ApartmentTable *table = NULL;
    table = malloc(sizeof(ApartmentTable));
    table->arr = malloc(sizeof(Apartment));
    table->size = 0;
    return table;
    // Todo: initial all pre saved data stores like commands, apartments, etc ..
}

COMMAND *commandLineParser(char *str) {
    COMMAND *cmd = malloc(sizeof(Dict));
    char *args = NULL, *command_name = NULL;

    // parsing command name
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

Dict* extractKwargs(char *str) {
    int pySize = 2, size = 0;
    KeyValue *arr;
    Dict* pt = malloc(sizeof(Dict));

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

char *splitFirst(const char *str, char needle) {
    /*
     * return char* str that wall allocated till first occur of char,
     * return NULL if not found
     */
    char *strEnd, *strOut;
    strEnd = strchr(str, needle);

    if (strEnd == NULL)
        return NULL;

    strOut = malloc(sizeof(char) * (strEnd - str) + 1);
    memset(strOut,'\0',sizeof(strOut));

    strncpy(strOut, str, strEnd - str);
    strOut[strEnd - str] = '\0';
    return trim(strOut);
}

List *extractArgs(char *args) {
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

void printDict(Dict* kwargs) {
    for (int i = 0; i < kwargs->size; i++) {
        printf("Key : %s \n", kwargs->arr[i].key);
        if (kwargs->arr[i].value != NULL) {
            printf("Value : %s \n", kwargs->arr[i].value);
        }
    }

}

char *getValueByKey(char *key, Dict *kwargs) {
    for (int i=0;i< kwargs->size;i++) {
        if (strcmp(kwargs->arr[i].key, key) == 0) {
            return kwargs->arr[i].value;
        }
    }
    return NULL;
}

BOOL isKeyExists(char *key, Dict *kwargs) {
    for (int i=0;i< kwargs->size;i++) {
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

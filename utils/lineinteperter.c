#include <stdlib.h>
#include <string.h>
#include "lineinteperter.h"


COMMAND* commandLineInterperter(char *str) {
    COMMAND* cmd = malloc(sizeof(COMMAND));
    char *tmp, *tmp1, *args;
    char *command_name;
    tmp1 = malloc(sizeof(char) * strlen(str));
    strcpy(tmp1, str);

    // parsing command name
    command_name = strtok(str, " ");
    cmd->command = strdup(command_name);

    // lets try to get args
    args = tmp1 + strlen(command_name) + 1;
    if (args[0] != '-') {
        cmd->args = extractArgs(args);
        cmd->size = 0;
    } else {
        // TODO : extract to function and substring the key and value from @str.
        Dict *dict;
        int size = 0, pySize = 2;
        dict = malloc(sizeof(Dict) * 2);
        cmd->kwargs = dict;
        strtok(tmp1, " ");
        tmp = strtok(NULL, "-");
        while (tmp != NULL) {
            if (size == pySize) {
                pySize *= 2;
                dict = realloc(dict, sizeof(Dict) * pySize);
            }
            dict[size].key = tmp;
            dict[size].value = tmp;
            tmp = strtok(NULL, "-");
            size++;
        }
        cmd->size = size;
    }

    free(tmp1);
    return cmd;
}


List* extractArgs(char *args) {
    List* pList = malloc(sizeof(List));
    char *tmp, *last;

    makeEmptyList(pList);

    while (args != NULL) {
        if (args[0] == '"') {
            args++;
            last = strchr(args, '"');
            tmp = malloc(sizeof(char) * (last - args) + 1);
            strncpy(tmp, args, last - args);
            insertDataToEndList(pList, tmp);
            args += last - args + 2;
        } else {
            last = strchr(args, ' ');
            if (last == NULL) {
                tmp = malloc(sizeof(char) * strlen(args) + 1);
                strcpy(tmp, args);
                insertDataToEndList(pList, tmp);
                break;
            } else {
                tmp = malloc(sizeof(char) * (last - args) + 1);
                strncpy(tmp, args, last - args);
                args += last - args + 1;
                insertDataToEndList(pList, tmp);
            }
        }
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

    if (command1.size == 0) {
        printf("command dont have kwargs values \n");
    } else {
        printf("command have kwargs values \n");
        printDict(command1.kwargs, command1.size);
    }
    printf("\n \n");

}

void printDict(Dict *pValue, int size) {
    for(int i=0;i<size;i++) {
        printf("Key : %s \n", pValue[i].key);
        printf("Value : %s \n", pValue[i].value);
    }

}

char *getValueByKey(char *key, Dict *dict) {
    return NULL;
}

BOOL isKeyExists(char *key, Dict *dict) {
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

void insertDataToEndList(List *pList, char* str) {
    ListNode *lNode;
    lNode = createNodeElement(str, NULL);
    insertNodeToEndList(pList, lNode);
}

ListNode *createNodeElement(char* str, ListNode *next) {
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

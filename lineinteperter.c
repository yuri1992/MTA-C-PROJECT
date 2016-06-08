#include <stdlib.h>
#include <string.h>
#include "lineinteperter.h"
#include "find-apt.h"

void start(ApartmentTable* db) {
    /*
     * waiting for input program, kind of router function
     */
    BOOL isEOF = FALSE;
    char line[INPUT_MAX];
    COMMAND *currCommand = NULL;

    printf("Welcome to your Apartments DB manager, Please Provide your command! \n");
    printf("(hint: exit (for exit), help (to see all avaliable commands)\n");

    while (isEOF == FALSE) {
        gets(line);
        if (line[0] != '\0') {
            if (strcmp(line, "exit") == 0) {
                printf("Saving all data to disk.... please wait... \n");
                exitHandler(db);
                printf("Good bye, All the data been saved and waiting for you...");
                break;
            } else {
                currCommand = commandLineInterperter(line);
                debugCommand(*currCommand);
                routerHandler(currCommand, db);
            }
        }
        printf("Completed! What you want to do next ?");
    }

}

void routerHandler(COMMAND* currCommand, ApartmentTable* db) {
    if (strcmp(currCommand->command, "find-apt") == 0) {
        find_apt(*currCommand, *db);
    } else {

    }
}

void exitHandler(ApartmentTable *table) {
    /*
     * Exit function handler
     */
    // Todo: save all necessary data to disk

}

ApartmentTable* initialProgramState() {
    /*
     * initializer for the all project, suppose to initial all data structures and
     * load pre-saved data
     */

    // !!!!! only for now i initial the table with "dump" data for tests and debug
    ApartmentTable *table =NULL;
    table = malloc(sizeof(ApartmentTable));
    table->arr = malloc(sizeof(Apartment) * 20);
    table->size = 5;
    
    table->arr[0].id = 1;
    table->arr[0].price = 1000000;
    table->arr[0].rooms = 4;
    table->arr[0].address = strdup("Steet 12, City, Israel");
    table->arr[0].entryDate = (short) 123213212;

    table->arr[1].id = 2;
    table->arr[1].price = 1123212;
    table->arr[1].rooms = 3;
    table->arr[1].address = strdup("Steet 12, City, Israel");
    table->arr[1].entryDate = (short) 123213212;

    table->arr[2].id = 3;
    table->arr[2].price = 100000;
    table->arr[2].rooms = 1;
    table->arr[2].address = strdup("Steet 12, City, Israel");
    table->arr[2].entryDate = (short) 123213212;

    table->arr[3].id = 4;
    table->arr[3].price = 3000000;
    table->arr[3].rooms = 2;
    table->arr[3].address = strdup("Steet 12, City, Israel");
    table->arr[3].entryDate = (short) 123213212;

    table->arr[4].id = 5;
    table->arr[4].price = 12132222;
    table->arr[4].rooms = 6;
    table->arr[4].address = strdup("Steet 12, City, Israel");
    table->arr[4].entryDate = (short) 123213212;


    // Todo: initial all pre saved data stores like commands, apartments, etc ..
}

COMMAND* commandLineInterperter(char *str) {
    COMMAND * cmd = malloc(sizeof(Dict));
    char *args, *command_name;

    // parsing command name
    command_name = strtok(str, " ");
    cmd->command = strdup(command_name);
    cmd->size = 0;

    /*
     * There only option to have args or extractKwargs (key value arg)
     */
    // lets try to get args
    args = str + strlen(command_name) + 1;
    if (args[0] != '-') {
        cmd->args = extractArgs(args);
    } else {
        cmd->kwargs = extractKwargs(args, &cmd->size);
    }

    return cmd;
}

Dict *extractKwargs(char *str, int *size) {
    int pySize = 2;

    Dict *dict;
    dict = malloc(sizeof(Dict) * 2);
    str = strtok(str, "-");

    while (str != NULL) {
        if (*size == pySize) {
            pySize *= 2;
            dict = realloc(dict, sizeof(Dict) * pySize);
        }
        dict[*size].key = splitFirst(str, ' ');
        dict[*size].value = strdup(str + strlen(dict[*size].key));
        str = strtok(NULL, "-");
        (*size)++;
    }

    return dict;
}

char* splitFirst(const char* str, char needle) {
    /*
     * return char* str that wall allocated till first occur of char,
     * return NULL if not found
     */
    char *strEnd, *strOut;
    strEnd = strchr(str, needle);

    if (strEnd == NULL)
        return NULL;

    strOut = malloc(sizeof(char) * (strEnd - str) + 1);
    strncpy(strOut, str, strEnd - str);

    return strOut;
}

List* extractArgs(char *args) {
    List* pList = malloc(sizeof(List));
    char *tmp, *last;

    makeEmptyList(pList);

    while (args != NULL) {
        if (args[0] == '"') {
            args++;
            tmp = splitFirst(args, '"');
        } else {
            tmp = splitFirst(args, ' ');
            if (tmp == NULL) {
                tmp = strdup(args);
                args = NULL;
            }
        }
        insertDataToEndList(pList, tmp);
        if (args != NULL)
            args += strlen(tmp) + 2;
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
    // Todo: implement get by key
    return NULL;
}

BOOL isKeyExists(char *key, Dict *dict) {
    // Todo: implement get by key
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

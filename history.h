//
// Created by yurir on 6/24/16.
//

#ifndef MTA_C_PROJECT_HISTORY_H
#define MTA_C_PROJECT_HISTORY_H

#define N 7

typedef struct history {
    char* short_term_history[N];
    char** long_term_history;
    int size_long_history;
} History;

void append_last_search(History* hist, char*str);
void short_history(History hist);
void history(History hist);
char* get_command_by_index(int ind, History* hist);


#endif //MTA_C_PROJECT_HISTORY_H

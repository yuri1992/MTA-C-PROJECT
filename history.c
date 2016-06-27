//
// Created by yurir on 6/24/16.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "history.h"


void append_last_search(History *hist, char *str) {
    char *tmp = NULL;
    // all short term history is full
    if (hist->short_term_history[N - 1] != NULL) {
        tmp = strdup(hist->short_term_history[N - 1]);
    }
    for (int i = N - 1; i >= 1; i--) {
        if (hist->short_term_history[i - 1] != NULL) {
            free(hist->short_term_history[i]);
            hist->short_term_history[i] = malloc(sizeof(char) * strlen(hist->short_term_history[i - 1]) + 1);
            strcpy(hist->short_term_history[i], hist->short_term_history[i - 1]);
        }
    }
    hist->short_term_history[0] = realloc(hist->short_term_history[0], strlen(str) + 1);
    strcpy(hist->short_term_history[0], str);

    if (tmp != NULL) {
        int new_size = hist->size_long_history + 1;

        if (hist->size_long_history == 0) {
            hist->long_term_history = malloc(sizeof(char*) * new_size);
        } else {
            hist->long_term_history = realloc(hist->long_term_history, sizeof(char*) * new_size);
        }
        hist->size_long_history = new_size;

        hist->long_term_history[new_size - 1] = malloc(sizeof(char) * strlen(tmp) + 1);
        strcpy(hist->long_term_history[new_size - 1], tmp);
        free(tmp);
    }
}

void short_history(History hist) {
    for (int i=N-1; i>=0; i--) {
        if (hist.short_term_history[i] != NULL)
            printf("%d: %s\n", hist.size_long_history + (N - i), hist.short_term_history[i]);

    }
}

void history(History hist) {
    // TODO : fix the printing of the commands by logic line and numbers
    for (int i=0; i<hist.size_long_history; i++) {
        printf("%d: %s\n", i + 1, hist.long_term_history[i]);
    }
    short_history(hist);
}

char* get_command_by_index(int ind, History *hist) {
    int total = hist->size_long_history;
    if (ind == -1) {
        return hist->short_term_history[0];
    } else if (ind > total) {
        return hist->short_term_history[N - (ind - total)];
    } else {
        return hist->long_term_history[ind-1];
    }
}

// TODO : implement all !command types
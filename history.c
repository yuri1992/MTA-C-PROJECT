//
// Created by yurir on 6/24/16.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
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
    free(hist->short_term_history[0]);
    hist->short_term_history[0] = malloc(strlen(str) + 1);
    strcpy(hist->short_term_history[0], str);

    if (tmp != NULL) {
        int new_size = hist->size_long_history + 1;

        if (hist->size_long_history == 0) {
            hist->long_term_history = malloc(sizeof(char *) * new_size);
        } else {
            hist->long_term_history = realloc(hist->long_term_history, sizeof(char *) * new_size);
        }
        hist->size_long_history = new_size;

        hist->long_term_history[new_size - 1] = malloc(sizeof(char) * strlen(tmp) + 1);
        strcpy(hist->long_term_history[new_size - 1], tmp);
        free(tmp);
    }
}

void short_history(History hist) {
    for (int i = N - 1; i >= 0; i--) {
        if (hist.short_term_history[i] != NULL)
            printf("%d: %s\n", hist.size_long_history + (N - i), hist.short_term_history[i]);

    }
}

void history(History hist) {
    for (int i = 0; i < hist.size_long_history; i++) {
        printf("%d: %s\n", i + 1, hist.long_term_history[i]);
    }
    short_history(hist);
}

char *get_command_by_index(int ind, History *hist) {
    int total = hist->size_long_history;
    if (ind == -1) {
        return hist->short_term_history[0];
    } else if (ind > total) {
        return hist->short_term_history[N - (ind - total)];
    } else {
        return hist->long_term_history[ind - 1];
    }
}

void load_from_history_file(History *hist) {
    FILE *fp1 = NULL;
    fp1 = fopen((const char *) HISTORY_FILE, "r");

    for (int i = 0; i < N; i++) {
        hist->short_term_history[i] = NULL;
    }
    hist->long_term_history = malloc(sizeof(char*));
    hist->size_long_history = 0;

    if (fp1 != NULL) {
        char line[256] = {};
        int i = 0, string_size = 0;
        while (fgets(line, sizeof line, fp1)) {
            string_size = (int) strlen(line);
            line[string_size - 1] = '\0';
            if (i < N) {
                hist->short_term_history[i] = malloc(sizeof(char) * string_size);
                strcpy(hist->short_term_history[i], line);
            } else {
                if (hist->size_long_history == i - N) {
                    hist->size_long_history++;
                    hist->long_term_history = realloc(hist->long_term_history, sizeof(char*) * hist->size_long_history);
                }
                hist->long_term_history[i - N] = malloc(sizeof(char) * string_size);
                strncpy(hist->long_term_history[i - N], line, (size_t) string_size);
            }
            i++;
        }
    }
}

void save_history_to_file(History hist) {
    FILE *fp1 = NULL;
    fp1 = fopen((const char *) HISTORY_FILE, "w");
    assert(fp1 != NULL);

    // Writing short history commands
    for (int i = 0; i < N; i++) {
        if (hist.short_term_history[i] != NULL) {
            fprintf(fp1, "%s\n", hist.short_term_history[i]);
        }
    }

    // Writing long history commands
    for (int i = hist.size_long_history - 1; i >= 0; i--) {
        fprintf(fp1, "%s\n", hist.long_term_history[i]);
    }

    fclose(fp1);
}
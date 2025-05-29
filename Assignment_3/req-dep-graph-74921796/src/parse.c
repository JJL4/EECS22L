#include "../include/parse.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Helper function to extract requirement tag from a line
static int extract_req_tag(const char *line, char *tag) {
    const char *p = strstr(line, "REQ-");
    if (!p) return 0;
    int i = 0;
    while (p[i] && (isalnum(p[i]) || p[i] == '-')) {
        tag[i] = p[i];
        i++;
        if (i >= 20) break;
    }
    tag[i] = '\0';
    return (i > 0);
}

// Function to parse requirements from a file and build the dependency graph
void parse_requirements(const char *filename, Graph *graph) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return;
    }
    FILE *report = fopen("rdgg-report-74921796.md", "a");
    if (!report) {
        printf("Error: Cannot open report file for writing\n");
        fclose(file);
        return;
    }

    // Characters to hold the current line and requirement tag
    char line[1024];
    int lineno = 0;
    char current_req[32] = "";
    int pending_record = 0;
    int pending_lineno = 0;
    char pending_tag[32] = "";

    while (fgets(line, sizeof(line), file)) {
        lineno++;
        char tag[32];

        // If we have a pending record and hit an empty line, register it now
        if (pending_record && (line[0] == '\n' || line[0] == '\r' || line[0] == 0)) {
            printf("Line %d: %s --\n", pending_lineno, pending_tag);
            fprintf(report, "Line %d: %s --\n", pending_lineno, pending_tag);
            add_requirement(graph, pending_tag);
            strcpy(current_req, pending_tag);
            pending_record = 0;
        }

        // Check for ID line
        if (strstr(line, "ID:")) {
            if (extract_req_tag(line, tag)) {
                pending_record = 1;
                pending_lineno = lineno; // Changed from lineno + 1 to lineno
                strcpy(pending_tag, tag);
            }
        }
        // Check for Parent/Parents line
        else if (strstr(line, "Parent:") || strstr(line, "Parents:")) {
            // Commit any pending ID before using current_req
            if (pending_record) {
                printf("Line %d: %s --\n", pending_lineno, pending_tag);
                fprintf(report, "Line %d: %s --\n", pending_lineno, pending_tag);
                add_requirement(graph, pending_tag);
                strcpy(current_req, pending_tag);
                pending_record = 0;
            }
            char *p = line;
            while (extract_req_tag(p, tag)) {
                printf("Line %d: %s -> %s\n", lineno, tag, current_req);
                fprintf(report, "Line %d: %s -> %s\n", lineno, tag, current_req);
                add_requirement(graph, tag);
                add_dependency(graph, tag, current_req);
                p = strstr(p, tag) + strlen(tag);
            }
        }
        // Check for Child/Children line
        else if (strstr(line, "Child:") || strstr(line, "Children:")) {
            // Commit any pending ID before using current_req
            if (pending_record) {
                printf("Line %d: %s --\n", pending_lineno, pending_tag);
                fprintf(report, "Line %d: %s --\n", pending_lineno, pending_tag);
                add_requirement(graph, pending_tag);
                strcpy(current_req, pending_tag);
                pending_record = 0;
            }
            char *p = line;
            while (extract_req_tag(p, tag)) {
                printf("Line %d: %s -> %s\n", lineno, current_req, tag);
                fprintf(report, "Line %d: %s -> %s\n", lineno, current_req, tag);
                add_requirement(graph, tag);
                add_dependency(graph, current_req, tag);
                p = strstr(p, tag) + strlen(tag);
            }
        }
    }

    // Final commit if file ends with a pending record
    if (pending_record) {
        printf("Line %d: %s --\n", pending_lineno, pending_tag);
        fprintf(report, "Line %d: %s --\n", pending_lineno, pending_tag);
        add_requirement(graph, pending_tag);
        strcpy(current_req, pending_tag);
    }

    fclose(file);
    fclose(report);
}

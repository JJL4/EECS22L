#include "../include/parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

#define MAX_LINE_LENGTH 1024
#define MAX_TAGS 50
#define REQ_PATTERN "REQ-[A-Z]{2}-[A-Z]{4}-[0-9]{4}"

//NEW FUNCTION
static int extract_tags(const char *str, char tags[MAX_TAGS][20]) {
    regex_t regex;
    regmatch_t matches[1];
    int count = 0;

    if (regcomp(&regex, REQ_PATTERN, REG_EXTENDED) != 0) {
        return 0; // Compilation failed
    }

    const char *p = str;
    while (regexec(&regex, p, 1, matches, 0) == 0) {
        int start = matches[0].rm_so;
        int end = matches[0].rm_eo;
        int len = end - start;
        
        if (len < 20) {
            strncpy(tags[count], p + start, len);
            tags[count][len] = '\0';
            count++;
        }
        p += end; // Move past the current match
    }

    regfree(&regex);
    return count; // Return the number of tags found
}
void parse_requirements(const char *filename, Graph *graph) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    } // Open the file for reading
    
    printf("Selected file: %s\n", filename); // Print the selected file name
    char line[MAX_LINE_LENGTH]; // Buffer to hold each line read from the file
    int line_num = 0; // Line number counter
    char current_req[20] = ""; // Current requirement ID being processed
    char tags[MAX_TAGS][20]; // Array to hold extracted tags
    int tag_count; // Number of tags extracted from the current line
    
    // Print first 3 lines
    for (int i = 0; i < 3 && fgets(line, sizeof(line), file); i++) {
        printf("%s", line);
    }
    rewind(file);
    
    while (fgets(line, sizeof(line), file)) {
        line_num++;
        
        // Extract all tags in line
        tag_count = extract_tags(line, tags);
        for (int i = 0; i < tag_count; i++) {
            printf("%04d: %s\n", line_num, tags[i]);
            add_requirement(graph, tags[i]);
        }
        
        // Process requirement records
        if (strstr(line, "ID:")) {
            if (tag_count > 0) {
                strcpy(current_req, tags[0]);
                printf("%04d: %s --\n", line_num, current_req);
            }
        }
        else if (strstr(line, "Parents:") && current_req[0]) {
            for (int i = 0; i < tag_count; i++) {
                if (strcmp(tags[i], current_req) != 0) {
                    printf("%04d: %s -> %s\n", line_num, tags[i], current_req);
                    add_dependency(graph, tags[i], current_req);
                }
            }
        }
        else if (strstr(line, "Children:") && current_req[0]) {
            for (int i = 0; i < tag_count; i++) {
                if (strcmp(tags[i], current_req) != 0) {
                    printf("%04d: %s -> %s\n", line_num, current_req, tags[i]);
                    add_dependency(graph, current_req, tags[i]);
                }
            }
        }
    }
    
    fclose(file);
}
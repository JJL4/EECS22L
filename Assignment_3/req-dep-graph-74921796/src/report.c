#include "../include/report.h"
#include <stdio.h>

// Generate a report of the requirements and their dependencies
void generate_report(const Graph *graph, const char *output_filename)
{
    FILE *f = fopen(output_filename, "w");
    if (!f) {
        printf("Error: Cannot open report file %s\n", output_filename);
        return;
    }
    // Write the header
    int req_count = get_requirement_count(graph);
    for (int i = 0; i < req_count; i++) {
        const char *req_id = get_requirement_id(graph, i);
        fprintf(f, "Requirement: %s\n", req_id);
        int dep_count = get_dependency_count(graph, req_id);
        for (int j = 0; j < dep_count; j++) {
            const char *dep_id = get_dependency_id(graph, req_id, j);
            fprintf(f, "  Depends on: %s\n", dep_id);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}
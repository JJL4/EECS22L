#include "../include/report.h"
#include <stdio.h>

void generate_report(const Graph *graph, const char *output_filename) {
    // Open the output file for writing
    FILE *file = fopen(output_filename, "w");
    if (!file) {
        perror("Error opening output file");
        return;
    }
    fprintf(file, "digraph requirement_dependencies {\n");
    fprintf(file, "  rankdir=LR;\n  node [shape=box];\n\n");

    // Write the number of requirements
    for (int i = 0; i < get_requirement_count(graph); i++) {
        const char *req_id = get_requirement_id(graph, i);
        fprintf(file, "  \"%s\" [label=\"%s\"];\n", req_id, req_id);
    }

    fprintf(file, "\n");

    // Add dependencies as edges
    for (int i = 0; i < get_requirement_count(graph); i++) {
        const char *from_id = get_requirement_id(graph, i);
        for (int j = 0; j < get_dependency_count(graph, from_id); j++) {
            const char *to_id = get_dependency_id(graph, from_id, j);
            fprintf(file, "  \"%s\" -> \"%s\";\n", from_id, to_id);
        }
    }
    fprintf(file, "}\n");
    fclose(file);
    printf("Report generated: %s\n", output_filename);

}
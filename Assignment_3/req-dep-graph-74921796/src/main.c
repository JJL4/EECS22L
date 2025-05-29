#include "../include/parse.h"
#include "../include/report.h"
#include "../include/graph.h"
#include <stdio.h>
#include <stdlib.h>

#define STUDENT_ID "74921796"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input.md>\n", argv[0]);
        return 1;
    } // Check if the correct number of arguments is provided
    
    Graph *graph = create_graph();
    parse_requirements(argv[1], graph);
    // Parse the requirements from the input file and add them to the graph
    
    char report_filename[50];
    snprintf(report_filename, sizeof(report_filename), 
             "rdgg-report-%s.md", STUDENT_ID);
    // Generate the report filename using the student ID
    
    generate_report(graph, report_filename);
    free_graph(graph);
    
    return 0;
}
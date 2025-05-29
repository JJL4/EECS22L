#include "../include/parse.h"
#include "../include/report.h"
#include "../include/graph.h"
#include <stdio.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <input_file> [output_file]\n", argv[0]);
        return 1;
    } // Get input and output file names from command line arguments
    const char* input_filename = argv[1];
    const char* output_filename = (argc > 2) ? argv[2] : "rdgg-report-74921796.md";

    // Print selected file name
    printf("Selected file: %s\n", input_filename);

    // Print first 3 lines of the file
    FILE *file = fopen(input_filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", input_filename);
        return 1;
    }
    char line[1024];
    int line_count = 0;
    while (fgets(line, sizeof(line), file) && line_count < 3) {
        printf("%s", line);
        line_count++;
    }
    fclose(file);

    // Write header to report file before parsing
    FILE *report = fopen(output_filename, "w");
    if (report) {
        fprintf(report, "# <center>Software Requirements Specification </center>\n");
        fprintf(report, "<center> EECS 22L - Spring 2025 </center>\n");
        fprintf(report, "<center> Project 1 - Chess Game </center>\n");
        fclose(report);
    }

    Graph *graph = create_graph();
    parse_requirements(input_filename, graph);
    // Optionally call generate_report if you want a dependency summary at the end
    // generate_report(graph, output_filename);
    free_graph(graph);
    return 0;
}
#include "../include/parse.h"
#include "../include/report.h"
#include "../include/graph.h"
//Bare minimum of libraries needed for compiling for main.c

int main(int argc, char **argv) {
    //TODO: Implement the main function to handle command line arguments and call the appropriate functions
    //The below are some example functions that are implemented and others can also be implemented as needed
    //Include argument parsing for input and output files. No more than 2 arguments usually
    const char* input_filename = argv[1];
    const char* output_filename = argv[2];
    //Include creating a graph and adding requirements and dependencies
    Graph *graph = create_graph();
    //Include parsing requirements from a file
    parse_requirements(input_filename, graph);
    //Include generating a report
    generate_report(graph, output_filename);
    //Include freeing the graph memory
    free_graph(graph);
    return 0;
}
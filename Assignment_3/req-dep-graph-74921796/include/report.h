#ifndef REPORT_H
#define REPORT_H

#include "graph.h"

void generate_report(const Graph *graph, const char *output_filename); // If this function is called, generate a report of the document or just print it out on console containing the requirements and dependencies in the graph

#endif // REPORT_H
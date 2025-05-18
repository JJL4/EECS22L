#ifndef GRAPH_H
#define GRAPH_H

typedef struct Graph Graph; // typedef struct Node Node; that basically forward declares the struct amd uses an invisible pointer 

Graph *create_graph();// Create a new graph in the memory
void add_requirement(Graph *graph, const char *req_id); // Add new requirement node to the graph if called
void add_dependency(Graph *graph, const char *from_req, const char *to_req); // Create a new dependency relationship between two requirements
void free_graph(Graph *graph);// If used, free the memory allocated for a selected graph and should become invalid
int get_requirement_count(const Graph *graph);// Ask user what is the number of requirements in the graph
const char *get_requirement_id(const Graph *graph, int index);// For each requirement, get the unique ID of the requirement
int get_dependency_count(const Graph *graph, const char *req_id);// Ask user what is the number of dependencies for a specific requirement
const char *get_dependency_id(const Graph *graph, const char *req_id, int index);// For each dependency made, get the unique dependency ID for a requirement

#endif// GRAPH_H
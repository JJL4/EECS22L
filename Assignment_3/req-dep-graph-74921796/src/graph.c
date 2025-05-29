#include "../include/graph.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Bare minimum of libraries needed for compiling

typedef struct Node {
    char *id; // Unique identifier for the requirement
    struct Node **dependencies; // Array of pointers to dependent nodes
    int dep_count; // Number of dependencies
    int dep_capacity; // Capacity of the dependencies array
}Node;

struct Graph {
    Node **requirements; // Array of pointers to requirements (nodes)
    int req_count; // Number of requirements
    int req_capacity; // Capacity of the requirements array
    //TODO: Implement the graph structure
};

Graph *create_graph() {
    Graph *graph = malloc(sizeof(Graph)); // Allocate memory for the graph structure
    graph->requirements = NULL; // Initialize the requirements array to NULL
    graph->req_count = 0; // Initialize the count of requirements to 0
    graph->req_capacity = 0; // Initialize the capacity of the requirements array to 0
    return graph;
}
//NEW FUNCTION
static Node *find_node(Graph *graph, const char *id) {
    // Search for a node with the given ID in the graph
    for (int i = 0; i < graph->req_count; i++) {
        if (strcmp(graph->requirements[i]->id, id) == 0) {
            return graph->requirements[i];
        }
    }
    return NULL; // Return NULL if not found
}

void add_requirement(Graph *graph, const char *req_id) {
    if (find_node(graph, req_id)) return; // If the requirement already exists, do nothing
    if (graph->req_count >= graph->req_capacity) {
        graph->req_capacity = graph->req_capacity ? graph->req_capacity * 2 : 4;
        graph->requirements = realloc(graph->requirements, graph->req_capacity * sizeof(Node*));
    } // Resize the requirements array if necessary
    Node *new_node = malloc(sizeof(Node)); // Allocate memory for the new node
    new_node->id = strdup(req_id); // Duplicate the requirement ID string
    new_node->dependencies = NULL; // Initialize dependencies to NULL
    new_node->dep_count = 0; // Initialize the dependency count to 0
    new_node->dep_capacity = 0; // Initialize the dependency capacity to 0
    graph->requirements[graph->req_count++] = new_node; // Add the new node to the graph
}    

void add_dependency(Graph *graph, const char *from_req, const char *to_req) {
    Node *new_node = find_node(graph, from_req); // Find the node for the 'from' requirement
    if (!new_node) return; // If the 'from' requirement does not exist, do nothing

    for (int i = 0; i < new_node->dep_count; i++) {
        if (strcmp(new_node->dependencies[i]->id, to_req) == 0) {
            return; // If the dependency already exists, do nothing
        }
    }

    if (new_node->dep_count >= new_node->dep_capacity) {
        new_node->dep_capacity = new_node->dep_capacity ? new_node->dep_capacity * 2 : 4;
        new_node->dependencies = realloc(new_node->dependencies, new_node->dep_capacity * sizeof(Node*));
    } // Resize the dependencies array if necessary

    new_node->dependencies[new_node->dep_count] = strdup(to_req); // Duplicate the dependency ID string
}

void free_graph(Graph *graph) {
    for (int i = 0; i < graph->req_count; i++) {
        free (graph ->requirements[i]->id); // Free the ID string of each requirement
        for (int j = 0; j < graph->requirements[i]->dep_count; j++) {
            free(graph->requirements[i]->dependencies[j]); // Free each dependency ID string
        }
        free(graph->requirements[i]->dependencies); // Free the dependencies array
        free(graph->requirements[i]); // Free the requirement node itself
    }
    free(graph->requirements); // Free the requirements array
    free(graph); // Free the graph structure itself
}

int get_requirement_count(const Graph *graph) {
    return graph->req_count; // Return the count of requirements in the graph
}

const char *get_requirement_id(const Graph *graph, int index) {
    if (index < 0 || index >= graph->req_count) {
        return NULL; // Return NULL if the index is out of bounds
    }
    return graph->requirements[index]->id; // Return the ID of the requirement at the given index
}

int get_dependency_count(const Graph *graph, const char *req_id) {
    Node *node = find_node(graph, req_id); // Find the node for the given requirement ID
    return node ? node->dep_count : 0; // Return the count of dependencies, or 0 if the node is not found
}

const char *get_dependency_id(const Graph *graph, const char *req_id, int index) {
    Node *node = find_node(graph, req_id); // Find the node for the given requirement ID
    if (!node || index < 0 || index >= node->dep_count) {
        return NULL; // Return NULL if the node is not found or the index is out of bounds
    }
    return node->dependencies[index]; // Return the ID of the dependency at the given index
}
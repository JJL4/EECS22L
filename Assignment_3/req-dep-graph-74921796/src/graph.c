#include "../include/graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Needed for strdup on Windows
#ifndef _MSC_VER
#include <strings.h>
#endif

typedef struct Node {
    char req_id[32];
    char **dependencies; // Array of child requirement IDs
    int dep_count;
    int dep_capacity;
    struct Node *next;
} Node;

struct Graph {
    Node *head;
    int req_count;
};

Graph *create_graph() {
    Graph *g = (Graph*)malloc(sizeof(Graph));
    g->head = NULL;
    g->req_count = 0;
    return g;
}

// Make find_node accept const Graph*
static Node *find_node(const Graph *graph, const char *req_id) {
    Node *cur = graph->head;
    while (cur) {
        if (strcmp(cur->req_id, req_id) == 0) return cur;
        cur = cur->next;
    }
    return NULL;
}

// Add a new requirement to the graph
void add_requirement(Graph *graph, const char *req_id) {
    if (find_node(graph, req_id)) return;
    Node *node = (Node*)malloc(sizeof(Node));
    strncpy(node->req_id, req_id, sizeof(node->req_id));
    node->req_id[sizeof(node->req_id) - 1] = '\0'; // Ensure null-termination
    node->dep_count = 0;
    node->dep_capacity = 2;
    node->dependencies = (char**)malloc(node->dep_capacity * sizeof(char*));
    node->next = graph->head;
    graph->head = node;
    graph->req_count++;
}

// NEW FUNCTION Provide a local strdup implementation if not available
#ifndef HAVE_STRDUP
static char *my_strdup(const char *s) {
    size_t len = strlen(s) + 1;
    char *d = (char*)malloc(len);
    if (d) memcpy(d, s, len);
    return d;
}
#else
#define my_strdup strdup
#endif

// Add a dependency from one requirement to another
void add_dependency(Graph *graph, const char *from_req, const char *to_req) {
    Node *from = find_node(graph, from_req);
    if (!from) return;
    // Check for duplicate
    for (int i = 0; i < from->dep_count; i++) {
        if (strcmp(from->dependencies[i], to_req) == 0) return;
    }
    if (from->dep_count >= from->dep_capacity) {
        from->dep_capacity *= 2;
        from->dependencies = (char**)realloc(from->dependencies, from->dep_capacity * sizeof(char*));
    }
    from->dependencies[from->dep_count] = my_strdup(to_req);
    from->dep_count++;
}
// Free the graph and all its nodes
void free_graph(Graph *graph) {
    Node *cur = graph->head;
    while (cur) {
        for (int i = 0; i < cur->dep_count; i++) {
            free(cur->dependencies[i]);
        }
        free(cur->dependencies);
        Node *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    free(graph);
}
// Get the number of requirements in the graph
int get_requirement_count(const Graph *graph) {
    return graph->req_count;
}

// Get the ID of a requirement by its index
const char *get_requirement_id(const Graph *graph, int index) {
    Node *cur = graph->head;
    int i = 0;
    while (cur) {
        if (i == index) return cur->req_id;
        cur = cur->next;
        i++;
    }
    return NULL;
}
// Get the number of dependencies for a given requirement
int get_dependency_count(const Graph *graph, const char *req_id) {
    const Node *node = find_node(graph, req_id); // Now uses const Graph*
    return node ? node->dep_count : 0;
}

// Get the ID of a dependency for a given requirement by index
const char *get_dependency_id(const Graph *graph, const char *req_id, int index) {
    const Node *node = find_node(graph, req_id); // Now uses const Graph*
    if (node && index < node->dep_count) {
        return node->dependencies[index];
    }
    return NULL;
}
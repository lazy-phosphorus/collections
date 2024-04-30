#include "linked-graph.h"

#include <asm-generic/errno-base.h>
#include <errno.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>

#include "array-list.h"
#include "types.h"

int GraphVertexConstruct(GraphVertex* const restrict vertex,
                         const void* const restrict value,
                         const unsigned long elementSize) {
    if (vertex == NULL || elementSize == 0) return -1;

    vertex->value = malloc(elementSize);
    if (vertex->value == NULL) return -1;
    memcpy(vertex->value, value, elementSize);
    vertex->mark = GRAPH_NOMARK;
    return 0;
}

GraphVertex* GraphVertexNew(const void* const restrict value,
                            const unsigned long elementSize) {
    GraphVertex* vertex = (GraphVertex*)malloc(sizeof(GraphVertex));
    if (vertex == NULL) return NULL;
    if (GraphVertexConstruct(vertex, value, elementSize) == -1) {
        free(vertex);
        return NULL;
    }
    return vertex;
}

void GraphVertexDestruct(GraphVertex* const restrict vertex) {
    if (vertex == NULL) return;
    free(vertex->value);
    vertex->value = NULL;
    vertex->mark = GRAPH_NOMARK;
}

void GraphVertexDelete(GraphVertex** const restrict vertex) {
    if (vertex == NULL) return;
    GraphVertexDestruct(*vertex);
    free(*vertex);
    *vertex = NULL;
}

int GraphConstruct(Graph* const restrict graph,
                   const unsigned long vertexElementSize,
                   const unsigned long edgeElementSize,
                   CompareFunction* const vertexCompare,
                   CompareFunction* const edgeCompare) {
    if (graph == NULL || vertexCompare == NULL || edgeCompare == NULL) {
        errno = EINVAL;
        return -1;
    }

    graph->vertex = ArrayListNew(10, sizeof(GraphVertex), vertexCompare);
    if (graph->vertex == NULL) return -1;
    graph->edge = ArrayListNew(10, sizeof(ArrayList), edgeCompare);
    if (graph->edge == NULL) return -1;
    graph->vertexElementSize = vertexElementSize;
    graph->edgeElementSize = edgeElementSize;
    return 0;
}

Graph* GraphNew(const unsigned long vertexElementSize,
                const unsigned long edgeElementSize,
                CompareFunction* const compare,
                CompareFunction* const edgeCompare);

void GraphDestruct(Graph* const restrict graph);

void GraphDelete(Graph** const restrict graph);
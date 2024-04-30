#ifndef __COLLECTIONS_LINKED_GRAPH__
#define __COLLECTIONS_LINKED_GRAPH__

#include "array-list.h"
#include "types.h"

typedef enum {
    GRAPH_NOMARK,
    GRAPH_VISITED,
    GRAPH_DEPRECATED,
} GraphMark;

typedef struct {
    void* value;
    GraphMark mark;
} GraphVertex;

typedef struct {
    void* value;
    GraphMark mark;
} GraphEdge;

typedef struct {
    ArrayList* vertex;
    ArrayList* edge;
    unsigned long vertexElementSize;
    unsigned long edgeElementSize;
} Graph;

int GraphVertexConstruct(GraphVertex* const restrict vertex,
                         const void* const restrict value,
                         const unsigned long elementSize);

GraphVertex* GraphVertexNew(const void* const restrict value,
                            const unsigned long elementSize);

void GraphVertexDestruct(GraphVertex* const restrict vertex);

void GraphVertexDelete(GraphVertex** const restrict vertex);

int GraphConstruct(Graph* const restrict graph,
                   const unsigned long vertexElementSize,
                   const unsigned long edgeElementSize,
                   CompareFunction* const vertexCompare,
                   CompareFunction* const edgeCompare);

Graph* GraphNew(const unsigned long vertexElementSize,
                const unsigned long edgeElementSize,
                CompareFunction* const vertexCompare,
                CompareFunction* const edgeCompare);

void GraphDestruct(Graph* const restrict graph);

void GraphDelete(Graph** const restrict graph);

#endif  // __COLLECTIONS_LINKED_GRAPH__
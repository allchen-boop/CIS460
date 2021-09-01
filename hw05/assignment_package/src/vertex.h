#ifndef VERTEX_H
#define VERTEX_H

#include <QListWidget>
#include <halfedge.h>
#include <la.h>

class HalfEdge;

static int lastVertex;

class Vertex : public QListWidgetItem
{
public:

    glm::vec3 pos;      // storing position
    HalfEdge* edge;     // pointer to one of the HalfEdges that points to this Vertex
    int id;             // unique integer to identify the Vertex
    QString name;

    Vertex();
    Vertex(const Vertex &vertex);
};

#endif // VERTEX_H

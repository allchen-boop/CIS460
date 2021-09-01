#ifndef VERTEX_H
#define VERTEX_H

#include <QListWidget>
#include <halfedge.h>
#include <joint.h>
#include <la.h>

class HalfEdge;

class Vertex : public QListWidgetItem
{
public:
    static int lastVertex;

    glm::vec3 pos;      // storing position
    HalfEdge* edge;     // pointer to one of the HalfEdges that points to this Vertex
    int id;             // unique integer to identify the Vertex
    QString name;

    // store which joints influence its transformation and by how much they influence it
    // pairs of joint ids and joint weights
    std::vector<std::pair<int, float>> influences;

    Vertex();
    Vertex(const Vertex &vertex);
};

#endif // VERTEX_H

#ifndef HALFEDGE_H
#define HALFEDGE_H

#include <QListWidget>
#include <vertex.h>
#include <face.h>
#include <la.h>

class Vertex;
class Face;

static int lastHalfEdge;

class HalfEdge : public QListWidgetItem
{
public:
    HalfEdge* next;     // pointer to the next HalfEdge in the loop of HalfEdges that lie on this HalfEdge's Face
    HalfEdge* symm;     // this HalfEdge's symmetrical HalfEdge
    Face* face;         // pointer to the Face on which this HalfEdge lies
    Vertex* vertex;     // pointer to the Vertex between this HalfEdge and its next HalfEdge
    int id;             // unique integer to identify the HalfEdge

    QString name;

    HalfEdge();
    HalfEdge(const HalfEdge &halfEdge);

};

#endif // HALFEDGE_H

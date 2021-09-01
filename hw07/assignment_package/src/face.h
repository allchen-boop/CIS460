#ifndef FACE_H
#define FACE_H

#include <QListWidgetItem>
#include <halfedge.h>
#include <la.h>

class HalfEdge;

class Face : public QListWidgetItem
{
public:
    static int lastFace;

    HalfEdge* edge;     // pointer to one of the HalfEdges that lies on this Face
    int id;             // unique integer to identify the Face
    glm::vec3 color;    // vec3 to represent this Face's color as an RGB value
    QString name;

    Face();
    Face(const Face &face);

    void setColor();
};

#endif // FACE_H

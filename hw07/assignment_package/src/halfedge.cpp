#include "halfedge.h"

int HalfEdge::lastHalfEdge = 0;

HalfEdge::HalfEdge()
    : QListWidgetItem(), next(nullptr), symm(nullptr),
      face(nullptr), vertex(nullptr), id(0), name("half edge ")
{
    id = lastHalfEdge++;
    name.append(QString::number(id));
    this->setText(name);
}

HalfEdge::HalfEdge(const HalfEdge &halfEdge)
    : QListWidgetItem(), next(halfEdge.next),
      symm(halfEdge.symm), face(halfEdge.face),
      vertex(halfEdge.vertex), id(halfEdge.id), name(halfEdge.name)
{}

void HalfEdge::setFace(Face *f) {
    this->face = f;
    f->edge = this;
}

void HalfEdge::setVertex(Vertex *v) {
    this->vertex = v;
    v->edge = this;
}

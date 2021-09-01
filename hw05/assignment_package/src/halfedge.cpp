#include "halfedge.h"

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

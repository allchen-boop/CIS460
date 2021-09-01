#include "vertex.h"

int Vertex::lastVertex = 0;

Vertex::Vertex()
    : QListWidgetItem(),
      pos(glm::vec3()), edge(nullptr),
      influences(),
      id(0), name("vertex ")
{
    id = lastVertex++;
    name.append(QString::number(id));
    this->setText(name);
}

Vertex::Vertex(const Vertex &vertex)
    : QListWidgetItem(),
      pos(vertex.pos), edge(vertex.edge),
      influences(vertex.influences),
      id(vertex.id), name(vertex.name)
{}



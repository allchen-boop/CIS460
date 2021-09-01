#include "vertex.h"

Vertex::Vertex()
    : QListWidgetItem(), pos(glm::vec3()),
      edge(nullptr), id(0), name("vertex ")
{
    id = lastVertex++;
    name.append(QString::number(id));
    this->setText(name);
}

Vertex::Vertex(const Vertex &vertex)
    : QListWidgetItem(), pos(vertex.pos),
      edge(vertex.edge), id(vertex.id),
      name(vertex.name)
{}



#include "face.h"

Face::Face()
    : QListWidgetItem(), edge(nullptr), id(0),
      color(glm::vec3(0, 0, 0)), name("face ")
{
    id = lastFace++;
    name.append(QString::number(id));
    this->setText(name);
}

Face::Face(const Face &face)
    : QListWidgetItem(), edge(face.edge), id(face.id),
      color(face.color), name(face.name)
{}


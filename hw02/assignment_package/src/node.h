#ifndef NODE_H
#define NODE_H

#include "smartpointerhelp.h"
#include "drawable.h"
#include "scene/polygon.h"

#include <QtWidgets/QTreeWidget>
#include <QString>
#include <vector>


class Node : public QTreeWidgetItem
{

private:
    QString name;
    Polygon2D* geometry;
    glm::vec3 color;

public:
    std::vector<uPtr<Node>> children;

    // constructors
    Node();
    Node(QString name);
    Node(const Node &node); // copy constuctor

    // getters
    Polygon2D* getPolygon();
    const QString getName();
    const glm::vec3 getColor();

    // setters
    void setPolygon(Polygon2D &geometry);
    void setColor(glm::vec3 color);

    // functions
    Node& addChild(uPtr<Node> node);

    virtual glm::mat3 transform() = 0;

    // destructor
    virtual ~Node();
};


#endif // NODE_H

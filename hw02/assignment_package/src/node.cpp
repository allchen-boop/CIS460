#include "node.h"
#include "translatenode.h"
#include "scalenode.h"
#include "rotatenode.h"

// constructors
Node::Node() : QTreeWidgetItem(), name(), geometry(nullptr), color(), children()
{
     this->QTreeWidgetItem::setText(0, this->name);
}

Node::Node(QString name)
    : QTreeWidgetItem(), name(name), geometry(nullptr), color(), children()
{
    this->QTreeWidgetItem::setText(0, this->name);
}


// copy constructor
Node::Node(const Node &node)
    : QTreeWidgetItem(), name(node.name), geometry(node.geometry), color(node.color)
{
    for (const uPtr<Node> &child : node.children) {

        TranslateNode *translate = dynamic_cast<TranslateNode*>(child.get());
        if (translate != nullptr) {
            children.push_back(mkU<TranslateNode>(*translate));
        }

        ScaleNode *scale = dynamic_cast<ScaleNode*>(child.get());
        if (scale != nullptr) {
            children.push_back(mkU<ScaleNode>(*scale));
        }

        RotateNode *rotate = dynamic_cast<RotateNode*>(child.get());
        if (rotate != nullptr) {
            children.push_back(mkU<RotateNode>(*rotate));
        }
    }

    this->QTreeWidgetItem::setText(0, this->name);
}


// getters
Polygon2D* Node::getPolygon() {
    return this->geometry;
}

const QString Node::getName() {
    return this->name;
}

const glm::vec3 Node::getColor() {
    return this->color;
}

// setters
void Node::setPolygon(Polygon2D &geometry) {
    this->geometry = &geometry;
}

void Node::setColor(glm::vec3 color) {
    this->color[0] = color[0];
    this->color[1] = color[1];
    this->color[2] = color[2];
}

// from lecture slides
Node& Node::addChild(uPtr<Node> node) {
    Node& ref = *node;
    this->children.push_back(std::move(node));
    QTreeWidgetItem::addChild(&ref);
    return ref;
}

Node::~Node() {
}

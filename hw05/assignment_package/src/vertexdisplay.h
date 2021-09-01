#ifndef VERTEXDISPLAY_H
#define VERTEXDISPLAY_H

#include <drawable.h>
#include <vertex.h>
#include <la.h>


class VertexDisplay : public Drawable
{
protected:
    Vertex *representedVertex;

public:
    // Creates VBO data to make a visual
    // representation of the currently selected Vertex
    void virtual create() override;
    // Change which Vertex representedVertex points to
    void updateVertex(Vertex*);

    GLenum drawMode() override;

    VertexDisplay(OpenGLContext* context);

    ~VertexDisplay();
};

#endif // VERTEXDISPLAY_H

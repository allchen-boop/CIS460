#ifndef MESH_H
#define MESH_H

#include <drawable.h>
#include <smartpointerhelp.h>
#include <face.h>
#include <halfedge.h>
#include <vertex.h>


class Mesh : public Drawable
{
public:

    std::vector<uPtr<Face>> faces;
    std::vector<uPtr<HalfEdge>> halfEdges;
    std::vector<uPtr<Vertex>> vertices;

    void buildCube();           // set up mesh data of cube
    void setCubeData();

    void setHalfEdgeVertices(int x, int y, int z, int vert);
    void triangulate(Face *face);
    void splitEdge(HalfEdge *he_1);

    void create() override;      // construct and send data to vbo
    GLenum drawMode() override;

    Mesh(OpenGLContext* context);

    ~Mesh();
};

#endif // MESH_H

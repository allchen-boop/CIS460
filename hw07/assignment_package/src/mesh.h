#ifndef MESH_H
#define MESH_H

#include <drawable.h>
#include <smartpointerhelp.h>
#include <face.h>
#include <halfedge.h>
#include <vertex.h>
#include <skeleton.h>
#include <set>


class Mesh : public Drawable
{
public:

    std::vector<uPtr<Face>> faces;
    std::vector<uPtr<HalfEdge>> halfEdges;
    std::vector<uPtr<Vertex>> vertices;
    std::vector<uPtr<Joint>> joints;

    void buildCube();           // set up mesh data of cube
    void setCubeData();

    void setHalfEdgeVertices(int x, int y, int z, int vert);

    void triangulate(Face *face);
    void splitEdge(HalfEdge *he_1);

    void subdivide();

    void centroid(std::map<Face*, Vertex*> *centroid_map,
                  std::vector<uPtr<Vertex>> *newVertices);

    void midpoint(std::map<Face*, Vertex*> *centroid_map,
                   std::map<HalfEdge*, Vertex*> *midpoint_map,
                   std::set<HalfEdge*>  *edge_split,
                   std::vector<uPtr<Vertex>> *newVertices);

    void smooth(std::map<Face*, Vertex*> *centroid_map,
                std::map<HalfEdge*, Vertex*> *midpoint_map);

    void quadrangulate(std::set<HalfEdge*>  *edge_split,
                       std::map<Face*, Vertex*> *centroid_map,
                       std::map<HalfEdge*, Vertex*> *midpoint_map,
                       std::vector<uPtr<HalfEdge>> *newHalfEdges,
                       std::vector<uPtr<Face>> *newFaces);

    void assignSymm(std::vector<uPtr<HalfEdge>> *in_edges,
                    std::vector<uPtr<HalfEdge>> *out_edges,
                    std::vector<uPtr<HalfEdge>> *newHalfEdges);

    void setFaces(std::vector<HalfEdge*> *temp_he, Face *f, int n);

    std::vector<uPtr<Face>> quadFaces(std::vector<HalfEdge*> *temp_he, Face *f);

    void create() override;      // construct and send data to vbo
    GLenum drawMode() override;

    Mesh(OpenGLContext* context);

    ~Mesh();
};

#endif // MESH_H

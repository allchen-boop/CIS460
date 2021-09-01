#include "mesh.h"
#include "iostream"



Mesh::Mesh(OpenGLContext* context)
    : Drawable(context), faces{}, halfEdges{}, vertices{}
{}

Mesh::~Mesh()
{}

// helper
int getNumSides(Face *face) {
    HalfEdge* curr = face->edge;
    int numSides = 0;

    do {
        curr = curr->next;
        numSides++;
    } while (curr != face->edge);

    return numSides;
}

void Mesh::create() {
    std::vector<glm::vec4> pos;
    std::vector<glm::vec4> nor;
    std::vector<glm::vec4> color;
    std::vector<GLuint> idx;

    for (uPtr<Face> &f : faces) {
        HalfEdge *currEdge = f->edge;
        int firstCount = pos.size();

        do {
            HalfEdge* curr = currEdge;
            glm::vec3 v1 = curr->next->vertex->pos - curr->vertex->pos;
            glm::vec3 v2 = curr->next->next->vertex->pos - curr->next->vertex->pos;

            while (glm::length(glm::cross(v1, v2)) < FLT_EPSILON) {
                curr = curr->next;
                v1 = curr->next->vertex->pos - curr->vertex->pos;
                v2 = curr->next->next->vertex->pos - curr->next->vertex->pos;
            }

            glm::vec4 normal = glm::vec4(glm::normalize(glm::cross(v1, v2)), 0);

            pos.push_back(glm::vec4(currEdge->vertex->pos, 1));
            nor.push_back(normal);
            color.push_back(glm::vec4(f->color, 1));

            currEdge = currEdge->next;

        } while (currEdge != f->edge);

        // mesh indices
        int i = 0;
        while (i < getNumSides(f.get()) - 2) {
            idx.push_back(firstCount);
            idx.push_back(firstCount + i + 1);
            idx.push_back(firstCount + i + 2);
            i++;
        }
    }

    count = idx.size();

    generateIdx();
    bindIdx();
    mp_context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx.size() * sizeof(GLuint), idx.data(), GL_STATIC_DRAW);

    generatePos();
    bindPos();
    mp_context->glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(glm::vec4), pos.data(), GL_STATIC_DRAW);

    generateNor();
    bindNor();
    mp_context->glBufferData(GL_ARRAY_BUFFER, nor.size() * sizeof(glm::vec4), nor.data(), GL_STATIC_DRAW);

    generateCol();
    bindCol();
    mp_context->glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(glm::vec4), color.data(), GL_STATIC_DRAW);
}

GLenum Mesh::drawMode() {
    return GL_TRIANGLES;
}

void Mesh::buildCube() {

    // initializing
    for (int i = 0; i < 6; i++) {
        uPtr<Face> face = mkU<Face>();
        faces.push_back(std::move(face));
    }

    for (int i = 0; i < 8; i++) {
        uPtr<Vertex> vertex = mkU<Vertex>();
        vertices.push_back(std::move(vertex));
    }

    for (int i = 0; i < 24; i++) {
        uPtr<HalfEdge> halfEdge = mkU<HalfEdge>();
        halfEdges.push_back(std::move(halfEdge));
    }

    setCubeData();
}

void Mesh::setHalfEdgeVertices(int x, int y, int z, int vert) {
    halfEdges.at(x)->vertex = vertices.at(vert).get();
    halfEdges.at(y)->vertex = vertices.at(vert).get();
    halfEdges.at(z)->vertex = vertices.at(vert).get();
}

void Mesh::setCubeData() {

   std::vector<glm::vec3> pos {glm::vec3 (-0.5, 0.5, 0.5),
                               glm::vec3 (-0.5, -0.5, 0.5),
                               glm::vec3 (0.5, -0.5, 0.5),
                               glm::vec3 (0.5, 0.5, 0.5),

                               glm::vec3 (0.5, 0.5, -0.5),
                               glm::vec3 (0.5, -0.5, -0.5),
                               glm::vec3 (-0.5, -0.5, -0.5),
                               glm::vec3 (-0.5, 0.5, -0.5)};

    std::vector<glm::vec3> col {glm::vec3 (0, 0, 1),
                                glm::vec3 (0, 0, 1),
                                glm::vec3 (1, 0, 0),

                                glm::vec3 (1, 0, 0),
                                glm::vec3 (0, 1, 0),
                                glm::vec3 (0, 1, 0)};

    for (int i = 0; i < 6; i++) {
        faces.at(i)->color = col[i];
        faces.at(i)->edge = halfEdges.at(4 * i).get();
    }

    for (int i = 0; i < 8; i++) {
        vertices.at(i)->pos = pos[i];
        vertices.at(i)->edge = halfEdges.at(i).get();
    }

    for (int i = 0; i < 24 ; i++) {
        halfEdges.at(i)->face = faces.at(i / 4).get();

        if (i % 4 == 3) {
            halfEdges.at(i)->next = halfEdges.at(i - 3).get();
        } else {
            halfEdges.at(i)->next = halfEdges.at(i + 1).get();
        }
    }

    setHalfEdgeVertices(0, 15, 17, 0);
    setHalfEdgeVertices(1, 14, 22, 1);
    setHalfEdgeVertices(2, 9, 21, 2);
    setHalfEdgeVertices(3, 8, 18, 3);
    setHalfEdgeVertices(4, 11, 19, 4);
    setHalfEdgeVertices(5, 10, 20, 5);
    setHalfEdgeVertices(6, 13, 23, 6);
    setHalfEdgeVertices(7, 12, 16, 7);

    halfEdges.at(0)->symm = halfEdges.at(18).get();
    halfEdges.at(18)->symm = halfEdges.at(0).get();

    halfEdges.at(1)->symm = halfEdges.at(15).get();
    halfEdges.at(15)->symm = halfEdges.at(1).get();

    halfEdges.at(2)->symm = halfEdges.at(22).get();
    halfEdges.at(22)->symm = halfEdges.at(2).get();

    halfEdges.at(3)->symm = halfEdges.at(9).get();
    halfEdges.at(9)->symm = halfEdges.at(3).get();

    halfEdges.at(4)->symm = halfEdges.at(16).get();
    halfEdges.at(16)->symm = halfEdges.at(4).get();

    halfEdges.at(5)->symm = halfEdges.at(11).get();
    halfEdges.at(11)->symm = halfEdges.at(5).get();

    halfEdges.at(6)->symm = halfEdges.at(20).get();
    halfEdges.at(20)->symm = halfEdges.at(6).get();

    halfEdges.at(7)->symm = halfEdges.at(13).get();
    halfEdges.at(13)->symm = halfEdges.at(7).get();

    halfEdges.at(8)->symm = halfEdges.at(19).get();
    halfEdges.at(19)->symm = halfEdges.at(8).get();

    halfEdges.at(9)->symm = halfEdges.at(3).get();
    halfEdges.at(3)->symm = halfEdges.at(9).get();

    halfEdges.at(10)->symm = halfEdges.at(21).get();
    halfEdges.at(21)->symm = halfEdges.at(10).get();

    halfEdges.at(12)->symm = halfEdges.at(17).get();
    halfEdges.at(17)->symm = halfEdges.at(12).get();

    halfEdges.at(14)->symm = halfEdges.at(23).get();
    halfEdges.at(23)->symm = halfEdges.at(14).get();
}

// from slides
void Mesh::triangulate(Face *face) {

    // arbitrary half-edge to which FACE1 points
    HalfEdge* he_0 = face->edge;

    for (int i = 0; i < getNumSides(face) - 3; i++) {

        // create two new half-edges HE_A and HE_B
        uPtr<HalfEdge> he_A = mkU<HalfEdge>();
        uPtr<HalfEdge> he_B = mkU<HalfEdge>();

        // HE_A points to HE_0.vert
        he_A->vertex = he_0->vertex;

        // HE_B points to HE_0.next.next.vert
        he_B->vertex = he_0->next->next->vertex;

        // HE_A and HE_B have each other for syms
        he_A->symm = he_B.get();
        he_B->symm = he_A.get();

        // create a second face FACE2
        uPtr<Face> face_2 = mkU<Face>();

        // HE_A, HE_0.next, and HE_0.next.next now all point to FACE2
        he_A->face = face_2.get();
        he_0->next->face = face_2.get();
        he_0->next->next->face = face_2.get();

        // HE_B points to FACE1
        he_B->face = face;

        // FACE2’s arbitrary half-edge pointer can be HE_A
        face_2->edge = he_A.get();

        // set FACE2 color
        face_2->color = face->color;

        // fix up the next pointers for our half-edges

        // HE_B.next = HE_0.next.next.next
        he_B->next = he_0->next->next->next;

        // HE_0.next.next.next = HE_A
        he_0->next->next->next = he_A.get();

        // HE_A.next = HE_0.next
        he_A->next = he_0->next;

        // HE_0.next = HE_B
        he_0->next = he_B.get();

        faces.push_back(std::move(face_2));
        halfEdges.push_back(std::move(he_A));
        halfEdges.push_back(std::move(he_B));
    }
}

// from slides
void Mesh::splitEdge(HalfEdge *he1) {
    HalfEdge* he2 = he1->symm;

    // create the new vertex V3
    uPtr<Vertex> v3 = mkU<Vertex>();

    // V3’s pos is the average of V1’s and V2’s
    Vertex* v1 = he1->vertex;
    Vertex* v2 = he2->vertex;

    glm::vec3 avg = 0.5f * (v1->pos + v2->pos);
    v3->pos = avg;
    v3->edge = he1;

    // create the two new half-edges HE1B and HE2B needed to surround V3
    uPtr<HalfEdge> he1B = mkU<HalfEdge>();
    uPtr<HalfEdge> he2B = mkU<HalfEdge>();

    // HE1B points to V1 and HE2B points to V2
    he1B->vertex = v1;
    he2B->vertex = v2;

    // set the correct face pointers for HE1B and HE2B
    he1B->face = he1->face;
    he2B->face = he2->face;

    // adjust the symm, next, and vert pointers of HE1, HE2, HE1B, and HE2B
    he1->symm = he2B.get();
    he2B->symm = he1;
    he2->symm = he1B.get();
    he1B->symm = he2;

    he1B->next = he1->next;
    he2B->next = he2->next;
    he1->next = he1B.get();
    he2->next = he2B.get();

    he1->vertex->edge = he1B.get();
    he2->vertex->edge = he2B.get();

    he1->vertex = v3.get();
    he2->vertex = v3.get();

    vertices.push_back(std::move(v3));
    halfEdges.push_back(std::move(he1B));
    halfEdges.push_back(std::move(he2B));
}

// from lecture slides
void Mesh::subdivide() {

    // store new primitives
    std::vector<uPtr<Vertex>> newVertices;
    std::vector<uPtr<HalfEdge>> newHalfEdges;
    std::vector<uPtr<Face>> newFaces;

    // set of edges to split
    std::set<HalfEdge*> edge_split;
    // access a centroid given its corresponding face
    std::map<Face*, Vertex*> centroid_map;
    // access a midpoint given its corresponding edge
    std::map<HalfEdge*, Vertex*> midpoint_map;

    // populate set of half edges to split
    for (uPtr<HalfEdge> &he: halfEdges) {
        if (std::find(edge_split.begin(), edge_split.end(),
                      he.get()->symm) == edge_split.end()) {
            edge_split.insert(he.get());
        }
    }

    // steps from slides
    centroid(&centroid_map, &newVertices);

    midpoint(&centroid_map, &midpoint_map, &edge_split, &newVertices);

    smooth(&centroid_map, &midpoint_map);

    quadrangulate(&edge_split, &centroid_map, &midpoint_map,
                  &newHalfEdges, &newFaces);

    // update originals
    for (uPtr<Vertex> &v : newVertices) {
        vertices.push_back(std::move(v));
    }

    for (uPtr<HalfEdge> &he : newHalfEdges) {
        halfEdges.push_back(std::move(he));
    }

    for (uPtr<Face> &face : newFaces) {
        faces.push_back(std::move(face));
    }
}

// centroid for each face
void Mesh::centroid(std::map<Face*, Vertex*> *centroid_map,
                    std::vector<uPtr<Vertex>> *newVertices) {

    // for the original faces
    for (uPtr<Face> &f : faces) {
        uPtr<Vertex> centroid = mkU<Vertex>();
        glm::vec3 centroid_pos = glm::vec3();

        HalfEdge *curr = f->edge;
        do {
            centroid_pos += curr->vertex->pos;
            curr = curr->next;
        } while (curr != f->edge);

        centroid_pos /= getNumSides(f.get());
        centroid->pos = centroid_pos;

        centroid_map->insert({f.get(), centroid.get()});
        newVertices->push_back(std::move(centroid));
    }
}

// compute the smoothed midpoint of each edge in the mesh
void Mesh::midpoint(std::map<Face*, Vertex*> *centroid_map,
                    std::map<HalfEdge*, Vertex*> *midpoint_map,
                    std::set<HalfEdge*> *edge_split,
                    std::vector<uPtr<Vertex>> *newVertices) {

    // for each eadge in the set of edges to split
    for (HalfEdge* he : *edge_split) {

        HalfEdge *prev = he->symm;

        glm::vec3 v1 = prev->vertex->pos;
        glm::vec3 v2 = he->vertex->pos;
        glm::vec3 f1 = centroid_map->find(he->face)->second->pos;
        glm::vec3 f2 = centroid_map->find(prev->face)->second->pos;

        // border edge
        glm::vec3 e = (v1 + v2 + f1) / 3.f;

        if (prev) {
            e = (v1 + v2 + f1 + f2) / 4.f;
        }

        uPtr<Vertex> midPoint = mkU<Vertex>();
        midPoint->pos = e;

        midpoint_map->insert({he, midPoint.get()});
        newVertices->push_back(std::move(midPoint));
    }
}

// smooth original vertices
void Mesh::smooth(std::map<Face*, Vertex*> *centroid_map,
                  std::map<HalfEdge*, Vertex*> *midpoint_map) {

    // smooth all old vertices
    for (uPtr<Vertex> &v : vertices) {

        HalfEdge *curr = v->edge;

        // sum of all adjacent midpoints
        glm::vec3 sum_e = glm::vec3();

        // sum of the centroids of all faces incident to v
        glm::vec3 sum_f = glm::vec3();

        // number of adjacent midpoints
        float n = 0;

        do {
            glm::vec3 midpt_sum = midpoint_map->find(curr)->second->pos;
            glm::vec3 centroid_sum = centroid_map->find(curr->face)->second->pos;

            if (midpoint_map->find(curr->symm) != midpoint_map->end()){
               midpt_sum = midpoint_map->find(curr->symm)->second->pos;
            }
            sum_e += midpt_sum;
            sum_f += centroid_sum;

            n++;
            curr = curr->next->symm;
        } while (curr != v->edge);

        sum_e /= (n * n);
        sum_f /= (n * n);

        glm::vec3 position = (n - 2.f) * v->pos / n + sum_e + sum_f;
        v->pos = position;
    }
}

// quadrangulate helper to assign edge symmetries
void Mesh::assignSymm(std::vector<uPtr<HalfEdge>> *in_edges,
                      std::vector<uPtr<HalfEdge>> *out_edges,
                      std::vector<uPtr<HalfEdge>> *newHalfEdges) {

    int last = in_edges->size() - 1;

    in_edges->at(last)->symm = out_edges->at(0).get();
    out_edges->at(0)->symm = in_edges->at(last).get();

    for (int i = 0; i < last; i++) {
        in_edges->at(i)->symm = out_edges->at(i + 1).get();
        out_edges->at(i + 1)->symm = in_edges->at(i).get();
    }

    for (uPtr<HalfEdge> &he : *in_edges) {
        newHalfEdges->push_back(std::move(he));
    }

    for (uPtr<HalfEdge> &he : *out_edges) {
        newHalfEdges->push_back(std::move(he));
    }
}

// set new quad faces
void Mesh::setFaces(std::vector<HalfEdge*> *temp_he, Face *f, int n) {

    f->setColor();

    temp_he->at(n)->face = f;
    f->edge = temp_he->at(n);

    temp_he->at(n)->next->face = f;
    f->edge = temp_he->at(n)->next;

    temp_he->at(n)->next->next->face = f;
    f->edge = temp_he->at(n)->next->next;

    temp_he->at(n)->next->next->next->face = f;
    f->edge = temp_he->at(n)->next->next;
}

// returns the list of quad faces
std::vector<uPtr<Face>> Mesh::quadFaces(std::vector<HalfEdge*> *temp_he, Face *f) {
    std::vector<uPtr<Face>> quad_faces;

    for (int i = 0; i < (int)temp_he->size() - 1; i++) {
        uPtr<Face> face = mkU<Face>();
        setFaces(temp_he, face.get(), i);
        quad_faces.push_back(std::move(face));
    }
    setFaces(temp_he, f, temp_he->size() - 1);

    return quad_faces;
}

// for each original face, split that into N quadrangle faces
void Mesh::quadrangulate(std::set<HalfEdge*> *edge_split,
                         std::map<Face*, Vertex*> *centroid_map,
                         std::map<HalfEdge*, Vertex*> *midpoint_map,
                         std::vector<uPtr<HalfEdge>> *newHalfEdges,
                         std::vector<uPtr<Face>> *newFaces) {

    // adding in midpoints (slightly modified splitEdge function)
    for (HalfEdge *he1: *edge_split) {
        HalfEdge* he2 = he1->symm;

        Vertex *midpoint = midpoint_map->find(he1)->second;

        Vertex* v1 = he1->vertex;
        Vertex* v2 = he2->vertex;

        uPtr<HalfEdge> he1B = mkU<HalfEdge>();
        uPtr<HalfEdge> he2B = mkU<HalfEdge>();

        he1B->vertex = v1;
        he2B->vertex = v2;

        he1B->face = he1->face;
        he1->face->edge = he1B.get();

        he2B->face = he2->face;
        he2->face->edge = he2B.get();

        he1->symm = he2B.get();
        he2B->symm = he1;
        he2->symm = he1B.get();
        he1B->symm = he2;

        he1B->next = he1->next;
        he2B->next = he2->next;
        he1->next = he1B.get();
        he2->next = he2B.get();

        he1->vertex->edge = he1B.get();
        he2->vertex->edge = he2B.get();

        he1->vertex = midpoint;
        he2->vertex = midpoint;


        newHalfEdges->push_back(std::move(he1B));
        newHalfEdges->push_back(std::move(he2B));
    }

    for (uPtr<Face> &f : faces) {
        HalfEdge *curr = f->edge;

        //storing the half edges temporarily
        std::vector<HalfEdge*> temp_he;
        // point towards centroid
        std::vector<uPtr<HalfEdge>> in_edges;
        // points from centroid (towards midpoint)
        std::vector<uPtr<HalfEdge>> out_edges;
        // access next half edge given id
        std::map<int, HalfEdge*> map_next;
        //the quadrangulated faces
        std::vector<uPtr<Face>> quad_faces;

        // storing temporary half edges
        do {
            temp_he.push_back(curr);
            curr = curr->next->next;
        } while (curr != f->edge);

        HalfEdge *next = temp_he.at(temp_he.size() - 1)->next;

        for (HalfEdge *he: temp_he) {
            map_next.insert({he->id, next});
            next = he->next;
        }

        for (HalfEdge *he : temp_he) {
            uPtr<HalfEdge> to_centroid = mkU<HalfEdge>();
            uPtr<HalfEdge> from_centroid = mkU<HalfEdge>();

            Vertex *cent_vert = centroid_map->find(he->face)->second;
            to_centroid->vertex = cent_vert;
            cent_vert->edge = to_centroid.get();

            Vertex *next_vert = map_next[he->id]->vertex;
            from_centroid->vertex = next_vert;
            next_vert->edge = from_centroid.get();

            // half edge ring
            he->next->next = to_centroid.get();
            to_centroid->next = from_centroid.get();
            from_centroid->next = he;

            in_edges.push_back(std::move(to_centroid));
            out_edges.push_back(std::move(from_centroid));
        }

        assignSymm(&in_edges, &out_edges, newHalfEdges);

        quad_faces = quadFaces(&temp_he, f.get());
        for (uPtr<Face> &face : quad_faces) {
            newFaces->push_back(std::move(face));
        }
    }
}

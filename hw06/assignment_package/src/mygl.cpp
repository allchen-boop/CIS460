#include "mygl.h"
#include <la.h>

#include <iostream>
#include <QApplication>
#include <QKeyEvent>
#include <QFileDialog>

MyGL::MyGL(QWidget *parent)
    : OpenGLContext(parent),
      m_geomSquare(this),
      m_progLambert(this), m_progFlat(this),
      m_vertDisplay(this),  m_faceDisplay(this),
      m_halfEdgeDisplay(this), m_mesh(this),
      m_glCamera(), m_selected(nullptr),
      color(glm::vec3())
{
    setFocusPolicy(Qt::StrongFocus);
}

MyGL::~MyGL()
{
    makeCurrent();
    glDeleteVertexArrays(1, &vao);
    m_geomSquare.destroy();
    m_mesh.destroy();
    m_vertDisplay.destroy();
    m_faceDisplay.destroy();
    m_halfEdgeDisplay.destroy();
}

void MyGL::initializeGL()
{
    // Create an OpenGL context using Qt's QOpenGLFunctions_3_2_Core class
    // If you were programming in a non-Qt context you might use GLEW (GL Extension Wrangler)instead
    initializeOpenGLFunctions();
    // Print out some information about the current OpenGL context
    debugContextVersion();

    // Set a few settings/modes in OpenGL rendering
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    // Set the size with which points should be rendered
    glPointSize(5);
    // Set the color with which the screen is filled at the start of each render call.
    glClearColor(0.5, 0.5, 0.5, 1);

    printGLErrorLog();

    // Create a Vertex Attribute Object
    glGenVertexArrays(1, &vao);

    //Create the instances of Cylinder and Sphere.
    //m_geomSquare.create();

    m_mesh.buildCube();
    m_mesh.create();

    // Create and set up the diffuse shader
    m_progLambert.create(":/glsl/lambert.vert.glsl", ":/glsl/lambert.frag.glsl");
    // Create and set up the flat lighting shader
    m_progFlat.create(":/glsl/flat.vert.glsl", ":/glsl/flat.frag.glsl");

    // We have to have a VAO bound in OpenGL 3.2 Core. But if we're not
    // using multiple VAOs, we can just bind one once.
    glBindVertexArray(vao);

    emit sig_sendVertexData(&m_mesh);
    emit sig_sendFaceData(&m_mesh);
    emit sig_sendHalfEdgeData(&m_mesh);
}

void MyGL::resizeGL(int w, int h)
{
    //This code sets the concatenated view and perspective projection matrices used for
    //our scene's camera view.
    m_glCamera = Camera(w, h);
    glm::mat4 viewproj = m_glCamera.getViewProj();

    // Upload the view-projection matrix to our shaders (i.e. onto the graphics card)

    m_progLambert.setViewProjMatrix(viewproj);
    m_progFlat.setViewProjMatrix(viewproj);

    printGLErrorLog();
}

//This function is called by Qt any time your GL window is supposed to update
//For example, when the function update() is called, paintGL is called implicitly.
void MyGL::paintGL()
{
    // Clear the screen so that we only see newly drawn images
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_progFlat.setViewProjMatrix(m_glCamera.getViewProj());
    m_progLambert.setViewProjMatrix(m_glCamera.getViewProj());
    m_progLambert.setCamPos(glm::vec3(m_glCamera.eye));
    m_progFlat.setModelMatrix(glm::mat4(1.f));

    glm::mat4 model = glm::mat4();
    m_progLambert.setModelMatrix(model);
    m_progLambert.draw(m_mesh);

    Vertex* vertex = dynamic_cast<Vertex*>(m_selected);
    Face* face = dynamic_cast<Face*>(m_selected);
    HalfEdge* halfEdge = dynamic_cast<HalfEdge*>(m_selected);

    glDisable(GL_DEPTH_TEST);

    if (vertex) {
        m_vertDisplay.create();
        m_progFlat.draw(m_vertDisplay);
    } else if (face) {
        m_faceDisplay.create();
        m_progFlat.draw(m_faceDisplay);
    } else if (halfEdge) {
        m_halfEdgeDisplay.create();
        m_progFlat.draw(m_halfEdgeDisplay);
    }
    glEnable(GL_DEPTH_TEST);
}

void MyGL::keyPressEvent(QKeyEvent *e)
{
    float amount = 2.0f;
    if(e->modifiers() & Qt::ShiftModifier){
        amount = 10.0f;
    }
    // http://doc.qt.io/qt-5/qt.html#Key-enum
    // This could all be much more efficient if a switch
    // statement were used
    if (e->key() == Qt::Key_Escape) {
        QApplication::quit();
    } else if (e->key() == Qt::Key_Right) {
        m_glCamera.RotateAboutUp(-amount);
    } else if (e->key() == Qt::Key_Left) {
        m_glCamera.RotateAboutUp(amount);
    } else if (e->key() == Qt::Key_Up) {
        m_glCamera.RotateAboutRight(-amount);
    } else if (e->key() == Qt::Key_Down) {
        m_glCamera.RotateAboutRight(amount);
    } else if (e->key() == Qt::Key_1) {
        m_glCamera.fovy += amount;
    } else if (e->key() == Qt::Key_2) {
        m_glCamera.fovy -= amount;
    } else if (e->key() == Qt::Key_W) {
        m_glCamera.TranslateAlongLook(amount);
    } else if (e->key() == Qt::Key_S) {
        m_glCamera.TranslateAlongLook(-amount);
    } else if (e->key() == Qt::Key_D) {
        m_glCamera.TranslateAlongRight(amount);
    } else if (e->key() == Qt::Key_A) {
        m_glCamera.TranslateAlongRight(-amount);
    } else if (e->key() == Qt::Key_Q) {
        m_glCamera.TranslateAlongUp(-amount);
    } else if (e->key() == Qt::Key_E) {
        m_glCamera.TranslateAlongUp(amount);
    } else if (e->key() == Qt::Key_R) {
        m_glCamera = Camera(this->width(), this->height());

    // visual debugging
    } else if (e->key() == Qt::Key_N) {
        HalfEdge* halfEdge = dynamic_cast<HalfEdge*>(m_selected);
        if (halfEdge) {
            slot_setSelectedHalfEdge(halfEdge->next);
        }
    } else if (e->key() == Qt::Key_M) {
        HalfEdge* halfEdge = dynamic_cast<HalfEdge*>(m_selected);
        if (halfEdge) {
            slot_setSelectedHalfEdge(halfEdge->symm);
        }
    } else if (e->key() == Qt::Key_F) {
        HalfEdge* halfEdge = dynamic_cast<HalfEdge*>(m_selected);
        if (halfEdge) {
            slot_setSelectedFace(halfEdge->face);
        }
    } else if (e->key() == Qt::Key_V) {
        HalfEdge* halfEdge = dynamic_cast<HalfEdge*>(m_selected);
        if (halfEdge) {
            slot_setSelectedVertex(halfEdge->vertex);
        }
    } else if ((e->modifiers() & Qt::ShiftModifier) && e->key() == Qt::Key_H) {
        Face* face = dynamic_cast<Face*>(m_selected);
        if (face) {
            slot_setSelectedHalfEdge(face->edge);
        }
    } else if (e->key() == Qt::Key_H) {
        Vertex* vertex = dynamic_cast<Vertex*>(m_selected);
        if (vertex) {
            slot_setSelectedHalfEdge(vertex->edge);
        }
    }
    m_glCamera.polarAttributes();
    update();  // Calls paintGL, among other things
}

void MyGL::slot_vertPosX(double x) {
    if (m_selected) {
        Vertex* vertex = dynamic_cast<Vertex*>(m_selected);

        if (vertex) {
            vertex->pos.x = x;
            m_mesh.destroy();
            m_mesh.create();
            update();
        }
    }
}

void MyGL::slot_vertPosY(double y) {
    if (m_selected) {
        Vertex* vertex = dynamic_cast<Vertex*>(m_selected);

        if (vertex) {
            vertex->pos.y = y;
            m_mesh.destroy();
            m_mesh.create();
            update();
        }
    }
}

void MyGL::slot_vertPosZ(double z) {
    if (m_selected) {
        Vertex* vertex = dynamic_cast<Vertex*>(m_selected);

        if (vertex) {
            vertex->pos.z = z;
            m_mesh.destroy();
            m_mesh.create();
            update();
        }
    }
}

void MyGL::slot_faceRed(double red) {
    if (m_selected) {
        Face* face = dynamic_cast<Face*>(m_selected);

        if (face) {
            color.r = red;
            face->color = color;
            m_mesh.destroy();
            m_mesh.create();
            update();
        }
    }
}

void MyGL::slot_faceGreen(double green) {
    if (m_selected) {
        Face* face = dynamic_cast<Face*>(m_selected);

        if (face) {
            color.g = green;
            face->color = color;
            m_mesh.destroy();
            m_mesh.create();
            update();
        }
    }
}

void MyGL::slot_faceBlue(double blue) {
    if (m_selected) {
        Face* face = dynamic_cast<Face*>(m_selected);

        if (face) {
            color.b = blue;
            face->color = color;
            m_mesh.destroy();
            m_mesh.create();
            update();
        }
    }
}

void MyGL::slot_setSelectedVertex(QListWidgetItem *v) {
    if (v) {
        m_selected = v;
        Vertex* vertex = dynamic_cast<Vertex*>(v);

        m_vertDisplay.destroy();

        if (vertex) {
            m_vertDisplay.updateVertex(vertex);
        }
        update();
    }
}

void MyGL::slot_setSelectedFace(QListWidgetItem *f) {
    if (f) {
        m_selected = f;
        Face* face = dynamic_cast<Face*>(f);

        m_faceDisplay.destroy();

        if (face) {
            m_faceDisplay.updateFace(face);
        }
        update();
    }
}

void MyGL::slot_setSelectedHalfEdge(QListWidgetItem *he) {
    if (he) {
        m_selected = he;
        HalfEdge* halfEdge = dynamic_cast<HalfEdge*>(he);

        m_halfEdgeDisplay.destroy();

        if (halfEdge) {
            m_halfEdgeDisplay.updateHalfEdge(halfEdge);
        }
        update();
    }
}


void MyGL::slot_splitEdge() {
    if (m_selected) {
        HalfEdge* he1 = dynamic_cast<HalfEdge*>(m_selected);

        if (he1) {
            m_mesh.splitEdge(he1);

            emit sig_sendHalfEdgeData(&m_mesh);
            emit sig_sendVertexData(&m_mesh);
        }
    }

    m_mesh.destroy();
    m_mesh.create();
    update();
}

void MyGL::slot_triangulate() {
    if (m_selected) {
        Face* face = dynamic_cast<Face*>(m_selected);

        if (face) {
            m_mesh.triangulate(face);
            emit sig_sendFaceData(&m_mesh);
        }
    }

    m_mesh.destroy();
    m_mesh.create();
    update();
}

void MyGL::slot_subdivide() {
    m_mesh.subdivide();

    m_mesh.destroy();
    m_mesh.create();
    update();

    emit sig_sendFaceData(&m_mesh);
    emit sig_sendVertexData(&m_mesh);
    emit sig_sendHalfEdgeData(&m_mesh);
}

void MyGL::init_edges(QStringList line_list) {

    uPtr<Face> face = mkU<Face>();
    face->setColor();

    for (int i = 1; i < line_list.length(); i++) {
        uPtr<HalfEdge> halfEdge = mkU<HalfEdge>();
        halfEdge->face = face.get();
        face->edge = halfEdge.get();

        // set vertex: f pos/uv/norm
        QStringList v_pos = line_list[i].split("/");
        int pos = v_pos[0].toInt() - 1;

        halfEdge->vertex = m_mesh.vertices[pos].get();
        m_mesh.vertices[pos]->edge = halfEdge.get();

        m_mesh.halfEdges.push_back(std::move(halfEdge));
    }

    m_mesh.faces.push_back(std::move(face));
}

void MyGL::slot_importOBJ() {

    // read file
    QString fileName = QFileDialog::getOpenFileName(0, QString("Load OBJ File"),
                                                    QDir::currentPath().append(QString("../..")),
                                                    QString("*.obj"));

    std::vector<glm::vec2> vt;
    std::vector<glm::vec3> vn;

    // access half edge given symm pair
    std::map<std::pair<int, int>, HalfEdge*> map_symm;

    QFile file(fileName);

    if (file.exists()) {

        // clear primitive data
        Vertex::lastVertex = 0;
        HalfEdge::lastHalfEdge = 0;
        Face::lastFace = 0;

        m_mesh.vertices.clear();
        m_mesh.faces.clear();
        m_mesh.halfEdges.clear();

        if (file.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream f(&file);

            while (!f.atEnd()) {
                QString line = f.readLine();
                QStringList line_list = line.split(" ");

                if (line_list.count() > 0) {

                    // vertices
                    if (line_list[0] == "v") {
                        uPtr<Vertex> vertex = mkU<Vertex>();
                        glm::vec3 position = glm::vec3(line_list[1].toFloat(),
                                                       line_list[2].toFloat(),
                                                       line_list[3].toFloat());
                        vertex->pos = position;
                        m_mesh.vertices.push_back(std::move(vertex));

                    // uv
                    } else if (line_list[0] == "vt") {
                        vt.push_back(glm::vec2(line_list[1].toFloat(),
                                               line_list[2].toFloat()));
                    // normal
                    } else if (line_list[0] == "vn") {
                        vn.push_back(glm::vec3(line_list[1].toFloat(),
                                               line_list[2].toFloat(),
                                               line_list[3].toFloat()));
                    // face
                    } else if (line_list[0] == "f") {

                        // initialze face edges
                        init_edges(line_list);

                        int line_last = line_list.size() - 1;
                        int he_size = m_mesh.halfEdges.size();

                        for (int i = 1; i <= line_last; i++) {
                            int line_length = line_list.size() - i;
                            int edges_size = he_size - line_length;

                            // setting next half edges
                            if (i != line_last) {
                                HalfEdge *next_he = m_mesh.halfEdges[edges_size + 1].get();
                                m_mesh.halfEdges[edges_size]->next = next_he;
                            }

                            // wraparound
                            int idx_last = he_size - (line_last + 1) + 1;
                            HalfEdge *last_he = m_mesh.halfEdges[idx_last].get();
                            m_mesh.halfEdges[he_size - 1]->next = last_he;

                            // setting symm half edges
                            HalfEdge *he = m_mesh.halfEdges[edges_size].get();

                            QStringList curr = line_list[i].split("/");
                            QStringList prev = line_list[i - 1].split("/");

                            // wraparound
                            if (i == 1) {
                                prev = line_list[line_last].split("/");
                            }

                            std::pair idx = {curr[0].toInt(), prev[0].toInt()};
                            std::pair idx_symm = {prev[0].toInt(), curr[0].toInt()};

                            if (map_symm.find(idx_symm) != map_symm.end()) {
                                HalfEdge *he_symm = map_symm.find(idx_symm)->second;
                                he->symm = he_symm;
                                he_symm->symm = he;
                            } else {
                                map_symm.insert({idx, he});
                            }
                        }
                    }
                }
            }
            file.close();

            m_mesh.destroy();
            m_mesh.create();

            emit sig_sendFaceData(&m_mesh);
            emit sig_sendVertexData(&m_mesh);
            emit sig_sendHalfEdgeData(&m_mesh);

            update();
        }
    }
}

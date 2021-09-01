#include "mygl.h"
#include <la.h>

#include <iostream>
#include <QApplication>
#include <QKeyEvent>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <queue>

MyGL::MyGL(QWidget *parent)
    : OpenGLContext(parent),
      m_geomSquare(this),
      m_progLambert(this),
      m_progFlat(this),
      m_progSkeleton(this),
      m_vertDisplay(this),
      m_faceDisplay(this),
      m_halfEdgeDisplay(this),
      m_mesh(this), m_skeleton(this),
      m_selected(nullptr),
      m_glCamera(),
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
    m_skeleton.destroy();
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

    m_mesh.buildCube();
    m_mesh.create();

    // Create and set up the diffuse shader
    m_progLambert.create(":/glsl/lambert.vert.glsl", ":/glsl/lambert.frag.glsl");
    // Create and set up the flat lighting shader
    m_progFlat.create(":/glsl/flat.vert.glsl", ":/glsl/flat.frag.glsl");
    // Create and set up the skeleton shader
    m_progSkeleton.create(":/glsl/skeleton.vert.glsl", ":/glsl/skeleton.frag.glsl");

    // We have to have a VAO bound in OpenGL 3.2 Core. But if we're not
    // using multiple VAOs, we can just bind one once.
    glBindVertexArray(vao);

    emit sig_sendVertexData(&m_mesh);
    emit sig_sendFaceData(&m_mesh);
    emit sig_sendHalfEdgeData(&m_mesh);
    emit sig_sendJointData(&m_skeleton);
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
    m_progSkeleton.setViewProjMatrix(viewproj);

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
    m_progLambert.setCamPos(m_glCamera.eye);
    m_progFlat.setModelMatrix(glm::mat4(1.f));
    m_progSkeleton.setViewProjMatrix(m_glCamera.getViewProj());

    glm::mat4 model = glm::mat4();
    m_progLambert.setModelMatrix(model);
    m_progFlat.setModelMatrix(model);
    m_progSkeleton.setModelMatrix(model);

    // if mesh is bound
    if (!m_mesh.vertices[0]->influences.empty()) {
        m_progSkeleton.draw(m_mesh);
        m_progSkeleton.draw(m_skeleton);
    } else {
        m_progFlat.draw(m_mesh);
    }

    printGLErrorLog();
    glDisable(GL_DEPTH_TEST);

    m_progFlat.draw(m_vertDisplay);
    m_progFlat.draw(m_faceDisplay);
    m_progFlat.draw(m_halfEdgeDisplay);
    m_progFlat.draw(m_skeleton);

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

        if (vertex) {
            m_vertDisplay.updateVertex(vertex);
            m_vertDisplay.destroy();
            m_vertDisplay.create();

            m_halfEdgeDisplay.updateHalfEdge(nullptr);
            m_faceDisplay.updateFace(nullptr);

            m_halfEdgeDisplay.destroy();
            m_halfEdgeDisplay.create();
            m_faceDisplay.destroy();
            m_faceDisplay.create();
        }
        update();
    }
}

void MyGL::slot_setSelectedFace(QListWidgetItem *f) {
    if (f) {
        m_selected = f;
        Face* face = dynamic_cast<Face*>(f);

        if (face) {
            m_faceDisplay.updateFace(face);
            m_faceDisplay.destroy();
            m_faceDisplay.create();

            m_vertDisplay.updateVertex(nullptr);
            m_halfEdgeDisplay.updateHalfEdge(nullptr);

            m_halfEdgeDisplay.destroy();
            m_halfEdgeDisplay.create();
            m_vertDisplay.destroy();
            m_vertDisplay.create();
        }
        update();
    }
}

void MyGL::slot_setSelectedHalfEdge(QListWidgetItem *he) {
    if (he) {
        m_selected = he;
        HalfEdge* halfEdge = dynamic_cast<HalfEdge*>(he);

        if (halfEdge) {
            m_halfEdgeDisplay.updateHalfEdge(halfEdge);
            m_halfEdgeDisplay.destroy();
            m_halfEdgeDisplay.create();

            m_vertDisplay.updateVertex(nullptr);
            m_faceDisplay.updateFace(nullptr);

            m_faceDisplay.destroy();
            m_faceDisplay.create();
            m_vertDisplay.destroy();
            m_vertDisplay.create();

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

        m_vertDisplay.destroy();
        m_faceDisplay.destroy();
        m_halfEdgeDisplay.destroy();

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

void MyGL::slot_loadJSON() {
    // read file
    QString fileName = QFileDialog::getOpenFileName(0, QString("Load JSON File"),
                                                    QDir::currentPath().append(QString("../..")),
                                                    QString("*.json"));
    QFile file(fileName);

    if (file.exists()) {
        Joint::lastJoint = 0;
        m_skeleton.representedJoint = -1;
        m_skeleton.joints.clear();

        for (uPtr<Vertex> &v : m_mesh.vertices) {
            v->influences.clear();
        }

        if (file.open(QFile::ReadOnly | QFile::Text)) {
            QString val = file.readAll();
            file.close();

            QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
            QJsonObject root = doc.object()["root"].toObject();

            loadJoint(root);
        }
    }
    file.close();

    m_skeleton.destroy();
    m_skeleton.create();

    emit sig_sendJointData(&m_skeleton);

    update();
}

Joint* MyGL::loadJoint(QJsonObject root) {
    QJsonArray position = root["pos"].toArray();
    QJsonArray rotation = root["rot"].toArray();
    QJsonArray children = root["children"].toArray();

    glm::vec3 pos =  glm::vec3(position[0].toDouble(),
                               position[1].toDouble(),
                               position[2].toDouble());

    double half = rotation[0].toDouble() / 2;

    glm::quat rot(cos(glm::radians(half)),
                  sin(glm::radians(half)) * rotation[1].toDouble(),
                  sin(glm::radians(half)) * rotation[2].toDouble(),
                  sin(glm::radians(half)) * rotation[3].toDouble());

    uPtr<Joint> j = mkU<Joint>(root["name"].toString());
    j->pos = pos;
    j->rot = rot;

    Joint* joint = j.get();
    m_skeleton.joints.push_back(std::move(j));

    for (QJsonValueRef child : children) {
        joint->addChild(loadJoint(child.toObject()));
    }
    return joint;
}

void MyGL::slot_jointRotXPos() {
    int selected_joint = m_skeleton.representedJoint;
    if (selected_joint != -1) {
        Joint* joint = dynamic_cast<Joint*>(m_skeleton.joints[selected_joint].get());

        if (joint) {
            glm::vec3 x_axis = glm::vec3(1, 0, 0);
            joint->rot *= glm::rotate(glm::quat(), glm::radians(5.f), x_axis);
            m_progSkeleton.setTransMatrix(m_skeleton.setTranslateMatrix());

            m_skeleton.destroy();
            m_skeleton.create();

            m_mesh.destroy();
            m_mesh.create();
            update();
        }
    }
}

void MyGL::slot_jointRotXNeg() {
    int selected_joint = m_skeleton.representedJoint;
    if (selected_joint != -1) {
        Joint* joint = dynamic_cast<Joint*>(m_skeleton.joints[selected_joint].get());

        if (joint) {
            glm::vec3 x_axis = glm::vec3(1, 0, 0);
            joint->rot *= glm::rotate(glm::quat(), glm::radians(-5.f), x_axis);
            m_progSkeleton.setTransMatrix(m_skeleton.setTranslateMatrix());

            m_skeleton.destroy();
            m_skeleton.create();

            m_mesh.destroy();
            m_mesh.create();
            update();
        }
    }
}

void MyGL::slot_jointRotYPos() {
    int selected_joint = m_skeleton.representedJoint;
    if (selected_joint != -1) {
        Joint* joint = dynamic_cast<Joint*>(m_skeleton.joints[selected_joint].get());

        if (joint) {
            glm::vec3 y_axis = glm::vec3(0, 1, 0);
            joint->rot *= glm::rotate(glm::quat(), glm::radians(5.f), y_axis);
            m_progSkeleton.setTransMatrix(m_skeleton.setTranslateMatrix());

            m_skeleton.destroy();
            m_skeleton.create();

            m_mesh.destroy();
            m_mesh.create();
            update();
        }
    }
}

void MyGL::slot_jointRotYNeg() {
    int selected_joint = m_skeleton.representedJoint;
    if (selected_joint != -1) {
        Joint* joint = dynamic_cast<Joint*>(m_skeleton.joints[selected_joint].get());

        if (joint) {
            glm::vec3 y_axis = glm::vec3(0, 1, 0);
            joint->rot *= glm::rotate(glm::quat(), glm::radians(-5.f), y_axis);
            m_progSkeleton.setTransMatrix(m_skeleton.setTranslateMatrix());

            m_skeleton.destroy();
            m_skeleton.create();

            m_mesh.destroy();
            m_mesh.create();
            update();
        }
    }
}


void MyGL::slot_jointRotZPos() {
    int selected_joint = m_skeleton.representedJoint;
    if (selected_joint != -1) {
        Joint* joint = dynamic_cast<Joint*>(m_skeleton.joints[selected_joint].get());

        if (joint) {
            glm::vec3 z_axis = glm::vec3(0, 0, 1);
            joint->rot *= glm::rotate(glm::quat(), glm::radians(5.f), z_axis);
            m_progSkeleton.setTransMatrix(m_skeleton.setTranslateMatrix());

            m_skeleton.destroy();
            m_skeleton.create();

            m_mesh.destroy();
            m_mesh.create();
            update();
        }
    }
}

void MyGL::slot_jointRotZNeg() {
    int selected_joint = m_skeleton.representedJoint;
    if (selected_joint != -1) {
        Joint* joint = dynamic_cast<Joint*>(m_skeleton.joints[selected_joint].get());

        if (joint) {
            glm::vec3 z_axis = glm::vec3(0, 0, 1);
            joint->rot *= glm::rotate(glm::quat(), glm::radians(-5.f), z_axis);
            m_progSkeleton.setTransMatrix(m_skeleton.setTranslateMatrix());

            m_skeleton.destroy();
            m_skeleton.create();

            m_mesh.destroy();
            m_mesh.create();
            update();
        }
    }
}

void MyGL::slot_jointPosX(double x) {
    int selected_joint = m_skeleton.representedJoint;
    if (selected_joint != -1) {
        Joint* joint = dynamic_cast<Joint*>(m_skeleton.joints[selected_joint].get());

        if (joint) {
            joint->pos.x = x;
            m_progSkeleton.setTransMatrix(m_skeleton.setTranslateMatrix());

            m_skeleton.destroy();
            m_skeleton.create();

            m_mesh.destroy();
            m_mesh.create();
            update();
        }
    }
}

void MyGL::slot_jointPosY(double y) {
    int selected_joint = m_skeleton.representedJoint;
    if (selected_joint != -1) {
        Joint* joint = dynamic_cast<Joint*>(m_skeleton.joints[selected_joint].get());

        if (joint) {
            joint->pos.y = y;
            m_progSkeleton.setTransMatrix(m_skeleton.setTranslateMatrix());

            m_skeleton.destroy();
            m_skeleton.create();

            m_mesh.destroy();
            m_mesh.create();
            update();
        }
    }
}

void MyGL::slot_jointPosZ(double z) {
    int selected_joint = m_skeleton.representedJoint;
    if (selected_joint != -1) {
        Joint* joint = dynamic_cast<Joint*>(m_skeleton.joints[selected_joint].get());

        if (joint) {
            joint->pos.z = z;
            m_progSkeleton.setTransMatrix(m_skeleton.setTranslateMatrix());

            m_skeleton.destroy();
            m_skeleton.create();

            m_mesh.destroy();
            m_mesh.create();
            update();
        }
    }
}

void MyGL::slot_skinMesh() {
    m_skeleton.setBindMatrix();
    m_progSkeleton.setTransMatrix(m_skeleton.setTranslateMatrix());

    for (uPtr<Vertex> &v : m_mesh.vertices) {
        Joint* joint_1 = nullptr;
        Joint* joint_2 = nullptr;
        float j1_dist = 0;
        float j2_dist = 0;

        for (uPtr<Joint> &j : m_skeleton.joints) {
            glm::vec4 joint_pos = j->getOverallTransformation() * glm::vec4(0, 0, 0, 1);
            float dist = glm::distance(glm::vec4(v->pos, 1), joint_pos);

            if (!joint_1) {
                joint_1 = j.get();
                j1_dist = dist;
            } else if (j1_dist > dist) {
                joint_2 = joint_1;
                j2_dist = j1_dist;
                joint_1 = j.get();
                j1_dist = dist;
            }
            joint_2 = j.get();
            j2_dist = dist;
        }

        float dist_sum = j1_dist + j2_dist;
        float j1_weight = 1 - j1_dist / dist_sum;
        float j2_weight = 1 - j2_dist / dist_sum;

        v->influences.push_back({joint_1->id, j1_weight});
        v->influences.push_back({joint_2->id, j2_weight});
    }
    updateMats();

    m_mesh.destroy();
    m_mesh.create();

    m_skeleton.destroy();
    m_skeleton.create();

    update();
}

void MyGL::updateMats() {
    std::vector<glm::mat4> bind;
    std::vector<glm::mat4> trans;

    for (uPtr<Joint> &j : m_skeleton.joints) {
        bind.push_back(j->bind_matrix);
        trans.push_back(j->getOverallTransformation());
    }
    m_progSkeleton.setBindMatrix(bind);
    m_progSkeleton.setTransMatrix(trans);
}

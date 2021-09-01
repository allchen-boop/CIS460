#include "mainwindow.h"
#include <ui_mainwindow.h>
#include "cameracontrolshelp.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mygl->setFocus();

    connect(ui->mygl, SIGNAL(sig_sendVertexData(Mesh*)),
            this, SLOT(slot_receiveVertexData(Mesh*)));
    connect(ui->mygl, SIGNAL(sig_sendFaceData(Mesh*)),
            this, SLOT(slot_receiveFaceData(Mesh*)));
    connect(ui->mygl, SIGNAL(sig_sendHalfEdgeData(Mesh*)),
            this, SLOT(slot_receiveHalfEdgeData(Mesh*)));
    connect(ui->mygl, SIGNAL(sig_sendJointData(Skeleton*)),
            this, SLOT(slot_receiveJointData(Skeleton*)));

    connect(ui->vertsListWidget, SIGNAL(itemClicked(QListWidgetItem*)),
            ui->mygl, SLOT(slot_setSelectedVertex(QListWidgetItem*)));
    connect(ui->facesListWidget, SIGNAL(itemClicked(QListWidgetItem*)),
            ui->mygl, SLOT(slot_setSelectedFace(QListWidgetItem*)));
    connect(ui->halfEdgesListWidget, SIGNAL(itemClicked(QListWidgetItem*)),
            ui->mygl, SLOT(slot_setSelectedHalfEdge(QListWidgetItem*)));
    connect(ui->jointTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)),
            this, SLOT(slot_setSelectedJoint(QTreeWidgetItem*, int)));

    // vertex position spin boxes
    connect(ui->vertPosXSpinBox, SIGNAL(valueChanged(double)),
            ui->mygl, SLOT(slot_vertPosX(double)));
    connect(ui->vertPosYSpinBox, SIGNAL(valueChanged(double)),
            ui->mygl, SLOT(slot_vertPosY(double)));
    connect(ui->vertPosZSpinBox, SIGNAL(valueChanged(double)),
            ui->mygl, SLOT(slot_vertPosZ(double)));

    // color spin boxes
    connect(ui->faceRedSpinBox, SIGNAL(valueChanged(double)),
            ui->mygl, SLOT(slot_faceRed(double)));
    connect(ui->faceGreenSpinBox, SIGNAL(valueChanged(double)),
            ui->mygl, SLOT(slot_faceGreen(double)));
    connect(ui->faceBlueSpinBox, SIGNAL(valueChanged(double)),
            ui->mygl, SLOT(slot_faceBlue(double)));

    // topology editing functions
    connect(ui->splitEdgeButton, SIGNAL(clicked(bool)), ui->mygl, SLOT(slot_splitEdge()));
    connect(ui->triangulateButton, SIGNAL(clicked(bool)), ui->mygl, SLOT(slot_triangulate()));

    // catmull-clark subdivision
    connect(ui->subdivideButton, SIGNAL(clicked(bool)), ui->mygl, SLOT(slot_subdivide()));

    // import obj
    connect(ui->importOBJButton, SIGNAL(clicked(bool)), ui->mygl, SLOT(slot_importOBJ()));

    // loading json
    connect(ui->loadJSONButton, SIGNAL(clicked(bool)), ui->mygl, SLOT(slot_loadJSON()));

    // skin/bind mesh
    connect(ui->skinMeshButton, SIGNAL(clicked(bool)), ui->mygl, SLOT(slot_skinMesh()));

    // joint rotation
    connect(ui->rotateJointXPosButton, SIGNAL(clicked(bool)),
            ui->mygl, SLOT(slot_jointRotXPos()));
    connect(ui->rotateJointXNegButton, SIGNAL(clicked(bool)),
            ui->mygl, SLOT(slot_jointRotXNeg()));
    connect(ui->rotateJointYPosButton, SIGNAL(clicked(bool)),
            ui->mygl, SLOT(slot_jointRotYPos()));
    connect(ui->rotateJointYNegButton, SIGNAL(clicked(bool)),
            ui->mygl, SLOT(slot_jointRotYNeg()));
    connect(ui->rotateJointZPosButton, SIGNAL(clicked(bool)),
            ui->mygl, SLOT(slot_jointRotZPos()));
    connect(ui->rotateJointZNegButton, SIGNAL(clicked(bool)),
            ui->mygl, SLOT(slot_jointRotZNeg()));

    // joint position spin boxes
    connect(ui->jointPosXSpinBox, SIGNAL(valueChanged(double)),
            ui->mygl, SLOT(slot_jointPosX(double)));
    connect(ui->jointPosYSpinBox, SIGNAL(valueChanged(double)),
            ui->mygl, SLOT(slot_jointPosY(double)));
    connect(ui->jointPosZSpinBox, SIGNAL(valueChanged(double)),
            ui->mygl, SLOT(slot_jointPosZ(double)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_actionCamera_Controls_triggered()
{
    CameraControlsHelp* c = new CameraControlsHelp();
    c->show();
}

void MainWindow::slot_setSelectedJoint(QTreeWidgetItem* j, int n) {
    if (j) {
        Joint* joint = dynamic_cast<Joint*>(j);

        if (joint) {
            ui->mygl->m_skeleton.updateJoint(joint);

            ui->jointPosXSpinBox->setValue(joint->pos[0]);
            ui->jointPosYSpinBox->setValue(joint->pos[1]);
            ui->jointPosZSpinBox->setValue(joint->pos[2]);

            float currRotX = glm::degrees(joint->rot[0]);
            float currRotY = glm::degrees(joint->rot[1]);
            float currRotZ = glm::degrees(joint->rot[2]);
            QString curr_rotation = QString::fromStdString(std::string("(").append(
                                                           std::to_string(currRotX)).append(",  ").append(
                                                           std::to_string(currRotY)).append(",  ").append(
                                                           std::to_string(currRotZ)).append(")"));


            QString curr_position = QString::fromStdString(std::string("(").append(
                                                           std::to_string(joint->pos[0])).append(",  ").append(
                                                           std::to_string(joint->pos[1])).append(",  ").append(
                                                           std::to_string(joint->pos[2])).append(")"));
            ui->currRot->setText(curr_rotation);
            ui->currPos->setText(curr_position);

            ui->mygl->m_skeleton.destroy();
            ui->mygl->m_skeleton.create();
        }
        ui->mygl->update();
    }
}

void MainWindow::slot_receiveVertexData(Mesh *mesh) {
    for (const uPtr<Vertex> &v : mesh->vertices) {
        ui->vertsListWidget->addItem(v.get());
    }
}

void MainWindow::slot_receiveFaceData(Mesh *mesh) {
    for (const uPtr<Face> &f : mesh->faces) {
        ui->facesListWidget->addItem(f.get());
    }
}

void MainWindow::slot_receiveHalfEdgeData(Mesh *mesh) {
    for (const uPtr<HalfEdge> &he : mesh->halfEdges) {
        ui->halfEdgesListWidget->addItem(he.get());
    }
}

void MainWindow::slot_receiveJointData(Skeleton *skeleton) {
    for (const uPtr<Joint> &j : skeleton->joints) {
        ui->jointTreeWidget->addTopLevelItem(j.get());
    }
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <vertex.h>
#include <face.h>
#include <halfedge.h>
#include <mesh.h>
#include <skeleton.h>

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();

    void on_actionCamera_Controls_triggered();

public slots:
    void slot_setSelectedJoint(QTreeWidgetItem* j, int);

    void slot_receiveVertexData(Mesh *mesh);
    void slot_receiveFaceData(Mesh *mesh);
    void slot_receiveHalfEdgeData(Mesh *mesh);
    void slot_receiveJointData(Skeleton *skeleton);

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H

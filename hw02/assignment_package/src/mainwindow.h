#pragma once

#include <QMainWindow>
#include <QtWidgets/QTreeWidget>

#include "node.h"
#include "translatenode.h"
#include "scalenode.h"
#include "rotatenode.h"


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

public slots:
    void slot_addRoot(QTreeWidgetItem* root);

    // spin boxes
    void slot_translateX(int value);
    void slot_translateY(int value);
    void slot_scaleX(int value);
    void slot_scaleY(int value);
    void slot_rotate(int value);

    // push buttons
    void slot_newTranslate(bool clicked);
    void slot_newScale(bool clicked);
    void slot_newRotate(bool clicked);
    void slot_newSquare(bool clicked);

private:
    Ui::MainWindow *ui;
};

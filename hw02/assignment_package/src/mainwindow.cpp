#include "mainwindow.h"
#include <ui_mainwindow.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mygl->setFocus();

    // node
    connect(ui->mygl, SIGNAL(sendRoot(QTreeWidgetItem*)), this,
            SLOT(slot_addRoot(QTreeWidgetItem*)));

    // spin boxes
    connect(ui->translate_x, SIGNAL(valueChanged(int)), this,
            SLOT(slot_translateX(int)));

    connect(ui->translate_y, SIGNAL(valueChanged(int)), this,
            SLOT(slot_translateY(int)));

    connect(ui->scale_x, SIGNAL(valueChanged(int)), this,
            SLOT(slot_scaleX(int)));

    connect(ui->scale_y, SIGNAL(valueChanged(int)), this,
            SLOT(slot_scaleY(int)));

    connect(ui->rotate, SIGNAL(valueChanged(int)), this,
            SLOT(slot_rotate(int)));


    // push buttons
    connect(ui->add_translate, SIGNAL(clicked(bool)), this,
            SLOT(slot_newTranslate(bool)));

    connect(ui->add_scale, SIGNAL(clicked(bool)), this,
            SLOT(slot_newScale(bool)));

    connect(ui->add_rotate, SIGNAL(clicked(bool)), this,
            SLOT(slot_newRotate(bool)));

    connect(ui->set_geom, SIGNAL(clicked(bool)), this,
            SLOT(slot_newSquare(bool)));
}

void MainWindow::slot_addRoot(QTreeWidgetItem* root) {
    ui->treeWidget->addTopLevelItem(root);
}

// spin boxes
void MainWindow::slot_translateX(int value) {
    if (TranslateNode* t = dynamic_cast<TranslateNode*>(ui->treeWidget->currentItem())) {
        float y = t->getY();
        t->translate(value, y);
    }
}

void MainWindow::slot_translateY(int value) {
    if (TranslateNode* t = dynamic_cast<TranslateNode*>(ui->treeWidget->currentItem())) {
        float x = t->getX();
        t->translate(x, value);
    }
}

void MainWindow::slot_scaleX(int value) {
    if (ScaleNode* s = dynamic_cast<ScaleNode*>(ui->treeWidget->currentItem())) {
        float y = s->getY();
        s->scale(value, y);
    }
}

void MainWindow::slot_scaleY(int value) {
    if (ScaleNode* s = dynamic_cast<ScaleNode*>(ui->treeWidget->currentItem())) {
        float x = s->getX();
        s->scale(x, value);
    }
}

void MainWindow::slot_rotate(int value) {
    if (RotateNode* r = dynamic_cast<RotateNode*>(ui->treeWidget->currentItem())) {
        r->rotate(value);
    }
}

// push buttons
void MainWindow::slot_newTranslate(bool clicked) {
   QTreeWidgetItem* curr = ui->treeWidget->currentItem();

    if (curr != nullptr) {
        Node* node = dynamic_cast<Node*>(curr);
        node->addChild(mkU<TranslateNode>(0, 0, "translate"));
    }
}

void MainWindow::slot_newScale(bool clicked) {
    QTreeWidgetItem* curr = ui->treeWidget->currentItem();

    if (curr != nullptr) {
        Node* node = dynamic_cast<Node*>(curr);
        node->addChild(mkU<ScaleNode>("scale", 0, 0));
    }
}

void MainWindow::slot_newRotate(bool clicked) {
    QTreeWidgetItem* curr = ui->treeWidget->currentItem();

    if (curr != nullptr) {
        Node* node = dynamic_cast<Node*>(curr);
        node->addChild(mkU<RotateNode>("rotate", 0));
    }
}

void MainWindow::slot_newSquare(bool clicked) {
    QTreeWidgetItem* curr = ui->treeWidget->currentItem();

    if (curr != nullptr) {
        Node* node = dynamic_cast<Node*>(curr);
        ui->mygl->setSquare(node);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::exit();
}

#include "mygl.h"
#include <la.h>

#include <iostream>
#include <QApplication>
#include <QKeyEvent>

#include "node.h"
#include "rotatenode.h"
#include "scalenode.h"
#include "translatenode.h"


MyGL::MyGL(QWidget *parent)
    : OpenGLContext(parent),
      prog_flat(this),
      m_geomGrid(this), m_geomSquare(this, {glm::vec3(0.5f, 0.5f, 1.f),
                                            glm::vec3(-0.5f, 0.5f, 1.f),
                                            glm::vec3(-0.5f, -0.5f, 1.f),
                                            glm::vec3(0.5f, -0.5f, 1.f)}),

      m_showGrid(true),
     m_geomCircle(this, 75)
{
    setFocusPolicy(Qt::StrongFocus);
}

MyGL::~MyGL()
{
    makeCurrent();

    glDeleteVertexArrays(1, &vao);
    m_geomSquare.destroy();
    m_geomGrid.destroy();
    m_geomCircle.destroy();
}

void MyGL::initializeGL()
{
    // Create an OpenGL context using Qt's QOpenGLFunctions_3_2_Core class
    // If you were programming in a non-Qt context you might use GLEW (GL Extension Wrangler)instead
    initializeOpenGLFunctions();
    // Print out some information about the current OpenGL context
    debugContextVersion();

    // Set a few settings/modes in OpenGL rendering
//    glEnable(GL_DEPTH_TEST);
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

    //Create the scene geometry
    m_geomGrid.create();
    m_geomSquare.create();
    m_geomCircle.create();

    // Create and set up the flat lighting shader
    prog_flat.create(":/glsl/flat.vert.glsl", ":/glsl/flat.frag.glsl");

    // We have to have a VAO bound in OpenGL 3.2 Core. But if we're not
    // using multiple VAOs, we can just bind one once.
    glBindVertexArray(vao);

    root = constructSceneGraph();
    emit sendRoot(root.get());
}

void MyGL::resizeGL(int w, int h)
{
    glm::mat3 viewMat = glm::scale(glm::mat3(), glm::vec2(0.2, 0.2)); // Screen is -5 to 5

    // Upload the view matrix to our shader (i.e. onto the graphics card)
    prog_flat.setViewMatrix(viewMat);

    printGLErrorLog();
}

//This function is called by Qt any time your GL window is supposed to update
//For example, when the function updateGL is called, paintGL is called implicitly.
void MyGL::paintGL()
{
    // Clear the screen so that we only see newly drawn images
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_showGrid)
    {
        prog_flat.setModelMatrix(glm::mat3());
        prog_flat.draw(*this, m_geomGrid);
    }

    traverse(root, glm::mat3());
}

void MyGL::keyPressEvent(QKeyEvent *e)
{
    // http://doc.qt.io/qt-5/qt.html#Key-enum
    switch(e->key())
    {
    case(Qt::Key_Escape):
        QApplication::quit();
        break;

    case(Qt::Key_G):
        m_showGrid = !m_showGrid;
        break;
    }
}

uPtr<Node> MyGL::constructSceneGraph() {

    glm::vec3 black = glm::vec3(0, 0, 0);
    glm::vec3 white = glm::vec3(1, 1, 1);
    glm::vec3 skin = glm::vec3(1, 0.85, 0.75);
    glm::vec3 mouth = glm::vec3(1, 0.5, 0.5);
    glm::vec3 pants = glm::vec3(1, 0.85, 0.95);
    glm::vec3 plant = glm::vec3(0.5, 0.85, 0.6);
    glm::vec3 yellow = glm::vec3(1, 0.75, 0.25);

    // torso
    uPtr<Node> torso = mkU<TranslateNode>(0, -0.75, "torso: root");

    // stem 1
    Node& stemTrans1 = torso->addChild(mkU<TranslateNode>(4, -4, "stem 1: translate"));
    stemTrans1.setPolygon(m_geomSquare);
    stemTrans1.setColor(plant);

    Node& stemScale1 = stemTrans1.addChild(mkU<ScaleNode>("stem 1: scale", 0.25, 4));
    stemScale1.setPolygon(m_geomSquare);
    stemScale1.setColor(plant);

    // flower 1
    Node& flower1 = stemTrans1.addChild(mkU<TranslateNode>(0, 2, "flower 1: translate"));

    Node& flowerScale1 = flower1.addChild(mkU<ScaleNode>("flower 1: scale", 1, 1));
    flowerScale1.setPolygon(m_geomCircle);
    flowerScale1.setColor(pants);

    Node& flowerCenter1 = flower1.addChild(mkU<TranslateNode>(0, 0, "flower 1: translate"));

    Node& flowerCenterScale1 = flowerCenter1.addChild(mkU<ScaleNode>("flower 1: scale", 0.45, 0.35));
    flowerCenterScale1.setPolygon(m_geomCircle);
    flowerCenterScale1.setColor(yellow);

    // stem 2
    Node& stemTrans2 = torso->addChild(mkU<TranslateNode>(-4, -4, "stem 2: translate"));
    stemTrans2.setPolygon(m_geomSquare);
    stemTrans2.setColor(plant);

    Node& stemScale2 = stemTrans2.addChild(mkU<ScaleNode>("stem 2: scale", 0.25, 4));
    stemScale2.setPolygon(m_geomSquare);
    stemScale2.setColor(plant);

    // flower 2
    Node& flower2 = stemTrans2.addChild(mkU<TranslateNode>(0, 2, "flower 1: translate"));

    Node& flowerScale2 = flower2.addChild(mkU<ScaleNode>("flower 2: scale", 1, 1));
    flowerScale2.setPolygon(m_geomCircle);
    flowerScale2.setColor(pants);

    Node& flowerCenter2 = flower2.addChild(mkU<TranslateNode>(0, 0, "flower 2: translate"));

    Node& flowerCenterScale2 = flowerCenter2.addChild(mkU<ScaleNode>("flower 2: scale", 0.45, 0.35));
    flowerCenterScale2.setPolygon(m_geomCircle);
    flowerCenterScale2.setColor(yellow);

    // neck
    Node& neckScale = torso->addChild(mkU<ScaleNode>("neck: scale", 1, 1));

    Node& neckTrans = neckScale.addChild(mkU<TranslateNode>(0, 2, "neck: translate"));

    Node& neckRotate = neckTrans.addChild(mkU<RotateNode>("neck: rotate", 0));

    Node& neckTrans2 = neckRotate.addChild(mkU<TranslateNode>(0, 0, "neck: translate"));

    Node& neckScale2 = neckTrans2.addChild(mkU<ScaleNode>("neck: scale", 0.75, 1));
    neckScale2.setPolygon(m_geomSquare);
    neckScale2.setColor(skin);

    // head
    Node& headScale = neckScale2.addChild(mkU<ScaleNode>("head: scale", 1.25, 1));

    Node& headTrans = headScale.addChild(mkU<TranslateNode>(0, 1, "head: translate"));

    Node& headRotate = headTrans.addChild(mkU<RotateNode>("head: rotate", 0));

    Node& headTrans2 = headRotate.addChild(mkU<TranslateNode>(0, 0.35, "head: translate"));

    Node& headScale2 = headTrans2.addChild(mkU<ScaleNode>("head: scale", 2, 2));
    headScale2.setPolygon(m_geomCircle);
    headScale2.setColor(skin);

    // eyes
    Node& rightEyeTrans = headTrans2.addChild(mkU<TranslateNode>(0.5, 0.15, "right eye: translate"));

    Node& rightEyeScale = rightEyeTrans.addChild(mkU<ScaleNode>("right eye: scale", 0.3, 0.3));
    rightEyeScale.setPolygon(m_geomCircle);
    rightEyeScale.setColor(black);

    Node& leftEyeTrans = headTrans2.addChild(mkU<TranslateNode>(-0.5, 0.15, "left eye: translate"));

    Node& leftEyeScale = leftEyeTrans.addChild(mkU<ScaleNode>("left eye: scale", 0.3, 0.3));
    leftEyeScale.setPolygon(m_geomCircle);
    leftEyeScale.setColor(black);

    // mouth
    Node& mouthTrans = headTrans2.addChild(mkU<TranslateNode>(0, -0.45, "mouth: translate"));

    Node& mouthScale = mouthTrans.addChild(mkU<ScaleNode>("mouth: scale", 0.65, 0.3));
    mouthScale.setPolygon(m_geomCircle);
    mouthScale.setColor(mouth);

    // hat
    Node& hatTrans = headRotate.addChild(mkU<TranslateNode>(0, 1.25, "hat: translate"));

    Node& hatScale = hatTrans.addChild(mkU<ScaleNode>("hat: scale", 2, 0.75));

    Node& hatTrans2 = hatScale.addChild(mkU<TranslateNode>(0, 1, "hat: translate"));
    hatScale.setPolygon(m_geomSquare);
    hatScale.setColor(black);

    Node& hatScale2 = hatTrans2.addChild(mkU<ScaleNode>("hat: scale", 0.75, 1));
    hatScale2.setPolygon(m_geomSquare);
    hatScale2.setColor(black);

    // right upper arm
    Node& upperRightArmScale = torso->addChild(mkU<ScaleNode>("right upper arm: scale", 1, 1));

    Node& rightUpperArmTrans = upperRightArmScale.addChild(mkU<TranslateNode>(1, 1.25, "right upper arm: translate"));

    Node& rightUpperArmRot = rightUpperArmTrans.addChild(mkU<RotateNode>("right upper arm: rotate", -50));

    Node& upperRightArmScale2 = rightUpperArmRot.addChild(mkU<ScaleNode>("right upper arm: scale", 1, 2));
    upperRightArmScale2.setPolygon(m_geomSquare);
    upperRightArmScale2.setColor(skin);

    // right forearm
    Node& rightForearmTrans = rightUpperArmRot.addChild(mkU<TranslateNode>(0, 1.25, "right forearm: translate"));

    Node& rightForearmRot = rightForearmTrans.addChild(mkU<RotateNode>("right forearm: rotate", 45));
    rightForearmRot.setPolygon(m_geomCircle);
    rightForearmRot.setColor(skin);

    Node& rightForearmTrans2 = rightForearmRot.addChild(mkU<TranslateNode>(0, 0.75, "right forearm: translate"));

    Node& rightForearmScale = rightForearmTrans2.addChild(mkU<ScaleNode>("right forearm: scale", 0.85, 2));
    rightForearmScale.setPolygon(m_geomSquare);
    rightForearmScale.setColor(skin);

    // left upper arm
    Node& leftUpperArmScale = torso->addChild(mkU<ScaleNode>("left upper arm: scale", 1, 1));

    Node& leftUpperArmTrans = leftUpperArmScale.addChild(mkU<TranslateNode>(-1, 1.25, "left upper arm: translate"));

    Node& leftUpperArmRot = leftUpperArmTrans.addChild(mkU<RotateNode>("left upper arm: rotate", 50));

    Node& leftUpperArmScale2 = leftUpperArmRot.addChild(mkU<ScaleNode>("left upper arm: scale", 1, 2));
    leftUpperArmScale2.setPolygon(m_geomSquare);
    leftUpperArmScale2.setColor(skin);

    // left forearm
    Node& leftForearmTrans = leftUpperArmRot.addChild(mkU<TranslateNode>(0, 1.15, "left forearm: translate"));

    Node& leftForearmRot = leftForearmTrans.addChild(mkU<RotateNode>("left forearm: rotate",-45));
    leftForearmRot.setPolygon(m_geomCircle);
    leftForearmRot.setColor(skin);

    Node& leftForearmTrans2 = leftForearmRot.addChild(mkU<TranslateNode>(0, 1, "left forearm: translate"));

    Node& leftForearmScale = leftForearmTrans2.addChild(mkU<ScaleNode>("left forearm: scale", 0.85, 2));
    leftForearmScale.setPolygon(m_geomSquare);
    leftForearmScale.setColor(skin);

    // legs
    Node& pantsScale = torso->addChild(mkU<ScaleNode>("pants: scale", 1, 1));

    Node& pantsTrans = pantsScale.addChild(mkU<TranslateNode>(0, -1.2, "pants: translate"));

    Node& pantsScale2 = pantsTrans.addChild(mkU<ScaleNode>("pants: scale", 2, 2));
    pantsScale2.setPolygon(m_geomSquare);
    pantsScale2.setColor(pants);

    // left leg
    Node& leftLegRot = pantsTrans.addChild(mkU<RotateNode>("left leg: rotate", 0));
    leftLegRot.setPolygon(m_geomSquare);
    leftLegRot.setColor(pants);

    Node& leftLegTrans = leftLegRot.addChild(mkU<TranslateNode>(-0.5, -2, "left leg: translate"));

    Node& leftLegScale = leftLegTrans.addChild(mkU<ScaleNode>("left leg: scale", 0.8, 2.25));
    leftLegScale.setPolygon(m_geomSquare);
    leftLegScale.setColor(pants);

    Node& leftFootTrans = leftLegScale.addChild(mkU<TranslateNode>(-0.75, -0.45, "left foot: translate"));

    Node& leftFootScale = leftFootTrans.addChild(mkU<ScaleNode>("left foot: scale", 1.25, 0.3));
    leftFootScale.setPolygon(m_geomCircle);
    leftFootScale.setColor(black);

    // right leg
    Node& rightLegRot = pantsTrans.addChild(mkU<RotateNode>("right leg: rotate", 45));
    rightLegRot.setPolygon(m_geomSquare);
    rightLegRot.setColor(pants);

    Node& rightLegTrans = rightLegRot.addChild(mkU<TranslateNode>(0.25, -1.5, "right leg: translate"));

    Node& rightLegScale = rightLegTrans.addChild(mkU<ScaleNode>("right leg: scale", 0.8, 2.75));
    rightLegScale.setPolygon(m_geomSquare);
    rightLegScale.setColor(pants);

    Node& rightFootTrans = rightLegScale.addChild(mkU<TranslateNode>(0.75, -0.45, "left foot: translate"));

    Node& rightFootScale = rightFootTrans.addChild(mkU<ScaleNode>("left foot: scale", 1.25, 0.25));
    rightFootScale.setPolygon(m_geomCircle);
    rightFootScale.setColor(black);

    // shirt
    Node& shirt = torso->addChild(mkU<TranslateNode>(0, 0.35, "shirt: translate"));

    Node& shirtScale = shirt.addChild(mkU<ScaleNode>("shirt: scale", 2, 3.75));
    shirtScale.setPolygon(m_geomCircle);
    shirtScale.setColor(white);

    return torso;
}

// from lecture slides
void MyGL::traverse(const uPtr<Node> &node, glm::mat3 mat) {
    mat = mat * node->transform();

    for (const uPtr<Node> &n : node->children) {
        traverse(n, mat);
    }

    // if node has geometry
    if (node->getPolygon() != nullptr) {
        node->getPolygon()->setColor(node->getColor());
        prog_flat.setModelMatrix(mat);
        prog_flat.draw(*this, *node->getPolygon());
    }
}

void MyGL::setSquare(Node *node) {
    if (node->getPolygon() == nullptr) {
        node->setPolygon(m_geomSquare);
    }
}

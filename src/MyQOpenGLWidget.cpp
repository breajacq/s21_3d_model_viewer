//
// Created by stf20 on 29.09.2022.
//
#define GL_SILENCE_DEPRECATION

#include "MyQOpenGLWidget.h"

MyQOpenGLWidget::MyQOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent) {}
MyQOpenGLWidget::~MyQOpenGLWidget() {
  delete prog;
};

void MyQOpenGLWidget::mousePressEvent(QMouseEvent* event) {
  Qt::MouseButton button = event->button();
  if (button == Qt::LeftButton) {
    this->leftButtonPress = true;
    this->leftButtonPoint = event->pos();
  } else if (button == Qt::RightButton) {
    this->rightButtonPress = true;
    this->rightButtonPoint = event->pos();
  }
}

void MyQOpenGLWidget::mouseReleaseEvent(QMouseEvent* event) {
  Qt::MouseButton button = event->button();
  if (button == Qt::LeftButton)
    this->leftButtonPress = false;
  else if (button == Qt::RightButton)
    this->rightButtonPress = false;
}

void MyQOpenGLWidget::mouseMoveEvent(QMouseEvent* event) {
  if (this->leftButtonPress) {
    emit leftButtonMove(event->pos() - this->leftButtonPoint);
    this->leftButtonPoint = event->pos();
  }

  if (this->rightButtonPress) {
    emit rightButtonMove(event->pos() - this->rightButtonPoint);
    this->rightButtonPoint = event->pos();
  }
}

void MyQOpenGLWidget::wheelEvent(QWheelEvent* event) {
  emit this->mouseScroll(event->angleDelta().y());
}

void MyQOpenGLWidget::changeBackgroundColor(int r, int g, int b) {
  this->color = QColor(r, g, b);
  update();
}

void MyQOpenGLWidget::changeColorLine(int r, int g, int b) {
  this->colorLine = QColor(r, g, b);
  update();
}

void MyQOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST); // включаем буфер глубины для отображения Z-координаты.

  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
}
void MyQOpenGLWidget::paintGL() {
  glClearColor(color.redF(), color.greenF(), color.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_TEST);

  if ((*this->cur_obect)) {
      glVertexPointer(3, GL_DOUBLE, 0, (*this->cur_obect)->list_vertex3.vertex3); // array_of_coord
      glEnableClientState(GL_VERTEX_ARRAY); // Enable state Opengl
          glColor3f(1, 0, 0); // color point
          glEnable(GL_POINT_SMOOTH);
              glPointSize(5);
              glDrawArrays(GL_POINTS, 0, ((*this->cur_obect)->list_vertex3.count));
          glDisable(GL_POINT_SMOOTH);

          std::cout << "redF = " << colorLine.redF() << std::endl;
          std::cout << "greenF = " << colorLine.greenF() << std::endl;
          std::cout << "blueF = " << colorLine.blueF() << std::endl;


          if (lineColorStatus) {
            glColor3f(colorLine.redF(), colorLine.greenF(), colorLine.blueF());
          } else {
            glColor3f(0.12, 0.69, 0.55); // color lines
          }


          if (lineType) {
              glEnable(GL_LINE_STIPPLE);
              glLineStipple(3, 0x00FF);
          }
          glLineWidth(2);

          glDrawElements(GL_LINES, (*this->cur_obect)->list_polygon.size, GL_UNSIGNED_INT, (*this->cur_obect)->list_polygon.polygons);

          if (lineType) glDisable(GL_LINE_STIPPLE);


      glDisableClientState(GL_VERTEX_ARRAY); // Disable state Opengl
  }
}

void MyQOpenGLWidget::saveBmpImage(const QString& filename) {
  this->grabFramebuffer().save(filename, "bmp");
}

void MyQOpenGLWidget::saveJpegImage(const QString& filename) {
  this->grabFramebuffer().save(filename, "jpeg");
}

void MyQOpenGLWidget::shift(double x, double y, double z) {
//    glTranslatef(x, y, z);
}



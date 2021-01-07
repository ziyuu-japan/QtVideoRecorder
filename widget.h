#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "graphicsscene.h"


namespace Ui {
class Form;
}

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    GraphicsScene m_scene;
    GraphicsScene *m_scene_ptr;
private:
    Ui::Form *ui;


signals:

};

#endif // WIDGET_H

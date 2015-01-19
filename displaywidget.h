#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>
#include "glscreen.h"

namespace Ui {
class DisplayWidget;
}

class DisplayWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit DisplayWidget(QWidget *parent = 0);
    ~DisplayWidget();
    
private:
    Ui::DisplayWidget *ui;
    GLScreen *glScreen;
};

#endif // DISPLAYWIDGET_H

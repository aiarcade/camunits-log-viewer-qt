#include "displaywidget.h"
#include "ui_displaywidget.h"

DisplayWidget::DisplayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayWidget)
{
    glScreen=new GLScreen(this);
    glScreen->showImage(QImage ("/home/mahesh/dev/camout//1194113754532499.jpg"));
    ui->setupUi(this);

}

DisplayWidget::~DisplayWidget()
{
    delete ui;
}

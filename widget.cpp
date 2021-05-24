#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    tcp_init();
    text_print("hello sytnocui!");
    text_print(QString("hello %1").arg("smartcar!"));
}

Widget::~Widget()
{
    delete ui;
}

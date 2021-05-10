#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

//tcp通信
#include <QTcpSocket>
#include <QHostAddress>
#include <QLineEdit>

#include <QUdpSocket>
#include <QFile>
#include <QFileDialog>
#include <QDateTime>
#include <QImage>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

///////////////////////////////////////////////////////////
typedef enum
{
    type_view,
    type_ctrl,
}PARA_USETYPE;

typedef enum
{
    type_int,
    type_float,
}PARA_DATATYPE;
///////////////////////////////////////////////////////////
typedef struct
{
    QString name;
    int *vari;
    float *varf;
    PARA_USETYPE type_use;
    PARA_DATATYPE type_data;
}TABLE_PARA;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QTcpSocket * tcpSocket;

    void tcp_init();
    void tcp_read_msg();
    void tcp_connected();

    void udp_init();

    void table_DataSetup();
    void table_init();//表格初始化
    void view_table_update();
    void ctrl_table_update();
    void ctrl_table_get();
    void table_para_construct(PARA_USETYPE type_use,PARA_DATATYPE type_data,const QString &name,void* varf);

    void text_print(QString qstr);

private slots:

    void on_ButtonCtrlSend_clicked();

    void on_ButtonConnect_clicked();

    void on_ButtonDisConnect_clicked();

    void on_ButtonToLoad_clicked();

    void on_ButtonToUnload_clicked();

    void on_ButtonToWait_clicked();

    void on_ButtonStop_clicked();

    void on_ButtonStart_clicked();

    void on_ButtonRestart_clicked();

    void on_ButtonTabImgRead_clicked();

    void on_ButtonTabImgClose_clicked();

    void on_ButtonRead_clicked();

    void on_ButtonCtrlSave_clicked();

private:
    Ui::Widget *ui;

    QList<TABLE_PARA> viewpara_list;//实时变量
    QList<TABLE_PARA> ctrlpara_list;//控制参数
};
#endif // WIDGET_H

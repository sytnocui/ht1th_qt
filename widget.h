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
    int vari;
    float varf;
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
    //udp通讯
    QUdpSocket * udpSocket;

    void tcp_init();
    void tcp_read_msg();
    void tcp_viewpara_get(QByteArray array);
    void tcp_connected();

    void udp_init();
    void udp_read_msg();

    //不需要初始化控制菜单
//    void ctrl_table_DataSetup();
    void ctrl_table_init();//表格初始化
    void ctrl_table_clean();//表格清零
    void ctrl_table_update();
    void ctrl_table_get();

    void view_table_init();
    void view_table_DataSetup();
    void view_table_update();
    void table_para_construct(PARA_USETYPE type_use,PARA_DATATYPE type_data,const QString &name);

    void text_print(QString qstr);

private slots:

    void on_ButtonConnect_clicked();

    void on_ButtonDisConnect_clicked();

    void on_ButtonToLoad_clicked();

    void on_ButtonToUnload_clicked();

    void on_ButtonToWait_clicked();

    void on_ButtonStop_clicked();

    void on_ButtonStart_clicked();

    void on_ButtonRestart_clicked();
private:
    Ui::Widget *ui;

    QList<TABLE_PARA> ctrlpara_list;//控制参数
    QList<TABLE_PARA> viewpara_list;//实时变量
};
#endif // WIDGET_H

#include "widget.h"
#include "ui_widget.h"

void Widget::tcp_init(){
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket,&QTcpSocket::connected,this,&Widget::tcp_connected);//建立新连接
    connect(tcpSocket,&QTcpSocket::readyRead,this,&Widget::tcp_read_msg);//接收信息
}

void Widget::tcp_connected(){
    text_print("成功和服务器建立好连接");
}

void Widget::tcp_read_msg(){
    //获取对方的ip和端口，peer意为对方的，tostring转换成字符串
    QString ip = tcpSocket->peerAddress().toString();
    qint16 port = tcpSocket->peerPort();
    //获取对方发送的内容
    QByteArray array = tcpSocket->readAll();
    QString temp = QString("[%1:%2]:%3").arg(ip).arg(port).arg(QString(array.toHex()));
    //追加到编辑区中
    text_print(temp);
}

void Widget::on_ButtonConnect_clicked(){
    //加判断
    //获取服务器ip和端口
    QString ip = ui->lineEditIP->text();
    qint16 port = ui->lineEditPort->text().toInt();
    //主动和服务器建立连接
    tcpSocket->connectToHost(QHostAddress(ip),port);
}

void Widget::on_ButtonDisConnect_clicked(){
    //主动和对方断开连接
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    text_print("成功和服务器断开连接");
}

////////////////////////////////////////////协议//////////////////////////////////////////////////
//*non-para*//
//Reset = 0x01
//Run   = 0x10
//Stop  = 0x20
//ImgOpen = 0x60
//ImgClose = 0x70
//*have-para*//
//To_Wait = 0x30
//To_Load = 0x40
//To_Unload = 0x50
//CtrlUpdate = 0x77
void Widget::on_ButtonRestart_clicked(){//复位
    QByteArray temp;
    temp.append(0x01);
    tcpSocket->write(temp);
    text_print("Reset");
}

void Widget::on_ButtonStart_clicked(){//运行
    QByteArray temp;
    temp.append(0x10);
    tcpSocket->write(temp);
    text_print("Run");}

void Widget::on_ButtonStop_clicked(){//停车
    QByteArray temp;
    temp.append(0x20);
    tcpSocket->write(temp);
    text_print("Stop");}

void Widget::on_ButtonTabImgRead_clicked(){//打开实时显示图像
    QByteArray temp;
    temp.append(0x60);
    tcpSocket->write(temp);
    text_print("ImgOpen");}

void Widget::on_ButtonTabImgClose_clicked(){//关闭实时显示图像
    QByteArray temp;
    temp.append(0x70);
    tcpSocket->write(temp);
    text_print("ImgClose");}

/////////have_para
void Widget::on_ButtonToWait_clicked(){//前往等待区
    float x,y = 0;
    x = ui->lineEditWaitx->text().toFloat();
    y = ui->lineEditWaity->text().toFloat();
    QByteArray x_byte,y_byte;
    x_byte.resize(sizeof(float));
    y_byte.resize(sizeof(float));
    memcpy(x_byte.data(),&x,sizeof(x));
    memcpy(y_byte.data(),&y,sizeof(y));
    QByteArray data_byte;
    data_byte.append(0x30).append(x_byte).append(y_byte);
//    qDebug()<<x_byte.toHex()<<y_byte.toHex();
//    qDebug()<<data_byte.toHex();
    //send
    tcpSocket->write(data_byte);
    text_print("To_Wait:"+QString(data_byte.toHex()));}

void Widget::on_ButtonToLoad_clicked(){//前往装货区
    float x,y = 0;
    x = ui->lineEditLoadx->text().toFloat();
    y = ui->lineEditLoady->text().toFloat();
    QByteArray x_byte,y_byte;
    x_byte.resize(sizeof(float));
    y_byte.resize(sizeof(float));
    memcpy(x_byte.data(),&x,sizeof(x));
    memcpy(y_byte.data(),&y,sizeof(y));
    QByteArray data_byte;
    data_byte.append(0x40).append(x_byte).append(y_byte);
//    qDebug()<<x_byte.toHex()<<y_byte.toHex();
//    qDebug()<<data_byte.toHex();
    //send
    tcpSocket->write(data_byte);
    text_print("To_Load:"+QString(data_byte.toHex()));}

void Widget::on_ButtonToUnload_clicked(){//前往卸货区
    float x,y = 0;
    x = ui->lineEditUnloadx->text().toFloat();
    y = ui->lineEditUnloady->text().toFloat();
    QByteArray x_byte,y_byte;
    x_byte.resize(sizeof(float));
    y_byte.resize(sizeof(float));
    memcpy(x_byte.data(),&x,sizeof(x));
    memcpy(y_byte.data(),&y,sizeof(y));
    QByteArray data_byte;
    data_byte.append(0x50).append(x_byte).append(y_byte);
//    qDebug()<<x_byte.toHex()<<y_byte.toHex();
//    qDebug()<<data_byte.toHex();
    //send
    tcpSocket->write(data_byte);
    text_print("To_Unload:"+QString(data_byte.toHex()));}

void Widget::on_ButtonCtrlSend_clicked(){//修改参数
    //获取控制参数
    ctrl_table_get();
//    ctrl_table_update();
//    view_table_update();
    //将控制参数加入缓存中
    QByteArray data_byte;
    data_byte.append(0x77);
    QByteArray ctrl_byte(4,0);//init qbytearray
    for(int i=0;i<ctrlpara_list.size();i++){
        switch (ctrlpara_list.at(i).type_data) {
        case type_int: memcpy(ctrl_byte.data(),&ctrlpara_list.at(i).vari,sizeof(int));
            data_byte.append(ctrl_byte);break;
        case type_float:memcpy(ctrl_byte.data(),&ctrlpara_list.at(i).varf,sizeof(float));
            data_byte.append(ctrl_byte);break;}}
    //send
    tcpSocket->write(data_byte);
    text_print("CtrlUpdate"+QString(data_byte.toHex()));}

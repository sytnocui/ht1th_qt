#include "widget.h"
#include "ui_widget.h"

///////////////////////////////////////////udp////////////////////////////////////////////////
void Widget::udp_init()
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::LocalHost, 8888);
    connect(udpSocket, &QUdpSocket::readyRead,this,&Widget::udp_read_msg);
}

void Widget::udp_read_msg()
{
    qDebug()<<"hello";
    QByteArray datagram;
    while (udpSocket->hasPendingDatagrams()) {
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
    }
    //处理数据
    if(datagram.size()<100)//更新参数
    {
        int para_num = datagram.size()/4;
        for(int i=0;i<viewpara_list.size();i++){
            if(para_num <= i)break;//数目不匹配跳出
            float value;
            memcpy(&value,&datagram.data()[4*i],sizeof(float));
            qDebug()<<value;
            switch (viewpara_list.at(i).type_data) {
            case type_int: qDebug()<<"不是说都是浮点数吗";break;
            case type_float: viewpara_list[i].varf = value;break;}
        }
        view_table_update();
    }
    else//更新图像
    {
        QPixmap pix;
        pix.loadFromData(datagram);
        ui->labelImg->setPixmap(pix.scaled(ui->labelImg->size()));
    }
}

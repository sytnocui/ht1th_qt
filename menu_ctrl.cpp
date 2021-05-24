#include "widget.h"
#include "ui_widget.h"

void Widget::on_ButtonRead_clicked()//读取参数
{
    ctrl_table_clean();//清除现有的控制参数

    QString path = QFileDialog::getOpenFileName(this,"open","../","TXT(*.txt)");
    if(path.isEmpty() == false)
    {
        //文件对象
        QFile file(path);
        //打开文件
        bool isOk = file.open(QIODevice::ReadOnly);
        if(isOk == true)
        {
            int i=0;
            TABLE_PARA temppara = {"init",0,0,type_ctrl,type_float};
            QString str;
            while(file.atEnd() == false)
            {
                ctrlpara_list<<temppara;
                str = QString(file.readLine());
                ctrlpara_list[i].name = str.section("##",0,0);
                ctrlpara_list[i].varf = str.section("##",1,1).toFloat();
                i++;
            }
        }
        //关闭文件
        file.close();
    }
    ctrl_table_init();
    ctrl_table_update();
}
void Widget::ctrl_table_clean()
{
    ctrlpara_list.clear();
}

void Widget::on_ButtonCtrlSave_clicked()//保存参数
{
    //获取界面上的控制参数
    ctrl_table_get();
    //开始写文件
    QString path = QFileDialog::getSaveFileName(this,"save","./","TXT(*.txt)");
    if(path.isEmpty()== false)
    {
        QFile file;//创建文件对象
        //关联文件名字
        file.setFileName(path);
        //打开文件，只写方式
        bool isOk = file.open(QIODevice::WriteOnly);
        if(isOk == true)
        {
            QString str;
            //获取参数信息
            for(int i=0;i<ctrlpara_list.size();i++){
                switch (ctrlpara_list.at(i).type_data) {
                case type_int: qDebug()<<"不是说都是浮点数吗";break;
                case type_float: str.append(ctrlpara_list.at(i).name)
                                    .append("##")
                                    .append(QString("%1").arg(ctrlpara_list.at(i).varf))
                                    .append("\n");break;}
            }
            qDebug()<<str;
            //写文件
            file.write(str.toUtf8());
        }
        file.close();
    }
}

void Widget::ctrl_table_init()
{
    //控制参数表格
    ui->tableWidgetCtrl->setColumnCount(2);
    ui->tableWidgetCtrl->setHorizontalHeaderLabels(QStringList()<<"参数名"<<"值");
    ui->tableWidgetCtrl->setRowCount(ctrlpara_list.size());//创建tableWidget，个数为列表大小
    for(int i=0;i<ctrlpara_list.size();i++){
        int col=0;
        ui->tableWidgetCtrl->setItem(i,col++,new QTableWidgetItem(ctrlpara_list.at(i).name));//at越界有报错的提示信息
        switch (ctrlpara_list.at(i).type_data) {
        case type_int: ui->tableWidgetCtrl->setItem(i,col++,new QTableWidgetItem(QString("%1").arg(ctrlpara_list.at(i).vari)));break;
        case type_float: ui->tableWidgetCtrl->setItem(i,col++,new QTableWidgetItem(QString("%1").arg(ctrlpara_list.at(i).varf)));break;}
    }
}

void Widget::ctrl_table_update(){//更新界面上的控制参数
    for(int i=0;i<ctrlpara_list.size();i++){
        switch (ctrlpara_list.at(i).type_data) {
        case type_int: ui->tableWidgetCtrl->setItem(i,1,new QTableWidgetItem(QString("%1").arg(ctrlpara_list.at(i).vari)));break;
        case type_float: ui->tableWidgetCtrl->setItem(i,1,new QTableWidgetItem(QString("%1").arg(ctrlpara_list.at(i).varf)));break;}
    }
}

void Widget::ctrl_table_get(){//获取界面上的控制参数
    for(int i=0;i<ctrlpara_list.size();i++){
        QString temp_str= ui->tableWidgetCtrl->item(i,1)->text();
        switch (ctrlpara_list.at(i).type_data) {
        case type_int: ctrlpara_list[i].vari = temp_str.toInt();break;
        case type_float: ctrlpara_list[i].varf = temp_str.toFloat();break;}
    }
}

void Widget::text_print(QString qstr){//打印
    ui->textEdit->append(qstr);}


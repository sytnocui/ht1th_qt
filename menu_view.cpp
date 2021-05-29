#include "widget.h"
#include "ui_widget.h"

void Widget::view_table_DataSetup(){//初始化菜单
    table_para_construct(type_view,type_float,"测试10");
    table_para_construct(type_view,type_float,"测试11");
    table_para_construct(type_view,type_float,"测试12");
    table_para_construct(type_view,type_float,"测试13");
    table_para_construct(type_view,type_float,"测试14");
    table_para_construct(type_view,type_float,"测试15");
    table_para_construct(type_view,type_float,"测试16");
    table_para_construct(type_view,type_float,"测试17");
}


void Widget::view_table_update(){//更新界面上的实时变量
    for(int i=0;i<viewpara_list.size();i++){
        switch (viewpara_list.at(i).type_data) {
        case type_int: qDebug()<<"不是说都是浮点数吗";
            ui->tableWidgetView->setItem(i,1,new QTableWidgetItem(QString("%1").arg(viewpara_list.at(i).vari)));break;
        case type_float: ui->tableWidgetView->setItem(i,1,new QTableWidgetItem(QString("%1").arg(viewpara_list.at(i).varf)));break;}
    }
}

void Widget::view_table_init()
{
    //实时变量表格
    ui->tableWidgetView->setColumnCount(2);    //设置列数
    ui->tableWidgetView->setHorizontalHeaderLabels(QStringList()<<"参数名"<<"值");//设置水平表头
    ui->tableWidgetView->setRowCount(viewpara_list.size());//设置行数
    ui->tableWidgetView->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑
    for(int i=0;i<viewpara_list.size();i++){
        int col=0;
        ui->tableWidgetView->setItem(i,col++,new QTableWidgetItem(viewpara_list.at(i).name));//at越界有报错的提示信息
        switch (viewpara_list.at(i).type_data) {
        case type_int: qDebug()<<"不是说都是浮点数吗";
            ui->tableWidgetView->setItem(i,col++,new QTableWidgetItem(QString("%1").arg(viewpara_list.at(i).vari)));break;
        case type_float: ui->tableWidgetView->setItem(i,col++,new QTableWidgetItem(QString("%1").arg(viewpara_list.at(i).varf)));break;}
    }
}

void Widget::table_para_construct(PARA_USETYPE type_use,PARA_DATATYPE type_data,const QString &name){
    TABLE_PARA temppara = {name,0,0,type_use,type_data};
    //判断参数类型
    switch (type_data) {
    case type_int: qDebug()<<"不是说都是浮点数吗";break;
    case type_float: break;}
    //判断参数用途,
    switch (type_use) {
    case type_view: viewpara_list<<temppara;break;
    case type_ctrl: qDebug()<<"怎么这里有控制参数";
            ctrlpara_list<<temppara;break;}
}

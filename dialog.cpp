#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
Dialog::Dialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Dialog)
{
	ui->setupUi(this);
	ui->tableWidget->setColumnCount(2);
	ui->tableWidget->setRowCount(0);
}

Dialog::~Dialog()
{
	delete ui;
}

void Dialog::addErrorMessage(QString data, QString message)
{
	ui->tableWidget->insertRow(ui->tableWidget->rowCount());
	ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(data));
	ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(message));
}

void Dialog::addRoots(QString, QString)
{

}

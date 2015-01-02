#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Dialog)
{
	ui->setupUi(this);
	setFixedSize(size());
	ui->tableWidget->setColumnCount(2);
	ui->tableWidget->setRowCount(0);
	ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
	ui->tableWidget->setColumnWidth(0,ui->tableWidget->width()/2-50);
}

Dialog::~Dialog()
{
	delete ui;
}

void Dialog::addLine(QString data, QString message)
{
	ui->tableWidget->insertRow(ui->tableWidget->rowCount());
	ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(data));
	ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(message));
}


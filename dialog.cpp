#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
Dialog::Dialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Dialog)
{
	ui->setupUi(this);
	ui->tableWidget->setColumnCount(2);
	ui->tableWidget->setHorizontalHeaderLabels(
				QStringList({"Coefficients","Roots"}));
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
	ui->tableWidget->resizeColumnToContents(1);
}

void Dialog::resizeEvent(QResizeEvent *resize)
{
	ui->tableWidget->resize(size().width()-15,size().height()-15);
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtMath>
#include "quadraticoperation.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pushButton_clicked()
{
	QStringList coefficients=ui->lineEdit->text().split(QRegExp("\\s"),QString::SkipEmptyParts);
	if(ui->lineEdit->text().contains(QRegExp("[^0-9\\si+-]")) or checkValidity(coefficients))
	{
		ui->statusBar->showMessage("Syntax error");
		return;
	}
	if (coefficients.size()!=3)
	{
		ui->statusBar->showMessage("Not quadratic");
		return;
	}
	ui->statusBar->clearMessage();

	QuadraticOperation quadratic(coefficients);
	qreal* result;
	result=quadratic.getResult();
	firstRoot[0]=result[0];
	firstRoot[1]=result[1];
	secondRoot[0]=result[2];
	secondRoot[1]=result[3];
	QString firstRootString,secondRootString;
	if(firstRoot[1]==0 and secondRoot[1]==0)
	{
		firstRootString=QString("First root: %1")
				.arg(firstRoot[0],0,'g',5);
		secondRootString=QString("Second root: %1")
				.arg(secondRoot[0],0,'g',5);
	}
	else
	{
		firstRootString=QString("First root: %1+%2i")
				.arg(firstRoot[0],0,'g',5).arg(firstRoot[1],0,'g',5);
		secondRootString=QString("Second root: %1+%2i")
				.arg(secondRoot[0],0,'g',5).arg(secondRoot[1],0,'g',5);
	}
	ui->label->setText(firstRootString);
	ui->label_2->setText(secondRootString);
}


bool MainWindow::checkValidity(QStringList list)
{
	QRegExp rex(".*[+-]{2,}.*|.*[+-]$");
	for(int i=0;i<list.size();i++)
	{
		if(rex.exactMatch(list[i]))
			return true;
	}
	return false;
}

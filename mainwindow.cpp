#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

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
	QStringList k=ui->lineEdit->text().split(QRegExp("\\s"));
	if (k.size()!=3)
	{
		ui->statusBar->showMessage("Уравнение не квадратное");
		return;
	}
	else
	{
		ui->statusBar->clearMessage();
	}
	QList<qreal> k_sep;
	k_sep=parseList(k);
	solve(k_sep);
	ui->label->setText("Первый корень: "+QString::number(x1));
	ui->label_2->setText("Второй корень: "+QString::number(x2));
}

QList<qreal> MainWindow::parseList(QStringList klist)
{
	QList<qreal> k_sep;
	return k_sep;
}

void MainWindow::solve(QList<qreal> k_sep)
{
	x1=0;
	x2=0;
}

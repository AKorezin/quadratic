#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtMath>

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
	QStringList k=ui->lineEdit->text().split(QRegExp("\\s"),QString::SkipEmptyParts);
	if(ui->lineEdit->text().contains(QRegExp("[^1-9\\si+-]")) or chck(k))
	{
		ui->statusBar->showMessage("Ошибка записи");
		return;
	}
	if (k.size()!=3)
	{
		ui->statusBar->showMessage("Уравнение не квадратное");
		return;
	}
	ui->statusBar->clearMessage();
	QList<qreal> k_sep;
	k_sep=parseList(k);
	solve(k_sep);
	ui->label->setText("Первый корень: "+QString::number(x1[0])+"+"+QString::number(x1[1])+"i");
	ui->label_2->setText("Второй корень: "+QString::number(x2[0])+"+"+QString::number(x2[1])+"i");
}

QList<qreal> MainWindow::parseList(QStringList klist)
{
	QList<qreal> k_sep;
	for(int i=0;i<klist.size()*2;i++)
		k_sep<<0;
	for(int i=0;i<klist.size();i++)
	{
		QString k=klist[i];
		QStringList klist_part,klist_sign;
		klist_part=k.split(QRegExp("[+-]"),QString::SkipEmptyParts);
		klist_sign=k.split(QRegExp("[^+-]"),QString::SkipEmptyParts);
		for(int j=0;j<klist_part.size();j++)
		{
			QString part;
			if(klist_part.size()!=klist_sign.size())
			{
				klist_sign.insert(0,"+");
			}
			part=klist_sign[j]+klist_part[j];
			if(klist_part[j].contains("i"))
			{
				part.remove("i");
				if(part.length()==1)
					k_sep[2*i+1]+=1;
				else
					k_sep[2*i+1]+=part.toDouble();
			}
			else
				k_sep[2*i]+=part.toDouble();
		}
	}
	qDebug()<<k_sep;
	return k_sep;
}

void MainWindow::solve(QList<qreal> k)
{
	qreal a,b;
	a=k[2]*k[2]-k[3]*k[3]-4*k[0]*k[4]+4*k[1]*k[5];
	b=2*k[2]*k[3]-4*k[0]*k[5]-4*k[1]*k[4];
	qDebug()<<a<<b;
	qreal c1,c2,l,atan;
	l=qPow(a*a+b*b,0.25);
	atan=qAtan(b/a);
	if (a<0)
		atan+=M_PI;
	c1=qCos(atan/2)*l;
	c2=qSin(atan/2)*l;
	qDebug()<<c1<<c2;
	qreal u1,u2,d1,d2;
	d1=k[0]*2;
	d2=k[1]*2;

	u1=-k[2]+c1;
	u2=-k[3]+c2;
	x1[0]=(u1*d1+u2*d2)/(d1*d1+d2*d2);
	x1[1]=(d1*u2-d2*u1)/(d1*d1+d2*d2);

	u1=-k[2]-c1;
	u2=-k[3]-c2;
	x2[0]=(u1*d1+u2*d2)/(d1*d1+d2*d2);
	x2[1]=(d1*u2-d2*u1)/(d1*d1+d2*d2);
}

bool MainWindow::chck(QStringList list)
{
	QRegExp rex(".*[+-]{2,}.*|.*[+-]$");
	for(int i=0;i<list.size();i++)
	{
		if(rex.exactMatch(list[i]))
			return true;
	}
	return false;
}

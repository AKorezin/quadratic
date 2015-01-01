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
	QList<qreal> coeffSeparated;
	coeffSeparated=parseList(coefficients);
	solve(coeffSeparated);
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

QList<qreal> MainWindow::parseList(QStringList coeffList)
{
	QList<qreal> coeffSeparated;
	for(int i=0;i<coeffList.size()*2;i++)
		coeffSeparated<<0;
	for(int i=0;i<coeffList.size();i++)
	{
		QString coeff=coeffList[i];
		QStringList coeffList_part,coeffList_sign;
		coeffList_part=coeff.split(QRegExp("[+-]"),QString::SkipEmptyParts);
		coeffList_sign=coeff.split(QRegExp("[^+-]"),QString::SkipEmptyParts);
		for(int j=0;j<coeffList_part.size();j++)
		{
			QString part;
			if(coeffList_part.size()!=coeffList_sign.size())
			{
				coeffList_sign.insert(0,"+");
			}
			part=coeffList_sign[j]+coeffList_part[j];
			if(coeffList_part[j].contains("i"))
			{
				part.remove("i");
				if(part.length()==1)
					coeffSeparated[2*i+1]+=1;
				else
					coeffSeparated[2*i+1]+=part.toDouble();
			}
			else
				coeffSeparated[2*i]+=part.toDouble();
		}
	}
	qDebug()<<coeffSeparated;
	return coeffSeparated;
}

void MainWindow::solve(QList<qreal> coeffSeparated)
{
	qreal a,b;
	a=coeffSeparated[2]*coeffSeparated[2]-coeffSeparated[3]*coeffSeparated[3]
			-4*coeffSeparated[0]*coeffSeparated[4]
			+4*coeffSeparated[1]*coeffSeparated[5];
	b=2*coeffSeparated[2]*coeffSeparated[3]
			-4*coeffSeparated[0]*coeffSeparated[5]
			-4*coeffSeparated[1]*coeffSeparated[4];
	qreal numeratorReal,numeratorImage,denumeratorReal,denumeratorImage;
	if(a==0 and b==0)
	{
		denumeratorReal=coeffSeparated[0]*2;
		denumeratorImage=coeffSeparated[1]*2;

		numeratorReal=-coeffSeparated[2];
		numeratorImage=-coeffSeparated[3];
		firstRoot[0]=(numeratorReal*denumeratorReal+numeratorImage*denumeratorImage)
				/(denumeratorReal*denumeratorReal+denumeratorImage*denumeratorImage);
		firstRoot[1]=(denumeratorReal*numeratorImage-denumeratorImage*numeratorReal)
				/(denumeratorReal*denumeratorReal+denumeratorImage*denumeratorImage);
		secondRoot[0]=firstRoot[0];
		secondRoot[1]=firstRoot[1];
	}
	else
	{
		qreal constant1,constant2,length,atan;
		length=qPow(a*a+b*b,0.25);
		atan=qAtan(b/a);
		if (a<0)
			atan+=M_PI;
		constant1=qCos(atan/2)*length;
		constant2=qSin(atan/2)*length;

		denumeratorReal=coeffSeparated[0]*2;
		denumeratorImage=coeffSeparated[1]*2;

		numeratorReal=-coeffSeparated[2]+constant1;
		numeratorImage=-coeffSeparated[3]+constant2;
		firstRoot[0]=(numeratorReal*denumeratorReal+numeratorImage*denumeratorImage)
				/(denumeratorReal*denumeratorReal+denumeratorImage*denumeratorImage);
		firstRoot[1]=(denumeratorReal*numeratorImage-denumeratorImage*numeratorReal)
				/(denumeratorReal*denumeratorReal+denumeratorImage*denumeratorImage);

		numeratorReal=-coeffSeparated[2]-constant1;
		numeratorImage=-coeffSeparated[3]-constant2;
		secondRoot[0]=(numeratorReal*denumeratorReal+numeratorImage*denumeratorImage)
				/(denumeratorReal*denumeratorReal+denumeratorImage*denumeratorImage);
		secondRoot[1]=(denumeratorReal*numeratorImage-denumeratorImage*numeratorReal)
				/(denumeratorReal*denumeratorReal+denumeratorImage*denumeratorImage);
	}
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

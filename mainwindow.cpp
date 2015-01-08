#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include "quadraticoperation.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setFixedSize(size());
	ui->actionSave->setEnabled(false);
	ui->pushButton_2->setEnabled(false);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pushButton_clicked()
{
	QStringList coefficients=ui->lineEdit->text().split(QRegExp("\\s"),QString::SkipEmptyParts);
	ui->label->setText("First root: ");
	ui->label_2->setText("Second root: ");
	if(ui->lineEdit->text().contains(QRegExp("[^0-9\\.\\si+-]")) or checkValidity(coefficients))
	{
		ui->statusBar->showMessage("Syntax error");
		ui->actionSave->setEnabled(false);
		ui->pushButton_2->setEnabled(false);
		return;
	}
	if (coefficients.size()!=3)
	{
		ui->statusBar->showMessage("Not quadratic");
		ui->actionSave->setEnabled(false);
		ui->pushButton_2->setEnabled(false);
		return;
	}
	data=ui->lineEdit->text();
	QuadraticOperation quadratic(coefficients);
	qreal* result;
	if (quadratic.getError())
	{
		ui->statusBar->showMessage("Not quadratic");
		ui->actionSave->setEnabled(false);
		ui->pushButton_2->setEnabled(false);
		return;
	}
	ui->statusBar->clearMessage();
	ui->actionSave->setEnabled(true);
	ui->pushButton_2->setEnabled(true);


	result=quadratic.getResult();
	firstRoot[0]=result[0];
	firstRoot[1]=result[1];
	secondRoot[0]=result[2];
	secondRoot[1]=result[3];
	QString firstRootString,secondRootString;
	firstRootString=QString("First root: ");
	secondRootString=QString("Second root: ");
	if(firstRoot[0]!=0)
		firstRootString+=QString("%1").arg(firstRoot[0],0,'g',5);
	if(firstRoot[0]!=0 and firstRoot[1]>0)
		firstRootString+=QString("+");
	if(firstRoot[1]!=0)
		firstRootString+=QString("%1i").arg(firstRoot[1],0,'g',5);
	if(firstRootString.endsWith(": "))
		firstRootString+=QString("0");


	if(secondRoot[0]!=0)
		secondRootString+=QString("%1").arg(secondRoot[0],0,'g',5);
	if(secondRoot[0]!=0 and secondRoot[1]>0)
		secondRootString+=QString("+");
	if(secondRoot[1]!=0)
		secondRootString+=QString("%1i").arg(secondRoot[1],0,'g',5);
	if(secondRootString.endsWith(": "))
		secondRootString+=QString("0");
	ui->label->setText(firstRootString);
	ui->label_2->setText(secondRootString);
}


bool MainWindow::checkValidity(QStringList list)
{
	QRegExp rex(".*[+-]{2,}.*|.*[+-]$|.*\\..*\\..*|.*i.*i.*");
	for(int i=0;i<list.size();i++)
	{
		if(rex.exactMatch(list[i]))
			return true;
	}
	return false;
}

void MainWindow::on_actionOpen_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(0, "Open File", "", "");
	if(fileName.isEmpty())
	{
		ui->statusBar->showMessage("No filename specified");
		return;
	}
	QFile file(fileName);
	if(!file.exists())
	{
		ui->statusBar->showMessage("File not found");
		return;
	}
	if(!file.open(QIODevice::ReadOnly))
	{
		ui->statusBar->showMessage("Could not read file");
		return;
	}
	ui->statusBar->showMessage("File opened");
	QTextStream in(&file);
	Dialog *displayFile=new Dialog(this);
	displayFile->show();
	while(!in.atEnd())
	{
		QString fileLine=file.readLine();
		QStringList lineParts=fileLine.split("\t");
		QStringList coefficients=lineParts[0].split(QRegExp("\\s"),QString::SkipEmptyParts);
		if(lineParts[0].contains(QRegExp("[^0-9\\.\\si+-]")) or checkValidity(coefficients))
		{
			displayFile->addLine(lineParts[0],"Syntax error");
			continue;
		}
		if (coefficients.size()!=3)
		{
			displayFile->addLine(lineParts[0],"Not quadratic");
			continue;
		}
		QuadraticOperation quadratic(coefficients);
		if (quadratic.getError())
		{
			displayFile->addLine(lineParts[0],"Not quadratic");
			continue;
		}
		qreal* result;
		result=quadratic.getResult();

		firstRoot[0]=result[0];
		firstRoot[1]=result[1];
		secondRoot[0]=result[2];
		secondRoot[1]=result[3];
		QString roots;

		if(firstRoot[0]!=0)
			roots=QString("%1").arg(firstRoot[0],0,'g',5);
		if(firstRoot[0]!=0 and firstRoot[1]>0)
			roots+=QString("+");
		if(firstRoot[1]!=0)
			roots+=QString("%1i").arg(firstRoot[1],0,'g',5);
		if(!roots.isEmpty())
			roots+=QString("; ");
		else
			roots+=QString("0; ");
		if(secondRoot[0]!=0)
			roots+=QString("%1").arg(secondRoot[0],0,'g',5);
		if(secondRoot[0]!=0 and secondRoot[1]>0)
			roots+=QString("+");
		if(secondRoot[1]!=0)
			roots+=QString("%1i").arg(secondRoot[1],0,'g',5);
		if(roots.endsWith("; "))
			roots+=QString("0");
		displayFile->addLine(lineParts[0],roots);

	}
	file.close();
}

void MainWindow::on_actionSave_triggered()
{
	QString fileName = QFileDialog::getSaveFileName(0, "Save File", "", "");
	if(fileName.isEmpty())
	{
		ui->statusBar->showMessage("No filename specified");
		return;
	}
	QFile savefile(fileName);
	if(!savefile.open(QIODevice::WriteOnly))
	{
		ui->statusBar->showMessage("Could not save file");
		return;
	}
	QTextStream out(&savefile);

	QString roots;

	if(firstRoot[0]!=0)
		roots=QString("%1").arg(firstRoot[0],0,'g',5);
	if(firstRoot[0]!=0 and firstRoot[1]>0)
		roots+=QString("+");
	if(firstRoot[1]!=0)
		roots+=QString("%1i").arg(firstRoot[1],0,'g',5);
	if(!roots.isEmpty())
		roots+=QString("; ");
	else
		roots+=QString("0; ");
	if(secondRoot[0]!=0)
		roots+=QString("%1").arg(secondRoot[0],0,'g',5);
	if(secondRoot[0]!=0 and secondRoot[1]>0)
		roots+=QString("+");
	if(secondRoot[1]!=0)
		roots+=QString("%1i").arg(secondRoot[1],0,'g',5);
	if(roots.endsWith("; "))
		roots+=QString("0");
	out<<data<<"\t"<<roots<<"\n";
	ui->statusBar->showMessage("File saved");

	savefile.close();
}

void MainWindow::on_pushButton_2_clicked()
{
	QString fileName = QFileDialog::getSaveFileName(0, "Save File", "", "", 0,QFileDialog::DontConfirmOverwrite);
	if(fileName.isEmpty())
	{
		ui->statusBar->showMessage("No filename specified");
		return;
	}
	QFile savefile(fileName);
	if(!savefile.open(QIODevice::Append))
	{
		ui->statusBar->showMessage("Could not append to file");
		return;
	}
	QTextStream out(&savefile);
	QString roots;

	if(firstRoot[0]!=0)
		roots=QString("%1").arg(firstRoot[0],0,'g',5);
	if(firstRoot[0]!=0 and firstRoot[1]>0)
		roots+=QString("+");
	if(firstRoot[1]!=0)
		roots+=QString("%1i").arg(firstRoot[1],0,'g',5);
	if(!roots.isEmpty())
		roots+=QString("; ");
	else
		roots+=QString("0; ");
	if(secondRoot[0]!=0)
		roots+=QString("%1").arg(secondRoot[0],0,'g',5);
	if(secondRoot[0]!=0 and secondRoot[1]>0)
		roots+=QString("+");
	if(secondRoot[1]!=0)
		roots+=QString("%1i").arg(secondRoot[1],0,'g',5);
	if(roots.endsWith("; "))
		roots+=QString("0");

	out<<data<<"\t"<<roots<<"\n";
	ui->statusBar->showMessage("Added to file");
	savefile.close();
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_pushButton_clicked();

	void on_actionOpen_triggered();

	void on_actionSave_triggered();

	void on_pushButton_2_clicked();

private:
	Ui::MainWindow *ui;
	qreal firstRoot[2],secondRoot[2];
	bool checkValidity(QStringList);
	QString data;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
	Ui::MainWindow *ui;
	qreal x1[2],x2[2];
	QList<qreal> parseList(QStringList);
	void solve(QList<qreal>);
	bool chck(QStringList);
};

#endif // MAINWINDOW_H

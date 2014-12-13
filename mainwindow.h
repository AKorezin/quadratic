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
	qreal x1,x2;
	QList<qreal> parseList(QStringList);
	void solve(QList<qreal>);
};

#endif // MAINWINDOW_H

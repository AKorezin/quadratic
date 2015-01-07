#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
	Q_OBJECT

public:
	explicit Dialog(QWidget *parent = 0);
	~Dialog();
	void addLine(QString,QString);
private:
	Ui::Dialog *ui;

	void resizeEvent(QResizeEvent *);
};

#endif // DIALOG_H

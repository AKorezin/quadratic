#ifndef QUADRATICOPERATION_H
#define QUADRATICOPERATION_H
#include <QStringList>

class QuadraticOperation
{
public:
	QuadraticOperation(QStringList coeffList);
	~QuadraticOperation();
	qreal* getResult();
private:
	qreal* result;
	QList<qreal> coeffSeparated;
	qreal* solve();
	QList<qreal> parseList(QStringList coeffList);

};

#endif // QUADRATICOPERATION_H

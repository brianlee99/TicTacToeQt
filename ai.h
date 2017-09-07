#ifndef AI_H
#define AI_H

#include <QObject>

class ai : public QObject
{
    Q_OBJECT
public:
    explicit ai(QObject *parent = nullptr);
    int computeBestMove();
signals:

public slots:
};

#endif // AI_H

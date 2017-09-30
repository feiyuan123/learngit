#ifndef first_H
#define first_H

#include <QtCore/QObject>

class first : public QObject
{
    Q_OBJECT

public:
    first();
    virtual ~first();

private slots:
    void output();
};

#endif // first_H

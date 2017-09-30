#include "first.h"

#include <QTimer>
#include <iostream>

first::first()
{
    QTimer* timer = new QTimer(this);
    connect( timer, SIGNAL(timeout()), SLOT(output()) );
    timer->start( 1000 );
}

first::~first()
{}

void first::output()
{
    std::cout << "Hello World!" << std::endl;
}

#include "first.moc"

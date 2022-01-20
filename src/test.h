#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QtTest/QtTest>
class Test: public QObject
{
    Q_OBJECT
private slots:

void test_value();
void test_record();
void initTestCase();


};

#endif // TEST_H

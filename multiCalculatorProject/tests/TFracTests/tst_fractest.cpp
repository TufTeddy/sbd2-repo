#include <QtTest>
#include "tfrac.h"

class fractest : public QObject
{
    Q_OBJECT

public:
    fractest();
    ~fractest();

private slots:
    void constructor_data();
    void stringConstructor_data();
    void summ_data();
    void substract_data();
    void mult_data();
    void divide_data();
    void getNumberAsString_data();

    void constructor();
    void stringConstructor();
    void summ();
    void substract();
    void mult();
    void divide();
    void getNumberAsString();
};

fractest::fractest()
{

}

fractest::~fractest()
{

}

void fractest::constructor_data()
{
    QTest::addColumn<int>("num");
    QTest::addColumn<int>("den");
    QTest::addColumn<int>("numAns");
    QTest::addColumn<int>("denAns");

    //QTest::newRow("constructor") << 0 << 0 << 0 << 0;
    QTest::newRow("constructor") << 0 << 5 << 0 << 5;
    QTest::newRow("constructor") << 5 << 10 << 5 << 10;
    QTest::newRow("constructor") << 3 << 5 << 3 << 5;
    QTest::newRow("constructor") << -5 << 7 << -5 << 7;
    QTest::newRow("constructor") << 5 << -7 << 5 << -7;
}

void fractest::stringConstructor_data()
{
    QTest::addColumn<QString>("frac");
    QTest::addColumn<int>("numAns");
    QTest::addColumn<int>("denAns");

    //QTest::newRow("constructorString") << "0/0" << 0 << 0;
    QTest::newRow("constructorString") << "0/5" << 0 << 5;
    QTest::newRow("constructorString") << "5/10" << 5 << 10;
    QTest::newRow("constructorString") << "3/5" << 3 << 5;
    QTest::newRow("constructorString") << "-5/7" << -5 << 7;
    QTest::newRow("constructorString") << "5/-7" << 5 << -7;
}

void fractest::summ_data()
{
    QTest::addColumn<QString>("summFirstArg");
    QTest::addColumn<QString>("summSecondArg");
    QTest::addColumn<QString>("answer");

    //QTest::newRow("summ") << "0/0" << "0/0" << "nan";
    QTest::newRow("summ") << "3/5" << "0/1" << "3/5";
    QTest::newRow("summ") << "-4/11" << "-4/11" << "-8/11";
    QTest::newRow("summ") << "5/6" << "1/6" << "1/1";
}

void fractest::substract_data()
{
    QTest::addColumn<QString>("subFirstArg");
    QTest::addColumn<QString>("subSecondArg");
    QTest::addColumn<QString>("answer");

    //QTest::newRow("sub") << "0/0" << "0/0" << "nan";
    QTest::newRow("sub") << "3/5" << "0/1" << "3/5";
    QTest::newRow("sub") << "-4/11" << "-4/11" << "0/1";
    QTest::newRow("sub") << "5/6" << "1/6" << "2/3";
    QTest::newRow("sub") << "3/4" << "-1/6" << "11/12";
}

void fractest::mult_data()
{
    QTest::addColumn<QString>("multFirstArg");
    QTest::addColumn<QString>("multSecondArg");
    QTest::addColumn<QString>("answer");

    //QTest::newRow("mult") << "0/0" << "0/0" << "nan";
    QTest::newRow("mult") << "3/5" << "0/1" << "0/1";
    QTest::newRow("mult") << "-4/11" << "-4/11" << "16/121";
    QTest::newRow("mult") << "5/6" << "1/6" << "5/36";
    QTest::newRow("mult") << "2/4" << "4/2" << "1/1";
}

void fractest::divide_data()
{
    QTest::addColumn<QString>("divFirstArg");
    QTest::addColumn<QString>("divSecondArg");
    QTest::addColumn<QString>("answer");

    //QTest::newRow("div") << "0/0" << "0/0" << "nan";
    //QTest::newRow("div") << "3/5" << "0/1" << "nan";
    QTest::newRow("div") << "-4/11" << "-4/11" << "1/1";
    QTest::newRow("div") << "5/6" << "1/6" << "5/1";
    QTest::newRow("div") << "2/4" << "4/2" << "1/4";
}

void fractest::getNumberAsString_data()
{
    QTest::addColumn<int>("num");
    QTest::addColumn<int>("den");
    QTest::addColumn<QString>("answer");

    //QTest::newRow("constructor") << 0 << 0 << "nan";
    QTest::newRow("constructor") << 0 << 5 << "0/5";
    QTest::newRow("constructor") << 5 << 10 << "5/10";
    QTest::newRow("constructor") << 3 << 5 << "3/5";
    QTest::newRow("constructor") << -5 << 7 << "-5/7";
    QTest::newRow("constructor") << 5 << -7 << "5/-7";
}

void fractest::constructor()
{
    QFETCH(int, num);
    QFETCH(int, den);
    QFETCH(int, numAns);
    QFETCH(int, denAns);


    TANumber *obj = new TFrac(num, den);
    QCOMPARE(dynamic_cast<TFrac*>(obj)->getNumerator(), numAns);
    QCOMPARE(dynamic_cast<TFrac*>(obj)->getDenominator(), denAns);
}

void fractest::stringConstructor()
{
    QFETCH(QString, frac);
    QFETCH(int, numAns);
    QFETCH(int, denAns);

    TANumber *obj = new TFrac(frac.toStdString());
    QCOMPARE(dynamic_cast<TFrac*>(obj)->getNumerator(), numAns);
    QCOMPARE(dynamic_cast<TFrac*>(obj)->getDenominator(), denAns);
}

void fractest::summ()
{
    QFETCH(QString, summFirstArg);
    QFETCH(QString, summSecondArg);
    QFETCH(QString, answer);

    TANumber * first = new TFrac(summFirstArg.toStdString());
    TANumber * second = new TFrac(summSecondArg.toStdString());
    first->summ(second->clone());

    QCOMPARE(QString::fromStdString(first->getNumberAsString()), answer);
}

void fractest::substract()
{
    QFETCH(QString, subFirstArg);
    QFETCH(QString, subSecondArg);
    QFETCH(QString, answer);

    TANumber * first = new TFrac(subFirstArg.toStdString());
    TANumber * second = new TFrac(subSecondArg.toStdString());
    first->substract(second->clone());

    QCOMPARE(QString::fromStdString(first->getNumberAsString()), answer);
}

void fractest::mult()
{
    QFETCH(QString, multFirstArg);
    QFETCH(QString, multSecondArg);
    QFETCH(QString, answer);

    TANumber * first = new TFrac(multFirstArg.toStdString());
    TANumber * second = new TFrac(multSecondArg.toStdString());
    first->mult(second->clone());

    QCOMPARE(QString::fromStdString(first->getNumberAsString()), answer);
}

void fractest::divide()
{
    QFETCH(QString, divFirstArg);
    QFETCH(QString, divSecondArg);
    QFETCH(QString, answer);

    TANumber * first = new TFrac(divFirstArg.toStdString());
    TANumber * second = new TFrac(divSecondArg.toStdString());
    first->divide(second->clone());

    QCOMPARE(QString::fromStdString(first->getNumberAsString()), answer);
}

void fractest::getNumberAsString()
{
    QFETCH(int, num);
    QFETCH(int, den);
    QFETCH(QString, answer);

    TANumber *obj = new TFrac(num, den);
    QCOMPARE(QString::fromStdString(obj->getNumberAsString()), answer);
}

QTEST_APPLESS_MAIN(fractest)

#include "tst_fractest.moc"

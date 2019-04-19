#include <QtTest>
#include "tcomplex.h"


class tcomplextest : public QObject
{
    Q_OBJECT

public:
    tcomplextest();
    ~tcomplextest();

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

tcomplextest::tcomplextest()
{

}

tcomplextest::~tcomplextest()
{

}

void tcomplextest::constructor_data()
{
    QTest::addColumn<double>("argReal");
    QTest::addColumn<double>("resultReal");
    QTest::addColumn<double>("argIm");
    QTest::addColumn<double>("resultIm");

    QTest::newRow("constructor") << 0.0 << 0.0 << 0.0 << 0.0;
    QTest::newRow("constructor") << -2.0 << -2.0 << 4.0 << 4.0;
}

void tcomplextest::stringConstructor_data()
{
    QTest::addColumn<QString>("arg");
    QTest::addColumn<QString>("resultReal");
    QTest::addColumn<QString>("resultIm");

    QTest::newRow("stringConstructor") << "0+i*0 " << "0.000000" << "0.000000";
    QTest::newRow("stringConstructor") << "-2+i*4 " << "-2.000000" << "4.000000";
    QTest::newRow("stringConstructor") << "10+i*5" << "10.000000" << "5.000000";
}

void tcomplextest::summ_data()
{
    QTest::addColumn<QString>("summFirstArg");
    QTest::addColumn<QString>("summSecondArg");
    QTest::addColumn<QString>("answer");

    QTest::newRow("summ") << "0.0+i*0.0" << "0.0+i*0.0" << "0 + i*0";
    QTest::newRow("summ") << "2+i*4" << "3-i*10" << "5 - i*6";
    QTest::newRow("summ") << "0+i*3" << "-4.3+i*2.5" << "-4.3 + i*5.5";
}

void tcomplextest::substract_data()
{
    QTest::addColumn<QString>("subFirstArg");
    QTest::addColumn<QString>("subSecondArg");
    QTest::addColumn<QString>("answer");

    QTest::newRow("sub") << "0.0+i*0.0" << "0.0+i*0.0" << "0 + i*0";
    QTest::newRow("sub") << "2+i*4" << "3-i*10" << "-1 + i*14";
    QTest::newRow("sub") << "0+i*3" << "-4.3+i*2.5" << "4.3 + i*0.5";
}

void tcomplextest::mult_data()
{
    QTest::addColumn<QString>("multFirstArg");
    QTest::addColumn<QString>("multSecondArg");
    QTest::addColumn<QString>("answer");

    QTest::newRow("mult") << "0.0+i*0.0" << "0.0+i*0.0" << "0 + i*0";
    QTest::newRow("mult") << "2+i*4" << "3-i*10" << "46 - i*8";
    QTest::newRow("mult") << "0+i*3" << "-4.3+i*2.5" << "-7.5 - i*12.9";
}

void tcomplextest::divide_data()
{
    QTest::addColumn<QString>("divFirstArg");
    QTest::addColumn<QString>("divSecondArg");
    QTest::addColumn<QString>("answer");

    QTest::newRow("div") << "0.0+i*0.0" << "0.0+i*0.0" << "0 + i*0";
    QTest::newRow("div") << "2+i*4" << "3-i*10" << "-0.311926 - i*0.293577";
    QTest::newRow("div") << "0+i*3" << "-4.3+i*2.5" << "0.303152 - i*0.521422";
}

void tcomplextest::getNumberAsString_data()
{
    QTest::addColumn<QString>("arg");
    QTest::addColumn<QString>("answer");

    QTest::newRow("getNumbAsString") << "0.0+i*0.0" << "0 + i*0";
    QTest::newRow("getNumbAsString") << "2+i*4" << "2 + i*4";
}

void tcomplextest::constructor()
{

    QFETCH(double, argReal);
    QFETCH(double, resultReal);
    QFETCH(double, argIm);
    QFETCH(double, resultIm);

    TANumber *first = new TComplex(argReal, argIm);
    QCOMPARE(dynamic_cast<TComplex*>(first)->getRealDouble(), resultReal);
    QCOMPARE(dynamic_cast<TComplex*>(first)->getImaginaryDouble(), resultIm);
}

void tcomplextest::stringConstructor()
{
    QFETCH(QString, arg);
    QFETCH(QString, resultReal);
    QFETCH(QString, resultIm);

    TANumber *first = new TComplex(arg.toStdString());
    QCOMPARE(QString::fromStdString(dynamic_cast<TComplex*>(first)->getRealStr()), resultReal);
    QCOMPARE(QString::fromStdString(dynamic_cast<TComplex*>(first)->getImaginaryStr()), resultIm);
}

void tcomplextest::getNumberAsString()
{
    QFETCH(QString, arg);
    QFETCH(QString, answer);

    TANumber *obj = new TComplex (arg.toStdString());
    QCOMPARE(QString::fromStdString(obj->getNumberAsString()), answer);
}
void tcomplextest::summ()
{

    QFETCH(QString, summFirstArg);
    QFETCH(QString, summSecondArg);
    QFETCH(QString, answer);

    TANumber* first = new TComplex(summFirstArg.toStdString());
    TANumber* second = new TComplex(summSecondArg.toStdString());
    first->summ(second->clone());

    QCOMPARE(QString::fromStdString(first->getNumberAsString()), answer);
}

void tcomplextest::substract()
{
    QFETCH(QString, subFirstArg);
    QFETCH(QString, subSecondArg);
    QFETCH(QString, answer);

    TANumber* first = new TComplex(subFirstArg.toStdString());
    TANumber* second = new TComplex(subSecondArg.toStdString());
    first->substract(second->clone());

    QCOMPARE(QString::fromStdString(first->getNumberAsString()), answer);

}

void tcomplextest::mult()
{
    QFETCH(QString, multFirstArg);
    QFETCH(QString, multSecondArg);
    QFETCH(QString, answer);

    TANumber* first = new TComplex(multFirstArg.toStdString());
    TANumber* second = new TComplex(multSecondArg.toStdString());
    first->mult(second->clone());

    QCOMPARE(QString::fromStdString(first->getNumberAsString()), answer);
}

void tcomplextest::divide()
{
    QFETCH(QString, divFirstArg);
    QFETCH(QString, divSecondArg);
    QFETCH(QString, answer);

    TANumber* first = new TComplex(divFirstArg.toStdString());
    TANumber* second = new TComplex(divSecondArg.toStdString());
    first->divide(second->clone());

    QCOMPARE(QString::fromStdString(first->getNumberAsString()), answer);
}

QTEST_APPLESS_MAIN(tcomplextest)

#include "tst_tcomplextest.moc"

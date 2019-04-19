#include <QtTest>
#include "tctrl.h"
#include "tfrac.h"

class ctrlrTest : public QObject
{
    Q_OBJECT

public:
    ctrlrTest();
    ~ctrlrTest();

private slots:
    void add_data();
    void add();

};

ctrlrTest::ctrlrTest()
{

}

ctrlrTest::~ctrlrTest()
{

}

void ctrlrTest::add_data()
{
    QTest::addColumn<QString>("summFirstArg");
    QTest::addColumn<QString>("summSecondArg");
    QTest::addColumn<QString>("answer");
    QTest::addColumn<QString>("answer2");

    //QTest::newRow("summ") << "0/0" << "0/0" << "nan";
    QTest::newRow("summ") << "3/5" << "0/1" << "3/5" << "0/1";
    QTest::newRow("summ") << "-4/11" << "-4/11" << "-8/11" << "32/121";
    QTest::newRow("summ") << "5/6" << "1/6" << "1/1" << "1/6";
}

void ctrlrTest::add()
{
    QFETCH(QString, summFirstArg);
    QFETCH(QString, summSecondArg);
    QFETCH(QString, answer);
    QFETCH(QString, answer2);

    TCtrl *controller = new TCtrl();
    TANumber *first = new TFrac(summFirstArg.toStdString());
    TANumber *second = new TFrac(summSecondArg.toStdString());
    controller->setOperation(TOprtn::Add, first->clone());

    QCOMPARE(QString::fromStdString(controller->doOperation(second->clone())), answer);

    controller->setOperation(TOprtn::Mul);

    QCOMPARE(QString::fromStdString(controller->doOperation(second->clone())), answer2);

}


QTEST_APPLESS_MAIN(ctrlrTest)

#include "tst_ctrlrtest.moc"

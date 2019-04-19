#include <QtTest>

// add necessary includes here

class ctrlrTest : public QObject
{
    Q_OBJECT

public:
    ctrlrTest();
    ~ctrlrTest();

private slots:
    void test_case1();

};

ctrlrTest::ctrlrTest()
{

}

ctrlrTest::~ctrlrTest()
{

}

void ctrlrTest::test_case1()
{

}

QTEST_APPLESS_MAIN(ctrlrTest)

#include "tst_ctrlrtest.moc"

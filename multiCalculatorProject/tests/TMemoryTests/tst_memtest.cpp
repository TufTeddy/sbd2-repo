#include <QtTest>

// add necessary includes here

class memTest : public QObject
{
    Q_OBJECT

public:
    memTest();
    ~memTest();

private slots:
    void test_case1();

};

memTest::memTest()
{

}

memTest::~memTest()
{

}

void memTest::test_case1()
{

}

QTEST_APPLESS_MAIN(memTest)

#include "tst_memtest.moc"

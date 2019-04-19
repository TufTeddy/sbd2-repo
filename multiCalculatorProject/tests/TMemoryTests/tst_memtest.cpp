#include <QtTest>
#include "tmemory.h"
#include "tfrac.h"

class memTest : public QObject
{
    Q_OBJECT

public:
    memTest();
    ~memTest();

private slots:
    void write_data();
    void clear_data();

    void write();
    void clear();
};

memTest::memTest()
{

}

memTest::~memTest()
{

}

void memTest::write_data()
{
    QTest::addColumn<QString>("first");
    QTest::addColumn<bool>("answerState");
    QTest::addColumn<QString>("answerNumber");

    QTest::addRow("write")<< "5/10" << true << "5/10";
}

void memTest::clear_data()
{
    QTest::addColumn<QString>("first");
    QTest::addColumn<bool>("answerState");
    QTest::addColumn<QString>("answerNumber");

    QTest::addRow("clear") << "3" << false << "3/1";
}

void memTest::write()
{
    QFETCH(QString, first);
    QFETCH(bool, answerState);
    QFETCH(QString, answerNumber);
    TANumber * obj = new TFrac(first.toStdString());
    TMemory * memory = new TMemory();
    memory->write(obj->clone());

    std::shared_ptr<TANumber> obj2 = memory->getFNumber()->clone();

    QCOMPARE(QString::fromStdString(obj2->getNumberAsString()),
             answerNumber);
    QCOMPARE(memory->getState(), answerState);
}

void memTest::clear()
{
    QFETCH(QString, first);
    QFETCH(bool, answerState);
    QFETCH(QString, answerNumber);
    TANumber * obj = new TFrac(first.toStdString());
    TMemory * memory = new TMemory();
    memory->write(obj->clone());
    memory->clear();

    QCOMPARE(QString::fromStdString(memory->getFNumber().get()->getNumberAsString()),
             answerNumber);
    QCOMPARE(memory->getState(), answerState);
}

QTEST_APPLESS_MAIN(memTest)

#include "tst_memtest.moc"

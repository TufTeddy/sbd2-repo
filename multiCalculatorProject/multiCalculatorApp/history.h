#ifndef HISTORY_H
#define HISTORY_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QScrollArea>
#include <QFrame>

class History : public QWidget
{
    Q_OBJECT
public:
    explicit History(QWidget *parent = nullptr);
    void addRecord(QString historyRecord);
signals:

public slots:
    void clearHistory();

private:
    void remove(QLayout* layout);
    void prepareView();
    QPushButton *clearButton;
    QScrollArea * scrollArea;
    QFrame *inner;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *wholeLayout;
    QVBoxLayout *recordsLayout;
    QVector<QLabel*> vectorOfLabels;
    int numberOfRecords;
};

#endif // HISTORY_H

#include "history.h"

History::History(QWidget *parent) : QWidget(parent)
{
    prepareView();
    QObject::connect(clearButton, &QPushButton::clicked, this, &History::clearHistory);
}

void History::addRecord(QString historyRecord)
{
    QLabel *temp = new QLabel(historyRecord);
    vectorOfLabels.push_back(temp);
    inner->layout()->addWidget(temp);
}

void History::clearHistory()
{
    vectorOfLabels.clear();
    remove(recordsLayout);
}

void History::remove(QLayout* layout)
{
    QLayoutItem* child;
    while(layout->count()!=0)
    {
        child = layout->takeAt(0);
        if(child->layout() != nullptr)
        {
            remove(child->layout());
        }
        else if(child->widget() != nullptr)
        {
            delete child->widget();
        }
        delete child;
    }
}

void History::prepareView()
{
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    setFixedSize(250, 250);

    clearButton = new QPushButton("Clear history");
    buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(clearButton);
    recordsLayout = new QVBoxLayout();
    scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setLayout(recordsLayout);
    inner = new QFrame(scrollArea);
    inner->setLayout(recordsLayout);
    scrollArea->setWidget(inner);

    wholeLayout = new QVBoxLayout();
    wholeLayout->addLayout(buttonLayout);
    wholeLayout->addWidget(scrollArea);

    this->setLayout(wholeLayout);
}

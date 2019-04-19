#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ctrlunit = new TCtrl();
    historyObject = new History();
    setViewOfMainWindow();
    checkButtonsToBase();
    setCurrentValidator();
    complexModButtonPushed();
    memoryLabel->hide();
}

MainWindow::~MainWindow()
{
    delete ctrlunit;
    delete historyObject;
    delete _number;
}

void MainWindow::showHistory()
{
    historyObject->show();
}

void MainWindow::digitButtonPushed(QString digitString)
{
    std::string temp = entryLineEdit->text().toStdString();
    std::string firstPart, secondPart;
    if(mode == calcMode::complex){
        size_t pos = temp.find('+');
        firstPart = temp.substr(0, pos);
        pos = temp.find('*');
        secondPart = temp.substr(pos+1, temp.size()-1);
        if(!lrComplex){
            if(firstPart[0] == '0' && firstPart[1] != '.')
                firstPart = digitString.toStdString();
            else {
                firstPart += digitString.toStdString();
            }

        }else{
            if(secondPart[0] == '0' && secondPart[1] != '.')
                secondPart = digitString.toStdString();
            else {
                secondPart += digitString.toStdString();
            }
        }
        entryLineEdit->setText(QString::fromStdString(firstPart+"+i*"+secondPart));
    }else if (mode==calcMode::pnumber){
        temp = entryLineEdit->text().toStdString();
        if(temp[0] == '0' && temp[1] != '.'){
            temp = digitString.toStdString();
        }
        else
            temp += digitString.toStdString();

        entryLineEdit->setText(QString::fromStdString(temp));
    } else if (mode == calcMode::frac){
        size_t pos = temp.find('/');
        firstPart = temp.substr(0, pos);
        secondPart = temp.substr(pos+1, temp.size()-1);
        if (!lrFrac){
            if(firstPart[0] == '0')
                firstPart = digitString.toStdString();
            else {
                firstPart += digitString.toStdString();
            }
        } else {
            if(secondPart[0] == '0')
                secondPart = digitString.toStdString();
            else {
                secondPart += digitString.toStdString();
            }
        }
        entryLineEdit->setText(QString::fromStdString(firstPart+"/"+secondPart));
    }
}

void MainWindow::complexModButtonPushed()
{
    _number = nullptr;
    _number = new TComplex();

    mode = calcMode::complex;
    pBaseSlider->hide();
    currentBaseLabel->hide();
    setCurrentBase(numbersInt::A);
    checkButtonsToBase();
    setCurrentValidator();

    dotButton->setEnabled(true);
    fracPartButton->setEnabled(false);
    complexPartButton->setEnabled(true);
    entryLineEdit->setText("0+i*0");
}

void MainWindow::pnumberModButtonPushed()
{
    _number = nullptr;
    _number = new TPNumber();

    mode = calcMode::pnumber;
    checkButtonsToBase();
    pBaseSlider->show();
    currentBaseLabel->show();
    setCurrentValidator();
    setCurrentBase(numbersInt::A);
    dotButton->setEnabled(true);
    fracPartButton->setEnabled(false);
    complexPartButton->setEnabled(false);

    entryLineEdit->setText("0");
}

void MainWindow::fracModButtonPushed()
{
    _number = nullptr;
    _number = new TFrac();

    ctrlunit->clear();
    mode = calcMode::frac;
    pBaseSlider->hide();
    currentBaseLabel->hide();
    setCurrentBase(numbersInt::A);
    checkButtonsToBase();
    setCurrentValidator();

    dotButton->setEnabled(false);
    fracPartButton->setEnabled(true);
    complexPartButton->setEnabled(false);

    entryLineEdit->setText("0/1");
}

void MainWindow::setViewOfSlider()
{
    pBaseSlider = new QSlider(Qt::Orientation::Horizontal);
    pBaseSlider->setMinimum(numbersInt::two);
    pBaseSlider->setMaximum(numbersInt::sixteen);
    pBaseSlider->setSliderPosition(numbersInt::A);
    pBaseSlider->setTickInterval(numbersInt::one);
    pBaseSlider->setTickPosition(QSlider::TicksBelow);
    pBaseSlider->hide();
    currentBaseLabel = new QLabel();
    currentBaseLabel->setText(QStringLiteral("Curr base: %1").arg(_currentBase));
    currentBaseLabel->hide();
    QObject::connect(pBaseSlider, &QSlider::valueChanged,
                     this, &MainWindow::sliderEventSlot);
}

void MainWindow::sliderEventSlot(int base)
{
    currentBaseLabel->setText(QStringLiteral("Curr base: %1").arg(base));
    setCurrentBase(base);
    transformPnumber();
    setCurrentBaseToOperate(base);
    setCurrentValidator();
    checkButtonsToBase();
}

void MainWindow::checkButtonsToBase()
{
    for (auto it : vectorOfButtons){
        it->setEnabled(false);
    }
    for (int i = 0; i < _currentBase; ++i)
    {
        vectorOfButtons[i]->setEnabled(true);
    }
}

void MainWindow::plusButtonPushed()
{
    if(ctrlunit->getCurState() == TCtrl::cOprtnChange){
        ctrlunit->setOperation(TOprtn::Add);
        return;
    }

    TANumber * tempObj = nullptr;
    if (mode == calcMode::complex){
        tempObj = new TComplex(entryLineEdit->text().toStdString());
        _number = tempObj;
        entryLineEdit->setText("0+i*0");
    }else if (mode == calcMode::frac){
        tempObj = new TFrac(entryLineEdit->text().toStdString());
        _number = tempObj;
        entryLineEdit->setText("0/1");
    }else if (mode == calcMode::pnumber) {
        tempObj = new TPNumber(entryLineEdit->text().toStdString(), QString::number(_currentBaseToOperate).toStdString());
        _number = tempObj;
        entryLineEdit->setText("0");
    }

    ctrlunit->setOperation(TOprtn::Add, std::shared_ptr<TANumber>(_number));
}

void MainWindow::minusButtonPushed()
{
    if(ctrlunit->getCurState() == TCtrl::cOprtnChange){
        ctrlunit->setOperation(TOprtn::Sub);
        return;
    }
    TANumber * tempObj = nullptr;
    if (mode == calcMode::complex){
        tempObj = new TComplex(entryLineEdit->text().toStdString());
        _number = tempObj;
        entryLineEdit->setText("0+i*0");
    }else if (mode == calcMode::frac){
        tempObj = new TFrac(entryLineEdit->text().toStdString());
        _number = tempObj;
        entryLineEdit->setText("0/1");
    }else if (mode == calcMode::pnumber) {
        tempObj = new TPNumber(entryLineEdit->text().toStdString(), QString::number(_currentBaseToOperate).toStdString());
        _number = tempObj;
        entryLineEdit->setText("0");
    }

    ctrlunit->setOperation(TOprtn::Sub, std::shared_ptr<TANumber>(_number));
}

void MainWindow::mulButtonPushed()
{
    if(ctrlunit->getCurState() == TCtrl::cOprtnChange){
        ctrlunit->setOperation(TOprtn::Mul);
        return;
    }
    TANumber * tempObj = nullptr;
    if (mode == calcMode::complex){
        tempObj = new TComplex(entryLineEdit->text().toStdString());
        _number = tempObj;
        entryLineEdit->setText("0+i*0");
    }else if (mode == calcMode::frac){
        tempObj = new TFrac(entryLineEdit->text().toStdString());
        _number = tempObj;
        entryLineEdit->setText("0/1");
    }else if (mode == calcMode::pnumber) {
        tempObj = new TPNumber(entryLineEdit->text().toStdString(), QString::number(_currentBaseToOperate).toStdString());
        _number = tempObj;
        entryLineEdit->setText("0");
    }

    ctrlunit->setOperation(TOprtn::Mul, std::shared_ptr<TANumber>(_number));
}

void MainWindow::divButtonPushed()
{
    if(ctrlunit->getCurState() == TCtrl::cOprtnChange){
        ctrlunit->setOperation(TOprtn::Dvd);
        return;
    }
    TANumber * tempObj = nullptr;
    if (mode == calcMode::complex){
        tempObj = new TComplex(entryLineEdit->text().toStdString());
        _number = tempObj;
        entryLineEdit->setText("0+i*0");
    }else if (mode == calcMode::frac){
        tempObj = new TFrac(entryLineEdit->text().toStdString());
        _number = tempObj;
        entryLineEdit->setText("0/1");
    }else if (mode == calcMode::pnumber) {
        tempObj = new TPNumber(entryLineEdit->text().toStdString(), QString::number(_currentBaseToOperate).toStdString());
        _number = tempObj;
        entryLineEdit->setText("0");
    }

    ctrlunit->setOperation(TOprtn::Dvd, std::shared_ptr<TANumber>(_number));
}

void MainWindow::resultButtonPushed()
{    
    try {
        if(ctrlunit->getCurState() == ctrlunit->cStart) return;
        toHistoryString = "";
        TANumber * tempObj = nullptr;
        if (mode == calcMode::complex){
            tempObj = new TComplex(entryLineEdit->text().toStdString());
            _number = tempObj;
            entryLineEdit->setText("0+i*0");
        }else if (mode == calcMode::frac){
            tempObj = new TFrac(entryLineEdit->text().toStdString());
            _number = tempObj;
            entryLineEdit->setText("0/1");
        }else if (mode == calcMode::pnumber) {
            tempObj = new TPNumber(entryLineEdit->text().toStdString(), QString::number(_currentBaseToOperate).toStdString());
            _number = tempObj;
            entryLineEdit->setText("0");
        }

        entryLineEdit->setText(QString::fromStdString(ctrlunit->doOperation(_number->clone())));
        historyObject->addRecord(QString::fromStdString(ctrlunit->getLastActionAsString()));
    } catch (std::exception *exptn) {
        QMessageBox::warning(this, "Warning", exptn->what());
        return;
    }
}

void MainWindow::changeModeComplex()
{
    if(lrComplex) {
        lrComplex = false;
        complexPartButton->setText("_ | i ");
    }else {
        lrComplex = true;
        complexPartButton->setText("  | i_");
    }
}

void MainWindow::changeModeFrac()
{
    if(lrFrac) {
        lrFrac = false;
        fracPartButton->setText("_ / ");
    }else {
        lrFrac = true;
        fracPartButton->setText("  /_");
    }
}

void MainWindow::memoryLoad()
{
    std::shared_ptr<TANumber> numberqe = ctrlunit->loadMem();
    entryLineEdit->setText(QString::fromStdString(numberqe->getNumberAsString()));
}

void MainWindow::memorySave()
{
    TANumber * tempObj = nullptr;
    if (mode == calcMode::complex){
        tempObj = new TComplex(entryLineEdit->text().toStdString());
    }else if (mode == calcMode::frac){
        tempObj = new TFrac(entryLineEdit->text().toStdString());
    }else if (mode == calcMode::pnumber) {
        tempObj = new TPNumber(entryLineEdit->text().toStdString(), QString::number(_currentBaseToOperate).toStdString());
    }
    _number = tempObj;
    ctrlunit->setMem(_number->clone());
    memoryLabel->show();
}

void MainWindow::clearAll()
{
    ctrlunit->clear();
    memoryLabel->hide();
    if (mode == calcMode::complex){
        entryLineEdit->setText("0+i*0");
    }else if (mode == calcMode::frac){
        entryLineEdit->setText("0/1");
    }else if (mode == calcMode::pnumber) {
        entryLineEdit->setText("0");
    }
}

void MainWindow::clearEntry()
{
    if (mode == calcMode::complex){
        entryLineEdit->setText("0+i*0");
    }else if (mode == calcMode::frac){
        entryLineEdit->setText("0/1");
    }else if (mode == calcMode::pnumber) {
        entryLineEdit->setText("0");
    }
}

void MainWindow::transformPnumber()
{
    TANumber *temp = new TPNumber(entryLineEdit->text().toStdString(), QString::number(_currentBase).toStdString());
    _number = temp;
    dynamic_cast<TPNumber*>(_number)->setBase(_currentBaseToOperate);
    qDebug() << QString::fromStdString(temp->getNumberAsString()) << " "<<entryLineEdit->text();
    entryLineEdit->setText(QString::fromStdString(_number->getNumberAsString()));
    delete temp;
}

void MainWindow::dotButtonPushed()
{
    std::string temp = entryLineEdit->text().toStdString();
    std::string firstPart, secondPart;
    if(mode == calcMode::complex){
        size_t pos = temp.find('+');
        firstPart = temp.substr(0, pos);
        pos = temp.find('*');
        secondPart = temp.substr(pos+1, temp.size()-1);
        if(!lrComplex){
            if(firstPart.find('.') == std::string::npos){
                firstPart += ".";
            }
            }else{
                if(secondPart.find('.') == std::string::npos)
                    secondPart += ".";
            }
        entryLineEdit->setText(QString::fromStdString(firstPart+"+i*"+secondPart));
    }
    else if(mode == calcMode::pnumber){
        if(temp.find('.') == std::string::npos)
            temp.push_back('.');
        entryLineEdit->setText(QString::fromStdString(temp));
    }
}

void MainWindow::backSpaceButtonPushed()
{
    std::string temp = entryLineEdit->text().toStdString();
    std::string firstPart, secondPart;
    if(mode == calcMode::complex){
        size_t pos = temp.find('+');
        firstPart = temp.substr(0, pos);
        pos = temp.find('*');
        secondPart = temp.substr(pos+1, temp.size()-1);
        if(!lrComplex){
            if(firstPart[0] == '0' && firstPart[1] != '.')
                return;
            else if(firstPart.size() == 1)
                firstPart = "0";
            else {
                firstPart.pop_back();
            }

        }else{
            if(secondPart[0] == '0' && secondPart[1] != '.')
                return;
            else if(secondPart.size() == 1)
                secondPart = "0";
            else {
                secondPart.pop_back();
            }
        }
        entryLineEdit->setText(QString::fromStdString(firstPart+"+i*"+secondPart));
    }else if (mode==calcMode::pnumber){
        temp = entryLineEdit->text().toStdString();
        if(temp.size() == 1){
            temp = "0";
        }else
            temp.pop_back();
        entryLineEdit->setText(QString::fromStdString(temp));
    } else if (mode == calcMode::frac){
        size_t pos = temp.find('/');
        firstPart = temp.substr(0, pos);
        secondPart = temp.substr(pos+1, temp.size()-1);
        if (!lrFrac){
            if(firstPart[0] == '0' && firstPart[1] != '.')
                return;
            else if(firstPart.size() == 1)
                firstPart = "0";
            else {
                firstPart.pop_back();
            }
        } else {
            if(secondPart[0] == '0' && secondPart[1] != '.')
                return;
            else if(secondPart.size() == 1)
                secondPart = "1";
            else {
                secondPart.pop_back();
            }
        }
        entryLineEdit->setText(QString::fromStdString(firstPart+"/"+secondPart));
    }
}

int MainWindow::currentBaseToOperate() const
{
    return _currentBaseToOperate;
}

void MainWindow::setCurrentBaseToOperate(int currentBaseToOperate)
{
    _currentBaseToOperate = currentBaseToOperate;
}

void MainWindow::setCurrentValidator()
{
    if(mode == calcMode::pnumber){
        QString rxLineEditString = QString("^[0-%1]*\\.[0-%1]{7}$").arg(_currentBaseToOperate-1);
        if(_currentBaseToOperate > numbersInt::nine)
            rxLineEditString = QString("^([0-%1]*[A-%2]*)*\\.([0-%1]?[A-%2]?){7}$")
                    .arg(numbersInt::nine)
                    .arg(QString('A' + _currentBaseToOperate - numbersInt::B));
        qDebug() << rxLineEditString << endl;
        QRegExp rxLineEdit(rxLineEditString);
        validatorLineEdit = new QRegExpValidator(rxLineEdit, this);
        entryLineEdit->setValidator(validatorLineEdit);
    }else if (mode == calcMode::complex){
        QString rxLineEditString = QString("^[0-9]*\\.[0-9]*\\+\\i\\*[0-9]*\\.[0-9]*$");
        QRegExp rxLineEdit(rxLineEditString);
        validatorLineEdit = new QRegExpValidator(rxLineEdit, this);
        entryLineEdit->setValidator(validatorLineEdit);
    }else if(mode == calcMode::frac){
        QString rxLineEditString = QString("^[0-9]*\\s?/\\s?[0-9]*$");
        QRegExp rxLineEdit(rxLineEditString);
        validatorLineEdit = new QRegExpValidator(rxLineEdit, this);
        entryLineEdit->setValidator(validatorLineEdit);
    }
}

int MainWindow::currentBase() const
{
    return _currentBase;
}

void MainWindow::setCurrentBase(int currentBase)
{
    _currentBase = currentBase;
}
void MainWindow::setViewOfMainWindow()
{
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    wholeLayout = new QGridLayout();
    setViewOfMenu();
    setViewOfLineEdit();
    setViewOfMemoryBlock();
    setViewOfSlider();
    setViewOfOperationButtons();
    setViewOfDigitButtons();
    insertingInLayout();

    window = new QWidget();
    setCentralWidget(window);
    window->setLayout(wholeLayout);
}

void MainWindow::setViewOfMenu()
{
    menubar = new QMenuBar();
    menu = new QMenu("Menu");
    menu->addAction("History", this, &MainWindow::showHistory, Qt::CTRL + Qt::Key_M);
    menubar->addMenu(menu);
    menubar->setFixedHeight(30);
}

void MainWindow::setViewOfMemoryBlock()
{
    memoryLabel = new QLabel("M");
    memoryLabel->setFixedHeight(30);
    memoryLabel->setFixedWidth(60);
    memLoadButton = new QPushButton("ML");
    memLoadButton->setFixedHeight(30);
    memLoadButton->setFixedWidth(60);
    memSaveButton = new QPushButton("MS");
    memSaveButton->setFixedHeight(30);
    memSaveButton->setFixedWidth(60);

    QObject::connect(memLoadButton, &QPushButton::clicked, this, &MainWindow::memoryLoad);
    QObject::connect(memSaveButton, &QPushButton::clicked, this, &MainWindow::memorySave);
}

void MainWindow::setViewOfLineEdit()
{
    entryLineEdit = new QLineEdit();
    entryLineEdit->setFixedHeight(30);
}

void MainWindow::setViewOfDigitButtons()
{
    int c = 0;
    for(int i = 0; i < 16; ++i){
        if (c > numbersInt::nine){
            QPushButton *temp = new QPushButton(QString('A' + c - numbersInt::A));
            temp->setFixedHeight(30);
            temp->setFixedWidth(60);
            QObject::connect(temp, &QPushButton::clicked,[this, temp](){digitButtonPushed(temp->text());});
            vectorOfButtons.push_back(temp);
        }else{
            QPushButton *temp = new QPushButton(QString::number(numbersInt::zero+c));
            temp->setFixedHeight(30);
            temp->setFixedWidth(60);
            QObject::connect(temp, &QPushButton::clicked,[this, temp](){digitButtonPushed(temp->text());});
            vectorOfButtons.push_back(temp);
        }
        c++;
    }
}

void MainWindow::setViewOfOperationButtons()
{
    backSpaceButton = new QPushButton("BS");
    backSpaceButton->setFixedHeight(30);
    backSpaceButton->setFixedWidth(60);
    QObject::connect(backSpaceButton, &QPushButton::clicked, this, &MainWindow::backSpaceButtonPushed);

    clearAllButton = new QPushButton("C");
    clearAllButton->setFixedHeight(30);
    clearAllButton->setFixedWidth(60);
    QObject::connect(clearAllButton, &QPushButton::clicked, this, &MainWindow::clearAll);

    clearEntryButton = new QPushButton("CE");
    clearEntryButton->setFixedHeight(30);
    clearEntryButton->setFixedWidth(60);
    QObject::connect(clearEntryButton, &QPushButton::clicked, this, &MainWindow::clearEntry);

    dotButton = new QPushButton(".");
    dotButton->setFixedHeight(30);
    dotButton->setFixedWidth(60);
    dotButton->setEnabled(false);
    QObject::connect(dotButton, &QPushButton::clicked, this, &MainWindow::dotButtonPushed);


    changeSignButton = new QPushButton("±");
    changeSignButton->setFixedHeight(30);
    changeSignButton->setFixedWidth(60);
    changeSignButton->setEnabled(false);

    plusButton = new QPushButton("+");
    plusButton->setFixedHeight(30);
    plusButton->setFixedWidth(60);
    QObject::connect(plusButton, &QPushButton::clicked, this, &MainWindow::plusButtonPushed);

    minusButton = new QPushButton("-");
    minusButton->setFixedHeight(30);
    minusButton->setFixedWidth(60);
    QObject::connect(minusButton, &QPushButton::clicked, this, &MainWindow::minusButtonPushed);

    divButton = new QPushButton("/");
    divButton->setFixedHeight(30);
    divButton->setFixedWidth(60);
    QObject::connect(divButton, &QPushButton::clicked, this, &MainWindow::divButtonPushed);

    mulButton = new QPushButton("*");
    mulButton->setFixedHeight(30);
    mulButton->setFixedWidth(60);
    QObject::connect(mulButton, &QPushButton::clicked, this, &MainWindow::mulButtonPushed);

    resultButton = new QPushButton("=");
    resultButton->setFixedHeight(30);
    resultButton->setFixedWidth(60);
    QObject::connect(resultButton, &QPushButton::clicked, this, &MainWindow::resultButtonPushed);

    complexPartButton = new QPushButton("_ | i ");
    complexPartButton->setFixedHeight(30);
    complexPartButton->setFixedWidth(60);
    QObject::connect(complexPartButton, &QPushButton::clicked, this, &MainWindow::changeModeComplex);

    fracPartButton = new QPushButton("_ / ");
    fracPartButton->setFixedHeight(30);
    fracPartButton->setFixedWidth(60);
    QObject::connect(fracPartButton, &QPushButton::clicked, this, &MainWindow::changeModeFrac);

    complexModeButton = new QPushButton("Complex");
    complexModeButton->setFixedHeight(30);
    QObject::connect(complexModeButton, &QPushButton::clicked, this, &MainWindow::complexModButtonPushed);

    pnumberModeButton = new QPushButton("P-Number");
    pnumberModeButton->setFixedHeight(30);
    QObject::connect(pnumberModeButton, &QPushButton::clicked, this, &MainWindow::pnumberModButtonPushed);

    fracModeButton = new QPushButton("Fraction");
    fracModeButton->setFixedHeight(30);
    QObject::connect(fracModeButton, &QPushButton::clicked, this, &MainWindow::fracModButtonPushed);

}

void MainWindow::insertingInLayout()
{
    wholeLayout->addWidget(menubar, 0, 0, 1, 6);
    wholeLayout->addWidget(memoryLabel, 2, 0, 1, 1);
    wholeLayout->addWidget(memLoadButton, 3, 0, 1, 1);
    wholeLayout->addWidget(memSaveButton, 3, 1, 1, 1);
    wholeLayout->addWidget(clearAllButton, 3, 2, 1,1);
    wholeLayout->addWidget(clearEntryButton, 3, 3, 1,1);
    wholeLayout->addWidget(backSpaceButton, 3, 4, 1,1);
    wholeLayout->addWidget(entryLineEdit, 2, 1, 1, 5);

    wholeLayout->addWidget(complexModeButton, 1, 0, 1, 2);
    wholeLayout->addWidget(fracModeButton, 1, 2, 1, 2);
    wholeLayout->addWidget(pnumberModeButton, 1, 4, 1, 2);

    wholeLayout->addWidget(vectorOfButtons.at(numbersInt::A), 4, 0, 1, 1);
    wholeLayout->addWidget(vectorOfButtons.at(numbersInt::B), 4, 1, 1, 1);
    wholeLayout->addWidget(vectorOfButtons.at(numbersInt::C), 5, 0, 1, 1);
    wholeLayout->addWidget(vectorOfButtons.at(numbersInt::D), 5, 1, 1, 1);
    wholeLayout->addWidget(vectorOfButtons.at(numbersInt::E), 6, 0, 1, 1);
    wholeLayout->addWidget(vectorOfButtons.at(numbersInt::F), 6, 1, 1, 1);

    wholeLayout->addWidget(vectorOfButtons.at(numbersInt::seven), 4, 2, 1, 1);
    wholeLayout->addWidget(vectorOfButtons.at(numbersInt::eight), 4, 3, 1, 1);
    wholeLayout->addWidget(vectorOfButtons.at(numbersInt::nine), 4, 4, 1, 1);
    wholeLayout->addWidget(vectorOfButtons.at(numbersInt::four), 5, 2, 1, 1);
    wholeLayout->addWidget(vectorOfButtons.at(numbersInt::five), 5, 3, 1, 1);
    wholeLayout->addWidget(vectorOfButtons.at(numbersInt::six), 5, 4, 1, 1);
    wholeLayout->addWidget(vectorOfButtons.at(numbersInt::one), 6, 2, 1, 1);
    wholeLayout->addWidget(vectorOfButtons.at(numbersInt::two), 6, 3, 1, 1);
    wholeLayout->addWidget(vectorOfButtons.at(numbersInt::three), 6, 4, 1, 1);
    wholeLayout->addWidget(vectorOfButtons.at(numbersInt::zero), 7, 3, 1, 1);

    wholeLayout->addWidget(divButton, 3, 5, 1, 1);
    wholeLayout->addWidget(mulButton, 4, 5, 1, 1);
    wholeLayout->addWidget(minusButton, 5, 5, 1, 1);
    wholeLayout->addWidget(plusButton, 6, 5, 1, 1);
    wholeLayout->addWidget(resultButton, 7, 5, 1, 1);
    wholeLayout->addWidget(dotButton, 7, 4, 1, 1);
    wholeLayout->addWidget(changeSignButton, 7, 2, 1,1);
    wholeLayout->addWidget(complexPartButton, 7, 1, 1, 1);
    wholeLayout->addWidget(fracPartButton, 7, 0, 1, 1);

    wholeLayout->addWidget(pBaseSlider, 8, 0, 1, 5);
    wholeLayout->addWidget(currentBaseLabel, 8, 5, 1, 1);
}

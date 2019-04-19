#include "tctrl.h"

TCtrl::TCtrl()
{
    proc = new TProc();
    proc->OprtnSet(TOprtn::None);
    memory = new TMemory();
}

TCtrl::~TCtrl()
{
    delete proc;
    delete memory;
}

void TCtrl::setOperation(TOprtn operation, std::shared_ptr<TANumber> number)
{
    proc->Lop_Res_Set(number);
    proc->OprtnSet(operation);
    curState = TCtrlState::cOprtnChange;
}

void TCtrl::setOperation(TOprtn operation)
{
    proc->OprtnSet(operation);
    curState = TCtrlState::cOprtnChange;
}

std::string TCtrl::doOperation(std::shared_ptr<TANumber> number)
{
    proc->Rop_Set(number);

    lastOp = proc->Lop_Res_Get()->getNumberAsString();

    if(proc->OprtnGet() == TOprtn::Add) lastOp += " + ";
    else if(proc->OprtnGet() == TOprtn::Sub) lastOp += " - ";
    else if(proc->OprtnGet() == TOprtn::Dvd) lastOp += " / ";
    else if(proc->OprtnGet() == TOprtn::Mul) lastOp += " * ";

    lastOp += proc->Rop_Get()->getNumberAsString();
    lastOp += " = ";

    proc->OprtnRun();
    proc->OprtnClear();
    lastOp += proc->Lop_Res_Get().get()->getNumberAsString();
    curState = TCtrlState::cOprtnDone;
    return proc->Lop_Res_Get().get()->getNumberAsString();
}

void TCtrl::clear()
{
    proc->ReSet();
    memory->clear();
    curState = TCtrlState::cStart;
}

std::unique_ptr<TANumber> TCtrl::loadMem()
{
    return memory->getFNumber()->clone();
}

void TCtrl::setMem(std::shared_ptr<TANumber> mem)
{
    memory->write(mem->clone());
}

void TCtrl::clearMem()
{
    memory->clear();
}

TCtrl::TCtrlState TCtrl::getCurState() const
{
    return curState;
}

void TCtrl::setCurState(const TCtrlState &value)
{
    curState = value;
}

std::string TCtrl::getLastActionAsString()
{
    return lastOp;
}


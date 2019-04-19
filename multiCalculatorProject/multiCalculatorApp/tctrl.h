#ifndef TCTRL_H
#define TCTRL_H
#include "tmemory.h"
#include "tproc.h"
#include "tanumber.h"

class TCtrl
{
public:
    enum TCtrlState{
        cStart,
        cEditing,
        cOprtnDone,
        cOprtnChange,
        cError
    };
    TCtrl();
    ~TCtrl();

    void setOperation(TOprtn operation,
                      std::shared_ptr<TANumber> number);
    void setOperation(TOprtn operation);
    std::string doOperation(std::shared_ptr<TANumber> number);

    void clear();
    std::unique_ptr<TANumber> loadMem();
    void setMem(std::shared_ptr<TANumber> mem);
    void clearMem();

    TCtrlState getCurState() const;
    void setCurState(const TCtrlState &value);

    std::string getLastActionAsString();

private:
    TProc * proc;
    TMemory * memory;
    TCtrlState curState;
    TANumber * number;
    std::string lastOp;
};

#endif // TCTRL_H

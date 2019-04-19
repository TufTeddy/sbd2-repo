#ifndef TPROC_H
#define TPROC_H
#pragma once
#include "tanumber.h"

enum TOprtn {
    None,
    Add,
    Sub,
    Mul,
    Dvd
};

enum TFunc {
    Rev,
    Sqr
};

class TProc
{
public:
    TProc() : Lop_Res(nullptr), Rop(nullptr)
    {
        Operation = None;
    }

    ~TProc()
    {

    }

    void ReSet()
    {
        Lop_Res = nullptr;
        Rop = nullptr;
        Operation = None;
    }

    void OprtnClear()
    {
        Operation = None;
    }

    void OprtnRun()
    {
        switch (Operation)
        {
        case Add:
            Lop_Res = Lop_Res->summ(Rop->clone());
            break;
        case Sub:
            Lop_Res = Lop_Res->substract(Rop->clone());
            break;
        case Mul:
            Lop_Res = Lop_Res->mult(Rop->clone());
            break;
        case Dvd:
            Lop_Res = Lop_Res->divide(Rop->clone());
            break;
        }
    }

    std::shared_ptr<TANumber> Lop_Res_Get() const
    {
        return std::move(Lop_Res);
    }

    void Lop_Res_Set(std::shared_ptr<TANumber> set)
    {
        Lop_Res = std::move(set);
    }

    void Rop_Set(std::shared_ptr<TANumber> set)
    {
        Rop = std::move(set);
    }

    std::shared_ptr<TANumber> Rop_Get() const
    {
        return std::move(Rop);
    }

    TOprtn OprtnGet() const
    {
        return Operation;
    }

    void OprtnSet(TOprtn set)
    {
        Operation = set;
    }

private:
    std::shared_ptr<TANumber> Lop_Res;
    std::shared_ptr<TANumber> Rop;
    TOprtn Operation;
};


#endif // TPROC_H

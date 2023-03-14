#ifndef STRATEGY_IO_H
#define STRATEGY_IO_H

#include "manager.h"

struct StrategyIO
{
    virtual void save() = 0;
    virtual void load() = 0;
};

struct StrategyIO_Choose : StrategyIO
{
    virtual void save() override;
    virtual void load() override;
};

struct StrategyIO_JSON : StrategyIO
{
    virtual void save() override;
    virtual void load() override;
};

struct StrategyIO_BD : StrategyIO
{
    virtual void save() override;
    virtual void load() override;
};

struct StrategyIO_Custom : StrategyIO
{
    virtual void save() override;
    virtual void load() override;
};


struct StrategyIO_CSV : StrategyIO
{
    virtual void save() override {};
    virtual void load() override;
};


#endif // STRATEGY_IO_H

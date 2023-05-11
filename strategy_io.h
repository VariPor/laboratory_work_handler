#ifndef STRATEGY_IO_H
#define STRATEGY_IO_H

#include "manager.h"

struct StrategyIO
{
    virtual void save(const QString&) = 0;
    virtual void load(const QString&) = 0;
};

struct StrategyIO_JSON : StrategyIO
{
    virtual void save(const QString&) override;
    virtual void load(const QString&) override;
};

struct StrategyIO_BD : StrategyIO
{
    virtual void save(const QString&) override;
    virtual void load(const QString&) override;
};

struct StrategyIO_CSV : StrategyIO
{
    virtual void save(const QString&) override;
    virtual void load(const QString&) override;
};


#endif // STRATEGY_IO_H

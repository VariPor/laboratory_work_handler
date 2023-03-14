#ifndef STRATEGY_IO_H
#define STRATEGY_IO_H

#include "manager.h"

struct StrategyIO
{
    virtual void save(Manager) = 0;
    virtual void load(Manager) = 0;
};

struct StrategyIO_Choose
{
    virtual void save(Manager) override;
    virtual void load(Manager) override;
};

struct StrategyIO_JSON
{
    virtual void save(Manager) override;
    virtual void load(Manager) override;
};

struct StrategyIO_BD
{
    virtual void save(Manager) override;
    virtual void load(Manager) override;
};

struct StrategyIO_Custom
{
    virtual void save(Manager) override;
    virtual void load(Manager) override;
};

#endif // STRATEGY_IO_H

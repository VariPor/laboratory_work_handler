#ifndef BLOCK_H
#define BLOCK_H

struct Block
{
    virtual void update() = 0;
    virtual void getVisibleWidgets() = 0;
    void exportBlock();
};

struct TextBlock : Block
{
    virtual void update() override;
    virtual void getVisibleWidgets() override;
};

struct PlotBlock : Block
{
    virtual void update() override;
    virtual void getVisibleWidgets() override;
};

struct TableBlock : Block
{
    virtual void update() override;
    virtual void getVisibleWidgets() override;
};

#endif // BLOCK_H


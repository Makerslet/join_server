#ifndef ICOMMAND_H
#define ICOMMAND_H

class icommand
{
public:
    virtual ~icommand() = default;
    virtual void execute() = 0;
};

#endif // ICOMMAND_H

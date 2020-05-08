#ifndef ISERVER_H
#define ISERVER_H

class iserver
{
public:
    virtual ~iserver() = default;
    virtual void start() = 0;
    virtual void stop() = 0;
};

#endif // ISERVER_H

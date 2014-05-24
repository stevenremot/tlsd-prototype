#ifndef SENDEVENT_H
#define SENDEVENT_H


#include "../Threading/Channel.h"
#include "../Threading/Thread.h"
using Threading::ThreadableInterface;

namespace Network{
class SendEvent
{
    public:
        SendEvent();
        virtual ~SendEvent();
    protected:
    private:
};
}
#endif // SENDEVENT_H

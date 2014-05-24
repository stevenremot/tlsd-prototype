#ifndef LISTENERCLIENT_H
#define LISTENERCLIENT_H

#include "../Threading/Channel.h"
#include "../Threading/Thread.h"
using Threading::ThreadableInterface;

namespace Network{
class ListenerClient : public ThreadableInterface
{
    public:
        ListenerClient();
        virtual ~ListenerClient();
    protected:
    private:
};
}
#endif // LISTENERCLIENT_H

#ifndef LISTENERSERVER_H
#define LISTENERSERVER_H

#include "../Threading/Channel.h"
#include "../Threading/Thread.h"
using Threading::ThreadableInterface;
namespace Network{
class ListenerServer : public ThreadableInterface
{
    public:
        ListenerServer();
        virtual ~ListenerServer();
    protected:
    private:
};
}
#endif // LISTENERSERVER_H

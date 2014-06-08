#ifndef LISTENER_H
#define LISTENER_H
#include <vector>
#include <iostream>
#include "PracticalSocket.h"
#include "../Threading/Thread.h"
using Threading::ThreadableInterface;
namespace Network{
class Listener : public ThreadableInterface
{
    public:
        Listener(vector<string>* ListeEvent, TCPSocket* client);
        virtual ~Listener();
        void run(void);
    protected:
    private:
      vector<string>* ListeEvent_;
      TCPSocket* client_;
};
}
#endif // LISTENER_H

#include <cstdlib>
#include <iostream>

#include "Event/EventManager.h"

using std::cout;
using std::endl;

using Event::EventType;

class QuitEvent: public Event::Event
{
public:
static const EventType Type;
    QuitEvent(): Event::Event(Type)
    {}
};
const EventType QuitEvent::Type = "quit";

class PrintEvent: public Event::Event
{
public:
static const EventType Type;

    PrintEvent(char c): Event::Event(Type), c_(c)
    {}

    char getChar() const
    {
        return c_;
    }
private:
    char c_;
};

const EventType PrintEvent::Type = "print";

class PrintListener: public Event::EventListener
{
public:
    virtual void call(const Event::Event & event)
    {
        cout << static_cast<const PrintEvent &>(event).getChar();
    }
};

static bool loop = true;

class QuitListener: public Event::EventListener
{
public:
    virtual void call(const Event::Event & event)
    {
        loop = false;
    }
};

int main() {
    Event::EventManager m;
    Event::ListenerRegister & reg = m.getListenerRegister();

    reg.put(PrintEvent::Type, new PrintListener());
    reg.put(QuitEvent::Type, new QuitListener());

    Event::EventQueue & queue = m.getEventQueue();

    queue.push(new PrintEvent('h'));
    queue.push(new PrintEvent('e'));
    queue.push(new PrintEvent('l'));
    queue.push(new PrintEvent('l'));
    queue.push(new PrintEvent('o'));
    queue.push(new QuitEvent());

    while (loop)
    {
        m.run();
    }

    return 0;
}

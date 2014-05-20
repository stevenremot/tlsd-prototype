/*
   This file is part of The Lost Souls Downfall prototype.

    The Lost Souls Downfall prototype is free software: you can
    redistribute it and/or modify it under the terms of the GNU
    General Public License as published by the Free Software
    Foundation, either version 3 of the License, or (at your option)
    any later version.

    The Lost Souls Downfall prototype is distributed in the hope that
    it will be useful, but WITHOUT ANY WARRANTY; without even the
    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
    PURPOSE.  See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Lost Souls Downfall prototype.  If not, see
    <http://www.gnu.org/licenses/>.
*/

#include "threading.h"

#include <string>
#include <iostream>
#include <list>
#include <vector>

#include "../Threading/Channel.h"
#include "../Threading/Thread.h"

using std::cout;
using std::endl;
using std::string;
using std::list;

using Threading::ThreadableInterface;
using Threading::Thread;
using Threading::ChannelInput;
using Threading::ChannelOutput;
using Threading::createChannel;

namespace ThreadingTest
{
    class Sender: public ThreadableInterface
    {
    public:
        Sender(ChannelInput<string>& chanInput):
            chanInput_(chanInput)
        {
            messages_.push_back("hello");
            messages_.push_back("world");
            messages_.push_back("!");
            messages_.push_back("/quit");
        }

        void run()
        {
            if (!messages_.empty())
            {
                cout << "Sending " << messages_.front() << endl;
                chanInput_ << messages_.front();
                messages_.pop_front();
            }
        }

    private:
        ChannelInput<string> chanInput_;
        list<string> messages_;
    };

    void testChannel()
    {
        ChannelInput<string> chanInput;
        ChannelOutput<string> chanOutput;
        createChannel<string>(chanInput, chanOutput);

        Sender sender(chanInput);

        std::vector<ThreadableInterface*> threadables;
        threadables.push_back(&sender);

        Thread thread(threadables, 2);
        thread.start();

        bool loop = true;
        while (loop)
        {
            string message;
            chanOutput >> message;

            if (message == "/quit")
            {
                cout << "Closed" << endl;
                loop = false;
            }
            else
            {
                cout << "Message received : " << message << endl;
            }
        }

        thread.stop();
    }
}

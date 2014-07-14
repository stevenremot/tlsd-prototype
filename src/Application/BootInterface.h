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

#ifndef APPLICATION_BOOT_INTERFACE_H
#define APPLICATION_BOOT_INTERFACE_H

#include <memory>

#include "../Threading/Thread.h"

namespace Application
{
    class Application;

    /**
     * Interface for objects that boots threads.
     */
    class BootInterface
    {
    public:
        typedef void (*Callback)(Application&, BootInterface&);

        BootInterface(Callback callback, Application& application):
            thread_(nullptr),
            callback_(callback, application)
        {}

        virtual void start() = 0;

        virtual ~BootInterface()
        {
            if (thread_ != nullptr)
            {
                thread_->stop();
                cleanUp();
            }
        }

        Threading::Thread& getThread()
        {
            return *thread_;
        }

        Application& getApplication()
        {
            return callback_.application;
        }

        void finishBoot()
        {
            callback_.callback(callback_.application, *this);
        }

    protected:
        void setThread(Threading::Thread* thread)
        {
            thread_ = std::unique_ptr<Threading::Thread>(thread);
        }

        virtual void cleanUp() {};

    private:
        typedef struct CallbackStruct {
            CallbackStruct(Callback callback, Application& application):
                callback(callback),
                application(application)
            {}

            Callback callback;
            Application& application;
        } CallbackStruct;

        std::unique_ptr<Threading::Thread> thread_;
        CallbackStruct callback_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:

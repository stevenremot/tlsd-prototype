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

#ifndef THREADING_THREAD_H
#define THREADING_THREAD_H

#include <cstdio>
#include <vector>
#include <exception>
#include <pthread.h>
#include <ctime>

#include "ThreadableInterface.h"

namespace Threading
{
    /**
     * Sleep the current thread for given milliseconds.
     */
    int sleep(long seconds, long milliseconds);

    /**
     * Class that can run multiple threadable objects.
     *
     * *Caution*: Does not own threadables' memory.
     */
    class Thread
    {
    public:
        /**
         * This exception is thrown when something went wrong on thread creation.
         */
        class Exception: std::exception
        {
        public:
            Exception(int error)
            {
                error_ = new char[64];
                std::sprintf(error_, "A threading error occured : %d", error);

            }

            ~Exception() throw()
            {
                delete[] error_;
            }

            const char * what() const throw()
            {
                return error_;
            }
        private:
            char * error_;
        };

        Thread(std::vector<ThreadableInterface*> threadables, int loopPerSecond):
            threadables_(threadables),
            running_(false),
            loopDelay_(1000 / loopPerSecond)
        {}

        void start();
        void stop();

        inline bool isRunning() const { return running_; }

    private:
        static void* loopFunction(void * obj);

        std::vector<ThreadableInterface*> threadables_;
        bool running_;
        pthread_t thread_;
        time_t loopDelay_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:

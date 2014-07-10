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

#ifndef THREADING_CHANNEL_H
#define THREADING_CHANNEL_H

#include <list>
#include <exception>

#include "Thread.h"
#include "ConcurrentRessource.h"

namespace Threading
{
    class ChannelClosedException: public std::exception
    {
    public:
        const char* what() const throw()
        {
            return "Attempted to read / write a closed channel.";
        }
    };

    /**
     * The class the centralizes the data for inter-process
     * communication.
     */
    template<typename T>
    class Channel
    {
    public:
        Channel():
            data_()
        {}

        void operator<<(const T& data)
        {
            data_.push_back(data);
        }

        void operator>>(T& data)
        {
            while(data_.empty())
            {
                sleep(0, 10);
            }

            data = data_.front();
            data_.pop_front();
        }

        bool isEmpty() const
        {
            return data_.empty();
        }

    private:
        std::list<T> data_;

        Channel(const Channel&);
    };

    /**
     * Interface for objects that can send data to a channel
     */
    template<typename T>
    class ChannelInput
    {
    public:
        ChannelInput():
            channel_(new Channel<T>)
        {};

        ChannelInput(ConcurrentRessource< Channel<T> >& channel):
            channel_(channel)
        {}

        ChannelInput(const ChannelInput& input):
            channel_(input.channel_)
        {}

        ChannelInput& operator=(const ChannelInput& input)
        {
            channel_ = input.channel_;
            return *this;
        }

        /**
         * Send data to the channel
         *
         * Throws a ChannelClosedException if the channel is closed.
         */
        void operator<<(const T& data)
        {
            (*channel_.getWriter()) << data;
        }

    private:
        ConcurrentRessource< Channel<T> > channel_;
    };

    /**
     * Interface for objects that can receive data from a channel
     */
    template<typename T>
    class ChannelOutput
    {
    public:
        ChannelOutput():
            channel_(new Channel<T>)
        {};

        ChannelOutput(ConcurrentRessource< Channel<T> >& channel):
            channel_(channel)
        {}

        ChannelOutput(const ChannelOutput& output):
            channel_(output.channel_)
        {}

        ChannelOutput& operator=(const ChannelOutput& output)
        {
            channel_ = output.channel_;
            return *this;
        }

        /**
         * Wait to receive data from the channel
         *
         * Throws a ChannelClosedException if the channel is closed.
         */
        void operator>>(T& data)
        {
            (*channel_.getWriter()) >> data;
        }

        bool isEmpty()
        {
            return channel_.getReader()->isEmpty();
        }

    private:
        ConcurrentRessource< Channel<T> > channel_;
    };

    /**
     * Create a new channel
     *
     * The channel is represented by a pair (input, output).
     *
     * @param[out] object that can send input to the channel
     * @param[out] object that can receive output from the channel
     */
    template<typename T>
    void createChannel(ChannelInput<T>& input,
                       ChannelOutput<T>& output)
    {
        ConcurrentRessource< Channel<T> > channel(new Channel<T>);
        input = ChannelInput<T>(channel);
        output = ChannelOutput<T>(channel);
    }
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:

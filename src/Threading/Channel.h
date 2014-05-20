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
        Channel(): data_(new std::list<T>), refs_(new int)
        {
            *refs_ = 1;
        }

        Channel(const Channel& channel): data_(channel.data_),
                                         refs_(channel.refs_)
        {
            (*refs_) += 1;
        }

        Channel& operator=(const Channel& channel)
        {
            freeData();
            data_ = channel.data_;
            refs_ = channel.refs_;

            (*refs_) += 1;

            return *this;
        }

        ~Channel()
        {
            freeData();
        }

        void operator<<(const T& data)
        {
            data_->push_back(data);
        }

        void operator>>(T& data)
        {
            while(data_->empty())
            {
                sleep(0, 10);
            }

            data = data_->front();
            data_->pop_front();
        }

    private:
        std::list<T>* data_;
        int* refs_;

        void freeData()
        {
            (*refs_) -= 1;

            if (*refs_ == 0)
            {
                delete data_;
                delete refs_;
            }
        }
    };

    /**
     * Interface for objects that can send data to a channel
     */
    template<typename T>
    class ChannelInput
    {
    public:

        ChannelInput() {};

        ChannelInput(Channel<T>& channel):
            channel_(channel)
        {}

        ChannelInput(const ChannelInput& input):
            channel_(input.channel_)
        {}

        /**
         * Send data to the channel
         *
         * Throws a ChannelClosedException if the channel is closed.
         */
        void operator<<(const T& data)
        {
            channel_ << data;
        }

    private:
        Channel<T> channel_;
    };

    /**
     * Interface for objects that can receive data from a channel
     */
    template<typename T>
    class ChannelOutput
    {
    public:

        ChannelOutput() {};

        ChannelOutput(Channel<T> channel):
            channel_(channel)
        {}

        ChannelOutput(const ChannelOutput& output):
            channel_(output.channel_)
        {}

        /**
         * Wait to receive data from the channel
         *
         * Throws a ChannelClosedException if the channel is closed.
         */
        void operator>>(T& data)
        {
            channel_ >> data;
        }

    private:
        Channel<T> channel_;
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
        Channel<T> channel;
        input = ChannelInput<T>(channel);
        output = ChannelOutput<T>(channel);
    }
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:

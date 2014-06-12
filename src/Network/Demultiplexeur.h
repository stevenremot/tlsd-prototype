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
#ifndef DEMULTIPLEXEUR_H
#define DEMULTIPLEXEUR_H
#include <vector>
#include <string>
#include "PracticalSocket.h"
#include "../Threading/ThreadableInterface.h"
#include "../Threading/Thread.h"
#include "SendEvent.h"
#include <iostream>

using Threading::ThreadableInterface;
using Threading::Thread;
using std::cout;
using std::endl;

namespace Network {
class Demultiplexeur :public ThreadableInterface
{
    public:
        Demultiplexeur(std::vector<TCPSocket*> *ListeClient,std::vector<string>* ListeEvent,TCPServerSocket* ServerSocket);
        virtual ~Demultiplexeur();
        void run(void);
    protected:
    private:
        std::vector<TCPSocket*>* ListeClient_;
        std::vector<string>* ListeEvent_;
        TCPServerSocket* ServerSocket_;
};

}
#endif // DEMULTIPLEXEUR_H

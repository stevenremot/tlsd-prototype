#include "AcceptClient.h"
namespace Network{
AcceptClient::AcceptClient(TCPServerSocket *Server,vector<TCPSocket*> *ListeClient)
{
    this->Server=Server;
    this->ListeClient=ListeClient;
}

AcceptClient::~AcceptClient(){
    this->Server=NULL;
    this->ListeClient=NULL;
}

void AcceptClient::run(void){
    TCPSocket *clntSock;
    // Create separate memory for client argument
    if(clntSock = this->Server->accept())
    {
    this->ListeClient->push_back(clntSock);


   // ListenerClient listenerclient = new ListenerClient(clntSock,EventQueue *enventqueue);


    }else{
    /// A supprimer
    std::cout<<" Erreur pour accepter client"<<std::endl;
    }
}
}

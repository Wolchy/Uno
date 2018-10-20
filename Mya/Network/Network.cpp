#include "Network.h"

Network::Network(){}

void Network::init(){
	if (isServer) {
		socketSet = SDLNet_AllocSocketSet(MAX_SOCKETS);
		if (socketSet == NULL){
			std::cout << "Failed to allocate the socket set: " << SDLNet_GetError() << std::endl;
		}else{
			std::cout << "Allocated socket set with size:  " << MAX_SOCKETS << ", of which " << MAX_CLIENTS << " are availble for use by clients." << std::endl;
		}

		// Initialize all the client sockets (i.e. blank them ready for use!)
		for (int loop = 0; loop < MAX_CLIENTS; loop++)
		{
			clientSocket[loop] = NULL;
			socketIsFree[loop] = true; // Set all our sockets to be free (i.e. available for use for new client connections)
		}

		int hostResolved = SDLNet_ResolveHost(&ip, NULL, PORT);

		if (hostResolved == -1){
			std::cout << "Failed to resolve the server host: " << SDLNet_GetError() << std::endl;
		}
		else // If we resolved the host successfully, output the details
		{
			// Get our IP address in proper dot-quad format by breaking up the 32-bit unsigned host address and splitting it into an array of four 8-bit unsigned numbers...
			Uint8 * dotQuad = (Uint8*)&ip.host;

			//... and then outputting them cast to integers. Then read the last 16 bits of the serverIP object to get the port number
			std::cout << "Successfully resolved server host to IP: " << (unsigned short)dotQuad[0] << "." << (unsigned short)dotQuad[1] << "." << (unsigned short)dotQuad[2] << "." << (unsigned short)dotQuad[3];
			std::cout << " port " << SDLNet_Read16(&ip.port) << std::endl << std::endl;
		}

		// Try to open the server socket
		tcpsock = SDLNet_TCP_Open(&ip);

		if (!tcpsock){
			std::cout << "Failed to open the server socket: " << SDLNet_GetError() << "\n";
		}else{
			std::cout << "Sucessfully created server socket." << std::endl;
		}

		SDLNet_TCP_AddSocket(socketSet, tcpsock);

		std::cout << "Awaiting clients..." << std::endl;
	}
	else {
		socketSet = SDLNet_AllocSocketSet(1);
		if (socketSet == NULL){
			std::cout << "Failed to allocate the socket set: " << SDLNet_GetError() << "\n";
		}else{
			std::cout << "Successfully allocated socket set." << std::endl;
		}

		int hostResolved = SDLNet_ResolveHost(&ip, serverName.c_str(), PORT);
		if (hostResolved == -1){
			std::cout << "Failed to resolve the server hostname: " << SDLNet_GetError() << "\nContinuing...\n";
		}else
		{
			Uint8 * dotQuad = (Uint8*)&ip.host;
			
			std::cout << "Successfully resolved host to IP: " << (unsigned short)dotQuad[0] << "." << (unsigned short)dotQuad[1] << "." << (unsigned short)dotQuad[2] << "." << (unsigned short)dotQuad[3];
			std::cout << " port " << SDLNet_Read16(&ip.port) << std::endl << std::endl;
		}

		if ((host = SDLNet_ResolveIP(&ip)) == NULL){
			std::cout << "Failed to resolve the server IP address: " << SDLNet_GetError() << std::endl;
		}else{
			std::cout << "Successfully resolved IP to host: " << host << std::endl;
		}

		bool shutdownClient = true;

		tcpsock = SDLNet_TCP_Open(&ip);
		if (!clientSocket)
		{
			std::cout << "Failed to open socket to server: " << SDLNet_GetError() << "\n";
		}
		else
		{
			std::cout << "Connection okay, about to read connection status from the server..." << std::endl;

			SDLNet_TCP_AddSocket(socketSet, tcpsock);
			int activeSockets = SDLNet_CheckSockets(socketSet, 10000);
			std::cout << "waiting at most 10seconds at most" << std::endl;

			std::cout << "There are " << activeSockets << " socket(s) with data on them at the moment." << std::endl;

			int gotServerResponse = SDLNet_SocketReady(clientSocket);

			if (gotServerResponse != 0){
				std::cout << "Got a response from the server... " << std::endl;
				int serverResponseByteCount = SDLNet_TCP_Recv(tcpsock, buffer, BUFFER_SIZE);

				std::cout << "Got the following from server: " << buffer << std::endl;

				if (strcmp(buffer, "OK") == 0){
					client_hasConnection = true;

					std::cout << "Joining server now..." << std::endl << std::endl;
				}else{
					std::cout << "Server is full... Terminating connection." << std::endl;
					Sleep(2000);
				}
			}
			else
			{
				std::cout << "No response from server..." << std::endl;
			}

		}
	}
}

void Network::exit(){
	SDLNet_FreeSocketSet(socketSet);
	SDLNet_TCP_Close(tcpsock);
}

void Network::server_update(){
	int numActiveSockets = SDLNet_CheckSockets(socketSet, 0);

	if (numActiveSockets != 0){
		std::cout << "There are currently " << numActiveSockets << " socket(s) with data to be processed." << std::endl;
	}

	int serverSocketActivity = SDLNet_SocketReady(tcpsock);

	if (serverSocketActivity != 0){
		if (clientCount < MAX_CLIENTS){

			int freeSpot = -99;
			for (int loop = 0; loop < MAX_CLIENTS; loop++){
				if (socketIsFree[loop] == true){
					socketIsFree[loop] = false;
					freeSpot = loop;            
					break;                      
				}
			}
			clientSocket[freeSpot] = SDLNet_TCP_Accept(tcpsock);
			SDLNet_TCP_AddSocket(socketSet, clientSocket[freeSpot]);
			clientCount++;

			strcpy(buffer, SERVER_NOT_FULL.c_str());
			int msgLength = strlen(buffer) + 1;
			SDLNet_TCP_Send(clientSocket[freeSpot], (void *)buffer, msgLength);

			std::cout << "Client connected. There are now " << clientCount << " client(s) connected." << std::endl << std::endl;
		}else
		{
			std::cout << "*** Maximum client count reached - rejecting client connection ***" << std::endl;

			TCPsocket tempSock = SDLNet_TCP_Accept(tcpsock);

			strcpy(buffer, SERVER_FULL.c_str());
			int msgLength = strlen(buffer) + 1;
			SDLNet_TCP_Send(tempSock, (void *)buffer, msgLength);

			SDLNet_TCP_Close(tempSock);
		}
	}

	for (int clientNumber = 0; clientNumber < MAX_CLIENTS; clientNumber++){
		int clientSocketActivity = SDLNet_SocketReady(clientSocket[clientNumber]);
		if (clientSocketActivity != 0){
			receivedByteCount = SDLNet_TCP_Recv(clientSocket[clientNumber], buffer, BUFFER_SIZE);

			if (receivedByteCount <= 0){
				std::cout << "Client " << clientNumber << " disconnected." << std::endl << std::endl;

				SDLNet_TCP_DelSocket(socketSet, clientSocket[clientNumber]);
				SDLNet_TCP_Close(clientSocket[clientNumber]);
				clientSocket[clientNumber] = NULL;
				socketIsFree[clientNumber] = true;
				clientCount--;

				std::cout << "Server is now connected to: " << clientCount << " client(s)." << std::endl << std::endl;
			}else
			{
				//std::cout << "Received: >>>> \"" << buffer << "\" from client number: " << clientNumber << std::endl;
				_buffer.push_back(std::to_string(clientNumber) + "&" + std::string(buffer));
				hasNewMessage = true;
			}
		}
	}
}

void Network::client_update(){
	if (client_hasConnection) {
		int socketActive = SDLNet_CheckSockets(socketSet, 0);

		if (socketActive != 0) {
			// Check if we got a response from the server
			int messageFromServer = SDLNet_SocketReady(tcpsock);

			if (messageFromServer != 0) {
				//std::cout << "Got a response from the server... " << std::endl;
				int serverResponseByteCount = SDLNet_TCP_Recv(tcpsock, buffer, BUFFER_SIZE);
				hasNewMessage = true;

				_buffer.push_back(buffer);
				//std::cout << "Received: " << buffer << "(" << serverResponseByteCount << " bytes)" << std::endl;
			}
			else {
				std::cout << "No response from server..." << std::endl;
			}
		} // End of if socket has activity check
	}
}

void Network::sendMessage(std::string msg){
	strcpy(buffer, msg.c_str());
	int msgLength = strlen(buffer) + 1;
	if (isServer) {
		for (int loop = 0; loop < clientCount; loop++){
			if(socketIsFree[loop] == false)
				SDLNet_TCP_Send(clientSocket[loop], (void *)buffer, msgLength);
		}
		//std::cout << "Sent: <<<< \"" << buffer << "\" to all of the clients." << std::endl;
	} else {
		SDLNet_TCP_Send(tcpsock, (void *)buffer, msgLength);
		//std::cout << "Sent: <<<< \"" << buffer << "\" to the server." << std::endl;
	}
}

void Network::server_sendMessage(int clientNumber, std::string msg){
	strcpy(buffer, msg.c_str());
	int msgLength = strlen(buffer) + 1;
	SDLNet_TCP_Send(clientSocket[clientNumber], (void *)buffer, msgLength);

	//std::cout << "Sent: <<<< \"" << buffer << "\" to client number: " << clientNumber << std::endl;
}

void Network::server_kick(int _id)
{
	SDLNet_TCP_DelSocket(socketSet, clientSocket[_id]);
	SDLNet_TCP_Close(clientSocket[_id]);
	clientSocket[_id] = NULL;
	socketIsFree[_id] = true;
	clientCount--;
}

void Network::client_disconnect()
{
	sendMessage("dc");
}

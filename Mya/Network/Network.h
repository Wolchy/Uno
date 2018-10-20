#pragma once

#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <vector>

#include <SDL_net.h>

class Network {
public:
	bool client_hasConnection = false;

	short PORT = 9998;
	const unsigned short BUFFER_SIZE = 512;					// Size of our message buffer
	const unsigned short MAX_SOCKETS = 9;					// Max number of sockets
	const unsigned short MAX_CLIENTS = MAX_SOCKETS - 1;

	const std::string SERVER_NOT_FULL = "OK";
	const std::string SERVER_FULL = "FULL";

	std::string serverName = "25.61.254.188";
	const char *host;

	IPaddress ip;											// The IP of the server (this will end up being 0.0.0.0 - which means roughly "any IP address")
	TCPsocket tcpsock;              						// The server socket that clients will use to connect to us
	TCPsocket clientSocket[8];								// An array of sockets for the clients, we don't include the server socket (it's specified separately in the line above)
	bool      socketIsFree[8];								// An array of flags to keep track of which client sockets are free (so we know whether we can use the socket for a new client connection or not)

	SDLNet_SocketSet socketSet;

	//std::string serverBufferThingy;
	std::vector<std::string> _buffer;
	char buffer[512];			    						// Array of characters used to store the messages we receive
	int receivedByteCount = 0;     							// A variable to keep track of how many bytes (i.e. characters) we need to read for any given incoming message i.e. the size of the incoming data
	int clientCount = 0;           							// Count of how many clients are currently connected to the server

	bool shutdownServer = false;
	bool isServer = false;
	bool hasNewMessage = false;

	

	Network();									//Object: actually does nothing in here.

	void init();								//Init: set 'isServer', 'serverName', and 'PORT' first! Init' will connect you to your 'serverName' and 'PORT'.
	void exit();								//Exit: closes connection to server.
	void server_update();						//server_update: is main loop for server only. DO NOT USE FOR CLIENT!
	void client_update();						//client_update: is main loop for client only. DO NOT USE FOR SERVER!
	void sendMessage(std::string);				//sendMessage: sends a message either to the server or the servers clients depending on which mode your in.
	void server_sendMessage(int, std::string);
	void server_kick(int id);
	void client_disconnect();
};
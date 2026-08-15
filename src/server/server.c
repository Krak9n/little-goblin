#include "server.h"

// Currently uses IPv4 by default. Later will the user to specify the protocol version.
// Or to decide it dynamically somehow.
Server newServer(int domain, int protocol, uint port, int backlog, int service, uint interface, void(*launch)(Server *server)) {
	Server server;

	server.domain = domain;
	server.protocol = protocol;
	server.port = port;
	server.service = service;
	server.backlog = backlog;
	server.interface = interface;

	server.ipv4_address.sin_family = domain;
	// Byte code transition
	server.ipv4_address.sin_port = htons(port);
	server.ipv4_address.sin_addr.s_addr = htonl(interface); 

	// Socket creation
	server.socket = socket(domain, service, protocol);
	if (!server.socket) {
		perror("Failed to connect socket");
		exit(1);
	}

	if (bind(server.socket, (struct sockaddr *)&server.ipv4_address, sizeof(server.ipv4_address)) < 0) {
		perror("Failed to bind socket");
		exit(1);
	}

	if (listen(server.socket, server.backlog) < 0) {
		perror("Failed to listen");
		exit(1);
	}

	server.launch = launch;
	return server;
}

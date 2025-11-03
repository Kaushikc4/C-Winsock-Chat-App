🔌 C-Winsock-Chat-App: Client-Server Chat Application
🌟 Project Overview
This project implements a fundamental TCP socket communication application, allowing a Server and a Client to establish a connection and exchange messages. It is specifically designed to be compiled and run on Windows using the Winsock library (ws2_32.lib), providing a basic, reliable chat functionality.

The server listens on a specified port, accepts one incoming client connection, and facilitates a simple command-line chat session until either party sends the "Bye" message.

💡 Project Description
This is a fundamental Client-Server communication program implemented entirely in C, utilizing the Winsock (WS2_32) library for Windows networking. The application establishes a reliable TCP connection (stream socket) between a single server and a single client to facilitate interactive message exchange.

Key Features:

Platform-Specific Networking: Built exclusively with the Windows Sockets API (Winsock).

TCP/IP Model: Demonstrates the complete flow of a TCP connection: initialization (WSAStartup), socket creation, binding, listening, connection acceptance, and cleanup.

Bidirectional Chat: Both the Server and Client can send messages to one another once the connection is established.

Graceful Exit: The session terminates when either the client or the server sends the keyword "Bye".

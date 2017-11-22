/* ======================================================================
	Socket Programming-1
   This progam is for creating a server socket. The server socket
       (a) is created with a socket() call
       (b) is bound with an IP address and Port
       (c) listens for connections with a listen() call 
       (d) accepts a connection with a accept() call
       (e) sends data with send() call and 
       (f) finshes its life with a close() call.
	---------------------------------------------------------------------- 
    *** htons(Port_No) is for converting HBO to NBO where
        ----> HBO: Host-Byte-Order
        ----> NBO: Network-Byte-Order
        Byte Order: Big Indian & Little Indian
	---------------------------------------------------------------------- 
    Necessary System Calls:
       1. socket(domain, type, protocol)
       2. bind()
       3. listen() 
       4. send()
       5. recv()
       6. close()         
   ---------------------------------------------------------------------- 
    Sangeeta Biswas
    Assistant Professor,
    Dept. of CSE, University of Rajshahi,
    Rajshahi-6205, Bangladesh
   ---------------------------------------------------------------------- 
    29/8/2017
	======================================================================
*/

#include <sys/socket.h> 	
#include <netinet/in.h>
#include <unistd.h> 		

int main() {
    // Create a socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Define server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the above socket to the specified IP and port
    int addr_len;
    struct sockaddr *sockaddr_ptr;
    addr_len = sizeof(server_address);
    sockaddr_ptr = (struct sockaddr *)&server_address;
    bind(server_socket, sockaddr_ptr, addr_len);
        
    // Listen
    listen(server_socket, 5);

    // Accept
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    // Send message to the client
    char server_message[256] = "Congratulation!!! You have reached the server.";
    int msg_size;
    msg_size = sizeof(server_message);
    send(client_socket, server_message, msg_size, 0);

    // Close socket
    close(server_socket);

}

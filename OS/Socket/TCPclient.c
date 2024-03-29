/* =====================================================================
	Socket Programming-1
    This progam is for creating a client socket. The client socket 
       (a) is created with a socket() call, 
       (b) is connected with a remote address with a connect() call, 
       (c) receives data with recv() call and 
       (d) finshes its life with a close() call.
	---------------------------------------------------------------------- 
    *** htons(Port_No) is for converting HBO to NBO where
        ----> HBO: Host-Byte-Order
        ----> NBO: Network-Byte-Order
        Byte Order: Big Indian & Little Indian
    ---------------------------------------------------------------------
    Necessary System Calls:
       1. socket(domain, type, protocol)
       2. connect() 
       3. recv()
       4. close()  
   ----------------------------------------------------------------------
    Sangeeta Biswas
    Assistant Professor,
    Dept. of CSE, University of Rajshahi,
    Rajshahi-6205, Bangladesh
   ----------------------------------------------------------------------
    28/8/2017
	======================================================================
*/

/* Directives */
#include <sys/socket.h>		// For system call: socket(). 
#include <stdio.h>			// For standard input-output.
#include <netinet/in.h>		// For sockaddr_in, sockaddr, htons().  
#include <unistd.h>			// For close().  
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdbool.h>



/* Main function*/
int main() {
    // STEP-1: socket()
    // 1.1. Create a socket.
    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // 1.2. Specify an address for the above socket.
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET; 
    server_address.sin_port = htons(12000);
    //inet_pton(AF_INET, "192.168.1.36", &(server_address.sin_addr)); //to connect other pc 
    server_address.sin_addr.s_addr = INADDR_ANY; // Local IP address

    // STEP-2: connect()
    // 2.1. Connect to the remote socket
    int addr_len;
    struct sockaddr *sockaddr_ptr;
    addr_len = sizeof(server_address);
    sockaddr_ptr = (struct sockaddr *) &server_address;



    int server_socket;
    server_socket = connect(client_socket, sockaddr_ptr, addr_len);
    
    // STEP-3: recv()
    // 3.1. Receive data from the server


	//declaring variables

	char client_message[256];
    int msg_size;
	char server_response[256];
	int buf_size;
	bool write = false;

	//just create a infinity loop

	while(1)
	{
		if(write)
		{
            printf("server waiting for your response\n");

            scanf ("%[^\n]%*c", client_message);

			//scanf("%[^\n]s",client_message);
			
            int sending = send(client_socket,&client_message,sizeof(client_message),0);

            if(sending < 0)
            {
                perror("sending failed");
            }

            write = false;
		}		
		else
        {
            
            int receiving = recv(client_socket, &server_response, sizeof(server_response), 0);

            if(receiving < 0)
            {
                printf("received is failed\n");
            }

            // 3.2. Check sever's response.
            printf("server: %s\n", server_response);

            write = true;

        }


        /*
        if(write)
        {
            write = false;
            printf("hi write\n");
           
        }
        else
        {
            write = true;
            printf("hi read\n");
        }*/
	
	}

    

    // STEP-4: close()
    // 4.1. Close the socket
    close(client_socket);

    return 0;
}





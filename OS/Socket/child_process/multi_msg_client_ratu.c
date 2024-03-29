/* ========================================================
                   ==== Developed By ====

                   SHAH MD. IMRAN HOSSAIN
                      ID - 1510176113
   ========================================================
*/

/* Directives */
#include <sys/socket.h>		// For system call: socket(). 
#include <stdio.h>			// For standard input-output.
#include <netinet/in.h>		// For sockaddr_in, sockaddr, htons().  
#include <unistd.h>			// For close().  
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdbool.h>     //to use bool data type in C 
#include <string.h>        // to use string functions in C 



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

	char client_message[256],client_name[50];
	char server_response[256];
	bool write = false,msg = true,intro_status = false;
    int good_bye_count = 0;

	//just create a infinity loop

	while(good_bye_count != 2)
	{
        //telling the server who am i
        if(!intro_status)
        {
            int receiving = recv(client_socket, &server_response, sizeof(server_response), 0);

            if(receiving < 0)
            {
                printf("received is failed\n");
            }

            printf("server: %s\n",server_response);

            scanf ("%[^\n]%*c", client_name);

            int sending = send(client_socket,&client_name,sizeof(client_name),0);

            if(sending < 0)
            {
                perror("sending failed");
            }

            intro_status = true;
        }

		while(write)
		{
            if(msg)
            {
                printf("%s,server waiting for your response\n",client_name);
                msg = false;
            }

            //you can type good bye to close the socket

            scanf ("%[^\n]%*c", client_message); //type "finish" to finish ur message


			//scanf("%[^\n]s",client_message);

            if(strcmp(client_message,"finish") == 0)
            {
                write = false;
                msg = true;

                int sending = send(client_socket,&client_message,sizeof(client_message),0);

                if(sending < 0)
                {
                    perror("sending failed");
                }
            }
            else
            {
                int sending = send(client_socket,&client_message,sizeof(client_message),0);

                if(sending < 0)
                {
                    perror("sending failed");
                }
            }
			

            if(strcmp(client_message,"good bye") == 0)
            {
                good_bye_count++;
            }
            
		}


		while(!write)
        {
            
            int receiving = recv(client_socket, &server_response, sizeof(server_response), 0);

            if(receiving < 0)
            {
                printf("received is failed\n");
            }


            if(strcmp(server_response,"finish") == 0)
            {
                write = true;
            }
            else
            {
                // 3.2. Check sever's response.
                printf("server: %s\n", server_response);

            }

            if(strcmp(server_response,"good bye") == 0)
            {
                good_bye_count++;
            }

        }

	
	}

    

    // STEP-4: close()
    // 4.1. Close the socket
    close(client_socket);

    return 0;
}





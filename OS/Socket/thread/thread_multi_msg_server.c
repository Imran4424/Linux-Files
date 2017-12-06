/* ========================================================
                   ==== Developed By ====

                   SHAH MD. IMRAN HOSSAIN
                      ID - 1510176113
   ========================================================
*/

#include <sys/socket.h> 	
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>  //to use bool data type in C 
#include<string.h>    // to use string functions in C 



int main() {
    // Create a socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Define server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12000);
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
    

	//declaring the variables

	char server_message[256];
	char client_response[256];
	bool write = true,msg = true;
    int good_bye_count = 0;
    

	
	//just creating a infinite loop

	while(good_bye_count != 2)
	{
		while(write)
		{
            if(msg)
            {
                printf("client Anik waiting for your response\n");

                msg = false;
            }

            //you can type good bye to close the socket			

			scanf ("%[^\n]%*c", server_message); //type finish to finish ur message

			//scanf("%[^\n]s",server_message);

            if(strcmp(server_message,"finish") == 0)
            {
                write = false;
                msg = true;

                int sending = send(client_socket, server_message, sizeof(server_message), 0);
                    
                if(sending < 0)
                {
                    perror("In server sending");
                }
            }
    		else
            {
                int sending = send(client_socket, server_message, sizeof(server_message), 0);
                    
                if(sending < 0)
                {
                    perror("In server sending");
                }
            }
        	   
            if(strcmp(server_message,"good bye") == 0)
            {
                good_bye_count++;
            }
			
		}


		while(!write)
		{
			

			int receiving = recv(client_socket,client_response,sizeof(client_response),0);

			if(receiving < 0)
			{
				perror("In server receiving");
			}

            if(strcmp(client_response,"finish") == 0)
            {
                write = true;
            }
            else
            {
                printf("client: %s\n", client_response);
            }


            if(strcmp(client_response,"good bye") == 0)
            {
                good_bye_count++;
            }
			
		}

	}


    // Close socket
    close(server_socket);

}

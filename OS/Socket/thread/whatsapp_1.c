#include <sys/socket.h>		// For system call: socket(). 
#include <stdio.h>			// For standard input-output.
#include <netinet/in.h>		// For sockaddr_in, sockaddr, htons().  
#include <unistd.h>			// For close().  
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>  //for exit()


//global variable
int good_bye_count = 0;
int client_socket;
int recei_status = false;


void *sender()
{
	//printf("sender\n");

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
    
    client_socket = accept(server_socket, NULL, NULL);

    if(client_socket == 4)
    {
        recei_status = true;
    }

    printf("connection stablish\n");

    // Send message to the client


    //declaring the variables

	char messenger_one_message[256];
	

	while(good_bye_count != 2)
	{
		//printf("sender in while\n");

		scanf ("%[^\n]%*c", messenger_one_message);  ///send good bye to finish the conversation

		//scanf("%[^\n]s",server_message);
				
	   	int sending = send(client_socket, messenger_one_message, sizeof(messenger_one_message), 0);
				
		if(sending < 0)
		{
			perror("In server sending");
		}

		if(strcmp(messenger_one_message,"good bye") == 0)
        {
                good_bye_count++;
        } 
	}


	// Close socket
    close(server_socket);

}




void *received()
{

	char messenger_two_response[256];


	while(good_bye_count != 2)
	{
		//printf("receiver in while\n");
        
        if(!recei_status)
        {
            continue;
        }

		int receiving = recv(client_socket,messenger_two_response,sizeof(messenger_two_response),0);

        

    	if(receiving < 0)
        {
        	printf("received is failed\n");
        }
        else
        {
            // 3.2. Check sever's response.
            printf("Anik: %s\n", messenger_two_response);

        }

        
        if(strcmp(messenger_two_response,"good bye") == 0)
	    {
	        good_bye_count++;
	        
	    } 
	}

}



int main()
{
	int tdStatus;
	pthread_t TID_1, TID_2;

	

	tdStatus = pthread_create(&TID_1, NULL, sender, NULL);
	if(tdStatus != 0){
		perror("Error during pthread_create()");
		exit(EXIT_FAILURE); // Equivalent of "return 1;".
	}

	


	tdStatus = pthread_create(&TID_2, NULL, received, NULL);
	if(tdStatus != 0){
		perror("Error during pthread_create()");
		exit(EXIT_FAILURE);
	} 

	while(1)
	{
        if(good_bye_count == 2)
        {
            break;
        }
	}

	return 0;
}

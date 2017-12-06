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
#include <stdlib.h>


//global variable
int good_bye_count = 0;
int client_socket;



void *sender()
{
    
    //declaring the variables

	char messenger_two_message[256];
	

	while(good_bye_count != 2)
	{
        //printf("sender in while\n");

		scanf ("%[^\n]%*c", messenger_two_message);  ///send good bye to finish the conversation

		//scanf("%[^\n]s",server_message);
				
	   	int sending = send(client_socket,&messenger_two_message,sizeof(messenger_two_message),0);
				
		if(sending < 0)
		{
			perror("In server sending");
		}

		if(strcmp(messenger_two_message,"good bye") == 0)
        {
                good_bye_count++;
        }
	}


}


void *received()
{
    //printf("receiver\n");

	// STEP-1: socket()
    // 1.1. Create a socket.
    
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

    printf("connection stablish\n");

    
    // STEP-3: recv()
    // 3.1. Receive data from the server

    //declaring the variables

	char messenger_one_response[256];


	while(good_bye_count != 2)
	{
        //printf("receiver in while\n");

		int receiving = recv(client_socket, &messenger_one_response, sizeof(messenger_one_response), 0);

    	if(receiving < 0)
        {
        	printf("received is failed\n");
        }
        else
        {

            // 3.2. Check sever's response.
            printf("Imran: %s\n", messenger_one_response);
        }


        if(strcmp(messenger_one_response,"good bye") == 0)
	    {
	        good_bye_count++;
	        
	    }
	}



	// STEP-4: close()
    // 4.1. Close the socket
    close(client_socket);
}



int main()
{
	pthread_t TID[3];
    int tdstatus;


    
	tdstatus = pthread_create(&TID[0],NULL,sender,NULL);
	
	if(tdstatus != 0)
	{
		perror("Error during pthread_create()");
		//exit(EXIT_FAILURE); // Equivalent of "return 1;".

        return 1;
	}


	tdstatus = pthread_create(&TID[1],NULL,received,NULL);
	
	if(tdstatus != 0)
	{
		perror("Error during pthread_create()");
		//exit(EXIT_FAILURE); // Equivalent of "return 1;".

        return 1;
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
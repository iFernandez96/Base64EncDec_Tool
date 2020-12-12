#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "Base64.h"


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

   if( argc == 2 )
   {
      printf("Not enough arguments provided.");
      PrintUseCase();
   }
   else if(argc == 3)
   {
       if (*argv[1] == '1')
       {
            FILE *fp = fopen(argv[2], "r+");
            
            fseek(fp, 0L, SEEK_END);
            long size = ftell(fp);
            rewind(fp);

            char * data;
            fread(data, 1, size, fp);
            
            fclose(fp);
            char * encoded_data = base64_encode(data, size, &size);
            
            fp = fopen(OutputFileForEncoded, "w+");
            fwrite(encoded_data, 1, strlen(encoded_data), fp);
            fclose(fp);

            printf("Encoded Data is stored into: %s \n", OutputFileForEncoded);
       }
       else if (*argv[1] == '2')
       {
            FILE *fp = fopen(argv[2], "r+");
            
            fseek(fp, 0L, SEEK_END);
            long size = ftell(fp);
            rewind(fp);

            char * encoded_data;
            fread(encoded_data, 1, size, fp);
            
            fclose(fp);

            char * decoded_data = base64_decode(encoded_data, size, &size);

            fp = fopen(OutputFileForDecoded, "w+");
            fwrite(encoded_data, 1, strlen(encoded_data), fp);
            fclose(fp);

            printf("Decoded Data is stored into: %s \n", OutputFileForDecoded);
       }
       else if (*argv[1] == '3')
       {
          system(argv[2]);
       }
   }
   else if( argc > 3 )
   {
      printf("Too many arguments supplied.\n");
      PrintUseCase();
   }
   else
   {
      printf("Two arguments expected.\n");
      PrintUseCase();
   }



   return 0;
}
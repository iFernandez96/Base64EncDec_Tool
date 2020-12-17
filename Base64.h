char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                         'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                         'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                         'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                         'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                         'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                         'w', 'x', 'y', 'z', '0', '1', '2', '3',
                         '4', '5', '6', '7', '8', '9', '+', '/'};


uint8_t CheckIfCharacter(uint8_t C)
{
   if ((C >= '0' && C <= '9') || (C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z') || C == '+' || C == '/')
   {
      return 1;
   }
   return 0;
}

size_t base64_encode(uint8_t* data, int data_size, uint8_t* DecodedOutput)
{
   int i, j, Num;
   
   for (i = 0, j = 0; i < data_size; i+=3, j+=3)
   {
      Num = data[i];
      Num = i+1 < data_size ? Num << 8 | data[i+1] : Num << 8;
      Num = i+2 < data_size ? Num << 8 | data[i+2] : Num << 8;

      DecodedOutput[j] = encoding_table[(Num >> 18) & 0x3F];
      
   }
   return 0;
}
 
unsigned char *base64_decode(const char *data, size_t input_length, size_t *output_length)
{

    return decoded_data;
}

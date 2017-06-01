


/*
**	Description:	To decode the data, encoded using 3 character encoding technique.
*/





#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void ThreeCharacterEncoding_Decode(uint8_t byte3, uint8_t byte2, uint8_t byte1, uint32_t *decodedOutput);

int main(void)
{
	uint32_t forDecodingDebug;
	uint8_t byte3, byte2, byte1;
	while(1)
	{
		printf("Input 3 bytes of data : \n");
		scanf("%u%u%u", &byte3, &byte2, &byte1);
		ThreeCharacterEncoding_Decode(byte3, byte2, byte1, &forDecodingDebug);
		printf("Decoded Value = %d\n", forDecodingDebug);
	}
}


/*
**	@brief											Function to decode the 3 character encoding, to extract the encoded distance.
**	@byte3(PARAM_IN)						Higher encoded byte.
**	@byte2(PARAM_IN)						High encoded byte.
**	@byte1(PARAM_IN)						Low encoded byte.
**	@decodedOutput(PARAM_OUT)		Pointer to the variable which will contain the decoded output.
*/
void ThreeCharacterEncoding_Decode(uint8_t byte3, uint8_t byte2, uint8_t byte1, uint32_t *decodedOutput)
{
	uint8_t temp_byte1;
	uint8_t temp_byte2;
	uint8_t temp_byte3;
	
	/*	Decryption starts with subtracting 0x30 from each of the encoded bytes	*/
	temp_byte3 = byte3 - 0x30;
	temp_byte2 = byte2 - 0x30;
	temp_byte1 = byte1 - 0x30;
	
	/*	Reset all bits of the output variable	*/
	*decodedOutput &= ~(*decodedOutput);
	
	/*	Populate the output variable with decoded data	*/
	*decodedOutput |= (temp_byte3 << 12);
	*decodedOutput |= (temp_byte2 << 6);
	*decodedOutput |= (temp_byte1 << 0);
	
	return;
}

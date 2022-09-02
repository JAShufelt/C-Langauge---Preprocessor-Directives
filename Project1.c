#include "Project1.h"

int main()
{
	unsigned int input_num = 0;
	int len = 15;
	char input[15];
	char selection[12] = "decimal";		//Default to decimal if no definition provided at compilation
	char option_num;

	#ifdef BINARY
		strcpy(selection, "binary");
	#endif

	#ifdef HEXADECIMAL
		strcpy(selection, "hexadecimal");
	#endif

	printf("Input number: ");	
	fgets(input, 15, stdin);			//Receives user input for "input"
	string_fix(&input, 15);				//Formats input into a string
	str_to_lint(&input_num, &input);	//Converts string into unsigned long int

	while(1)
	{
		printf("Select option:\n");
		printf("1 - display number in %s\n", selection);
		printf("2 - exchange outer bytes\n");
		printf("3 - exchange inner bytes\n");
		printf("4 - display number of set bits in each byte\n");
		printf("5 - exit\n");

		fgets(input, 15, stdin);	//Receives input for user option selection. 
		string_fix(&input, 15);		//Properly format user input into string.
		option_num = atoi(input);	//Convert string into integer in option_num

		switch((int)option_num)
		{
		case 1:
			printf("number:\t"); display_routine(input_num); printf("\n");
			break;
		case 2:
			printf("number before:\t"); display_routine(input_num); printf("\n");
			XOUTER(input_num);
			printf("number after:\t"); display_routine(input_num); printf("\n");
			break;
		case 3:
			printf("number before:\t"); display_routine(input_num); printf("\n");
			XINNER(input_num);
			printf("number after:\t"); display_routine(input_num); printf("\n");
			break;
		case 4:
			setbytes_count(input_num);	//Calls routine to print the count of set bits for each byte within input_num
			break;
		case 5:
			return 0;	//Exit successfully
			break;
		}
	}
}

void string_fix(char* input, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (input[i] == '\n')
		{
			input[i] = '\0';
			break;
		}
	}
}

void str_to_lint(unsigned long int* num, char* input)
{
	*num = 0;
	int end_index = 0;
	for(int i = 0; input[i] != '\0'; i++)	//Locates end of string and stores index into end_index
	{
		end_index = i;
	}

	for(int i = end_index, mult = 1; i > -1; i--, mult*=10)	//Starts at the end of string (1s digit in decimal) and adds each decimal digit into num
	{
		*num = *num + ((((int)input[i]) - 48) * mult);	//NOTE "-48" because ASCII value of 0 is 48. subtract 48 to convert char to int properly.
	}
}

void setbytes_count(unsigned long int num)
{
	num = (num & 0xFFFFFFFF);	//Zero out any bits greater than 2^31;
	int bytes[4] = { 0,0,0,0 };
	
	for(int i = 0; i < 4; i++)	//For each of the 4 bytes
	{
		for(int j = 0; j < 8; j++)	//For each 8 bits of byte i
		{
			if(num & 1)
			{
				bytes[i]++;
			}
			num >>= 1;
		}
	}
	printf("byte 3 count: %d byte 2 count: %d byte 1 count: %d byte 0 count: %d \n", bytes[3], bytes[2], bytes[1], bytes[0]);

}

void display_routine(unsigned long int num)
{
	#ifdef BINARY
		for(unsigned int i = TWO_TO_POW_31; i > 0; i/=2)
		{
			if (num & i)
				printf("%d", 1);
			else
				printf("%d", 0);
		}
	
	#elif defined HEXADECIMAL
		printf("0x%08x", num);
	
	#elif defined DECIMAL
		printf("%u", num);
	
	#else	//Default is decimal
		printf("%u", num);
	#endif
}
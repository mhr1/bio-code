/*
 *  FASTA_reader.cpp
 *  
 *
 *  Created by Mhr on 07/03/2012.
 *  Copyright 2012. All rights reserved.
 *
 */

#include "FASTA_reader.h"
#include <iostream>

/** This will get one sequence and one header from a FASTA format file. If there is more than one
 sequence then the contents of header and sequence will be those of the last sequence in the file.
 */
/*
int FASTA::file_reader_dep(const char* filename)
{
	sequence_fa.open(filename);
	char buffer[2056];
	bool FASTA_SEQUENCE = FALSE;
	
	if(!sequence_fa.is_open())return(-1); // -1 file error
	
	while(sequence_fa.getline(buffer, 2055))
	{
		if(buffer[0] == 0x3E)  // fasta header
		{
			header = (char*) malloc(strlen(buffer) + 1);
			strcpy(header, strtok(buffer,">\n"));
			FASTA_SEQUENCE = FALSE;
		}
		else if(FASTA_SEQUENCE)
		{
			sequence = (char*)realloc(sequence, strlen(sequence) + strlen(buffer) + 1);
			strcat(sequence, buffer);
		}
		else 
		{
			sequence = (char*) malloc(strlen(buffer) + 1);
			strcpy(sequence, buffer);
			FASTA_SEQUENCE = TRUE;
		}
	}
	return(TRUE);
}*/

int FASTA::single_sequence_reader(ifstream &sequence_fa)
{	
	bool FASTA_SEQUENCE = FALSE;	
	string t_buffer;
		
	while(getline(sequence_fa, t_buffer))
	{
		
		if(t_buffer[0] == 0x3E)  // fasta header
		{
			if(FASTA_SEQUENCE) // Header and sequence complete
				return(TRUE);
			
			header = t_buffer;
			FASTA_SEQUENCE = FALSE;
		}
		else if(FASTA_SEQUENCE)
		{
			sequence += t_buffer;
		}
		else 
		{
			sequence = t_buffer;
			FASTA_SEQUENCE = TRUE;
		}
	} 
	return(TRUE);
}

int FASTA::read_all_header_IDs(const char* filename)
{
	string t_buffer;
	sequence_fa.open(filename);
	string header_list;
	string temp_str;
	char temp[128];
	char *buffer;
	
	if(!sequence_fa.is_open())return(-1); // -1 file error
	
	number_of_headers = 0;
	
	while(getline(sequence_fa, t_buffer))
	{		
		if(t_buffer[0] == 0x3E)  // fasta header
		{
			buffer = new char [t_buffer.size() + 1];
			strcpy(buffer, t_buffer.c_str());
			strcpy(temp, strtok(buffer, "> \n"));
			
			//cout << "Header " << number_of_headers << " = " << temp << endl;
			header_list += temp_str.assign(temp);
			header_list += "\n";
			number_of_headers++;
		}
	} 
	
	cout << header_list << endl;
	
	return(TRUE);
}

/*
 *  FASTA_reader.h
 *  
 *
 *  Created by Mhr on 07/03/2012.
 *  Copyright 2012 Michael C. Riley. All rights reserved.
 *
 */

#ifndef FASTA_READER_H
#define FASTA_READER_H

#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>

#define FALSE 0
#define TRUE 1

using namespace std;

class FASTA
{
public:
	FASTA(){};
	~FASTA(){};
	int single_sequence_reader(ifstream &sequence_fa);
	//int file_reader_dep(const char* filename);
	int read_all_header_IDs(const char* filename);
	string header;
	string sequence;
	int number_of_headers;
	
private:
	ifstream sequence_fa;
	
};

#endif

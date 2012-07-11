/*
 *  g_data_analysis.cpp
 *  
 *
 *  Created by Mhr on 07/03/2012.
 *  Copyright 2012 University of Wales, Aberystwyth. All rights reserved.
 *
 */

#include <cstdio>
#include <iostream>
#include "FASTA_reader.h"
#include <ctime>

#define A 65
#define T 84
#define G 71
#define C 67

using namespace std;

int main(int argc, char** argv)
{
	
	char filename[128];
	int i, j, k, n;
	int nuc[4] = {65,84,71,67};
	char codon[64][3];
	
	char *sequence;
	clock_t start, stop;
	
	// Make Codons
	n = 0;
	
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			for(k = 0; k < 4; k++)
			{
				codon[n][0] = nuc[i];
				codon[n][1] = nuc[j];
				codon[n][2] = nuc[k];	
				n++;
			}
		}
	}
	
	int codon_array = n;
	
   	//cout << "genome data analysis 7th March 2012\n";
	//cout << "Version 1.0\n";
	
	cout << argv[1] << endl << endl;
	
	if(!(argv[1]))
	{
		cout << "Use: exe <gene sequence file>\n";
		return(0);
	}
	else 
	{
		strcpy(filename, argv[1]);
	}
	
	/** Use FASTA object my_fa to read FASTA file given in first argument of command line */
	FASTA my_fa;	
	my_fa.read_all_header_IDs(filename);
	//cout << "Header: " << my_fa.header << endl;
	//cout << "Sequence: " << my_fa.sequence << endl;
	
	/*my_fa.file_reader(filename);
	cout << "Header: " << my_fa.header << endl;
	//cout << "Sequence: " << my_fa.sequence << endl;*/
	
	return(TRUE);
	
	start = clock();
	
	int seq_len = my_fa.sequence.size();
	long count = 0;
	
	for(i = 0; i < codon_array; i++)
	{	
		count = 0;
		
		for(int j = 0; j < seq_len - 2; j++)
		{
			if (my_fa.sequence[j]     == codon[i][0] &&
				my_fa.sequence[j + 1] == codon[i][1] &&
				my_fa.sequence[j + 2] == codon[i][2])
				count++;
			/*
			if (*(my_fa.sequence + j)     == codon[i][0] &&
				*(my_fa.sequence + j + 1) == codon[i][1] &&
				*(my_fa.sequence + j + 2) == codon[i][2])
				count++;*/
				
		}
		cout << "Codon " << codon[i][0] << codon[i][1] << codon[i][2] << " occurs " << count << " times\n";
		count = 0;
	}
	stop = clock();
	
	cout << "Processing time: " << stop - start << " microseconds" << endl;
	
	cout << "Phase II using char array\n";
	start = clock();
	sequence = new char [my_fa.sequence.size() + 1];
	strcpy(sequence, my_fa.sequence.c_str());

	
	for(i = 0; i < codon_array; i++)
	{	
		count = 0;
		
		for(int j = 0; j < seq_len - 2; j++)
		{
			/*if (sequence[j]     == codon[i][0] &&
				sequence[j + 1] == codon[i][1] &&
				sequence[j + 2] == codon[i][2])
				count++;*/
			
			if (*(sequence + j)     == codon[i][0] &&
				*(sequence + j + 1) == codon[i][1] &&
				*(sequence + j + 2) == codon[i][2])
				count++; // fastest
			
			/*if (*(sequence + j)     == *(codon[i]) &&
				*(sequence + j + 1) == *(codon[i]+1) &&
				*(sequence + j + 2) == *(codon[i]+2))
			 count++;*/
			
		}
		cout << "Codon " << codon[i][0] << codon[i][1] << codon[i][2] << " occurs " << count << " times\n";
		count = 0;
	}
	stop = clock();
	
	cout << "Processing time: " << stop - start << " microseconds" << endl;
	
    return(1);
}

/**
 Here's the output from this app for S. cere chr 4
 
 Header: Chr_IV
 Codon AAA occurs 60840 times
 Codon AAT occurs 45659 times
 Codon AAG occurs 33698 times
 Codon AAC occurs 27468 times
 Codon ATA occurs 37889 times
 Codon ATT occurs 45546 times
 Codon ATG occurs 28135 times
 Codon ATC occurs 27411 times
 Codon AGA occurs 31835 times
 Codon AGT occurs 23358 times
 Codon AGG occurs 17748 times
 Codon AGC occurs 17429 times
 Codon ACA occurs 26340 times
 Codon ACT occurs 22880 times
 Codon ACG occurs 13030 times
 Codon ACC occurs 17483 times
 Codon TAA occurs 33959 times
 Codon TAT occurs 37825 times
 Codon TAG occurs 20060 times
 Codon TAC occurs 21625 times
 Codon TTA occurs 34561 times
 Codon TTT occurs 60872 times
 Codon TTG occurs 35576 times
 Codon TTC occurs 36105 times
 Codon TGA occurs 31704 times
 Codon TGT occurs 26232 times
 Codon TGG occurs 22230 times
 Codon TGC occurs 18786 times
 Codon TCA occurs 30988 times
 Codon TCT occurs 30863 times
 Codon TCG occurs 13823 times
 Codon TCC occurs 19262 times
 Codon GAA occurs 37327 times
 Codon GAT occurs 27166 times
 Codon GAG occurs 17531 times
 Codon GAC occurs 14706 times
 Codon GTA occurs 21415 times
 Codon GTT occurs 27703 times
 Codon GTG occurs 16231 times
 Codon GTC occurs 14602 times
 Codon GGA occurs 19557 times
 Codon GGT occurs 17310 times
 Codon GGG occurs 9742 times
 Codon GGC occurs 11762 times
 Codon GCA occurs 18799 times
 Codon GCT occurs 17443 times
 Codon GCG occurs 8387 times
 Codon GCC occurs 11673 times
 Codon CAA occurs 35539 times
 Codon CAT occurs 28331 times
 Codon CAG occurs 19081 times
 Codon CAC occurs 15933 times
 Codon CTA occurs 19604 times
 Codon CTT occurs 32993 times
 Codon CTG occurs 19010 times
 Codon CTC occurs 16818 times
 Codon CGA occurs 13634 times
 Codon CGT occurs 13051 times
 Codon CGG occurs 8652 times
 Codon CGC occurs 8325 times
 Codon CCA occurs 22757 times
 Codon CCT occurs 17239 times
 Codon CCG occurs 8422 times
 Codon CCC occurs 9954 times
 
 Note: Using character arrays is more than twice as fast as string container
*/ 

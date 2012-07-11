/*
 *  header_reader.cpp
 *  
 *
 *  Created by Mhr on 07/03/2012.
 *  Copyright 2012 University of Wales, Aberystwyth. All rights reserved.
 *
 */

#include "FASTA_reader.h"

using namespace std;

int main(int argc, char** argv)
{
	FASTA my_fa;
	my_fa.read_all_header_IDs("lactis_220612_1000_all.fa");
		
	return(1);
}
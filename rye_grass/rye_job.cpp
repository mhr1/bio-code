/*
 rye_job.cpp
 
 Creates Beowulf submit_job scripts for each rad id in qvalues_foralltraitcomponents_ls151211.csv over a q value of 0.5
 
 For each successful Rad ID the sequence is extracted from the file rad.fa
 
 */

#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;

int run_blastn_job(const char* sequence, const char* name, const char* template_filename, int linkage_grp)
{
	char query_filename[64], submit_filename[64], command[256];                
    ofstream query_file, submit_file; // for sequence to be BLASTed
  
// Make sequence into a FASTA file for input to blastn using 'name' for the filename
// and for the FASTA header
    sprintf(query_filename, "%s.tfa", name);
    query_file.open(query_filename);
    query_file << ">" << name << endl << sequence << endl;
    query_file.close();
	
// Make condor submit file
	sprintf(submit_filename, "%s_submit", name);
    submit_file.open(submit_filename);
    submit_file << "Executable = rye_b\n"
				<< "Universe = vanilla\n"
				<< "notification = never\n"
				<< "should_transfer_files = YES\n"
				<< "when_to_transfer_output = ON_EXIT\n"
				<< "arguments = " << name << " " << template_filename << " " << linkage_grp << endl
				<< "transfer_input_files = blastn, " << template_filename << ", " << query_filename << endl
				<< "log = " << name << ".log\n"
				<< "output = " << name << ".out\n"
				<< "error = " << name << ".err\n"
				<< "queue\n";
	
    submit_file.close();
	
// Submit job
	sprintf(command, "condor_submit %s_submit", name);
	system(command);
	
	return(1);
}


int main(int argc, char** argv)
{  
	char buffer[2056];
	char* token;
	char csv_data[1000][32];    
	char sequence[128] = {"CTCGACATGCCCAGGCTCCTGAACAAGCCGGCGTTCGGCACGGGCCCCTCGAGGCGGTTCGACGAGAGGTTGAGAKCCCTCAGG"};
	char rad_id[1000][32];
	int linkage_group[1000];
	double qc183_y1c1[1000];
	double threshold = 0.5;
	int data_count;
	string results;

    ifstream fin_qvalues("qvalues_foralltraitcomponents_ls151211.csv");
	ifstream fin_rad;
        /*if(argc != 2) {
          cout << argv[0] << ": Please provide a DNA string as argument" << endl;
          exit(1);
        }*/
	
	// Get top line
	fin_qvalues.getline(buffer, 2055);
	
	int i = 0;
	int columns = 0;
	
	token = strtok(buffer, ",\r\t\n");
	strcpy(csv_data[columns], token);
	columns++;
	
	while(token = strtok(NULL, ",\r\t\n"))
	{
		if(token)
		{
			strcpy(csv_data[columns], token);
			columns++;
		}
	}
	
	// Show data as csv
	//cout << csv_data[0]; for(i = 1; i < columns; i++)cout << ", " << csv_data[i]; cout << endl;
	
	// Need to get rad ID for chosen qvalue > 0.5, and find the corresponding sequence in rad.fa.
	
    //blastn_sequence(sequence, "my_seq", "rice_chromosomes.fa")? cout << "Ok\n": cout << "Fail\n";
    
// Get all rad IDs for qvalue > 0.5	
	data_count = 0;	 
	while(fin_qvalues.getline(buffer, 2055))
	{
		columns = 0;
		token = strtok(buffer, ",\r\t\n");	
		columns++;
	
		while(token = strtok(NULL, ",\r\t\n"))
		{
			if(token)
			{
				if(columns == 1)strcpy(rad_id[data_count], token);
				if(columns == 2)linkage_group[data_count] = atoi(token);
				if(columns == 8)qc183_y1c1[data_count] = atof(token);
				columns++;
			}
		}
		if(qc183_y1c1[data_count] > threshold)data_count++;
	}
	
	for(i = 0; i < 10; i++) cout << rad_id[i] << ", " << qc183_y1c1[i] << endl;

	// Get sequences for selected rad IDs and BLAST them
	char rad_buffer[128];
	char temp_rad_id[32];

	cout << "Data count is " << data_count << endl;
	
	for(i = 0; i < data_count; i++)
	//for(i = 510; i < 520; i++)
	{
		sprintf(temp_rad_id, ">%s", rad_id[i]);
		
		fin_rad.open("rad.fa");
		while(fin_rad.getline(rad_buffer, 127))
		{
			token = strtok(rad_buffer, " \t\r\n");
			//cout << "Token is " << token << endl;
			if(!strcmp(temp_rad_id, token))
			{
				fin_rad.getline(rad_buffer, 127);
				//token = strtok(rad_buffer, " \t\r\n");
				strcpy(sequence, rad_buffer);
				
				cout << i << ": " << sequence << endl;
				
				if(strlen(sequence) < 80) // Normally 84 in length
					cout << "Sequence shorter than expected\n";
				else
				{
					run_blastn_job(sequence, rad_id[i], "rice_chromosomes.fa", linkage_group[i]);
				}
					
				break;
			}
		
		}
		
		cout << "Results: " << results;
		fin_rad.close();
		
		
	}
    return(1);
}  

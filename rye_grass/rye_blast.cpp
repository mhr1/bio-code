
/** USE: <exec> <query name/id> <template/subject filename> <linkage_group>

For work done in May 2012:
	build = g++ rye_blast.cpp -o rye_b
 <exec> 						= 'rye_b'
 <query name/id> 				= rad tag name* (must correspond to an existing .tfa file, 
												eg 'test' for test.tfa when testing on central)
 <template/subject filename> 	= 'rice_chromosomes.fa'
 Note that linkage group is just an integer often referring to chromosome number
 
 * rad tag rad_xxxxx_yy.zz 
		where xxxx 	= unique number for the rad sequence/contig
		yy 			= sequence depth (confidence in SNP
		zz			= location of SNP on RAD sequence
*/

#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;
class results_data
{
public:
	char query[64];
	long query_length;
	char subject[64];
	long subject_length;
	//char chromosome[16];
	double e_result;
	double bit_score;
	int score;
	int identity;
	int match_length;
	double percent_identity;
	long query_start_location;
	char query_hit_sequence[1024];
	long query_end_location;
	char identity_sequence[1024];
	long subject_start_location;
	char subject_hit_sequence[1024];
	long subject_end_location;
};

class genblast
{
public:
	genblast();
	~genblast(){};
	
	int blastn_results_parser(const char* filename);
	int blastn_sequence(const char* sequence, const char* name, const char* template_filename);
	int blastn_file(const char* query_filename, const char* template_filename, const char* name);

// Blast parameters	
	double evalue; 
    int wordsize;

// Blast results
	int hits_total;
	results_data res[1024];
	
	
private:
	
};

genblast::genblast(void)
{
// Defaults
	evalue = 1.0e-6; // 1.0e-6 is Matt's evalue
	wordsize = 7;
}

/* 
 The results parser takes the output file from blast and puts the data into an array
 of results_data objects 
 */

int genblast::blastn_results_parser(const char* filename)
{       
    char buffer[256];
    char temp[256];
    char* token;
	
	int hit_count = 0;
	char query[64];
	long query_length;
	char subject[64];
	long subject_length;
	double evalue;
	
    ifstream fin(filename);
        
    while(fin.getline(buffer, 255))
    {
        if(!strncmp(buffer, "Query=", 6))
        { 
            token = buffer + 7;
			strcpy(query, token);
			cout << query << endl;
			
			fin.getline(buffer, 255);
			fin.getline(buffer, 255);
            
			if(!strncmp(buffer, "Length", 6))
			{
					token = buffer + 7;
					query_length = atol(token);
					//cout << query_length << endl;
			}
			else 
				cout << "Error - Query length missed\n";			

			while(fin.getline(buffer, 255))
			{
				if(!strncmp(buffer, "Subject", 7))
				{
					token = buffer + 9;
					strcpy(subject, token);
					//cout << subject << endl;
					fin.getline(buffer, 255);
					fin.getline(buffer, 255);
					
					if(!strncmp(buffer, "Length", 6))
					{
						token = buffer + 7;
						subject_length = atol(token);
						//cout << subject_length << endl;
					}
					else
						cout << "Error - Subject length missed\n";
					
					break;
				}
			}
			
// Now get hits

			//hit_count = 0;
			while(fin.getline(buffer, 255))
			{
				if(!strncmp(buffer, "*****", 5))
				{
					// No hits
					cout << "No hits\n";
				}
				if(!strncmp(buffer, " Score", 6))
				{
					// We have a hit
					strcpy(res[hit_count].query, query); 
					res[hit_count].query_length = query_length;					
					strcpy(res[hit_count].subject, subject);
					res[hit_count].subject_length = subject_length;
					//cout << res[hit_count].chromosome << endl;
					
					token = strtok(buffer, " =(),\n\t\r"); // "Score"
					token = strtok(NULL, " =(),\n\t\r"); // score value bits
					res[hit_count].bit_score = atof(token);
					//cout << res[hit_count].bit_score << endl;
					
					token = strtok(NULL, " =(),\n\t\r"); // "bits"					
					token = strtok(NULL, " =(),\n\t\r"); // score value
					res[hit_count].score = atoi(token);
					//cout << res[hit_count].score << endl;
					
					token = strtok(NULL, " =(),\n\t\r"); // "Expect"
					token = strtok(NULL, " =(),\n\t\r"); // e value					
					res[hit_count].e_result = atof(token); 
					//cout << res[hit_count].e_result << endl;
					
					fin.getline(buffer, 255);
					token = strtok(buffer, " =(),/\n\t\r"); // "Identities"
					token = strtok(NULL, " =(),/\n\t\r"); // identity
					res[hit_count].identity = atoi(token);
					//cout << res[hit_count].identity << endl;
					
					token = strtok(NULL, " =(),/\n\t\r"); // match length
					res[hit_count].match_length = atoi(token);
					//cout << res[hit_count].match_length << endl;
					
					token = strtok(NULL, " =(),/%\n\t\r"); // score value
					res[hit_count].percent_identity = atof(token);
					//cout << res[hit_count].percent_identity << endl;
					
					// Next line example:- Strand=Plus/Plus, Strand=Plus/Minus
					fin.getline(buffer, 255);
					
					// Blank line
					fin.getline(buffer, 255);
					
					// Next line - Eg: Query  43        GGCCCCTCGAGGCGGTTCGACGA  65
					fin.getline(buffer, 255);
					token = strtok(buffer, " =(),/\n\t\r"); // "Query"
					token = strtok(NULL, " =(),/\n\t\r"); // start location
					res[hit_count].query_start_location = atoi(token);
					
					token = strtok(NULL, " =(),/\n\t\r"); // query_hit_sequence
					strcpy(res[hit_count].query_hit_sequence, token);
		
					token = strtok(NULL, " =(),/%\n\t\r"); // end location
					res[hit_count].query_end_location = atoi(token);
					
					// Eg:                  ||||| |||||| ||||||||||
					fin.getline(buffer, 255);
					token = strtok(buffer, " =(),/\n\t\r"); 
					strcpy(res[hit_count].identity_sequence, token);
					
					// Eg: Sbjct  20307025  GGCCCGTCGAGGTGGTTCGACGA  20307003
					fin.getline(buffer, 255);
					token = strtok(buffer, " =(),/\n\t\r"); // "Sbjct"
					token = strtok(NULL, " =(),/\n\t\r"); // start location
					res[hit_count].subject_start_location = atoi(token);
					
					token = strtok(NULL, " =(),/\n\t\r"); // query_hit_sequence
					strcpy(res[hit_count].subject_hit_sequence, token);
					
					token = strtok(NULL, " =(),/%\n\t\r"); // end location
					res[hit_count].subject_end_location = atoi(token);
					
					
					//cout << hit_count << ", " << subject << ", " << evalue << endl;
					hit_count++;
				}
				
				if(!strncmp(buffer, "Lambda", 6)) // End of record for sequence/chromosome
				{
					fin.getline(buffer, 255);
					// tokenise(" \t") buffer to get Lambda, K and H values
					break;
				}

			}
			//cout << "We have " << hit_count << " for " << subject << endl;
			hits_total = hit_count;
        }                               
    } 
    return(1); 
}

/* blast requires 2 files as input, so this method simply makes a <name>.fa file of the sequence
 before calling the blastn_file method*/


int genblast::blastn_sequence(const char* sequence, const char* name, const char* template_filename)
{
    char query_filename[64];                
    ofstream fseq; // for sequence to be BLASTed
     
// Make sequence into a FASTA file for input to blastn using 'name' for the filename
// and for the FASTA header
    sprintf(query_filename, "%s.fa", name);
    fseq.open(query_filename);
    fseq << ">" << name << endl << sequence << endl;
    fseq.close();
  
	blastn_file(query_filename, template_filename, name);
	
	return(1);
}

/* System call to blast followed by a call to the blastn_results parser */

int genblast::blastn_file(const char* query_filename, const char* template_filename, const char* name)
{
	char command[1024];
	
// Run blastn (Orig. "./blastn -subject %s -query %s.fa -evalue %f -word_size %i -dust no -ungapped -out %s.out") 
    sprintf(command, 
	  "./blastn -subject %s -query %s -evalue %f -word_size %i -out %s.out", 
	  template_filename, 
	  query_filename,
	  evalue,
	  wordsize,
	  name);
	  
    system(command); //? Ok = 1:Ok = 0; No, system does not pick up failed apps.

// Parse results 
	char out_filename[32];
	
	sprintf(out_filename, "%s.out", name);
	blastn_results_parser(out_filename);

	return(1); 

}

int main(int argc, char** argv)
{  
	char name[32];
	char query_filename[64], results_filename[64], template_filename[64];
	int linkage_group;
	
	strcpy(name, argv[1]);
	strcpy(template_filename, argv[2]);
	linkage_group = atoi(argv[3]);
	//cout << name << endl;
	
	sprintf(results_filename, "%s.res", name);
	ofstream fres(results_filename);
	genblast myblast;
	// Blast parameters: E < 1 * 10-6, hit length >60bp
	myblast.evalue = 1.0e-6;
	myblast.wordsize = 7;
	
	sprintf(query_filename, "%s.tfa", name);
	myblast.blastn_file(query_filename, template_filename, name);
	
	//fres << ">" << name << " " << linkage_group << endl;
	
	for(int i = 0; i < myblast.hits_total; i++)
	{
		if(myblast.res[i].match_length >= 60)
		{
			fres << name << ", " << linkage_group << ", " << myblast.res[i].subject << ", "			
				<< myblast.res[i].subject_start_location << ", " << myblast.res[i].e_result << ", " 
				<< myblast.res[i].percent_identity << ", " << myblast.res[i].match_length << endl;
		}
	}
	
	fres.close();
    return(1);
}      


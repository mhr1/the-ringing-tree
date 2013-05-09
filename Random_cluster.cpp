/*
   Random cluster (25/01/10) produces a random nucleotide sequence which is mutated
   at random a set number of times for each generation.

   Nucleotide sequences can be translated to protein sequences using
   translate(char*, char*).

   Pipe std::out to a file at runtime.
*/

#include "epro.h"
using namespace std;

static unsigned long my_seed = 11056; //default random seed
#define MY_RAND_MAX 2147483646 // 2^32 - 2, 1 less than mod value in rand no gen

#define SEQUENCE_LENGTH 36
unsigned long my_rand(void)
{
	// Park & Miller's minimal standard multiplicative congruential algorithm
   // USE: Pick a random number x  from range
	//	x = (int)((double)my_rand() * (double)range/MY_RAND_MAX);
	unsigned long random_number;

	random_number = (16807 * my_seed) % (MY_RAND_MAX + 1);
	my_seed = random_number;
	return(random_number);
}


int translate(char* sequence, char* protein)
{  char amino_acid[32] = "ACDEFGHIKLMNPQRSTVWYL" ;
   int i, j;

   for(i = 0; i < (strlen(sequence)/3)-1; i++)
   {

		j = i * 3;
      
		switch(sequence[j])
      {  case 0x41: switch(sequence[j + 1])
	      {  case 0x41: switch(sequence[j + 2])
            {  case 0x41: case 0x47: protein[i] = amino_acid[8]; break;
               case 0x43: case 0x54: protein[i] = amino_acid[11]; break;
               //default: cout << "?";
            }break;
	         case 0x54: switch(sequence[j + 2])
            {  case 0x47: protein[i] = amino_acid[10]; break;
               case 0x41: case 0x43: case 0x54: protein[i] = amino_acid[7];
               //default: cout << "?";
            } break;
	         case 0x47: switch(sequence[j + 2])
            {  case 0x41: case 0x47: protein[i] = amino_acid[14]; break;
               case 0x43: case 0x54: protein[i] = amino_acid[15]; break;
               //default: cout << "?";
            } break;
	         case 0x43: protein[i] = amino_acid[16]; break;
            default: cout << "?";
	      } break;

         case 0x54: switch(sequence[j + 1])
	      {  case 0x41: switch(sequence[j + 2])
            {  case 0x43: case 0x54: protein[i] = amino_acid[19]; break;
            	case 0x41: case 0x47: protein[i] = amino_acid[20]; break;
            } break;
	         case 0x54: switch(sequence[j + 2])
            {  case 0x43: case 0x54: protein[i] = amino_acid[5]; break;
               case 0x41: case 0x47: protein[i] = amino_acid[9]; break;
            } break;
	         case 0x47: switch(sequence[j + 2])
            {  case 0x47: protein[i] = amino_acid[18]; break;
               case 0x41: protein[i] = amino_acid[20]; break;
               case 0x43: case 0x54: protein[i] = amino_acid[1]; break;
            } break;
	         case 0x43: protein[i] = amino_acid[15]; break;
	      } break;

         case 0x47: switch(sequence[j + 1])
	      {  case 0x41: switch(sequence[j + 2])
            {  case 0x43: case 0x54: protein[i] = amino_acid[2]; break;
            	case 0x41: case 0x47: protein[i] = amino_acid[3]; break;
            } break;
	         case 0x54: protein[i] = amino_acid[17]; break;
	         case 0x47: protein[i] = amino_acid[5]; break;
	         case 0x43: protein[i] = amino_acid[0]; break;
	      } break;

         case 0x43: switch(sequence[j + 1])
	      {  case 0x41: switch(sequence[j + 2])
            {  case 0x43: case 0x54: protein[i] = amino_acid[6]; break;
               case 0x41: case 0x47: protein[i] = amino_acid[13]; break;
            } break;
	         case 0x54: protein[i] = amino_acid[9]; break;
	         case 0x47: protein[i] = amino_acid[14]; break;
	         case 0x43: protein[i] = amino_acid[12]; break;
	      } break;

         default: cout << "?";
      }
   }
   protein[(strlen(sequence)/3)-1] = 0x00;
   return(0);
}

int mutate(char* sequence, int number)
{  
	char nucleotide[16] = "AGTC";
   // random selection
   for(int i = 0; i < number; i++)
   {
	   int x = (int)(3.0 + (double)my_rand() * ((double)strlen(sequence)-3.0)/MY_RAND_MAX);
	   //cout << x << endl;
	   int y = (int)((double)my_rand() * 4.0/MY_RAND_MAX);
	   sequence[x] = nucleotide[y];
   }
   //check for stop

}

int main(int argc, char** argv)
{
   char amino_acid[32] = "ACDEFGHIKLMNPQRSTVWY" ;
   char nucleotide[16] = "AGTC";
   int protein_length = 500;
   char protein_sequence[protein_length];

   int DNA_length = protein_length * 3;
   char DNA_sequence[DNA_length + 10];
   char First[2][DNA_length + 10];
   char Second[4][DNA_length + 10];
   char Third[8][DNA_length + 10];
   char Fourth[16][DNA_length + 10];
   char Fifth[32][DNA_length + 10];
   //char Sixth[64][DNA_length + 10];
   char distant[DNA_length + 10];

   int i, j, k;

   protein_sequence[0] = amino_acid[10]; // Proteins start with M
   for(i = 1; i < protein_length; i++)
   {
   	int x = (int)((double)my_rand() * 20.0/MY_RAND_MAX);
      protein_sequence[i] = amino_acid[x];
   }

   bool A, B;

   DNA_sequence[0] = nucleotide[0]; // Proteins start with M
   DNA_sequence[1] = nucleotide[2];
   DNA_sequence[2] = nucleotide[1];

   for(int i = 3; i < DNA_length; i+=3)
   {  A = FALSE;
      B = FALSE;

   	int x = (int)((double)my_rand() * 4.0/MY_RAND_MAX);
      DNA_sequence[i] = nucleotide[x];
      if(DNA_sequence[i] == 0x54) A = TRUE;
      x = (int)((double)my_rand() * 4.0/MY_RAND_MAX);
      DNA_sequence[i+1] = nucleotide[x];
      x = (int)((double)my_rand() * 4.0/MY_RAND_MAX);
      DNA_sequence[i+2] = nucleotide[x];
      if(DNA_sequence[i+1] == 0x41 && DNA_sequence[i+2] == 0x41) B = TRUE;
      else if(DNA_sequence[i+1] == 0x41 && DNA_sequence[i+2] == 0x47) B = TRUE;
      else if(DNA_sequence[i+1] == 0x47 && DNA_sequence[i+2] == 0x41) B = TRUE;
      if(A && B) i-=3;  // Have a stop codon so re do last 3
   }
   DNA_sequence[DNA_length] = 0x00;

  //make_children(DNA_sequence, child_A, child_B);

// FASTA format output
  /* 	cout << ">outgroup" << endl;
   	j = 1;
   	for(i = 0; i < DNA_length; i++)
   	{
      	cout << DNA_sequence[i];
      	if(j++ == 60){cout << endl; j = 1;}
   	}
      cout << endl;  */
   strcpy(distant, DNA_sequence);
   mutate(distant, 50);

   strcpy(First[0], DNA_sequence);
   strcpy(First[1], DNA_sequence);

   mutate(First[0], 10);
   mutate(First[1], 10);
   j = 0;
   for(i = 0; i < 4; i++)
   { 	if(i > 1) j = 1;
   	strcpy(Second[i], First[j]);
      mutate(Second[i], 10);
   }

   j = 0; k = 0;
   for(i = 0; i < 8; i++)
   {  if(j++ > 1){j = 1; k++;}
   	strcpy(Third[i], Second[k]);
      mutate(Third[i], 10);
   }
   j = 0; k = 0;
   for(i = 0; i < 16; i++)
   {  if(j++ > 1){j = 1; k++;}
   	strcpy(Fourth[i], Third[k]);
      mutate(Fourth[i], 10);
   }

   j = 0; k = 0;
   for(i = 0; i < 32; i++)
   { 	if(j++ > 1){j = 1; k++;}
   	strcpy(Fifth[i], Fourth[k]);
      mutate(Fifth[i], 10);
   }
   int a =0,b=0,c=0,d=0,e=0;

   for(k = 0; k < 32; k++)
   {  if(a > 1){a = 0; b++;}
   	if(b > 1){b = 0; c++;}
   	if(c > 1){c = 0; d++;}
   	if(d > 1){d = 0; e++;}

		translate(Fifth[k], protein_sequence);

      cout << ">"<< e << d << c << b << a << endl;
   	j = 1;
   	for(i = 0; i < strlen(protein_sequence); i++)
   	{
      	cout << protein_sequence[i];
      	if(j++ == 60){cout << endl; j = 1;}
   	}
      cout << endl;
      a++;
   }
   protein_sequence[0] = amino_acid[10]; // Proteins start with M
   	for(int i = 1; i < protein_length; i++)
   	{
      	int x = (int)((double)my_rand() * 20.0/MY_RAND_MAX);
      	protein_sequence[i] = amino_acid[x];
   	}
// FASTA format output
   	cout << ">outgroup" << endl;
   	j = 1;
   	for(i = 0; i < protein_length; i++)
   	{
      	cout << protein_sequence[i];
      	if(j++ == 60){cout << endl; j = 1;}
   	}
      cout << endl;

      translate(distant, protein_sequence);
      cout << ">distant\n";
   	j = 1;
   	for(i = 0; i < protein_length; i++)
   	{
      	cout << protein_sequence[i];
      	if(j++ == 60){cout << endl; j = 1;}
   	}
      cout << endl;
}
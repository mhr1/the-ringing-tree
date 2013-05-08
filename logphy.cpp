// PhyLog.cpp Converts phylip tree file (Newick/New hampshire format)
// to datalog
// latest 01/11/07, 13/01/08,
// Ver 3 - 04/09/09 Handle bootstrap results

// Ex2: version

#include "epro.h"


using namespace std;
class datalog_data
{
public:
	char node[32];
	char ancestor[32];
	char distance[32];
};

int node_search(char* root, datalog_data my_data[], int nodes)
{
	int i, j, i_count = 0, o_count = 0;
	bool inodes = FALSE;
	char inode_list[10][32];
	char otu_list[60][32];
	
	for(i = 0; i < nodes; i++)   		
		if(!strcmp(my_data[i].ancestor, root))		
			if(!strncmp(my_data[i].node,"inode",5))
			{
				strcpy(inode_list[i_count],my_data[i].node);
				i_count++;
				inodes = TRUE;
			}
			else
			{
				strcpy(otu_list[o_count],my_data[i].node);
				o_count++;
			}
						
	// Deal with inodes
	if(inodes)
	{	
		cout << "(";	
		for(j = 0; j < i_count - 1; j++)
		{			
			node_search(inode_list[j], my_data, nodes);
			cout << ",";
		}
		node_search(inode_list[i_count - 1], my_data, nodes);		
	}
	
	// Print list of OTUs
	if(o_count)
	{
		if(inodes) cout << ",";
		for(i = 0; i < o_count - 1; i++)
		{
			cout << otu_list[i] << ",";
		}
		cout << otu_list[o_count - 1] << ")";
		cout << "nod";
		cout << ":" << "1.0";
	}
	
	return(1);
}

int main(int argc, char** argv)
{
   char buffer[256];
   char root[32];
   long nodes;   
   datalog_data my_data[1000];
   bool found = FALSE;
   long i = 0;
   
   //cout << "Prolog to Newick converter version 1 - 18/12/09" << endl;

   ifstream fin("test_tree.pl");
   if(!fin.is_open()){cout << "Error opening input file\n"; return(0);}

   while(fin.getline(buffer, 255))
   {
       strtok(buffer, " (),\n\t");
       strcpy(my_data[i].node, strtok(NULL, " (),\n\t"));
       strcpy(my_data[i].ancestor, strtok(NULL, " (),\n\t"));
       strcpy(my_data[i].distance, strtok(NULL, " (),\n\t"));
       i++;
   }
   nodes = i;
   fin.close();

   // find root. It's the only inode that occurs in p(_,X,...) and not p(X,_,...)
   for(i = 0; i < nodes; i++)
   {
      if(!strncmp(my_data[i].node,"inode",5))
      {
          found = FALSE;
          for(int j = 0; j < nodes; j++)
            if(!strcmp(my_data[j].node, my_data[i].ancestor))found = TRUE;

          if(!found) strcpy(root, my_data[i].ancestor);
      }
   }
   
   // Search for connections
	//cout << "(";
	node_search(root, my_data, nodes);
	cout << ";\n";
   return(1);
}
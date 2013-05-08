/*
	aho.cpp 17/04/13

*/

#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

//#include <ctype.h>   ?

#define TRUE 1
#define FALSE 0
int step = 0;
int level = 0;

using namespace std;
class datalog_data
{
public:
	char A[32];
	char B[32];
	char C[32];
};

class list
{
public:
	char data[1000][32];
	int head;
	list()
	{
		head = 0;
		//*data = new char[1000][32];
	}
	int add(char* item)
	{
		bool found = FALSE;
		for(int j = 0; j < head; j++)
		{
			if(!strcmp(data[j], item))
				found = TRUE;			
		}
		if(!found)
		{
			strcpy(data[head], item);
			head++;	
		}
		return(1);
	}
	
	int find(char* item)
	{
		bool found = FALSE;
		for(int j = 0; j < head; j++)
		{
			if(!strcmp(data[j], item))
				found = TRUE;			
		}
		return(found);
	}
	
	int remove(char* item)
	{
		bool found = FALSE;
		for(int j = 0; j < head; j++)
		{
			if(!strcmp(data[j], item))
			{			
				found = TRUE;
				head--;
			}
			if(found)
				strcpy(data[j], data[j + 1]);			
		}	
		return(1);
	}
	
	int show(void)
	{
		for(int j = 0; j < head; j++)
		{
			cout << data[j] << " ";		
		}
		return(1);
	}
private:

	
};

int get_components(datalog_data my_data[], int lines, list* my_list, list* placed)
{
	int i, j, k = 0;
	list *new_list;
	list *lcopy = new list;;
	new_list = new list[100];

	for(i = 0; i < my_list->head; i++)
		lcopy->add(my_list->data[i]);

	//lcopy->show();
	
	while(my_list->head > 0)
	{
		new_list[k].add(my_list->data[0]);
		
		for(j = 0; j < new_list[k].head; j++)
		{
			for(i = 0; i < lines; i++)
			{
				if(!strcmp(my_data[i].A, new_list[k].data[j]))
				{
					if(!placed->find(my_data[i].C) && lcopy->find(my_data[i].C))
						new_list[k].add(my_data[i].B);
				}
				if(!strcmp(my_data[i].B, new_list[k].data[j]))
				{	
					if(!placed->find(my_data[i].C) && lcopy->find(my_data[i].C))
						new_list[k].add(my_data[i].A);
				}
			}
		}
		
		for(i = 0; i < new_list[k].head; i++)
			my_list->remove(new_list[k].data[i]);
		k++;
	}
	
	if(k <= 1)
	{
		cout << "Unable to place: ";
		new_list[0].show();
		cout << endl;
		
		/*for(j = 0; j < new_list[0].head; j++)
		{
			for(i = 0; i < lines; i++)
			{
				if(!strcmp(my_data[i].C, new_list[0].data[j]))
				{
					if(new_list[0].find(my_data[i].A) && new_list[0].find(my_data[i].B))
						cout << my_data[i].A << ", " << my_data[i].B << ", " << my_data[i].C << endl;
				}
			}
		}*/
		return(0);
	}
	
	for(i = 0; i < k; i++)
	{		
		if(new_list[i].head == 1)
		{
			cout << new_list[i].data[0] << ",";
			placed->add(new_list[i].data[0]);
		}
	}
	
	for(i = 0; i < k; i++)
	{	
		if(new_list[i].head == 2)
		{
			cout << "(" << new_list[i].data[0] << "," << new_list[i].data[1] << ")";
			placed->add(new_list[i].data[0]);
			placed->add(new_list[i].data[1]);
		}
	}
	
	for(i = 0; i < k; i++)
	{
		if(new_list[i].head > 2)
		{
			cout << "(";
			get_components(my_data, lines, &new_list[i], placed);
			cout << ")";
		}
	}
	
	return(TRUE);
};

int main(int argc, char** argv)
{
	char buffer[256];
	int lines; 
	char comment = '%';
	datalog_data * my_data = new datalog_data[100000];
	int i = 0, j = 0;
	list *my_list = new list;
	list *placed = new list;

   
	ifstream fin("c:/Ex5/metazoa/selected_triples.pl");
	//ifstream fin("c:/Ex5/mini_tree.pl");
	if(!fin.is_open()){cout << "Error opening input file\n"; return(0);}

	while(fin.getline(buffer, 255))
	{
		if(buffer[0] != (int)comment)
		{
			strtok(buffer, " (),\n\t");
			strcpy(my_data[i].A, strtok(NULL, " (),\n\t"));
			strcpy(my_data[i].B, strtok(NULL, " (),\n\t"));
			strcpy(my_data[i].C, strtok(NULL, " (),\n\t"));
			i++;
		}
		else
		{	//comment
		}
	}
	lines = i;
	fin.close();

    // Get members
	for(i = 0; i < lines; i++)
	{
		//cout << my_data[i].A << ", " << my_data[i].B << ", "<< my_data[i].C << endl;
		my_list->add(my_data[i].A);
		my_list->add(my_data[i].B);
		my_list->add(my_data[i].C);	
	}
	cout << "(";
	get_components(my_data, lines, my_list, placed);
	cout << ");";
	return(1);
}
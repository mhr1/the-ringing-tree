/********************************************************************
 
 ringing_tree.cpp
 
 Created by:	Michael C. Riley
 
 Date:			7th April 2017
 
 Copyright (c) 2017 Michael C. Riley
 All rights reserved.
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 OWNERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 
 *******************************************************************/

/** \file ringing_tree.cpp
 \brief 

*/

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <ctime>

#define TRUE 1
#define FALSE 0

using namespace std;

struct m_column
{
	char id[32];
	double column_data[300];
};

struct m_data
{
	string date;
	m_column row_data[140];
};

int day_of_the_week(string date) // Date in numbers format: YYYY-MM-DD Eg. 2017-04-07
{
	int year = 2017;
	int month = 4;
	int day = 7;
	char* token;
	
	char myArray[date.size() + 1];
	strcpy(myArray, date.c_str());

	year = atoi(strtok(myArray, "-\n\t\r"));
	month = atoi(strtok(NULL, "-\n\t\r"));
	day = atoi(strtok(NULL, "-\n\t\r"));

	tm timeStruct = {};
	timeStruct.tm_year = year - 1900;
	timeStruct.tm_mon = month - 1;
	timeStruct.tm_mday = day;
	timeStruct.tm_hour = 12;    //  To avoid any doubts about summer time, etc.
	mktime( &timeStruct );

	return timeStruct.tm_wday;  //  0...6 for Sunday...Saturday
}

int main(int argc, char** argv)
{
	char l_buffer[1024];
	char buffer[1024];
	int i = 0, j = 0, k = 0, l = 0;
	int epic_count = 0;
	int sum_k = 0;
	int subject_count = 0;
	char filename[128];
	char id[16];
	string sample_timepoint;
	double init;
	double high;
	double low;
	double term;
	double term_adj;
	double volume;
	string timepoint3[300];
	double temp;
	double tempa;
	
	m_column *mydata = new m_column[140];
	
	
	// mydata[x].column_data[y] = K;
	 
	for(i = 0; i < 300; i++)
		timepoint3[i] = 0.0;
	
	ifstream fin_a;	
	ifstream flist("/Users/mcr/ring_data/ring_list.txt");
	if(!flist.is_open()) cout << "unable to open rlist data\n" ;
	
	while(flist.getline(l_buffer, 1024))
	{
		sprintf(filename, "/Users/mcr/ring_data/%s", l_buffer);
		strcpy(mydata[epic_count].id, strtok(l_buffer, " .\n\t\r"));
		
		//cout << filename << endl;
		fin_a.open(filename);
		if(!fin_a.is_open()) cout << "unable to open rtest data\n" ;
		
	// Get header
		fin_a.getline(buffer, 1024);
	//cout << buffer << endl;
		j = 0;	
		while(fin_a.getline(buffer, 1024))
		{
		//cout << buffer;
			
			sample_timepoint = strtok(buffer, ", \t\n\r");
			init = atof(strtok(NULL, ", \t\n\r")); 
			high = atof(strtok(NULL, ", \t\n\r")); 
			low = atof(strtok(NULL, ", \t\n\r")); 
			term = atof(strtok(NULL, ", \t\n\r")); 
			volume = atof(strtok(NULL, ", \t\n\r"));
			term_adj = atof(strtok(NULL, ", \t\n\r"));
		
			//cout << ", " << term << ", ";
			//cout << day_of_the_week(sample_timepoint) << endl;
		
			if(day_of_the_week(sample_timepoint) == 3)
			{
				timepoint3[j] = sample_timepoint;
				mydata[epic_count].column_data[j] = term;
				j++;
			}
			//if(i++ > 5)break;
		}
		/*
		k = 0;
	
		for(i = j - 1; i > 0; i--)
		{
			temp = (timepoint3[i] - timepoint3[i - 1])/timepoint3[i - 1];
		
			if(temp > 0.035)
			{
				//cout << temp << endl;
				k++;
			}
		}
		
		sum_k += k;
	
		cout << id << ": " << k << "/" << j << endl;
	*/
		epic_count++;
		fin_a.close();
		
		//if(l++ > 3)break;
	}

// Show a small table of the data	
/*	cout << "\t";
	for(j = 12; j < 20; j++)
		cout << "\t" << mydata[j].id;
	cout << endl;
	
	for(i = 0; i < 10; i++)
	{
		cout << timepoint3[i];
		for(j = 12; j < 20; j++)
		{
			cout << "\t" << mydata[j].column_data[i];
		
		}
		cout << endl;
	}
*/	
// Show some data
	//cout << mydata[18].id << ": " << timepoint3[5] << ", " << mydata[18].column_data[5] << endl;
//
	flist.close();
	
// Now we cn analyse the data

// Init freq data
	int freq_up[128], freq_down[128];

	for(i = 0; i < 123; i++) // each epic
	{
		subject_count = 0;
		
		for(l = 0; l < 123; l++)
		{
			freq_up[l] = 0;
			freq_down[l] = 0;
		}
		
		for(j = 0; j < 261 - 2; j++) // all Wednesdays
		{
			temp = (mydata[i].column_data[j] - mydata[i].column_data[j + 1])/mydata[i].column_data[j + 1];
			if(temp > 0.025)
			{
				//cout << timepoint3[j] << ": " << mydata[i].id << " = " << temp << endl;
				// check all epics
				for(k = 0; k < 123; k++)
				{
					tempa = (mydata[k].column_data[j + 1] - mydata[k].column_data[j + 2])/mydata[k].column_data[j + 2];
					if(abs(tempa) > 0.025)
					{
						if(tempa > 0)  // up
							freq_up[k]++;
						else
							freq_down[k]++;
						
					}
				}
				subject_count++;
				
			}
	
		}
	/*
		cout << mydata[i].id << " - up \n";
		for(l = 0; l < 123; l++)		
			cout << mydata[l].id << ", " << freq_up[l] << endl;
		
		cout << mydata[i].id << " - down \n";
		for(l = 0; l < 123; l++)
			cout << mydata[l].id << ", " << freq_down[l] << endl;
	*/
		cout << mydata[i].id << " + " << subject_count << ": ";
		tempa = subject_count/2;
		for(l = 0; l < 123; l++)
		{
			if(abs(freq_up[l] - freq_down[l]) > tempa)
				cout << mydata[l].id << ", " << freq_up[l] - freq_down[l]<< ". ";
		}	
		cout  << endl;
	}
	
	return(1);
}

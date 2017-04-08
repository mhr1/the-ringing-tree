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

#define TRUE 1
#define FALSE 0

using namespace std;

int main(int argc, char** argv)
{
	char buffer[1024];
	int i = 0;
	string sample_point;
	double init;
	double high;
	double low;
	double term;
	double volume;
	
	ifstream fin_a("/Users/mcr/ring_data/rtest.csv");
	if(!fin_a.is_open()) cout << "unable to open rtest data\n" ;
		
	// Get header
	fin_a.getline(buffer, 1024);
	//cout << buffer << endl;
			
	while(fin_a.getline(buffer, 1024))
	{
		cout << buffer;
			
		date = strtok(buffer, "; \t\n\r");
		open = atof(strtok(NULL, "; \t\n\r")); 
		high = atof(strtok(NULL, "; \t\n\r")); 
		low = atof(strtok(NULL, "; \t\n\r")); 
		close = atof(strtok(NULL, "; \t\n\r")); 
		volume = atof(strtok(NULL, "; \t\n\r"));
		
		cout << close << endl;
		
		if(i++ > 5)break;
	}
	
	fin_a.close();
	return(1);
}
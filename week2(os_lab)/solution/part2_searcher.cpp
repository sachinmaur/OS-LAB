#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <signal.h>

using namespace std;

int main(int argc, char **argv)
{
	if(argc != 5)
	{
		// cout <<"usage: ./partitioner.out <path-to-file> <pattern> <search-start-position> <search-end-position>\nprovided arguments:\n";
		for(int i = 0; i < argc; i++)
			cout << argv[i] << "\n";
		return -1;
	}
	
	char *file_to_search_in = argv[1];
	char *pattern_to_search_for = argv[2];
	int search_start_position = atoi(argv[3]);
	int search_end_position = atoi(argv[4]);

	//TODO
	ifstream file(file_to_search_in, ios::in | ios::binary);
		if(!file.is_open()){
			cerr<<"unable to open file: "<< *file_to_search_in << endl;
			return false;
		}
		else{
			// now we will read the file from 0 Bytes to 67108863 Bytes 
			// for that we will calculate the length to read from file.txt
			int length_to_read = search_end_position - search_start_position + 1;
			// now to store the file portion to read we need certain storage
			char * buffer = new char[length_to_read+1];
			//we will point to the start of file
			file.seekg(search_start_position, ios::beg);
			// now we will read the file upto to length_to_read
			file.read(buffer, length_to_read);
			// we need to end the buffer with \0
			buffer[length_to_read + 1] = '\0';
			// now since we read binary content need to conver to string 
			string content(buffer);
			//deleting the buffer and closing file
			delete [] buffer;
			file.close();
			//now to find the substring 
			size_t found_pos = content.find(string(pattern_to_search_for));
			if(found_pos != string::npos){
				cout << "[" << getpid() << "] found at " << (search_start_position + found_pos) << endl;
			}
			else{
				cout << "[" << getpid() << "] didn't find" << endl;
    
			}
		}
	// cout << "[-1] didn't find\n";
	// return 0;
	return 0;
}

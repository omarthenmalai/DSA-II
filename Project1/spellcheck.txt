// ECE-165 Data Structures & Algorithms 2 Program #1
// Omar Thenmalai

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include "hash.h"

#define MAX_LENGTH 20

using namespace std;

hashTable dict(2000000);

void timediff(clock_t &t1, clock_t &t2, const string &action);
void load_file( ifstream &dictstream );
void spellcheck(ifstream &inputstream, ofstream &outputstream);

// Calculate and print the difference between two times
void timediff(clock_t &t1, clock_t &t2, const string &action)
{
    double load_time = (double(t2 - t1)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to " << action << ": " << load_time << endl;
}

// Loads dictionary into the hash table. Treats each line as a new word
void load_file(ifstream &dictstream)
{
    string line;
    while(getline(dictstream, line))
	{ 
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        dict.insert(line);
    }
}

// Spellcheck the given input file and write to the given output file.
void spellcheck(ifstream &inputstream, ofstream &outputstream)
{
    string characters = "abcdefghijklmnopqrstuvwxyz0123456789'-";
    string numbers = "0123456789";
    string line, word;
    int line_number = 1;
    int start, end;
    while(getline(inputstream, line)) 
	{
        transform(line.begin(), line.end(), line.begin(), ::tolower); // Convert line to lowercase and skip if blank 

        if(line == "") // Check if the line is empty.
		{
            line_number++;
            continue;
        }

        start = line.find_first_of(characters);
        while(start != string::npos) 
		{
            end = line.find_first_not_of(characters, start);
            word = line.substr(start, end - start); // Get the current word
            start = line.find_first_of(characters, end); // Get the next valid word
            if(word.find_first_of(numbers) != string::npos) // Check if the word contains a number
                continue;
			else if(word.length() > MAX_LENGTH) // Check if the word is too long
                outputstream << "Long word at line " << line_number << ", starts: " << word.substr(0, MAX_LENGTH) << endl;
            else if(!dict.contains(word)) // Check if the word is in the dictionary
                outputstream << "Unknown word at line " << line_number << ": " << word << endl;
            else if(end == string::npos) // Check if the end of the line has been reached
                break;
        }
        line_number++;
    }
}


int main()
{
    string dictionary_file, output_file, input_file;
    clock_t t1, t2;

    cout << "Enter name of dictionary: "; // Prompt user for dictionary name
    cin >> dictionary_file;
    ifstream dictstream(dictionary_file.c_str());
    if(!dictstream) // If the file could not be opened, print to cerr and exit.
	{
        cerr << "ERROR: Could not open " << dictionary_file << endl;
        exit(1);
    }

    t1 = clock();
    load_file(dictstream); // load the words from the dictionary_file into the dict hash table
    t2 = clock();
    timediff(t1, t2, "load_file dictionary"); // print the load time to cout
    dictstream.close();

    cout << "Enter name of input file: "; // Prompt the user for the input file name
    cin >> input_file;
    ifstream inputstream(input_file.c_str());
    if(!inputstream) // If the file could not be opened, print to cerr and exit
	{
        cerr << "ERROR: Could not open " << input_file << endl;
        exit(1);
    }

    cout << "Enter name of output file: "; // Prompt the user for the output file name
    cin >> output_file;
    ofstream outputstream(output_file.c_str());
    if(!outputstream) // If the file could not be opened, print to cerr and exit.
	{
        cerr << "ERROR: Could not open " << input_file << endl;
        exit(1);
    }

    t1 = clock();
    spellcheck(inputstream, outputstream); // Spellcheck the input file and write to the output file.
    t2 = clock();
    timediff(t1, t2, "check document");

    return 0;
}
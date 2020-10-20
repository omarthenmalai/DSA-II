// Omar Thenmalai
#include <iostream>
#include <cstring>
#include <fstream>

int is_valid_merge(const std::string &A, const std::string &B, std::string &C, int a_index, int b_index, int c_index);
void merge(const std::string &A, const std::string &B, std::string &C, std::ofstream &output);
int matrix[50][50];
int iterations = 0;

int main() 
{
    std::string input_file, output_file;
    std::cout << "Enter name of input file: ";
    std::cin >> input_file;
    std::cout << "Enter name of output file: ";
    std::cin >> output_file;

    std::ifstream input(input_file);
    std::ofstream output(output_file);
	std::string A, B, C;

	while (std::getline(input, A) && std::getline(input, B) && std::getline(input, C))
	{
		merge(A, B, C, output);
	}
	std::cout << iterations << std::endl;
}

void merge(const std::string &A, const std::string &B, std::string &C, std::ofstream &output) 
{
    int a_index = 0, b_index = 0,  c_index = 0;
	memset(matrix, -1, sizeof(matrix));
	if (is_valid_merge(A, B, C, 0, 0, 0)) 
	{
        while ((a_index < A.size() || b_index < B.size()) && c_index < C.size()) 
		{
            if (a_index < A.size() && matrix[a_index+1][b_index] == 1 && (matrix[a_index+1][b_index+1] == 1 || matrix[a_index+2][b_index])) 
			{
				C[c_index] = toupper(A[a_index]);
				c_index++;
				a_index++;
			}
			else
			{
                c_index++;
                b_index++;
            }
        }
        output << C << std::endl;
    } 
	else 
	{
        output << "*** NOT A MERGE ***" << std::endl;

	}
	std::cout << C << std::endl;
	for(int i = 0; i<C.size();i++)
	{
		for(int j = 0; j<C.size(); j++)
			std::cout << matrix[i][j] << "\t";
		std::cout << std::endl;
		
	}
}

int is_valid_merge(const std::string &A, const std::string &B, std::string &C, int a_index, int b_index, int c_index) 
{
	iterations++;
	int &valid_merge = matrix[a_index][b_index];
	if (valid_merge != -1)
	{
		return matrix[a_index][b_index];
	}
	
    if (a_index >= A.size() && b_index >= B.size() && c_index >= C.size())
    {
		valid_merge = 1;
		return valid_merge;
    }
	
	valid_merge = 0;
	
	// If there are still characters left in A, and the character at the given position in C is the same as that in A
	if (a_index < A.size() && C[c_index] == A[a_index])
	{
	//std::cerr << "a: " << A[a_index] << std::endl;
        valid_merge = valid_merge | is_valid_merge(A, B, C, (a_index+1), b_index, (c_index+1));
	}

	if(valid_merge == 1)
	{
		//std::cout << C[c_index] << ": valid" << std::endl;
		return valid_merge;
	}
	// If there are still characters left in B, and the character at the given position in C is the same as that in B
	if (b_index < B.size() && C[c_index] == B[b_index])
    {
		//std::cerr << "b: " << B[b_index]<< std::endl;
		valid_merge = valid_merge | is_valid_merge(A, B, C, a_index, (b_index+1), (c_index+1));
	}
	return valid_merge;
}
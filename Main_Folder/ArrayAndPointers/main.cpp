#include <iostream>


int main()

{
	int values[5]{1,2};

	for (int i = 0; i < std::size(values); ++i)
	{
		std::cout << "value[ " << i << "]: " << values[i] << std::endl;
	}




	int* pvalues = new int[10]; // allocate memory for 10 integers      
	memset(pvalues, 0, sizeof(int) * 10); // initialize allocated memory to zero

	for (int i = 0; i < 10; ++i) // loop through the allocated memory
	{
		pvalues[i] = i; // assign values to the allocated memory
		std::cout << "pvalue[ " << i << "]: " << pvalues[i] << std::endl;
	}



	// 2D array position and value
	int values2D[6][5]{
	   //0,1,2,3,4 columns
		{1,2,3,6,5}, // row 0 
		{2,3,4,5,4}, // row 1
		{3,4,5,4,3}, // row 2
		{5,6,7,3,2}, // row 3
		{7,8,9,3,2}, //	row 4
		{9,8,9,6,1}  // row 5
		// ex: values2D[0][0] = 1, values2D[0][1] = 2, values2D[0][2] = 3, values2D[0][3] = 6, values2D[0][4] = 5
	};
	// Loop through the 2D array and print the values
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			std::cout << "values2D[" << i << "][" << j << "]: " << values2D[i][j] << std::endl;
		}
	}

	int* pvalues2d = &values2D[0][0]; // pointer to the first element of the 2D array
	for (int i = 0; i < 12; ++i)
	{
		std::cout << "pvalues2d[" << i << "]: " << *(pvalues2d + i) << std::endl; // print the values of the 2D array using pointer arithmetic
		
		
	};

	delete[] pvalues; // free the allocated memory for the 1D array for freeing up memory

	return 0;
}
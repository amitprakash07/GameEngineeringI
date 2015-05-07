#include "Matrix.h"
#include <iostream>

void displayMatrix(myEngine::Matrix4x4);


void main()
{
	float f[16];
	int index = -1;
	/*for (size_t i = 1; i <= 4; i++)
	{
		std::cout << "Enter" << i << "th row\n";
		for (size_t j = 1; j <= 4; j++)
		{
			std::cout << "Enter value for(" << i << "," << j << ")\n";
			std::cin >> f[++index];
		}
	}

	myEngine::Matrix4x4 mMatrix(
		f[0], f[1], f[2], f[3],
		f[4], f[5], f[6], f[7],
		f[8], f[9], f[10], f[11],
		f[12], f[13], f[14], f[15]);*/

	myEngine::Matrix4x4 mA(
		1, 0, 0, 4,
		0, 1, 0, 5,
		0, 0, 1, 0,
		0, 0, 0, 1
		);

	myEngine::Matrix4x4 mB(
		1, 0, 0, 6,
		0, 1, 0, 13,
		0, 0, 1, 0,
		0, 0, 0, 1
		);

	//displayMatrix(mA);
	//std::cout << std::endl;
	//displayMatrix(mMatrix.getCoFactorMatrix());
	//std::cout << std::endl;
	displayMatrix(mA);
	std::cout << "\n";
	displayMatrix(mB);
	std::cout << "\n";
	mA.invert();
	displayMatrix(mA);
	std::cout << "\n";
	displayMatrix(mA * mB);
	std::cout << "\n";

	
}

void displayMatrix(myEngine::Matrix4x4 i_matrix)
{
	for (size_t i = 1; i <= 4; i++)
	{
		for (size_t j = 1; j <= 4; j++)
		{
			std::cout<<i_matrix(i-1, j-1)<<"\t";
		}
		std::cout<<std::endl;
	}
}


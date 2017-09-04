// stackoverflow.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include "BinaryTree.h"
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<numeric>
#include<ctime>
#include <stdio.h>
#include "sort.h"
#include <stdlib.h>
#include <sstream>
#include <math.h>

using namespace std;

//////////////////////////////////////////////////////////////////////////
// 1. seg fault
// 2. Binary Tree
// 3. Binary Tree
// 4. Array Random https://stackoverflow.com/questions/46029259/how-to-generate-combinations-from-arrays
//////////////////////////////////////////////////////////////////////////
// seg fault

void test1(){
	char* commandLine = "use me 123456 abc";
	int state = 0;
	char *token = strtok(commandLine, " ");
	string c, u, p, a;
	while(token != NULL)
	{
		switch(state)
		{
		case 0: c = token; break;
		case 1: u = token; break;                          
		case 2: p = token;break;                        
		case 3: a = token; break;            
		}
		token = std::strtok(NULL, " ");
		state++;
	}

	const char* command = c.c_str();
	const char* user = u.c_str();
	const char* password = p.c_str();
	const char* args = a.c_str();
};

//////////////////////////////////////////////////////////////////////////
// 3.Binary Tree
//void TestBinaryTree()
//{
//	int randNum;
//	vector<int> randData;
//	vector<int>::iterator iter;
//	size_t size = randData.size();
//	srand(time(0));
//	BinaryTree tree;
//	cout << "number: ";
//	for (int i = 0; i < 5; i++)
//	{
//		randNum = rand() % 1000 + 1;
//		tree.insertNode(randNum);
//		
//		cout << randNum << " ";
//	}
//	cout << endl << "display : \n";
//	tree.displayInOrder();
//	cout << endl;
//	for(int i=1; i<=5;i++)
//	{ 
//		cout<< "number: " << i << " level = "<< tree.getLevel(i) << endl;
//	}
//}
//////////////////////////////////////////////////////////////////////////
//void TestQuickSort()
//{
//
//	// The user inputs a string of numbers (e.g. "6 4 -2 88 ..etc") and those integers are then put into a vector named 'vec'.
//	std::vector<int> vec;
//
//	// Converts string from input into integer values, and then pushes said values into vector.
//	std::string line;
//	if ( getline(std::cin, line) )
//	{
//		std::istringstream str(line);
//
//		int value;
//		str >> value;
//		vec.push_back( value );
//		while ( str >> value ) 
//		{
//			vec.push_back( value );
//		}
//	}
//	// Creating QuickSort object.
//	QuickSort qSort;
//	QuickSort *ptrQSort = &qSort;
//	// Creating new vector that has been 'Quick Sorted'.
//	int vecSize = vec.size();
//	std::vector<int> qSortedVec;
//	qSortedVec = ptrQSort->sortFunc( vec, 0, vecSize-1 );
//
//	// Middle, start, and end positions on the vector.
//	int mid = ( 0 + (vec.size()-1) )  / 2;
//	int start = 0, end = vec.size() - 1;
//
//	// Creating RecursiveBinarySearch object.
//	RecursiveBinarySearch bSearch;
//	RecursiveBinarySearch *ptrBSearch = &bSearch;
//	//bool bS = ptrBSearch->binarySearch( qSortedVec, mid, start, end );
//	bool bS = ptrBSearch->binarySearch( bSortedVec, mid, start, end );
//
//
//	/*--------------------------------------OUTPUT-----------------------------------------------------------------------*/
//
//	// Print out inputted integers and the binary search result.
//
//	// Depending on the binary search, print either 'true' or 'false'.
//	if ( bS == 1 )
//	{
//		std::cout << "true ";
//	}
//	if ( bS == 0 )
//	{
//		std::cout << "false ";
//	}
//
//	// Prints the result of the 'quick sorted' array.
//	int sortedSize = qSortedVec.size();
//	for ( int i = 0; i < sortedSize; i++ )
//	{
//		std::cout << qSortedVec[i] << " ";
//	}
//	std::cout << "\n";
//}

//////////////////////////////////////////////////////////////////////////
// 4. Array Random
void TestCreateArrange(){
	const int COL = 3;
	char arr [][COL] = {
		{'a', 'b', 'c'},
		{'d', 'e', 'f'},
		{'g', 'h', 'i'},
	};
	int ROW = sizeof(arr)/sizeof(arr[0]);

	// print all
	int nTotal = pow(float(COL), (float)ROW);
	for (int i = 0; i < nTotal; ++i)
	{
		if (i % COL == 0)
			cout << endl;
		int nCol = i % COL;
		int nRow = i / COL;
		cout << arr[nRow][nCol] << ",";

		for (int j = 0; j < COL; ++j)
		{
			int nRow = i/pow(float(COL), (float)(ROW-1));
		}
		cout << endl;
	}
}
//////////////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{
	// 1.seg fault
	//test1();

	// 2. Binary Tree
	//TestBinaryTree();

	// 4. Array Random
	TestCreateArrange();

	getchar();
	return 0;
}


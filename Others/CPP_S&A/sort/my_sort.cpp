/*********************************************************************************
*     File Name           :     my_sort.cpp
*     Created By          :     
*     Creation Date       :     [2015-09-22 22:34]
*     Last Modified       :     [2015-09-23 09:21]
*     Description         :      
**********************************************************************************/


#include <iostream>
#include <cstdlib>
#include <utility>
using namespace std;

#define PRINT(x , n) for(int i=0;i<n;i++)cout<<x[i]<<"  ";cout<<endl;

template<typename T> 

bool BubbleSortInPlace(T *p_data , int ele_num){
	for (int i = 0; i < ele_num - 1; i++) {
		int max_index = ele_num - i - 1;
		for (int j = 0; j < max_index ; j++) {
			if(p_data[j]>p_data[j+1])swap(p_data[j],p_data[j+1]);
		}
	}
}

int main(int argc, char const* argv[])
{
	double data[] = {3,4,2,7,4,9,3,2,9,5};
	PRINT(data , 10);
	BubbleSortInPlace(data , 10);
	PRINT(data , 10);
	
	
}


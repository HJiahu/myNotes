/*********************************************************************************
*     File Name           :     ./TEST/test.cpp
*     Created By          :     jiahu
*     Creation Date       :     [2015-10-11 21:53]
*     Last Modified       :     [2015-10-11 22:33]
*     Description         :      
**********************************************************************************/

#include <iostream>
#include <vector>
using namespace std;
int main(int argc, char const* argv[])
{
	vector<int> int_vec{0,1,2,3,4,5,6};
	
	cout<<int_vec.pop_back();
	for (auto i : int_vec) {
		cout<<i<<"  ";
	}
	cout<<endl;
	int_vec.back();


	return 0;
}



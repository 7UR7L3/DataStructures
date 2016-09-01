// template example

#include <iostream>

using namespace std;

template <typename Tarantula>
Tarantula sqr( Tarantula x )
{
	return x*x;
}

int main()
{
	int n = 3, sq = sqr< int >( n );	//	really only need sqr( n ) cause compilers aren't shit
	cout << sq << endl;
	return 0;
}
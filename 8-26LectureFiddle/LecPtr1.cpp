#include <iostream>
#include <vector>

using namespace std;

void swapShat( int *a, int *b )
{
	*a ^= *b ^= *a ^= *b;	
}
class foo
{
	public:
		int bar = -5;
};

void lolwat( int *wan, int *too )
{
	cout << (wan == too) << endl;
}

int main()
{
	vector<int> someshit = vector<int>();
	someshit.push_back( 87 );
	cout << (someshit)[0] << endl;
	int wan = 16;
	int *wa = &wan, *tu = ( new int(16) );
	lolwat( wa, tu );
	cout << wa << " " << tu << endl;
	delete wa;
	return 0;
}
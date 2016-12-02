#include <iostream>

using namespace std;

using add_atom = atom_constant<atom("add")>;
using multiply_atom = atom_constant<atom("multiply")>;

// Message handler model
behavior do_math{
	[](add_atom, int a, int b){
		return a+b;
	},
	[](multiply_atom, int a, int b){
		return a*b;
	}
};

int main()
{
	// caller side : send(math_actor, add_atom::value, 1, 2)
}
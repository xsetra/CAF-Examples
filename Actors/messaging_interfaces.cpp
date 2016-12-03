#include <iostream>
#include <caf/all.hpp>

using namespace std;
using namespace caf;

/*
Statik olarak yazılmış aktörler soyut mesaj arayüzüne ihtiyaç duyar. Bunun sebebi, derleyicinin 
aktörler arasındaki iletişimi kontröl etmesini sağlamak
CAF'da arayüzler, uygun aktör kontrolörünü tanımlar ve variadic template'ini kullanarak tanımlanır.
Her template parametresi bir input-output çiftini tanımlar. "replies_to<X1,...,Xn>::with<Y1,...,Yn>"
Output üretmeyen girdiler için "reacts_to<X1,...,Xn>" kullanılabilir şunun yerine "replies_to<X1,...,Xn>::with<void>"

*/

using add_atom = atom_constant<atom("add")>;
using sub_atom = atom_constant<atom("sub")>;

// Mesaj arayüzü tanımlaması. Basit hesaplama için.
using calculator_actor = typed_actor<replies_to<add_atom, int, int>::with<int>,
									 replies_to<sub_atom, int, int>::with<int>>;
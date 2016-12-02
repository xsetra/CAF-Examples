#include <iostream>
#include <string>

// POD struct foo
struct foo {
	std::vector<int> a;
	int b;
}

/*
CAF inspection API'sini kullanarak bir mesajın elementlerini serileştirebilir.
Bu api, kullanıcılarına code serileştirme ve string dönüşümü sağlar.

"inspect" fonksiyonu, (inspect'in) kontrolörün variadic çağrı operatörüne meta bilgi ve veri alanları geçirir.
*/


// foo' serileştirilmeli
template <class Inspector>
typename Inspector::result_type inspect(Inspector& f, foo& x){
	return f(meta::type_name("foo"), x.a, x.b);
}

/*
Bu sayede genişletilebilirlik elde ediyoruz. Ayrı bir şekilde parser yazmaktan bizi kurtarıyor.
Çünkü return değeri, std::tuple, std::pair, C_Arrays , Herhangi bir tip, x.size() , x.empty(), x.begin() ve x.end()
*/

int main()
{
	return 0;
}
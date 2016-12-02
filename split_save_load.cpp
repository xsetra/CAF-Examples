#include <iostream>

using namespace std;


// Burada public bir erişim yok niteliklere. Getter ve Setter aracılıgı ile işlemler yapabiliyoruz.
class foo{
	public:
		foo(int a0 = 0, int b0 = 0) : a_(a0), b_(b0) {
			//Constructor
		}

		foo(const foo&) = default;
		foo& operator = const(foo&) = default;

		// Getter a_
		int a() const {
			return a_;
		}
		// Setter a_
		void set_a(int val) {
			a_ = val;
		}

		// Getter b_
		int b() const {
			return b_;
		}
		// Setter b_
		void set_b(int val) {
			b_ = val;
		}

	private:
		int a_;
		int b_;
};

// a_ ve b_ veri alanlarına erişim yok. foo da değişiklik yapmakta mümkün degil varsayıyoruz.

// Uygulamamızı bölmeliyiz. Şu şekilde:

template <class Inspector>
typename std::enable_if<Inspector::reads_state, 
						typename Inspector::result_type>::type
inspect(Inspector& f, foo& x)
{
	return f(meta::type_name("foo"), x.a(), x.b());
}

template <class Inspector>
typename std::enable_if<Inspector::writes_state,
						typename Inspector::result_type>::type
inspect(Inspector& f, foo& x){
	int a;
	int b;
	// Degeri geriye x'e yaz, kapsamdan çıkış esnasında
	auto g = make_scope_guard([&] {
		x.set_a(a);
		x.set_b(b);
	});
	return f(meta::type_name("foo"), a, b);
}

behavior testee(event_based_actor* self){
	return {
		[=](const foo& x){
			aout(self) << to_string(x) << endl;
		}
	};
}

/*
Yukarıdaki uygulamada kapsam güvenliğinin amacı, kapsamdan otomatik çıkışta içeriği geriye foo ya yazması
*/
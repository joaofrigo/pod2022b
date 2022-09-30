
#include <iostream>
#include <vector>
#include <random>
#include <functional>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <cassert>

using namespace std;

template<typename T>
void Selecao( vector<T>& A ) {
	for( auto i = 0; i < A.size(); i++ ){
		auto min = i;
		for( auto j= i+1; j < A.size(); j++) 
			if( A[j] < A[min] )
				min = j;
		swap( A[min], A[i] );
	}
}

int main(void)
{
    auto n = 1000;
    vector<int> A(n);
    vector<int> Acopia(n);

     // a semente e o tempo desde 1/1/1970
    auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    default_random_engine r1(seed);
    uniform_int_distribution<int> uniform_dist(0, 10000);

    // gera entrada aleatoria
    auto rand = bind(uniform_dist, r1);
    generate( A.begin(), A.end(), rand );
    // faz copia de verificacao
    copy( A.begin(), A.end(), Acopia.begin() );

    // imprime entrada
    for(auto it= A.begin(); it != A.end(); it++)
        cout << *it << " ";
    cout << endl;

    {
        // teste do algoritmo 
        auto inicio = chrono::system_clock::now();
        Selecao( A );
        auto fim = chrono::system_clock::now();
        auto tempo = chrono::duration_cast<chrono::microseconds>(fim-inicio).count();
        cout << setprecision(4) << tempo << " (us)" << endl;
    }
 
    {
        // ordena original e tempo
        auto inicio = chrono::system_clock::now();
        sort( Acopia.begin(), Acopia.end() );
        auto fim = chrono::system_clock::now();
        auto tempo = chrono::duration_cast<chrono::microseconds>(fim-inicio).count();
        cout << setprecision(4) << tempo << " (us)" << endl;
    }

    // testamos a validade do resultado
    assert( equal( A.begin(), A.end(), Acopia.begin() ) );

    return 0;
}
#include <iostream>
#include <random>
#include <time.h>
#include <cmath>
#include <numeric>

using namespace std;


unsigned long long gcd (unsigned long long n1, unsigned long n2) {
    unsigned long long tmp;
    while (n2 != 0) {
        tmp = n1;
        n1 = n2;
        n2 = tmp % n2;
    }
    return n1;
}

 unsigned long long gcdex (unsigned long long a, unsigned long long b, unsigned long long &x, unsigned long long &y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	unsigned long long x1, y1;
	unsigned long long d = gcdex (b%a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}


unsigned long long ExpModulus (unsigned long long base, unsigned long long exp, unsigned long long modul){
    unsigned long long basemodul = base;
    unsigned long long res = 1;
    for (unsigned long long i = 0; i < exp; i++){
        res = (res*basemodul) % modul;
    }
    return res;
}

bool IsPrime (unsigned long long num){
    bool primechecker = 1;
    unsigned long long sqnum = sqrt(num);
    for (unsigned long long i = 2; i <= sqnum; i++){
        if ((num % i) == 0) primechecker = 0;
    }
    return primechecker;
}


long PublicKeyGeneration(unsigned long long m, unsigned long long &n, unsigned long long &e){
    unsigned long long phi, d, y;
    unsigned long long p = 4;
    unsigned long long q = 6;
    e = 8;
    srand(time(NULL));
    while (!IsPrime(p)){
        p = (rand() % 90000) + 10000;
    }
    while ((!IsPrime(q))&&(q!=p)){
        q = (rand() % 90000) + 10000;
    }
    n = p*q;
    phi = (p-1)*(q-1);
    srand(time(NULL));
    while ((!IsPrime(e))&&(gcd(e, phi)!=1)&&(e<phi)){
        e = (rand() % 90000) + 10000;
    };


    unsigned long long g = gcdex (e, phi, d, y);
    if (g != 1){
        cout << "no solution";
    }

    else {
        d = (d % phi + phi) % phi;
    }
    return d;
}

unsigned long long Encryption (unsigned long long m, unsigned long long e, unsigned long long n){
    unsigned long long c = ExpModulus(m, e, n);
    return c;
}

unsigned long long Decryption (unsigned long long c, unsigned long long d, unsigned long long n){
    unsigned long long decryptedc = ExpModulus (c, d, n);
    return decryptedc;
}

int main()
{
    unsigned long long message, publickeyN, encrypted, decrypted, privatekeyD, publickeyE;
    cout << "Input your number-message:\t";
    cin >> message;
    privatekeyD = PublicKeyGeneration (message, publickeyN, publickeyE);
    encrypted = Encryption(message, publickeyE, publickeyN);
    cout << "\nEncrypted is\t" << encrypted;
    decrypted = Decryption(encrypted, privatekeyD, publickeyN);
    cout << "\nDecrypted is\t" << decrypted;
    if (decrypted == message) cout << "\nThe message was encrypted and decrypted correctly.";
    else cout << "\nThere are some errors during encryption and decryption.";
    return 0;
}

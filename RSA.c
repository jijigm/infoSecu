#include <stdio.h>
#include <math.h>

int lcm(int p, int q);
int gcd(int p, int q);

int main(void) {
	int plainText, cipherText;
	int p, q, N, L, E, D;

	srand(time(NULL));

	p = rand(); //초기 p 생성
	q = rand(); //초기 q 생성


	while (p < 2) {
		p = rand();
	}

	while (q < 2) {
		q = rand();
	}

	for (int i = 2; i < p; i++) { // p가 소수가 아니면 다시 생성
		if (p % i == 0) {
			p = rand();
			while (p < 2) p = rand();
			i = 1;
		}
	}
	for (int j = 2; j < q; j++) { //q가 소수가 아니면 다시 생성
		if (q % j == 0) {
			q = rand();
			while (q < 2) q = rand();
			j = 1;
		}
	}


	N = p * q;
	L = lcm(p - 1, q - 1);
	printf("%d %d %d", p, q, L);

	return 0;
}

int lcm(int p, int q) {
	return p * q / gcd(p, q);
}

int gcd(int p, int q) {
	int temp;

	while (q != 0) {
		temp = p % q;
		p = q;
		q = temp;
	}

	return p;
}
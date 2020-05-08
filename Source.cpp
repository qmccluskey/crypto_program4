//Quinn McCluskey
//CPSC 370, 12:30
//qmccluskey@live.esu.edu
//11/12/19
//RSA program based on user entered info to encrypt/decrypt

using namespace std;

#include <iostream>
#include <string>
#include <stdio.h>
#include<math.h>
#include<time.h>
#include <iomanip>
#include<stdlib.h>

int prime(int input);
int gcd(int e, int phi);
int extendedEuclid(int e, int n);
int fastExpo(int t, int b, int n);

//this randomly selects two primes
int prime(int input)
{
	int count = 1;

	int array[10000] = { 0 };
	int prime[10000] = { 0 };

	for (int i = 2; i < 1000; i++) 
	{
		for (int j = i * i; j < 1000; j += i) 
		{
			array[j - 1] = 1;
		}
	}

	for (int i = input; i < 200; i++) 
	{
		if (array[i - 1] == 0) 
		{
			prime[count] = i;
			count++;
		}
	}

	int num = sizeof(prime) / sizeof(prime[0]); 
	int r = rand() % count; 
	return prime[r];
}

//Euclidean algorithm
int gcd(int e, int phi)
{
	if (e == 0)
	{
		return phi;
	}

	return gcd(phi%e, e);
}

//extended euchlidean algorithm, finds d
int extendedEuclid(int e, int n)
{
	int r[100];
	int q[100];
	int x[100];
	int y[100];

	r[0] = e;
	r[1] = n;
	x[0] = 1;
	x[1] = 0;
	y[0] = 0;
	y[1] = 1;

	int temp = 2;

	while (r[temp] != 0) 
	{
		r[temp] = r[temp - 2] % r[temp - 1];

		if (r[temp] == 0) 
		{
			while (x[temp - 1] < 0) 
			{
				x[temp - 1] += n;
			}
			return x[temp - 1];
		}

		q[temp] = r[temp - 2] / r[temp - 1];
		x[temp] = x[temp - 2] - (q[temp] * x[temp - 1]);
		y[temp] = y[temp - 2] - (q[temp] * y[temp - 1]);
		temp++;
	}
}

//this encrypts and decrypts
int fastExpo(int t, int b, int n)
{
	if (t == 0)
	{
		return 0;
	}

	if (b == 0)
	{
		return 1;
	}

	long int temp;

	if (b % 2 == 0)
	{
		temp = fastExpo(t, b / 2, n);
		temp = (temp * temp) % n;
	}
	else
	{
		temp = t % n;
		temp = (temp * fastExpo(t, b - 1, n) % n) % n;
	}

	return (temp + n) % n;
}

int main()
{
	int input;
	srand(time(0));

	cout << "RSA program is starting!" << endl;

	cout << "Please input the text that will be encrypted and decrypted/signed" << endl;
	cin >> input;
	cout << endl;
	while (input < 100 || input > 1000) 
	{
		cout << "Please enter a number more than 100 but less than 1000" << endl;
		cin >> input;
	}

	cout << "Here are the results of the RSA calculations:" << endl;
	int p = prime(input);
	int q = prime(input);
	int n = p * q;
	int phi = (p - 1)*(q - 1);
	int e = rand() % phi;
	int E = gcd(e, phi);
	int d = extendedEuclid(e, phi);
	int C = fastExpo(input, e, n);
	int de = fastExpo(C, d, n);

	while (E != 1) 
	{
		e = rand() % phi;
		E = gcd(e, phi);
	}

	//this prints off everything
	cout << "p = " << p << endl;
	cout << "q = " << q << endl;
	cout << "n = " << n << endl;
	cout << "phi = " << phi << endl;
	cout << "e = " << e << endl;
	cout << "d = " << d << endl;
	cout << "Encrypted Message = " << C << endl;
	cout << "Decrypted Message = " << de << endl;

	//the loops if the user wants to enter that they want to encrypt and decrypt again
	char input2;

	cout << "Would you like to encrypt/decrypt, again? If yes, enter y " << endl;
	cin >> input2;
	if (input2 == 'y' || input2 == 'Y') 
	{
		main();
	}

	system("pause");

	return 0;
}
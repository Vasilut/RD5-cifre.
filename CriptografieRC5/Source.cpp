
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <fstream>
#include <string.h>
#include <cstring>
#include <cstring>
#include <stdlib.h>

using namespace std;

#define KEYSIZE 16	 /* size of key, in bytes */
typedef unsigned int WORD; /* Should be 32-bit = 4 bytes        */

WORD P = 0xb7e15163, Q = 0x9e377989; // magic constant
#define ROTL(x,y) (((x)<<(y&(31))) | ((x)>>(32-(y&(31))))) 
#define ROTR(x,y) (((x)>>(y&(31))) | ((x)<<(32-(y&(31)))))


typedef enum {
	KeyWords = KEYSIZE / 4,
	NumRounds = 15,  /* Number of cryptographic rounds  */
	TableSize = 32   /* size of table = 2 * (NumRounds + 1) */
} bogus;


WORD S[TableSize];
WORD L[KeyWords];

char keystr[KEYSIZE];
char cheie[KEYSIZE];

/* 2 WORD: input plain text, output encrypted text    */
void encrypt(WORD *PlainText, WORD *CryptoText)
{

	WORD i, temp;
	WORD A;
	WORD B;

	A = PlainText[0] + S[0];
	B = PlainText[1] + S[1];

	for (i = 1; i <= NumRounds; i++) {
		temp = i << 1;
		A = ROTL(A^B, B) + S[temp];
		B = ROTL(A^B, A) + S[temp + 1];
	}
	CryptoText[0] = A;
	CryptoText[1] = B;
}  /* RC5_Cypto::encrypt */



   /* 2 WORD input encrypted text, output plain text    */
void decrypt(WORD *CryptoText, WORD *PlainText)
{
	WORD i, temp;
	WORD B;
	WORD A;

	B = CryptoText[1];
	A = CryptoText[0];

	for (i = NumRounds; i > 0; i--) {
		temp = i << 1;
		B = ROTR(B - S[temp + 1], A) ^ A;
		A = ROTR(A - S[temp], B) ^ B;
	}
	PlainText[1] = B - S[1];
	PlainText[0] = A - S[0];
} 	/*  decrypt */




void setup(char* K) /* secret input key K[0...KEYSIZE-1]   */
{

	WORD i;
	WORD A;
	WORD B;
	WORD j;
	WORD k;
	WORD u = TableSize / 8;

	//intialize L
	for (i = KEYSIZE - 1, L[KeyWords - 1] = 0; i != -1; i--)
	{
		L[i / u] = (L[i / u] << 8) + K[i];
	}

	//initialize the table 
	S[0] = P;
	for (i = 1; i < TableSize; i++)
	{
		S[i] = S[i - 1] + Q;
	}
	/* 3*t > 3*KeyWords */

	for (A = 0, B = 0, i = 0, j = 0, k = 0; k < 3 * TableSize; k++, i = (i + 1) % TableSize, j = (j + 1) % KeyWords) {
		S[i] = ROTL(S[i] + (A + B), 3);
		A = S[i];
		L[j] = ROTL(L[j] + (A + B), (A + B));
		B = L[j];
	}
} 	/* setup */



	/*
	Testbench for crytography algorithm
	*/
int main(int argc, char* argv[])
{
	char firstNumber[TableSize];
	char secondNumber[TableSize];
	char inputUser[2];

	for (int i = 0; i < argc; ++i)
	{
		if (i == 1)
		{
			strcpy(inputUser, argv[i]);
		}
		else
			if (i == 2)
			{
				strcpy(firstNumber, argv[i]);
			}
			else
				if (i == 3)
				{
					strcpy(secondNumber, argv[i]);
				}
				else
					if (i == 4)
					{
						strcpy(cheie, argv[i]);
					}
	}
	//cout << inputUser << " " << firstNumber << " " << secondNumber << " " << cheie << '\n';

	if (inputUser[0] == '1')
	{
		//encrypt part

		//copy the key
		memset(keystr, 0, KEYSIZE * sizeof(char));
		strcpy(keystr, cheie);

		WORD i;
		WORD PlainText1[2];
		WORD CryptoText[2] = { 0,0 };

		//set the initial number
		int firstNr = atoi((char *)firstNumber);
		int secondNr = atoi((char *)secondNumber);
		CryptoText[0] = firstNr;
		CryptoText[1] = secondNr;

		//encrypt part
		PlainText1[0] = CryptoText[0];
		PlainText1[1] = CryptoText[1];


		setup(keystr);
		encrypt(PlainText1, CryptoText);

		//write the crypto to a file
		ofstream out("cryptedfiles.out");
		out << CryptoText[0] << " " << CryptoText[1] << '\n';
		for (i = 0; i < TableSize; ++i)
		{
			out << S[i] << " ";
		}

		cout << "Crypted -----" << '\n';

	}
	else
		if (inputUser[0] == '2')
		{
			//decrypt part
			WORD PlainText1[2];
			WORD CryptoText[2] = { 0,0 };


			//copy the key
			memset(keystr, 0, KEYSIZE * sizeof(char));
			strcpy(keystr, cheie);

			//reading the file
			ifstream in("cryptedfiles.out");
			in >> CryptoText[0] >> CryptoText[1];
			/*for (int i = 0; i < TableSize; ++i)
				in >> S[i];*/

			//decrypt
			setup(keystr);
			decrypt(CryptoText, PlainText1);

			ofstream out("decryptedfiles.out");
			out << PlainText1[0] << " " << PlainText1[1] << '\n';

			cout << "Decripted -----" << '\n';
		}
	/*
	WORD i;
	WORD PlainText1[2], PlainText2[2];
	WORD CryptoText[2] = { 0,0 };

	char *keystr = "TheQuickBrownFox";

	if (sizeof(WORD) != 4)
		printf("RC5 error: WORD has %d bytes.\n", sizeof(WORD));

	printf("RC5-32/15/16 examples:\n");
	for (i = 1; i < 6; i++)
	{
		PlainText1[0] = CryptoText[0];
		PlainText1[1] = CryptoText[1];

		//
		setup(keystr);
		encrypt(PlainText1, CryptoText);
		decrypt(CryptoText, PlainText2);

		// Print out results, checking for decryption failure
		printf("\n   plaintext %.8lX %.8lX  --->  ciphertext %.8lX %.8lX   --> desciphertext %.8lX %.8lX \n",
			PlainText1[0], PlainText1[1], CryptoText[0], CryptoText[1], PlainText2[0], PlainText2[1]);
		if (PlainText1[0] != PlainText2[0] || PlainText1[1] != PlainText2[1])
			printf("Decryption Error!");
	}
*/
	cin.get();

}
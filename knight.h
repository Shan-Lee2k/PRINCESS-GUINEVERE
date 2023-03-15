#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#define MAX_ITEM 99
#include "main.h"
bool isPrime(int n);
int nextPrime(int n);
int fibonacci(int n);
bool isMountain(int* arr, int n, int& maxVal, int& indexMax);
void theSecondMax(int* arr, int n, int& max2_3x, int& max2_3i);
void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue);
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);
int readFile(string file_input, int& HP, int& level, int& remedy, int& maidenkiss, int& phoenixdown);
#endif  //__KNIGHT_H__
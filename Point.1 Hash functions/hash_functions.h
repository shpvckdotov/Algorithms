#pragma once
#include <stdint.h>


long long HashMultiplicative(int key);

long long HashInt(int key);

long long HashDoubleRound(double key);

long long HashDoubleReint(double key);

long long HashStrlen(char* string);

long long HashCharSum(char* string);

long long HashCRC32(char* string);

long long HashPolynomial(char* string);
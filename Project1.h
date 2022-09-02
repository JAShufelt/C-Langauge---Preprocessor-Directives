//Course:		CSCI 311/312
//Project:		Project 1
//Purpose:		The objective of this project is to gain experience with C language
//				Pre-processor directives and bitwise operators.
//
//Author:		Jake Shufelt
//Date			8/30/2022

#pragma once
#include <stdio.h>

//Macro for swapping byte 0 and 3 of int N
#define XOUTER(N)							\
N = (N & 0xFFFFFFFF);						\
unsigned int left = ((N) & 0xFF000000);		\
unsigned int right = ((N) & 0x000000FF);	\
unsigned int middle = ((N) & 0x00FFFF00);	\
right = right << 24;						\
left = left >> 24;							\
N = (middle | right | left);				\

//Macro for swapping byte 1 and 2 of int N
#define XINNER(N)								\
N = ((N) & 0xFFFFFFFF);							\
unsigned int mid_left = ((N) & 0x00FF0000);		\
unsigned int mid_right = ((N) & 0x0000FF00);	\
unsigned int outsides = ((N) & 0xFF0000FF);		\
mid_left = mid_left >> 8;						\
mid_right = mid_right << 8;						\
N = (outsides | mid_left | mid_right);			\

#define TWO_TO_POW_31 2147483648	// 214783648 is equivalent to 2^31

void string_fix(char* input, int len);	//Correctly formats char[] into a string after receiving data from stdin.

void str_to_lint(unsigned long int* num, char* input);	//Converts string to long integer

void setbytes_count(unsigned long int num);	//Calculates the number of set bits within first four bytes of a unsigned long int num

void display_routine(unsigned long int num);	//Display integer value of num based on -D preprocessor directives. 



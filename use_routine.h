#pragma once
#include<iostream>
#include<tuple>
#include<vector>
#include"Header.h"
#include <ilcplex/ilocplex.h>
#include<cstdlib>



ILOSTLBEGIN //#define ILOSTLBEGIN using namespace std;
using namespace std;

//user_program
void makeCostMatrix(double* c_var, int arrlength);
tuple<float, float> Routine1(double* c_var, PNODE current, int n,
	int branch_var, int left_right, float*x_arr, vector<tuple<int, int>> *constaints_split,
	int max_min,int arrLength);
void quickSort(vector<tuple<int, int, int>> &s, int l, int r);
int MST(float*x_arr);
int greedy(float*x_arr);
int greedy2(float*x_arr);

tuple<float, float> Routine2(double* c_var, PNODE current, int n,
	int branch_var, int left_right, float*x_arr, vector<tuple<int, int>> *constaints_split,
	int max_min, int arrLength);

int getLowerBound();
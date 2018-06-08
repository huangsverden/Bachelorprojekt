#ifndef HEADER_H
#define HEADER_H

#include<iostream>
#include<queue>
#include<tuple>
#include<vector>
#include<array>
#include<string>
#include<sstream>
#include<strstream>

using namespace std;
#define INF 10000
typedef struct node
{
	float lb;
	float ub;
	float x_var[INF];
	struct node* left;
	struct node* right;
	int nr;
	int left_or_rigth[INF];
	int cutoff;

}NODE,*PNODE;

struct cmp {
	bool operator()(PNODE a, PNODE b) {
		return a->lb > b->lb;
		//return a->ub - a->lb > b->ub - b->lb;
	}
};


PNODE createNode(int lb, int ub, int index, PNODE fatherNode,
	int n, int nr, int left_or_rigth, int cutoff,float*x_arr);
void freeNode(PNODE node);
void freeconstaints(char* constaints[], int c);
void printStatus(NODE* root,int n, PNODE fatherNode,int max_min, float LB, float UB);
int checkEnd(PNODE node,int n,int LB,PNODE root,PNODE &result,int UB, int max_min,int userRoutine);
void takeConstriants(vector<tuple<int,int>>* res, char* c[100], int arrlength);
int checkConstraints(vector<tuple<int, int>> *constaints_split, int &arrlength,int* left_or_rigth, int n);
PNODE whileBody(PNODE &fatherNode, int n,
	tuple<float, float>(*Routine1)(double*, PNODE, int, int, int,float*, vector<tuple<int,int>> *, int,int),
	double* c_var, float &UB, float &LB, int &nrCount, vector<tuple<int, int>> *constaints_split,
	char**constaints, int c, int z_o, int index,int max_min,PNODE &result, int userRoutine);
int checkAllth(PNODE node, int n);
int choose_x(PNODE node, int n);
void createGraf(vector<tuple<int,int>> *constaints_split, char* constaints[100], int v, int &n, double* c_var,int &c);
int checkSubtour(int* c_var, int arrlength, vector<tuple<int, int>>&t);

vector<string> mySplit(string str, string pattern);
vector<int> mySplit3(vector<string> str);
vector<tuple<int, int>> mySplit2(vector<string> str);
#endif // DEBUG

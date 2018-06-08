#define _CRT_SECURE_NO_WARNINGS
#include"stdafx.h"

#define min(a,b)  (((a) < (b)) ? (a) : (b))

PNODE createNode(int lb, int ub, int index, PNODE fatherNode,
	int n,int nr, int left_or_rigth,int cutoff, float*x_arr)
{
	PNODE node=(PNODE) malloc(sizeof(NODE));
	node->lb = lb;
	node->ub = ub;
	if (index != -1)
	{
		for (int i = 0;i < n;i++)
		{
			node->x_var[i] = x_arr[i];
			node->left_or_rigth[i] = fatherNode->left_or_rigth[i];
		}
		//node->x_var[index] = status;
		node->left_or_rigth[index] = left_or_rigth;
	}
	else {

		
		for (int i = 0;i < n;i++)
		{
			node->x_var[i] = x_arr[i];
			node->left_or_rigth[i] = -1;
		}
	}
	node->cutoff = cutoff;
	node->nr = nr;
	node->left = NULL;
	node->right = NULL;


	return node;
}

void freeNode(PNODE node)
{

	if (node!=NULL)
	{
		if (node->left)
			freeNode(node->left);
		if (node->right)
			freeNode(node->right);
		free(node);
	}
}

void freeconstaints(char* constaints[], int c)
{
	for (int i=0;i<c;i++)
	{
		if (constaints)
		{
			free(constaints[i]);
		}
	}
}


void printStatus(NODE* root,int n, PNODE fatherNode, int max_min, float LB, float UB)
{
	cout << "\n**********STATUS**********" << endl;
	if (max_min)
	{
		printf("inc_ub:%d\n", UB);
	}
	else
	{
		printf("inc_lb:%d\n", LB);
	}

	queue<NODE *> nodeQueue;  
	nodeQueue.push(root);
	NODE *node;
	while (!nodeQueue.empty()) {
		node = nodeQueue.front();
		nodeQueue.pop();

		if (node->left==NULL && !node->cutoff)
		{
			printf("nr:%d, lb:%.2f, ub:%.2f\nvisited: ", node->nr, node->lb, node->ub);
			for (int i = 0;i < n;i++)
			{
				//printf("%d:%d  ", node->x_var[i], node->left_or_rigth[i]);
				printf("%d  ", node->left_or_rigth[i]);
			}
			printf("\nPsolution: ");
			for (int i = 0;i < n;i++)
			{
				//printf("%d:%d  ", node->x_var[i], node->left_or_rigth[i]);
				printf("x%d:%.2f ",i+1, node->x_var[i]);
			}
			printf("\n\n");
		}

		if (node->left) {
			nodeQueue.push(node->left); 
		}
		if (node->right) {
			nodeQueue.push(node->right); 
		}
	}

	cout << "your current opsition is:" << endl;
	printf("nr:%d, lb:%d, ub:%d\nvisited: ", fatherNode->nr, fatherNode->lb, fatherNode->ub);
	for (int i = 0;i < n;i++)
	{
		//printf("%d:%d  ", fatherNode->x_var[i],fatherNode->left_or_rigth[i]);
		printf("%d  ", fatherNode->left_or_rigth[i]);
	}
	cout << "\n**************************" << endl;

}

int checkEnd(PNODE node, int n, int LB, PNODE root, PNODE &result, int UB, int max_min, int userRoutine)
{
	if (!node) return 0;

	if (userRoutine==1)
	{
		for (int i = 0;i < n;i++)
		{
			if (node->left_or_rigth[i] == -1)
			{
				return 0;
			}
		}
	}

	


	if (max_min && node->lb == LB)
	{
		//printf("found lowerbound: %d\n", node->lb);
		//printStatus(root, n, node, max_min,LB,UB);
		return 1;
	}
	else if (!max_min && node->lb == LB)
	{
	}


	
	return 0;
}

void takeConstriants(vector<tuple<int, int>>* res, char* c[100], int arrlength)
{

	for (int i = 0;i < arrlength;i++)
	{
		string x(c[i]);
		vector<string> ss = mySplit(x, "+");
		int n = ss.size();
		vector<tuple<int, int>> ar = mySplit2(ss);
		res[i] = ar;
		
		
	
		
	}
	
}



#define MAX_N 10000
int cost1[MAX_N][MAX_N];
int cost2[MAX_N][MAX_N];
int vertex1;

int check(int tempi, int tempj, vector<tuple<int, int>>&t)
{
	int count = 1;
	int start = tempi;
	int startj = tempj;
	for (int i = 1; i <= vertex1; i++)
	{
		for (int j = 1; j <= vertex1; j++)
		{
			if (j != tempi &&cost2[tempj][j] == 1)
			{
				//printf("%d, ", cost1[tempi][tempj]);
				tuple<int, int> tu(1, cost1[tempi][tempj] - 1);
				t.push_back(tu);
				count++;
				if (start == j && count < vertex1)
				{
					//printf("%d.............\n", cost1[tempj][j]);
					tuple<int, int> tu(1, cost1[tempj][j] - 1);
					t.push_back(tu);
					return 1;
				}
				tempi = tempj;
				tempj = j;
				break;
			}
			if (j == vertex1) return 0;
		}
	}
	return 0;
}

int checkSubtour(int* c_var, int arrlength, vector<tuple<int, int>>&t)
{
	if (!vertex1)
	{
		for (int i = 2;i < 1000;i++)
		{
			if (i*(i - 1) / 2 == arrlength)
			{
				vertex1 = i;
				break;
			}
		}
	}

	int index = 0;
	for (int i = 1; i <= vertex1; i++)
	{
		for (int j = i; j <= vertex1; j++)
		{
			if (i == j)
			{
				cost2[i][j] = 100000;
				continue;
			}
			cost2[i][j] = c_var[index];
			cost2[j][i] = c_var[index++];
		}
	}


	for (int i = 1; i <= vertex1; i++)
	{
		for (int j = 1; j <= vertex1; j++)
		{
			if (cost2[i][j]==1)
			{
				if (check(i, j,t))
				{

					//printf("blablablablablabla\n");
					return 1;
				}
			}
		}
	}
	return 0;

}

int checkConstraints(vector<tuple<int, int>> *constaints_split,int &arrlength,int* left_or_rigth,int n)
{

	for (int i = 0;i < arrlength;i++)
	{
		int temp = 0;
		int flag = 1;
		vector<tuple<int, int>> ve = constaints_split[i];
		for (int j=0;j<ve.size()-2;j++)
		{
			int x_var=left_or_rigth[get<1>(ve[j])];
			if (x_var != -1)
			{
				flag = 1;
				temp += get<0>(ve[j])*x_var;
				//printf("%d %d %d\n", temp, x_var, get<0>(ve[j]));
			}
			else
			{
				flag = 0;
				break;
			}
		}

		if (flag)
		{
			int index = ve.size() - 2;
			int num = get<0>(ve[index]);
			if (num == 1)
			{
				if (temp != get<0>(ve[ve.size() - 1]))
					return i;
			}
			else if (num == 2)
			{
				if (temp > get<0>(ve[ve.size() - 1]))
					return i;
			}
			else if (num == 3)
			{
				if (temp < get<0>(ve[ve.size() - 1]))
					return i;
			}
		}
		
	}
	vector<tuple<int,int>>t;
	if (checkSubtour(left_or_rigth, n,t))
	{
		int size = t.size();
		tuple<int, int> tu(2, -1);
		t.push_back(tu);
		tuple<int, int> tu2(size - 1, -1);
		t.push_back(tu2);
		constaints_split[arrlength]=t;
		arrlength++;
		return 1;
	}

	return -1;
}


PNODE whileBody(PNODE &fatherNode, int n, 
	tuple<float, float> (*Routine1)(double*,PNODE,int,int,int,float*, vector<tuple<int, int>> *, int,int),
	double* c_var,float &UB,float &LB, int &nrCount, vector<tuple<int, int>> *constaints_split,
	char**constaints,int c,int z_o,int index,int max_min,PNODE &result, int userRoutine)
{
	float l, u;
	int level;
	int flag = 0;

	cout << "what is it's lowerbound and uperbound,when x" << index << "="<<z_o << endl;
	//cin >> l >> u;
	
	float x_arr[INF] = { 0 };
	tuple<float, float>t = Routine1(c_var, fatherNode, n, index - 1, z_o, x_arr, constaints_split, max_min,c);
	//printf("lb:%.2f  ub:%.2f\n", get<0>(t), get<1>(t));
	l = get<0>(t);
	u = get<1>(t);


	PNODE myNode=0;
	
	
	if (max_min && l >= UB)
	{
		cout << "it's lowerbound is larger equal than inc_ub, branch is cutting off" << endl;
		myNode = createNode(l, u, index - 1, fatherNode, n, nrCount++, z_o, 1,x_arr);
	}
	else if (!max_min && u <= LB)
	{
		cout << "it's Uperbound is less equal than inc_lb, branch is cutting off" << endl;
		myNode = createNode(l, u, index - 1, fatherNode, n, nrCount++, z_o, 1,x_arr);
	}
	else {
		myNode = createNode(l, u, index - 1, fatherNode, n, nrCount, z_o, 0,x_arr);

		int message;
		if ((message = checkConstraints(constaints_split, c, myNode->left_or_rigth,n)) != -1)
		{
			//cout << "it don't meets the constraints:" << constaints[message] << ", branch is cutting off" << endl;
			myNode = createNode(l, u, index - 1, fatherNode, n, nrCount, z_o, 1,x_arr);
		}
		else {
			flag = 1;

			if (max_min)
			{
				if (u < UB)
				{
					//printf("inc_ub opdater to %d\n", u);
					UB = u;
					result = myNode;
				}
			}
			else
			{
				if (l > LB)
				{
					//printf("inc_lb opdater to %d\n", l);
					LB = l;
					result = myNode;
				}
			}
			
			if (l == u)
			{
				//printf("l==u\n");
				flag = 0;
				if (!result)
				{
					result = myNode;
					
				}
				else if(max_min && result->ub>u)
				{
					result = myNode;
				}
				else if (!max_min && result->lb < l)
				{
					result = myNode;
				}
			}

		
			for (int i = 0;i <= n;i++)
			{
				if (userRoutine == 2 && i == n)
				{
					int x_v[10000] = { 0 };
					for (int j = 0;j < n;j++)
						x_v[j] = (int)myNode->x_var[j];

					vector<tuple<int, int>>t;
					if (checkSubtour(x_v, n, t))
					{
						//printf("wrong result for userRoutine2\n");

						break;
					}
					//printf("result->lb:%d,  %d,  %d\n", result->lb, !max_min,l);
					if (!result)
					{
						//printf("lalalala111..........\n");
						result = myNode;

					}
					else if (max_min && result->ub > myNode->ub)
					{
					//	printf("lalalala222..........\n");
						result = myNode;
					}
					else if (!max_min && result->lb < myNode->ub)
					{
						flag = 0;
						//printf("lalalala333..........\n");
						result = myNode;
						LB = myNode->ub;
						break;
					}
				}
				if (userRoutine == 2 && ((myNode->x_var[i] - int(myNode->x_var[i])) != 0))
				{
					//printf("%f,%f\n", myNode->x_var[i], (myNode->x_var[i] - int(myNode->x_var[i])));
					//printf("........\n");
					break;
				}
			}

		}

		nrCount++;
	}
	

	if (z_o==0)
		fatherNode->left = myNode;
	else if(z_o==1)
		fatherNode->right = myNode;
	//printf("flag:%d\n", flag);
	if (flag) 
		return myNode; 
	else 
		return 0;
}

int checkAllth(PNODE node,int n)
{
	int flag = 1;
	for (int i = 0;i < n;i++)
	{
		if (node->left_or_rigth[i] == -1) 
			flag = 0;
	}
	return flag;
}

int choose_x(PNODE node,int n)
{
	int index=-1;
	for (int i=0;i<n;i++)
	{
		if(node->left_or_rigth[i] == -1)
		{
			float number = node->x_var[i];
			if ((number=number-(int)number)!=0)
			{
				if (index == -1)
				{
					index = i;
				}
				else {
					if (abs(number - 0.5) < node->x_var[index])
					{
						index = i;
					}
				}
			}
		}
	}
	if (index == -1)
	{
		for (int i = 0;i < n;i++)
		{
			if (node->left_or_rigth[i] == -1)
			{
				return i;
			}
		}
	}

	return index;
}

void createGraf(vector<tuple<int, int>> *constaints_split, char* constaints[100], int v, int &n, double* c_var, int &c)
{
	
	int ii = v - 1;
	while (ii)
	{
		n += ii;
		ii--;
	}
	for (int j = 0;j < n;j++)
	{
		c_var[j] = j + 1;
	}
		

	int index = 0;
	for (int i = 1; i <= v; i++)
	{
		for (int j = i; j <= v; j++)
		{
			if (i == j)
			{
				cost1[i][j] = INF;
				continue;
			}
			cost1[i][j] = c_var[index];
			cost1[j][i] = c_var[index++];
		}
	}

	
	for (int i = 1; i <= v; i++)
	{
		vector<tuple<int,int>> temp;
		for (int j = 1; j <= v; j++)
		{
			if (i != j)
			{
				tuple<int, int> t (1,cost1[j][i] - 1);
				temp.push_back(t);
			}
		}
		tuple<int, int> t1(1, -1);
		temp.push_back(t1);
		tuple<int, int> t2(2, -1);
		temp.push_back(t2);
		constaints_split[i-1]=temp;
	}
/*
	printf("v:%d\n", v);
	for (int i = 0;i < v;i++)
	{
		vector<int> ve = constaints_split[i];
		for (int j = 0;j < ve.size();j++)
		{
			printf("i%d:%d ", i,ve[j]);
		}
		printf("\n");
	}*/
}

vector<string> mySplit(string str, string pattern)
{
	vector<string> resVec;

	if ("" == str)
	{
		return resVec;
	}

	string strs = str + pattern;

	int pos = strs.find(pattern);
	int size = strs.size();

	while (pos != string::npos)
	{
		string x = strs.substr(0, pos);
		resVec.push_back(x);
		strs = strs.substr(pos + 1, size);
		pos = strs.find(pattern);
	}
	return resVec;
}

vector<int> mySplit3(vector<string> str)
{
	vector<int> resVec;
	for (int i = 0;i < str.size();i++)
	{
		vector<string> temp = mySplit(str[i], "x");
		int res = atoi(temp[0].c_str());
		resVec.push_back(res);
	}
	return resVec;
}
bool isNum(string str)
{
	stringstream sin(str);
	double d;
	char c;
	if (!(sin >> d))
		return false;
	if (sin >> c)
		return false;
	return true;
}
vector<tuple<int, int>> mySplit2(vector<string> str)
{
	vector<tuple<int, int>> resVec;
	vector<string> temp;
	vector<string> temp2;

	for (int i = 0;i < str.size() - 1;i++)
	{
		
		temp = mySplit(str[i], "x");
		//printf("%s %s\n", temp[0], temp[1]);
		
		TCHAR zz[100];

		/*
		CString zz;
		zz.Format(_T("%s %s"), temp[0].c_str(), temp[1].c_str());
		MessageBox(0,zz, 0, 0);
		*/

		if (!isNum(temp[0].c_str()))
		{
			tuple<int, int> t(1, atoi(temp[1].c_str()) - 1);
			resVec.push_back(t);
			
			//MessageBox(0, L"tome", 0, 0);
		}
		else
		{
			tuple<int, int> t(atoi(temp[0].c_str()), atoi(temp[1].c_str()) - 1);
			resVec.push_back(t);
			//MessageBox(0, L"ind", 0, 0);
		}

	}


	int last = str.size() - 1;
	if (str[last].find("<") != string::npos)
	{
		temp2 = mySplit(str[str.size() - 1], "<=");
		temp2[1] = mySplit(temp2[1], "=")[1];
		temp = mySplit(temp2[0], "x");
		if (temp[0] == "")
		{
			tuple<int, int> t(1, atoi(temp[1].c_str()) - 1);
			resVec.push_back(t);
		}
		else
		{
			tuple<int, int> t(atoi(temp[0].c_str()), atoi(temp[1].c_str()) - 1);
			resVec.push_back(t);
		}
		tuple<int, int> tt(2, -1);
		resVec.push_back(tt);
	}
	else if (str[last].find(">") != string::npos)	{
		temp2 = mySplit(str[str.size() - 1], ">=");
		temp2[1] = mySplit(temp2[1], "=")[1];
		temp = mySplit(temp2[0], "x");
		if (temp[0] == "")
		{
			tuple<int, int> t(1, atoi(temp[1].c_str()) - 1);
			resVec.push_back(t);
		}
		else
		{
			tuple<int, int> t(atoi(temp[0].c_str()), atoi(temp[1].c_str()) - 1);
			resVec.push_back(t);
		}
		tuple<int, int> tt(3, -1);
		resVec.push_back(tt);
	}
	else
	{
		temp2 = mySplit(str[str.size() - 1], "=");
		temp = mySplit(temp2[0], "x");
		if (temp[0] == "")
		{
			tuple<int, int> t(1, atoi(temp[1].c_str()) - 1);
			resVec.push_back(t);
		}
		else
		{
			tuple<int, int> t(atoi(temp[0].c_str()), atoi(temp[1].c_str()) - 1);
			resVec.push_back(t);
		}
		tuple<int, int> tt(1, -1);
		resVec.push_back(tt);
	}


	tuple<int, int> tt(atoi(temp2[1].c_str()), -1);
	resVec.push_back(tt);
	return resVec;
}
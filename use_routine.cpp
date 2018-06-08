#pragma once
#include"stdafx.h"

#define INF 1000000
#define MAX_N 10000
int cost[MAX_N][MAX_N];
int c_index[MAX_N][MAX_N];
int vertex;

void makeCostMatrix(double* c_var, int arrlength)
{
	

	for (int i = 2;i < 1000;i++)
	{
		if (i*(i - 1) / 2 == arrlength)
		{
			vertex = i;
			break;
		}
	}

	int index = 0;
	for (int i = 1; i <= vertex; i++)
	{
		for (int j = i; j <= vertex; j++)
		{
			if (i == j)
			{
				cost[i][j] = INF;
				c_index[i][j]= -1;
				continue;
			}
			cost[i][j] = c_var[index];
			cost[j][i] = c_var[index];
			c_index[i][j] = index;
			c_index[j][i] = index++;
		}
	}


}




tuple<float, float> Routine1(double* c_var,PNODE current,
	int n,int branch_var,int left_right,float*x_arr, vector<tuple<int, int>> *constaints_split,
	int max_min, int arrLength)
{

	double* temp_c_var = (double*)malloc(sizeof(double)*n);
	memcpy(temp_c_var, c_var, sizeof(double)*n);

	tuple<int, int> result;
	int lb = 0;
	int ub = 0;
	if (branch_var !=-1)
	{
		for (int i = 0;i < n;i++)
		{
			int temp = current->left_or_rigth[i];

			if (temp!=-1)
			{
				//printf("ind.....\n");
				if (temp == 1)
				{
					lb += temp_c_var[i];
					ub += temp_c_var[i];
					//printf("x%d to 0\n", i + 1, temp_c_var[i]);
					temp_c_var[i] = 0;
				}
				else if(temp==0){
					//printf("x%d to INF\n", i + 1, temp_c_var[i]);
					temp_c_var[i] = INF;
				}
			}
		}

		/*
		for (int j = 0; j < n; j++)
		{
				printf("%f ",temp_c_var[j]);
		}
		printf("\n");
		*/

		if (left_right == 1)
		{
			lb += temp_c_var[branch_var];
			ub += temp_c_var[branch_var];
			//printf("%f is change to 0\n", temp_c_var[branch_var]);
			temp_c_var[branch_var] = 0;
		}
		else {
			//printf("%f is change to INF\n", temp_c_var[branch_var]);
			temp_c_var[branch_var] = INF;
		}
	}

	makeCostMatrix(temp_c_var, n);
	/*
	for (int i = 1; i <= vertex; i++)
	{
		for (int j = 1; j <= vertex; j++)
		{
			printf("%d ", cost[i][j]);
		}
		printf("\n");
	}*/
	
	lb += MST(0);
	ub += greedy2(x_arr);
	result = make_tuple(lb, ub);
	free(temp_c_var);
	return result;
}

void quickSort(vector<tuple<int, int, int>> &s, int l, int r)
{
	if (l < r)
	{
		int i = l, j = r, x = get<2>(s[l]);
		tuple<int, int, int> bibi = s[l];
		while (i < j)
		{
			while (i < j && get<2>(s[j]) >= x) // 从右向左找第一个小于x的数  
				j--;
			if (i < j)
				s[i++] = s[j];
			while (i < j && get<2>(s[i]) < x) // 从左向右找第一个大于等于x的数  
				i++;
			if (i < j)
				s[j--] = s[i];
		}
		s[i] = bibi;
		quickSort(s, l, i - 1); // 递归调用  
		quickSort(s, i + 1, r);
	}
}

int MST(float*x_arr)
{
	int result = 0;
	vector<tuple<int, int, int>> ve;
	for (int i = 2;i <= vertex;i++)
	{
		for (int j = 1 + i;j <= vertex;j++)
		{
			tuple<int, int, int> p(i, j, cost[i][j]);
			ve.push_back(p);
		}
	}

	quickSort(ve, 0, ve.size() - 1);
	

	vector<vector<int>> disjoint_set;

	vector<int> temp = { get<0>(ve[0]),get<1>(ve[0]) };
	disjoint_set.push_back(temp);
	result += get<2>(ve[0]);
	
	if(x_arr)
		x_arr[c_index[get<0>(ve[0])][get<1>(ve[0])]] = 1;

	for (int i = 1;i<ve.size();i++)
	{
		int temp1 = get<0>(ve[i]);
		int temp2 = get<1>(ve[i]);
		int index1 = -1;
		int index2 = -1;
		int flag0 = -1;

		for (int j = 0;j<disjoint_set.size();j++)
		{
			vector<int> temp3 = disjoint_set[j];
			int flag1 = -1;
			int flag2 = -1;

			for (int k = 0;k<temp3.size();k++)
			{
				if (temp3[k] == temp1) flag1 = j;
				if (temp3[k] == temp2) flag2 = j;
			}

			if ((flag1 != -1 && flag2 != -1))
			{
				j = disjoint_set.size() + 1;
				flag0 = 1;
			}
			else if ((index1 != -1 && index2 != -1))
				j = disjoint_set.size() + 1;
			else if (flag1 != -1 && flag2 == -1)
				index1 = flag1;
			else if (flag1 == -1 && flag2 != -1)
				index2 = flag2;
		}

		if (index1 != -1 && index2 != -1)
		{
			disjoint_set[index1].insert(
				disjoint_set[index1].end(),
				disjoint_set[index2].begin(),
				disjoint_set[index2].end());

			result += get<2>(ve[i]);
			if (x_arr)
				x_arr[c_index[get<0>(ve[i])], get<1>(ve[i])] = 1;

			vector<vector<int>>::iterator it = disjoint_set.begin() + index2;
			disjoint_set.erase(it);
		}
		else if (index1 != -1 && index2 == -1)
		{
			disjoint_set[index1].push_back(temp2);
			result += get<2>(ve[i]);
			if (x_arr)
				x_arr[c_index[get<0>(ve[i])][get<1>(ve[i])]] = 1;
		}
		else if (index1 == -1 && index2 != -1)
		{
			disjoint_set[index2].push_back(temp1);
			result += get<2>(ve[i]);
			if (x_arr)
				x_arr[c_index[get<0>(ve[i])][get<1>(ve[i])]] = 1;
		}
		else if (index1 == -1 && index2 == -1 && flag0 != 1)
		{
			vector<int> temp = { temp1,temp2 };
			disjoint_set.push_back(temp);
			result += get<2>(ve[i]);
			if (x_arr)
				x_arr[c_index[get<0>(ve[i])][get<1>(ve[i])]] = 1;
		}

		if (disjoint_set[0].size() == vertex - 1)
			break;
	}

	int min1 = cost[1][1];
	int min1Index = -1;
	int min2Index = -2;
	for (int i = 1;i <= vertex;i++)
	{
		if (min1>cost[1][i])
		{
			min1 = cost[1][i];
			min1Index = i;
		}
	}
	int min2 = cost[1][1];
	for (int i = 1;i <= vertex;i++)
	{
		if (min1Index != i && min2 > cost[1][i])
		{
			min2 = cost[1][i];
			min2Index = i;
		}
	}
	result += min1;
	result += min2;
	if (x_arr)
		x_arr[c_index[get<0>(ve[1])][get<1>(ve[min1Index])]] = 1;
	//printf("%d,%d\n", get<0>(ve[1]), get<1>(ve[min2Index]));
	if (x_arr)
		x_arr[c_index[get<0>(ve[1])][get<1>(ve[min2Index])]] = 1;

	return result;
}

int greedy(float*x_arr)
{
	int tempIndex, currentIndex = 1;
	int result = 0;
	int dfs_visited[MAX_N] = { 0 };
	dfs_visited[1] = true;

	for (int i = 1;i < vertex;i++)
	{
		int min = INF;
		for (int j = 1;j <= vertex;j++)
		{
			if (!dfs_visited[j] && min > cost[currentIndex][j])
			{
				min = cost[currentIndex][j];
				tempIndex = j;
				
			}
		}
	
		result += min;
	
		if (x_arr)
			x_arr[c_index[currentIndex][tempIndex]]=1;
		dfs_visited[tempIndex] = true;
		currentIndex = tempIndex;
	}

	
	result += cost[1][tempIndex];
	if (x_arr)
		x_arr[c_index[1][tempIndex]] = 1;
	return result;
}

int greedy2(float*x_arr)
{
	int tempIndex, currentIndex = 1;
	int result = 0;
	int dfs_visited[MAX_N] = { 0 };
	vector<tuple<int, int,int>> ve1;
	vector<tuple<int, int,int>> ve2;
	vector<tuple<int, int,int>> rute;
	dfs_visited[1] = true;
	int count = 0;

	for (int i = 1;i < vertex;i++)
	{
		int min = INF;
		for (int j = 1;j <= vertex;j++)
		{
			if (!dfs_visited[j] && min > cost[currentIndex][j])
			{
				min = cost[currentIndex][j];
				tempIndex = j;

			}
		}


		tuple<int, int,int> t(currentIndex, tempIndex,count++);
		rute.push_back(t);

		if (cost[currentIndex][tempIndex]!=0 && cost[currentIndex][tempIndex] != INF)
		{
			ve1.push_back(t);
			//printf("ve1\n");
		}else if(cost[currentIndex][tempIndex] == INF)
		{
			//printf("ve2\n");
			ve2.push_back(t);
		}

		x_arr[c_index[currentIndex][tempIndex]] = 1;
		dfs_visited[tempIndex] = true;
		currentIndex = tempIndex;
	}
	//printf("result:%d + %d\n", result, cost[1][tempIndex]);

	tuple<int, int,int> t(1, tempIndex,count);
	rute.push_back(t);
	if (cost[1][tempIndex] != 0 && cost[1][tempIndex] != INF)
	{
		//printf("v1\n");
		ve1.push_back(t);
	}
	else if (cost[1][tempIndex] == INF)
	{
		//printf("v2\n");
		ve2.push_back(t);
	}


	if (ve2.size())
	{
		for (int i = 0;i < ve1.size();i++)
		{
			if (get<0>(ve1[i]) != get<0>(ve2[0]) && get<1>(ve1[i]) != get<0>(ve2[0]) &&
				get<0>(ve1[i]) != get<1>(ve2[0]) && get<1>(ve1[i]) != get<1>(ve2[0]))
			{
				if (cost[get<1>(ve1[i])][get<1>(ve2[0])] +
					cost[get<0>(ve1[i])][get<0>(ve2[0])] <
					cost[get<0>(ve1[i])][get<1>(ve1[i])] +
					cost[get<1>(ve2[0])][get<0>(ve2[0])])
				{
					if (get<2>(ve2[0]) > get<2>(ve1[i]))
					{
						tuple<int, int, int> tt(get<0>(ve1[i]), get<1>(ve2[0]), count);
						tuple<int, int, int> tt2(get<1>(ve1[i]), get<0>(ve2[0]), count);
		
						rute[get<2>(ve2[0])] = tt;
						rute[get<2>(ve1[i])] = tt2;

						break;
					}
				}
			}
		}
	}

	for (int i=0;i<rute.size();i++)
	{
		int x = get<0>(rute[i]);
		int y = get<1>(rute[i]);
		result += cost[x][y];

		x_arr[c_index[x][y]] = 1;
	}


	return result;
}

void changeTU(double* temp_c_var, 
	int n, int &judge, vector<tuple<int, int>> *constaints_split,
	vector<tuple<int, int>> *constaints_split2,int &arrLength2,int arrLength)
{
	int flag = 0;
	int i;


	for (int jj = 0;jj < arrLength;jj++)
	{
		vector<tuple<int, int>> newtu;
		vector<tuple<int, int>> tu = constaints_split[jj];
		if (tu.size() > 3)
		{
			int temp = 0;

	
			for (int z = 0;z < tu.size() - 2;z++)
			{
				int ff = 0;
				for (int jjj = 0;jjj < n;jjj++)
				{
					if (temp_c_var[jjj] == -1 || temp_c_var[jjj] == -2)
					{
						if ((get<1>(tu[z]) == jjj))
						{
					
							ff = temp_c_var[jjj];
							break;
						}
					}
				}
				if (ff == -1)
				{
					temp += get<0>(tu[z]);
				
				}else if (ff==-2)
				{
				}
				else {
			
					newtu.push_back(tu[z]);
				}

			}

			newtu.push_back(tu[tu.size() - 2]);
		
				tuple<int, int> pp(get<0>(tu[tu.size() - 1]) - temp, -1);
				newtu.push_back(pp);
				constaints_split2[arrLength2++] = newtu;

		}
	}



	for (int jj = 0;jj < arrLength;jj++)
	{
		vector<tuple<int, int>> newtu;
		vector<tuple<int, int>> tu = constaints_split[jj];
		if (tu.size() == 3)
		{
			int flag2 = 0;
			for (int i = 0;i < n;i++)
			{
				if (temp_c_var[i] == -1 || temp_c_var[i] == -2)
				{
					if (get<1>(tu[0]) == i)
					{
						flag2 = 1;
						flag = temp_c_var[i];
						break;
					}
				}
			}

			if (flag2)
			{
				//printf("i=%d............\n", i);
				int op = get<0>(tu[1]);
				if (op == 1)
				{
					if (flag == -1)
					{
						if (get<0>(tu[2]) != get<0>(tu[0]))
						{
							judge = 1;
							printf("1111111111111111111111111\n");
							return;
						}

					}
					else if (flag == -2)
					{
						if (get<0>(tu[2]) != 0)
						{
							judge = 1;
							printf("22222222222222222222222222\n");
							return;
						}
					}
				}
				else if (op == 2)
				{
					if (flag == -1)
					{
						if (get<0>(tu[2]) < get<0>(tu[0]))
						{
							judge = 1;
							printf("3333333333333333333333333\n");
							return;
						}
					}
					else if (flag == -2)
					{
						if (get<0>(tu[2]) < 0)
						{
							judge = 1;
							printf("4444444444444444444444444\n");
							return;
						}
					}
				}
				else if (op == 3)
				{
					if (flag == -1)
					{
						if (get<0>(tu[2]) > get<0>(tu[0]))
						{
							judge = 1;
							printf("55555555555555555555555\n");
							return;
						}
					}
					else if (flag == -2)
					{
						if (get<0>(tu[2]) > 0)
						{
							judge = 1;
							printf("66666666666666666666666666\n");
							return;
						}
					}
				}
			}
			else
			{
				constaints_split2[arrLength2++] = tu;
				continue;
			}
		}
	}


}

vector<tuple<int, int>> changelala(vector<tuple<int, int>>*constaints_split2, int arrLength2, int*arrr,int n,int n2)
{
	int arrr2[10000] = { 0 };
	vector<tuple<int, int>> tu;
	int index = 1;
	for (int i=0;i<n;i++)
	{
		if (arrr[i]==-1)
		{
			arrr2[i] = index++;
			if (i + 1!= arrr2[i])
			{
				tuple<int, int> t(i + 1, arrr2[i]);
				tu.push_back(t);
			}
		}
	}


	int flag = 0;
	for (int i=0;i<arrLength2;i++)
	{
		vector<tuple<int, int>> bibi=constaints_split2[i];
		vector<tuple<int, int>> newbibi;
		for (int j=0;j<bibi.size();j++)
		{
			for (int z = 0;z < tu.size();z++)
			{
				if (get<1>((bibi)[j])==(get<0>(tu[z])-1))
				{
					//printf("......................ddd.....\n");
					tuple<int, int> ttt(get<0>((bibi)[j]), (get<1>(tu[z]) - 1));
					newbibi.push_back(ttt);
					flag = 1;
				}
			}
			//printf("22222\n");
			if (flag!=1)
			{
				//printf("1111\n");
				newbibi.push_back(bibi[j]);
			}
			flag = 0;
		}
		constaints_split2[i]=newbibi;
	}
	return tu;
}

tuple<float, float> Routine2(double* c_var, PNODE current, int n,
	int branch_var, int left_right, float*x_arr, vector<tuple<int, int>> *constaints_split,
	int max_min, int arrLength)
{

	double* temp_c_var = (double*)malloc(sizeof(double)*n);
	memcpy(temp_c_var, c_var, sizeof(double)*n);
	int arrr[10000] = {0};

	float result = 0.0;

	float lb = 0;
	float ub = 0;
	int n2 = n;
	int judge = 0;
	vector<tuple<int, int>> constaints_split2[100];
	int arrLength2 = 0;

	if (branch_var != -1)
	{
		
		n2--;
		for (int i = 0;i < n;i++)
		{
			float temp = current->left_or_rigth[i];

			if (temp != -1)
			{
				n2--;
				//printf("ind.....\n");
				if (temp >= 1)
				{
					lb += c_var[i]*temp;
					ub += c_var[i]*temp;
					//printf("x%d to 0\n", i + 1, temp_c_var[i]);
					temp_c_var[i] = -1;

				}
				else if (temp == 0) {
					//printf("x%d to INF\n", i + 1, temp_c_var[i]);
					temp_c_var[i] = -2;
				}
			}
		}

		if (left_right == 1)
		{
			lb += temp_c_var[branch_var];
			ub += temp_c_var[branch_var];
			//printf("%f is change to 0\n", temp_c_var[branch_var]);
			temp_c_var[branch_var] = -1;
		}
		else {
			//printf("%f is change to INF\n", temp_c_var[branch_var]);
			temp_c_var[branch_var] = -2;
		}


					changeTU(temp_c_var,n,judge, constaints_split, constaints_split2, arrLength2,arrLength);
					if (judge==1)
					{
						if (max_min)
						{
							//printf("ind1......\n");
							return  make_tuple(INF, INF);
						}
						else
						{
							//printf("ind2..........\n");
							return make_tuple(0, -100);
						}
					}
					judge = 0;
	
		
	}
	else {
		for (int i = 0;i < arrLength;i++)
		{
			constaints_split2[i] = constaints_split[i];
		}

		arrLength2 = arrLength;

	}


	int tempp = 0;
	
	if (branch_var != -1)
	{
		for (int i = 0;i < n;i++)
		{
			int temp = current->left_or_rigth[i];
			arrr[i] = temp;
			if (temp==-1 && branch_var!=i)
			{
				temp_c_var[tempp++] = c_var[i];
			}
		}
		if (left_right)
		{
			arrr[branch_var] = 1;
		}else
			arrr[branch_var] = 0;
		changelala(constaints_split2, arrLength2, arrr,n,n2);
	}
	
	
	
	IloEnv env;
	
	try {
		IloModel model(env);
		IloNumVarArray vars(env);

		for (int i = 0;i < n2;i++)
		{
			vars.add(IloNumVar(env, 0.0, 1.0));
		}

		IloExpr fo(env);

	
		for (int i = 0;i < n2;i++)
		{
			fo += temp_c_var[i] * vars[i];
		}
		


		if(max_min)
			model.add(IloMinimize(env, fo));
		else
			model.add(IloMaximize(env, fo));

		//printf("size: %d\n", arrLength);
		for (int i=0;i<arrLength2;i++)
		{
			IloExpr fo_constraints(env);
			vector<tuple<int,int>> ve=constaints_split2[i];
			for (int j=0;j<ve.size()-2;j++)
			{
				if (ve.size()<=0)
				{
					break;
				}

				fo_constraints += get<0>(ve[j])*vars[get<1>(ve[j])];
				
			}
		
			//MessageBox(0, L"new", 0, 0);
			if (ve.size()>0)
			{
			
				if (get<0>(ve[ve.size() - 2]) == 1)
				{
					model.add(fo_constraints == get<0>(ve[ve.size() - 1]));
				}
				else if (get<0>(ve[ve.size() - 2]) == 2)
				{
					model.add(fo_constraints <= get<0>(ve[ve.size() - 1]));
				}
				else if (get<0>(ve[ve.size() - 2]) == 3)
				{
					model.add(fo_constraints >= get<0>(ve[ve.size() - 1]));
				}
			}
			
		}
		

		IloCplex cplex(model);
		if (!cplex.solve()) {
			env.error() << "Failed to optimize LP." << endl;
			throw(-1);
		}

		IloNumArray vals(env);
		//env.out() << "solution status = " << cplex.getStatus() << endl;
		env.out() << "Solution value=" << cplex.getObjective() << endl;

		cplex.getValues(vals, vars);
		env.out() << "Values = " << vals << endl;
		
		int lala = 0;

		for (int i = 0;i < n;i++)
		{
			if (current)
			{
				int temp = arrr[i];
				if (temp==-1)
				{
					//printf("ind11111\n");
					//printf("vals:%f, %f........\n", vals[lala],vals[lala]* temp_c_var[lala]);
					result += vals[lala] * temp_c_var[lala];
					x_arr[i] = vals[lala];
					lala++;
				}
				else {
					//printf("ind222222\n");
					x_arr[i] = temp;
				}
			}
			else {
				result += vals[i] * c_var[i];
				x_arr[i] = vals[i];
			}
		}

		result += ub;
	}

	// cathch functions, refer to "C++ try&catch"
	catch (IloException&e) {
		cerr << "Concert exception caught:" << e << endl;
	}
	catch (...) {
		cerr << "Unknown exception caught" << endl;
	}

	env.end();

	if (max_min)
		return  make_tuple(result, INF);
	else
		return make_tuple(0, result);
}


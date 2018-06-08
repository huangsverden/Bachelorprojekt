
// MFCApplication2Dlg.cpp : implementation file
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
#define MAX_N 10000
int strategi;
int max_min;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication2Dlg dialog



CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION2_DIALOG, pParent)
	, vertices(0)
	, routine(0)
	, constra(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, objectFunction);
	DDX_Text(pDX, IDC_EDIT5, vertices);
	DDX_Text(pDX, IDC_EDIT3, routine);
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
	DDX_Control(pDX, IDC_EDIT2, constraints);
	DDX_Text(pDX, IDC_EDIT2, constra);
	DDX_Control(pDX, IDC_EDIT3, routi);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication2Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO1, &CMFCApplication2Dlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMFCApplication2Dlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO6, &CMFCApplication2Dlg::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO7, &CMFCApplication2Dlg::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_RADIO8, &CMFCApplication2Dlg::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_CHECK1, &CMFCApplication2Dlg::OnBnClickedCheck1)
	ON_EN_CHANGE(IDC_EDIT5, &CMFCApplication2Dlg::OnEnChangeEdit5)
END_MESSAGE_MAP()


// CMFCApplication2Dlg message handlers

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication2Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CMFCApplication2Dlg::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	max_min = 0;
}


void CMFCApplication2Dlg::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	max_min = 1;
}

void CharToTchar(const char * _char, TCHAR * tchar)
{
	MultiByteToWideChar(CP_ACP, 0, _char, -1, tchar, 100);
}

void CMFCApplication2Dlg::OnBnClickedButton1()
{

	// TODO: Add your control notification handler code here
	/*
	int state = ((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck();
	if (state)
	{
	MessageBox((LPCTSTR)"1", 0, 0);
	}
	else {
	MessageBox((LPCTSTR)"0", 0, 0);
	}

	if (max_min)
	{
	LPCTSTR s = L"min";
	MessageBox(s, 0, 0);
	}
	else
	{
	MessageBox(L"max", 0, 0);
	}
	CString c_user;
	objectFunction.GetWindowTextW(c_user);
	MessageBox(c_user, 0, 0);

	TCHAR szCmd[100] = { 0 };
	GetDlgItemText(IDC_EDIT2, szCmd, 100);
	MessageBox((LPCTSTR)szCmd, 0, 0);

	UpdateData(TRUE);
	CString s;
	s.Format(_T("%d"), vertices);
	MessageBox(s, 0, 0);

	CString t;
	for (int i = 0;i < sss.size(); i++)
	{
	CString zz;
	zz.Format(_T("%f"),c_var[i]);
	MessageBox(zz, 0, 0);
	t.Append(zz);
	t.Append(L"\r\n");
	}
	SetDlgItemText(IDC_EDIT4, t);

	TCHAR zz[100];
	CharToTchar("ffff", zz);
	MessageBox(zz, 0, 0);
	*/
	float UB;
	float LB;
	int n = 0;
	int c = 0;
	double c_var[MAX_N];

	char* constaints[200];

	vector<tuple<int, int>> constaints_split[200];

	int nrCount = 0;

	PNODE result = 0;
	PNODE root = 0;
	int test=((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck();

	if (test)
	{
		UpdateData(TRUE);
		createGraf(constaints_split, constaints, vertices, n, c_var, c);
		max_min = 1;
		c = vertices;
		
	}
	else {
		CString c_user;
		objectFunction.GetWindowTextW(c_user);
		string x = CT2A(c_user.GetBuffer());
		vector<string> ss = mySplit(x, "+");
		n = ss.size();
		vector<int> sss=mySplit3(ss);



		CString t;
		for (int i = 0;i < sss.size(); i++)
		{
			//1x2+3x4
			c_var[i] = sss[i];
		}

		CString con;
		constraints.GetWindowTextW(con);
		//MessageBox(con, 0, 0);
		string e2 = CT2A(con.GetBuffer());
		vector<string> ccc=mySplit(e2, "\r\n");
		c = ccc.size();
		for (int i = 0;i < ccc.size(); i++)
		{
			/*
			1x2+3x4<=3
			5x6+7x8=2
			*/
			constaints[i] = (char*)malloc(100);

			strcpy(constaints[i], (char*)ccc[i].c_str());
			/*
			TCHAR zz[100];
			CharToTchar(constaints[i], zz);
			MessageBox(zz, 0, 0);*/
		}
		takeConstriants(constaints_split, constaints, c);
	}

	CString zz;
	routi.GetWindowTextW(zz);
	int userRoutine=atoi(CT2A(zz));

	tuple<float, float>(*Routine)(double*, PNODE, int, int, int, float*, vector<tuple<int, int>> *, int, int) = 0;
	if (userRoutine == 1)
	{
		Routine = Routine1;
	}
	else if (userRoutine == 2)
	{
		Routine = Routine2;
	}
agian:
	
	float x_var[MAX_N] = { 0 };
	tuple<float, float>t = Routine(c_var, 0, n, -1, -1, x_var, constaints_split, max_min, c);
	//printf("lb:%d  ub:%d\n", get<0>(t), get<1>(t));
	UB = get<1>(t);
	LB = get<0>(t);
	//cin >> UB >> LB;
	root = createNode(LB, UB, -1, 0, n, nrCount++, 0, 0, x_var);
	result = root;

	if (UB == LB)
	{
		goto End;
	}
	for (int i = 0;i <= n;i++)
	{
		if (userRoutine == 2 && i == n)
		{
			int x_v[MAX_N] = { 0 };
			for (int j = 0;j < n;j++)
			{
				x_v[j] = (int)root->x_var[j];
				
			}
				

			vector<tuple<int, int>>t;
			if (checkSubtour(x_v, n, t))
			{
				//MessageBox(L"wrong", 0, 0);
				//printf("wrong result\n");
				int size = t.size();
				tuple<int, int> tu(2, -1);
				t.push_back(tu);
				tuple<int, int> tu2(size - 1, -1);
				t.push_back(tu2);

				constaints_split[c++] = t;
				/*
				for (int s=0;s<c;s++)
				{
				vector<int>zz= constaints_split[s];
				for (int z = 0;z < zz.size();z++)
				{
				printf("%d ", zz[z]);
				}
				printf("\n");
				}*/
				freeNode(root);
				goto agian;
			}
			goto End;
		}
		if (userRoutine == 2 && ((x_var[i] - int(x_var[i])) != 0))
		{
			//printf("..\n");
			break;
		}
	}




	

	if (strategi == 1)
	{
		vector<PNODE> pq;
		pq.push_back(root);
		while (pq.size())
		{
			PNODE fatherNode = pq[pq.size() - 1];
			pq.pop_back();

			if (checkAllth(fatherNode, n)) continue;

			//printStatus(root, n, fatherNode, max_min, LB, UB);


			int index = choose_x(fatherNode, n);
			index++;
			//cout << "which x variable do you wanna branch on:" << endl;
			//printf("x%d\n", index);
			/*
			int index;
			cout << "which x variable do you wanna branch on:" << endl;
			cin >> index;
			while (fatherNode->left_or_rigth[index - 1] != -1)
			{
			cout << "this x variable is been taken, choose new one:" << endl;
			cin >> index;
			}*/

			PNODE leftNode = whileBody(fatherNode, n, Routine, c_var,
				UB, LB, nrCount, constaints_split, constaints, c, 0, index, max_min, result, userRoutine);


			PNODE rightNode = whileBody(fatherNode, n, Routine, c_var,
				UB, LB, nrCount, constaints_split, constaints, c, 1, index, max_min, result, userRoutine);

			if (rightNode) pq.push_back(rightNode);
			//if (checkEnd(rightNode, n, LB, root, result, UB,max_min,userRoutine)) goto End;
			if (leftNode) pq.push_back(leftNode);
			//if (checkEnd(leftNode, n, LB, root, result, UB, max_min,userRoutine)) goto End;
		}

	}
	else if (strategi == 2)
	{
		queue<PNODE> pq;
		pq.push(root);
		while (pq.size())
		{
			PNODE fatherNode = pq.front();
			pq.pop();

			if (checkAllth(fatherNode, n)) continue;

			//printStatus(root, n, fatherNode, max_min, LB, UB);

			int index = choose_x(fatherNode, n);
			index++;
			//cout << "which x variable do you wanna branch on:" << endl;
			//printf("x%d\n", index);
			/*
			int index;
			cout << "which x variable do you wanna branch on:" << endl;
			cin >> index;
			while (fatherNode->left_or_rigth[index - 1] != -1)
			{
			cout << "this x variable is been taken, choose new one:" << endl;
			cin >> index;
			}*/

			PNODE leftNode = whileBody(fatherNode, n, Routine, c_var,
				UB, LB, nrCount, constaints_split, constaints, c, 0, index, max_min, result, userRoutine);
			if (leftNode) pq.push(leftNode);

			//if (checkEnd(leftNode, n, LB, root, result, UB, max_min,userRoutine)) goto End;


			PNODE rightNode = whileBody(fatherNode, n, Routine, c_var,
				UB, LB, nrCount, constaints_split, constaints, c, 1, index, max_min, result, userRoutine);
			if (rightNode) pq.push(rightNode);

			//if (checkEnd(rightNode, n, LB, root, result, UB, max_min,userRoutine)) goto End;
		}
	}
	else if (strategi == 3)
	{
		priority_queue<PNODE, vector<PNODE>, cmp> pq;
		pq.push(root);
		while (pq.size())
		{
			PNODE fatherNode = pq.top();
			pq.pop();

			if (checkAllth(fatherNode, n)) continue;

			//printStatus(root, n, fatherNode, max_min, LB, UB);


			int index = choose_x(fatherNode, n);
			index++;
			//cout << "which x variable do you wanna branch on:" << endl;
			//printf("x%d\n", index);
			/*
			cout << "which x variable do you wanna branch on:" << endl;
			cin >> index;
			while (fatherNode->left_or_rigth[index - 1] != -1)
			{
			cout << "this x variable is been taken, choose new one:" << endl;
			cin >> index;
			}*/


			PNODE leftNode = whileBody(fatherNode, n, Routine, c_var,
				UB, LB, nrCount, constaints_split, constaints, c, 0, index, max_min, result, userRoutine);
			if (leftNode) printf("pq push\n");


			if (leftNode) pq.push(leftNode);

			if (checkEnd(leftNode, n, LB, root, result, UB, max_min, userRoutine)) goto End;


			PNODE rightNode = whileBody(fatherNode, n, Routine, c_var,
				UB, LB, nrCount, constaints_split, constaints, c, 1, index, max_min, result, userRoutine);
			if (rightNode) pq.push(rightNode);

			if (checkEnd(rightNode, n, LB, root, result, UB, max_min, userRoutine)) goto End;
		}
	}

End:
	if (result)
	{
		
		CString r;
		CString temp;
	

		int ruteLength = 0;
		for (int i = 0;i < n;i++)
		{
			printf("x%d:%.0f  ", i + 1, result->x_var[i]);
			r.Append(L"x");
			temp.Format(_T("%d"), i+1);
			r.Append(temp);
			r.Append(L":");
			temp.Format(_T("%.0f"), result->x_var[i]);
			r.Append(temp);
			r.Append(L" ");
			ruteLength += int(result->x_var[i])*c_var[i];
		}
		r.Append(L"\r\n");
		r.Append(L"z:");
		temp.Format(_T("%d"), ruteLength);
		r.Append(temp);
		r.Append(L"\r\n");

		r.Append(L"total create: ");
		temp.Format(_T("%d"), nrCount);
		r.Append(temp);
		r.Append(L" nodes");
		SetDlgItemText(IDC_EDIT4, r);
		
		
	}

	int test1 = ((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck();
	if (test1)
	{
		GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
	}
	freeconstaints(constaints, c);
	freeNode(root);

}


void CMFCApplication2Dlg::OnBnClickedRadio6()
{
	// TODO: Add your control notification handler code here
	strategi = 1;
}


void CMFCApplication2Dlg::OnBnClickedRadio7()
{
	// TODO: Add your control notification handler code here
	strategi = 2;
}


void CMFCApplication2Dlg::OnBnClickedRadio8()
{
	// TODO: Add your control notification handler code here
	strategi = 3;
}


void CMFCApplication2Dlg::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
	int test = ((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck();
	if (test)
	{
		GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
		CButton *bn1 = (CButton *)this->GetDlgItem(IDC_RADIO1);
		bn1->EnableWindow(FALSE);
		CButton *bn2 = (CButton *)this->GetDlgItem(IDC_RADIO2);
		bn2->EnableWindow(FALSE);
	}
	else {
		GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
		CButton *bn1 = (CButton *)this->GetDlgItem(IDC_RADIO1);
		bn1->EnableWindow(TRUE);
		CButton *bn2 = (CButton *)this->GetDlgItem(IDC_RADIO2);
		bn2->EnableWindow(TRUE);
	}
	
}


void CMFCApplication2Dlg::OnEnChangeEdit5()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	
}

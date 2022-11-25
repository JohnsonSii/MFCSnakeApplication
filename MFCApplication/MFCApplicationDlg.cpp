
// MFCApplicationDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication.h"
#include "MFCApplicationDlg.h"
#include "afxdialogex.h"
#include "Snake.h"
#include <iostream>
#include <random>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCApplicationDlg 对话框



CMFCApplicationDlg::CMFCApplicationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SCORE, Score);
}

BEGIN_MESSAGE_MAP(CMFCApplicationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CMFCApplicationDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CMFCApplicationDlg::OnBnClickedButtonStop)
	ON_WM_TIMER()
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()


// CMFCApplicationDlg 消息处理程序

BOOL CMFCApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplicationDlg::OnPaint()
{
	/*
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	*/

	CPaintDC dc(this); // 用于绘制的设备上下文


	// 初始化控件

	CRect IGameRect = this->GetControlRect(IDC_GAME);
	GetDlgItem(IDC_GAME)->MoveWindow(IGameRect.left, IGameRect.top, 680, 600, false);


	// 自定义字体

	TinyFont.CreatePointFont(90, _T("Arial"));
	NormFont.CreatePointFont(135, _T("Arial"));
	LargeFont.CreatePointFont(180, _T("Arial"));


	// 设置 IDC_EDIT_SCORE 字体

	CWnd* IEditScore = this->GetDlgItem(IDC_EDIT_SCORE);
	IEditScore->SetFont(&LargeFont);


	// 设置 Offset 以实现垂直方向居中对齐

	CRect IEditScoreRect = this->GetControlRect(IDC_EDIT_SCORE);
	IEditScore->GetClientRect(&IEditScoreRect);
	OffsetRect(&IEditScoreRect, 0, 9);
	IEditScore->SendMessage(EM_SETRECT, 0, (LPARAM)&IEditScoreRect);


	// 设置 IDC_STATIC_SCORE 字体

	CWnd* IStaticScore = this->GetDlgItem(IDC_STATIC_SCORE);
	IStaticScore->SetFont(&NormFont);


	// 绘制背景

	CDC* pdc = GetDC();
	IGameRect = this->GetControlRect(IDC_GAME);
	CBrush bgBrush(RGB(255, 255, 255));
	pdc->SelectObject(&bgBrush);
	pdc->Rectangle(IGameRect);
	pdc->DeleteDC();

	// 游戏初始化

	GameInit();


}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CRect CMFCApplicationDlg::GetControlRect(int nID)
{
	CRect rect;
	CWnd* IDlgItem = this->GetDlgItem(nID);
	IDlgItem->GetWindowRect(&rect);  // 获取控件相对于屏幕的位置
	ScreenToClient(rect); // 转化为相对于客户区的位置
	return rect;
}

void CMFCApplicationDlg::GameInit()
{
	CDC* pdc = GetDlgItem(IDC_GAME)->GetWindowDC();

	// 绘制网格

	CBrush gridBrush(RGB(0, 0, 0));
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 34; j++) {
			Map[i][j].left = 0 + j * 20;
			Map[i][j].right = 20 + j * 20;
			Map[i][j].top = 0 + i * 20;
			Map[i][j].bottom = 20 + i * 20;
			pdc->SelectObject(&gridBrush);
			pdc->Rectangle(Map[i][j]);
		}
	}
	pdc->DeleteDC();

	// 蛇初始化

	Snake.Init();
	Score = 0;
	START = false;
	DEAD = false;
	srand((unsigned)time(NULL));
	DrawSnakeBody();
	SetBean();

	CWnd* IEditScore = this->GetDlgItem(IDC_EDIT_SCORE);

	IEditScore->SetWindowTextW(_T("0"));

	SetDlgItemText(IDC_BUTTON_START, _T("Start"));

	UpdateMoveRight();

	SetTimer(1, 120, NULL);

}

void CMFCApplicationDlg::DrawSnakeBody()
{
	CDC* pdc = GetDlgItem(IDC_GAME)->GetWindowDC();

	// 绘制蛇身

	CBrush snackBrush(RGB(255, 0, 0));
	for (int i = 0; i < Snake.len; i++) {

		pdc->SelectObject(&snackBrush);
		pdc->Rectangle(Map[Snake.body[i].xPos][Snake.body[i].yPos]);

	}
	pdc->DeleteDC();
}

void CMFCApplicationDlg::UpdateMoveLeft()
{
	CDC* pdc = GetDlgItem(IDC_GAME)->GetWindowDC();

	// 将最后一个恢复背景色

	CBrush bgBrush(RGB(0, 0, 0));
	pdc->SelectObject(&bgBrush);
	pdc->Rectangle(Map[Snake.body[Snake.len - 1].xPos][Snake.body[Snake.len - 1].yPos]);
	Snake.MoveLeft();
	DrawSnakeBody();
	pdc->DeleteDC();
}

void CMFCApplicationDlg::UpdateMoveRight()
{
	CDC* pdc = GetDlgItem(IDC_GAME)->GetWindowDC();

	// 将最后一个恢复背景色

	CBrush bgBrush(RGB(0, 0, 0));
	pdc->SelectObject(&bgBrush);
	pdc->Rectangle(Map[Snake.body[Snake.len - 1].xPos][Snake.body[Snake.len - 1].yPos]);
	Snake.MoveRight();
	DrawSnakeBody();
	pdc->DeleteDC();
}

void CMFCApplicationDlg::UpdateMoveUp()
{
	CDC* pdc = GetDlgItem(IDC_GAME)->GetWindowDC();

	// 将最后一个恢复背景色

	CBrush bgBrush(RGB(0, 0, 0));
	pdc->SelectObject(&bgBrush);
	pdc->Rectangle(Map[Snake.body[Snake.len - 1].xPos][Snake.body[Snake.len - 1].yPos]);
	Snake.MoveUp();
	DrawSnakeBody();
	pdc->DeleteDC();
}

void CMFCApplicationDlg::UpdateMoveDown()
{
	CDC* pdc = GetDlgItem(IDC_GAME)->GetWindowDC();

	// 将最后一个恢复背景色

	CBrush bgBrush(RGB(0, 0, 0));
	pdc->SelectObject(&bgBrush);
	pdc->Rectangle(Map[Snake.body[Snake.len - 1].xPos][Snake.body[Snake.len - 1].yPos]);
	Snake.MoveDown();
	DrawSnakeBody();
	pdc->DeleteDC();
}

void CMFCApplicationDlg::OnTimer(UINT_PTR nIDEvent)
{
	UpdateData(true);
	if (START && !DEAD) {
		switch (Snake.head)
		{
		case Dire::Left: UpdateMoveLeft(); break;
		case Dire::Right: UpdateMoveRight(); break;
		case Dire::Up: UpdateMoveUp(); break;
		case Dire::Down: UpdateMoveDown(); break;
		default:
			break;
		}

		Score = Score--;
		CString str;
		str.Format(_T("%d"), Score);
		CWnd* IEditScore = this->GetDlgItem(IDC_EDIT_SCORE);
		IEditScore->SetWindowTextW(str);

		if (CheckLive() == false) {
			DEAD = true;
			CString str;
			str.Format(_T("Sorry, your score is %d . \n\n Please try again !"), Score);
			//str = TEXT("sorry, your score is " + str + " ~ \n\n Please try again~");

			/*CInfoDlg dlg(NULL, m_showFont1, str);
			CInfoDlg dlg;
			INT_PTR nres = dlg.DoModal();
			if (IDOK == nres) {
				OnBnClickedButtonStop();
			}*/

			if (MessageBox(str, TEXT("INFO"), MB_ICONINFORMATION) == IDOK) {
				OnBnClickedButtonStop();
			}
			GameOver();
		}
		EatBean();
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CMFCApplicationDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanging(lpwndpos);

	// TODO: 在此处添加消息处理程序代码
	// 获取屏幕宽度
	int nMaxX = GetSystemMetrics(SM_CXSCREEN);
	// 获取屏幕高度
	int nMaxY = GetSystemMetrics(SM_CYSCREEN);

	// 判断窗口X坐标有无超过左边桌面。
	if (lpwndpos->x < 0)
	{
		lpwndpos->x = 0;
	}

	// 判断窗口X坐标有无超过右边桌面。
	if (lpwndpos->x + lpwndpos->cx > nMaxX)
	{
		lpwndpos->x = nMaxX - lpwndpos->cx;
	}

	// 判断窗口Y坐标有无超过顶部桌面。
	if (lpwndpos->y < 0)
	{
		lpwndpos->y = 0;
	}

	// 判断窗口Y坐标有无超过底部桌面。
	if (lpwndpos->y + lpwndpos->cy > nMaxY)
	{
		lpwndpos->y = nMaxY - lpwndpos->cy;
	}
}

BOOL CMFCApplicationDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (START && DEAD == false) {
		if (Snake.head != Dire::Down && (pMsg->wParam == VK_UP || pMsg->wParam == 'w' || pMsg->wParam == 'W')) Snake.head = Dire::Up;
		else if (Snake.head != Dire::Up && (pMsg->wParam == VK_DOWN || pMsg->wParam == 's' || pMsg->wParam == 'S')) Snake.head = Dire::Down;
		else if (Snake.head != Dire::Right && (pMsg->wParam == VK_LEFT || pMsg->wParam == 'a' || pMsg->wParam == 'A')) Snake.head = Dire::Left;
		else if (Snake.head != Dire::Left && (pMsg->wParam == VK_RIGHT || pMsg->wParam == 'd' || pMsg->wParam == 'D')) Snake.head = Dire::Right;
	}
	/*if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_EDIT_score)->m_hWnd)
		{
			return true;
		}
	}*/

	//return CDialogEx::PreTranslateMessage(pMsg);
	return FALSE;
}

void CMFCApplicationDlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	START = true;

}

void CMFCApplicationDlg::OnBnClickedButtonStop()
{
	// TODO: 在此添加控件通知处理程序代码
	GameOver();
	GameInit();
}

bool CMFCApplicationDlg::CheckLive()
{
	// 判断是否出界
	if (Snake.body[0].xPos < 0 || Snake.body[0].xPos >= 30 || Snake.body[0].yPos < 0 || Snake.body[0].yPos >= 38) return false;
	// 判断是否撞到了自己
	for (int i = 1; i < Snake.len; i++) {
		if (Snake.body[0].xPos == Snake.body[i].xPos && Snake.body[0].yPos == Snake.body[i].yPos) return false;
	}
	return true;
}

void CMFCApplicationDlg::GameOver()
{
	KillTimer(1);
	START = false;
}

bool CMFCApplicationDlg::SetBean()
{
	srand((unsigned)time(NULL));
	bool setB = false;
	bool safe = true;
	while (safe) {
		pos.xPos = rand() % 30;
		pos.yPos = rand() % 34;
		for (int i = 0; i < Snake.len; i++) {
			if (pos.xPos == Snake.body[i].xPos && pos.yPos == Snake.body[i].yPos) {
				safe = false; break;
			}
		}
		if (safe) {
			setB = true;
			safe = false;
		}
		else safe = true;
	}
	CDC* pdc = GetDlgItem(IDC_GAME)->GetWindowDC();
	CBrush beanBrush(RGB(0, 255, 0));
	pdc->SelectObject(&beanBrush);
	pdc->Rectangle(Map[pos.xPos][pos.yPos]);
	pdc->DeleteDC();
	return setB;
}

void CMFCApplicationDlg::EatBean()
{
	if (pos.xPos == Snake.body[0].xPos && pos.yPos == Snake.body[0].yPos) {
		Snake.len++;
		SetBean();
		Score = Score + pow((pow(abs(pos.xPos - Snake.body[0].xPos), 2) + pow(abs(pos.yPos - Snake.body[0].yPos), 2)), 0.6);
		CString str;
		str.Format(_T("%d"), Score);
		CWnd* IEditScore = this->GetDlgItem(IDC_EDIT_SCORE);
		IEditScore->SetWindowTextW(str);

	}
}

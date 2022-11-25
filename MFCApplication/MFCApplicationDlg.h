
// MFCApplicationDlg.h: 头文件
//

#pragma once

#include "Snake.h"


// CMFCApplicationDlg 对话框
class CMFCApplicationDlg : public CDialogEx
{
// 构造
public:
	CMFCApplicationDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int Score = 0;
	bool INIT = true;
	bool START = false;
	bool DEAD = false;
	CSnake Snake;
	CFont TinyFont;
	CFont NormFont;
	CFont LargeFont;
	CRect Map[30][34];
	Point pos = { 0, 0 };

	CRect GetControlRect(int nID);
	void GameInit();
	void DrawSnakeBody();
	void UpdateMoveLeft();
	void UpdateMoveRight();
	void UpdateMoveUp();
	void UpdateMoveDown();
	void GameOver();
	bool CheckLive();
	bool SetBean();
	void EatBean();

	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

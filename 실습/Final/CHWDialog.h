#pragma once
#include "afxdialogex.h"


// CHWDialog 대화 상자

class CHWDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHWDialog)

public:
	CHWDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CHWDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_NewHeight;
	int m_NewWidth;
};

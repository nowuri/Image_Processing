#pragma once
#include "afxdialogex.h"


// CDialogMask 대화 상자

class CDialogMask : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogMask)

public:
	CDialogMask(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDialogMask();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_input;
};

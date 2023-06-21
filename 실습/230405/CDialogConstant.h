#pragma once
#include "afxdialogex.h"


// CDialogConstant 대화 상자

class CDialogConstant : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogConstant)

public:
	CDialogConstant(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDialogConstant();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_Input1;
	int m_Input2;
};

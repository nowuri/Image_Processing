#pragma once
#include "afxdialogex.h"


// CDialogRadio 대화 상자

class CDialogRadio : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogRadio)

public:
	CDialogRadio(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDialogRadio();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};

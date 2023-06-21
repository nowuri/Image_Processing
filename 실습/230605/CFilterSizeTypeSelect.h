#pragma once
#include "afxdialogex.h"


// CFilterSizeTypeSelect 대화 상자

class CFilterSizeTypeSelect : public CDialogEx
{
	DECLARE_DYNAMIC(CFilterSizeTypeSelect)

public:
	CFilterSizeTypeSelect(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CFilterSizeTypeSelect();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};

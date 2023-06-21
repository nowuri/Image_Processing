#pragma once
#include "afxdialogex.h"


// CFilterTypeSelection 대화 상자

class CFilterTypeSelection : public CDialogEx
{
	DECLARE_DYNAMIC(CFilterTypeSelection)

public:
	CFilterTypeSelection(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CFilterTypeSelection();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILTERSELECTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_ListType = 0;

	CComboBox m_ComboList_FilterType;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboFiltertype();
};

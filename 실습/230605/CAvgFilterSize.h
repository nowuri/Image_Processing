#pragma once
#include "afxdialogex.h"


// CAvgFilterSize 대화 상자

class CAvgFilterSize : public CDialogEx
{
	DECLARE_DYNAMIC(CAvgFilterSize)

public:
	CAvgFilterSize(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAvgFilterSize();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BLURRING_FILTERAVESIZECHANGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nFilterSize;
};

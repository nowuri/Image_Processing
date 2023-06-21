#pragma once
#include "afxdialogex.h"


// ImageRotate 대화 상자

class ImageRotate : public CDialogEx
{
	DECLARE_DYNAMIC(ImageRotate)

public:
	ImageRotate(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ImageRotate();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_ImageDegree;
};

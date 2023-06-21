// CAvgFilterSize.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication3.h"
#include "afxdialogex.h"
#include "CAvgFilterSize.h"


// CAvgFilterSize 대화 상자

IMPLEMENT_DYNAMIC(CAvgFilterSize, CDialogEx)

CAvgFilterSize::CAvgFilterSize(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BLURRING_FILTERAVESIZECHANGE, pParent)
	, m_nFilterSize(0)
{

}

CAvgFilterSize::~CAvgFilterSize()
{
}

void CAvgFilterSize::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_nFilterSize);
}


BEGIN_MESSAGE_MAP(CAvgFilterSize, CDialogEx)
END_MESSAGE_MAP()


// CAvgFilterSize 메시지 처리기

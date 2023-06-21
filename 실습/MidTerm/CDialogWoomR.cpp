// CDialogWoomR.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "CDialogWoomR.h"


// CDialogWoomR 대화 상자

IMPLEMENT_DYNAMIC(CDialogWoomR, CDialogEx)

CDialogWoomR::CDialogWoomR(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_ZoomIn(0)
{

}

CDialogWoomR::~CDialogWoomR()
{
}

void CDialogWoomR::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_ZoomIn);
	DDV_MinMaxInt(pDX, m_ZoomIn, 0, 255);
}


BEGIN_MESSAGE_MAP(CDialogWoomR, CDialogEx)
END_MESSAGE_MAP()


// CDialogWoomR 메시지 처리기

// CDialogConstant.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "CDialogConstant.h"


// CDialogConstant 대화 상자

IMPLEMENT_DYNAMIC(CDialogConstant, CDialogEx)

CDialogConstant::CDialogConstant(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, m_Input1(0)
	, m_Input2(0)
{

}

CDialogConstant::~CDialogConstant()
{
}

void CDialogConstant::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Input1, m_Input1);
	DDV_MinMaxInt(pDX, m_Input1, 0, 255);
	DDX_Text(pDX, IDC_Input2, m_Input2);
	DDV_MinMaxInt(pDX, m_Input2, 0, 255);
}


BEGIN_MESSAGE_MAP(CDialogConstant, CDialogEx)
END_MESSAGE_MAP()


// CDialogConstant 메시지 처리기

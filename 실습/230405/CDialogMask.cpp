// CDialogMask.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "CDialogMask.h"


// CDialogMask 대화 상자

IMPLEMENT_DYNAMIC(CDialogMask, CDialogEx)

CDialogMask::CDialogMask(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, m_input(0)
{

}

CDialogMask::~CDialogMask()
{
}

void CDialogMask::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_input, m_input);
}


BEGIN_MESSAGE_MAP(CDialogMask, CDialogEx)
END_MESSAGE_MAP()


// CDialogMask 메시지 처리기

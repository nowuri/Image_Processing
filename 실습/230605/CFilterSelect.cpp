// CFilterSelect.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication3.h"
#include "afxdialogex.h"
#include "CFilterSelect.h"


// CFilterSelect 대화 상자

IMPLEMENT_DYNAMIC(CFilterSelect, CDialogEx)

CFilterSelect::CFilterSelect(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, m_nFilterSize(0)
{

}

CFilterSelect::~CFilterSelect()
{
}

void CFilterSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_nFilterSize);
}


BEGIN_MESSAGE_MAP(CFilterSelect, CDialogEx)
END_MESSAGE_MAP()


// CFilterSelect 메시지 처리기

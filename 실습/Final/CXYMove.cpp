// CXYMove.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication3.h"
#include "afxdialogex.h"
#include "CXYMove.h"


// CXYMove 대화 상자

IMPLEMENT_DYNAMIC(CXYMove, CDialogEx)

CXYMove::CXYMove(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG5, pParent)
	, m_xMove(0)
	, m_yMove(0)
{

}

CXYMove::~CXYMove()
{
}

void CXYMove::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_xMove, m_xMove);
	DDX_Text(pDX, IDC_yMove, m_yMove);
}


BEGIN_MESSAGE_MAP(CXYMove, CDialogEx)
END_MESSAGE_MAP()


// CXYMove 메시지 처리기

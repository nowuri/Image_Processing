// CHWDialog.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication3.h"
#include "afxdialogex.h"
#include "CHWDialog.h"


// CHWDialog 대화 상자

IMPLEMENT_DYNAMIC(CHWDialog, CDialogEx)

CHWDialog::CHWDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, m_NewHeight(0)
	, m_NewWidth(0)
{

}

CHWDialog::~CHWDialog()
{
}

void CHWDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NHeight, m_NewHeight);
	DDX_Text(pDX, IDC_NWidth, m_NewWidth);
}


BEGIN_MESSAGE_MAP(CHWDialog, CDialogEx)
END_MESSAGE_MAP()


// CHWDialog 메시지 처리기

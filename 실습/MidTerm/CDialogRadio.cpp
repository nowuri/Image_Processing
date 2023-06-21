// CDialogRadio.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "CDialogRadio.h"


// CDialogRadio 대화 상자

IMPLEMENT_DYNAMIC(CDialogRadio, CDialogEx)

CDialogRadio::CDialogRadio(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

CDialogRadio::~CDialogRadio()
{
}

void CDialogRadio::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogRadio, CDialogEx)
END_MESSAGE_MAP()


// CDialogRadio 메시지 처리기

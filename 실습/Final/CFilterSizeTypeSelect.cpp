// CFilterSizeTypeSelect.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication3.h"
#include "afxdialogex.h"
#include "CFilterSizeTypeSelect.h"


// CFilterSizeTypeSelect 대화 상자

IMPLEMENT_DYNAMIC(CFilterSizeTypeSelect, CDialogEx)

CFilterSizeTypeSelect::CFilterSizeTypeSelect(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CFilterSizeTypeSelect::~CFilterSizeTypeSelect()
{
}

void CFilterSizeTypeSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFilterSizeTypeSelect, CDialogEx)
END_MESSAGE_MAP()


// CFilterSizeTypeSelect 메시지 처리기

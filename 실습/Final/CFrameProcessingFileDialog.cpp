// CFrameProcessingFileDialog.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication3.h"
#include "afxdialogex.h"
#include "CFrameProcessingFileDialog.h"


// CFrameProcessingFileDialog 대화 상자

IMPLEMENT_DYNAMIC(CFrameProcessingFileDialog, CDialogEx)

CFrameProcessingFileDialog::CFrameProcessingFileDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG6, pParent)
	, m_intFrameOperation(FALSE)
{

}

CFrameProcessingFileDialog::~CFrameProcessingFileDialog()
{
}

void CFrameProcessingFileDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_intFrameOperation);
}


BEGIN_MESSAGE_MAP(CFrameProcessingFileDialog, CDialogEx)
END_MESSAGE_MAP()


// CFrameProcessingFileDialog 메시지 처리기

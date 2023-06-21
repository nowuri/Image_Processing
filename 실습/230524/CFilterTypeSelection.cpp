// CFilterTypeSelection.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication3.h"
#include "afxdialogex.h"
#include "CFilterTypeSelection.h"
#include "CFilterTypeSelection.h"


// CFilterTypeSelection 대화 상자

IMPLEMENT_DYNAMIC(CFilterTypeSelection, CDialogEx)

CFilterTypeSelection::CFilterTypeSelection(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILTERSELECTION, pParent)
{

}

CFilterTypeSelection::~CFilterTypeSelection()
{
}

void CFilterTypeSelection::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FILTERTYPE, m_ComboList_FilterType);
}


BEGIN_MESSAGE_MAP(CFilterTypeSelection, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_FILTERTYPE, &CFilterTypeSelection::OnCbnSelchangeComboFiltertype)
END_MESSAGE_MAP()


// CFilterTypeSelection 메시지 처리기


BOOL CFilterTypeSelection::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_ComboList_FilterType.AddString(_T("Average Filter"));
	m_ComboList_FilterType.AddString(_T("Gaussian Smoothing"));
	m_ComboList_FilterType.AddString(_T("Sharpening Filter"));

	m_ComboList_FilterType.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CFilterTypeSelection::OnCbnSelchangeComboFiltertype()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ListType = m_ComboList_FilterType.GetCurSel();
}

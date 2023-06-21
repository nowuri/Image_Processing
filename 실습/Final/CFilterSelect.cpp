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
	DDX_Control(pDX, IDC_COMBO2, m_ComboList_FilterType);
}


BEGIN_MESSAGE_MAP(CFilterSelect, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CFilterSelect::OnCbnSelchangeComboFilter)
	ON_BN_CLICKED(IDC_RADIO1, &CFilterSelect::OnBnClickedRadio1)
END_MESSAGE_MAP()


// CFilterSelect 메시지 처리기


BOOL CFilterSelect::OnInitDialog()
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


void CFilterSelect::OnCbnSelchangeComboFilter()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ListType = m_ComboList_FilterType.GetCurSel();
}


void CFilterSelect::OnBnClickedRadio1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

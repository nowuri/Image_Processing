﻿// CHistogramDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication3.h"
#include "afxdialogex.h"
#include "CHistogramDlg.h"
#include "CDib.h"
#include "RGBBYTE.h"
#include "MFCApplication3Doc.h"
#include "MFCApplication3View.h"
#include "DibEnhancement.h"

// CHistogramDlg 대화 상자

IMPLEMENT_DYNAMIC(CHistogramDlg, CDialogEx)

CHistogramDlg::CHistogramDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HISTOGRAM, pParent)
{
	memset(m_Histogram, 0, sizeof(int) * 256);
}

CHistogramDlg::~CHistogramDlg()
{
}

void CHistogramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHistogramDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CHistogramDlg 메시지 처리기
void CHistogramDlg::SetImage(CDib& dib)
{
	// 정규화된 히스토그램을 임시 배열에 저장한다.
	float histo[256] = { 0.f, };
	DibHistogram(dib, histo);
	// m_Histogram 배열의 최대값을 구한다.
	register int i;
	float max_value = histo[0];
	for (i = 1; i < 256; i++)
	{
		if (histo[i] > max_value) max_value = histo[i];
	}
	// m_Histogram 배열의 최대값이 100이 되도록 전체 배열의 값을 조절한다.
	for (i = 0; i < 256; i++)
	{
		m_Histogram[i] = (int)(histo[i] * 100 / max_value);
	}
}




void CHistogramDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	register int i;
	// 히스토그램 박스 출력
	dc.MoveTo(20, 30);
	dc.LineTo(20, 130);
	dc.LineTo(275, 130);
	dc.LineTo(275, 30);
	// 각 그레이스케일에 해당하는 히스토그램 출력
	for (i = 0; i < 256; i++)
	{
		dc.MoveTo(20 + i, 130);
		dc.LineTo(20 + i, 130 - m_Histogram[i]);
	}
	// 그레이스케일 레벨 출력
	for (i = 0; i < 256; i++)
	{
		dc.SelectStockObject(DC_PEN);
		dc.SetDCPenColor(RGB(i, i, i));
		dc.MoveTo(20 + i, 140);
		dc.LineTo(20 + i, 155);
	}
}

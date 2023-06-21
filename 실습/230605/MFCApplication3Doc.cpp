
// MFCApplication3Doc.cpp: CMFCApplication3Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication3.h"
#endif

#include "MFCApplication3Doc.h"

#include <propkey.h>
#include "CDib.h"
#include "RGBBYTE.h"
#include "CDialog1.h"
#include "CAvgFilterSize.h"
#include "CFilterTypeSelection.h"
#include "ImageRotate.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCApplication3Doc

IMPLEMENT_DYNCREATE(CMFCApplication3Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFCApplication3Doc, CDocument)
END_MESSAGE_MAP()


// CMFCApplication3Doc 생성/소멸

CMFCApplication3Doc::CMFCApplication3Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMFCApplication3Doc::~CMFCApplication3Doc()
{
}

BOOL CMFCApplication3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.
	BOOL bSuccess = TRUE;

	//처리된 m_pNewDib 값을 m_Dib에 복사하면 OnDraw에서 m_Dib를 보여줌
	if (theApp.m_pNewDib != NULL) {
		m_Dib.Copy(theApp.m_pNewDib);
		theApp.m_pNewDib = NULL;
	}
	else {
		bSuccess = FALSE;
	}

	return bSuccess;
}




// CMFCApplication3Doc serialization

void CMFCApplication3Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMFCApplication3Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMFCApplication3Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCApplication3Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCApplication3Doc 진단

#ifdef _DEBUG
void CMFCApplication3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCApplication3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCApplication3Doc 명령


BOOL CMFCApplication3Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return m_Dib.Load(lpszPathName);
}


BOOL CMFCApplication3Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return m_Dib.Save(lpszPathName);
}

void CMFCApplication3Doc::DibInverse(CDib& dib) {
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	if (dib.GetBitCount() == 8) {
		BYTE** ptr = dib.GetPtr();

		for (j = 0; j < h; j++) {
			for (i = 0; i < 2; i++) {
				ptr[j][i] = (255 - ptr[j][i]);
			}
		}
	}
	else if (dib.GetBitCount() == 24) {
		RGBBYTE** ptrrgb = dib.GetRGBPtr();

		BYTE r, g, b;
		for (j = 0; j < h; j++) {
			for (i = 0; i < w; i++) {
				r = ptrrgb[j][i].r;
				g = ptrrgb[j][i].g;
				b = ptrrgb[j][i].b;

				ptrrgb[j][i].r = (255 - r);
				ptrrgb[j][i].g = (255 - g);
				ptrrgb[j][i].b = (255 - b);
			}
		}
	}
}

//사용자 점처리 그룹
void CMFCApplication3Doc::Group(CDib &dib)
{
	// TODO: 여기에 구현 코드 추가.

	CDialog1 dlg;

	if (dlg.DoModal() == IDOK) {
		if (dlg.n_input1 == 0) {
			register int i, j;

			int w = dib.GetWidth();
			int h = dib.GetHeight();

			if (dib.GetBitCount() == 8) {
				BYTE** ptr = dib.GetPtr();

				for (j = 0; j < h; j++) {
					for (i = 0; i < 2; i++) {
						if (ptr[j][i] >= 150) {
							ptr[j][i] = 255;
						}
						else {
							ptr[j][i] = 0;
						}
					}
				}
			}
			else if (dib.GetBitCount() == 24) {
				RGBBYTE** ptrrgb = dib.GetRGBPtr();

				BYTE r, g, b;
				for (j = 0; j < h; j++) {
					for (i = 0; i < w; i++) {
						r = ptrrgb[j][i].r;
						g = ptrrgb[j][i].g;
						b = ptrrgb[j][i].b;

						if ((r > g) && (r > b)) {
							ptrrgb[j][i].r = 255;
							ptrrgb[j][i].g = 0;
							ptrrgb[j][i].b = 0;
						}
						else if ((g > r) && (g > b)) {
							ptrrgb[j][i].r = 0;
							ptrrgb[j][i].g = 255;
							ptrrgb[j][i].b = 0;
						}
						else {
							ptrrgb[j][i].r = 0;
							ptrrgb[j][i].g = 0;
							ptrrgb[j][i].b = 255;
						}

					}
				}
			}
		}
		else if(dlg.n_input1 == 1) {
			DibInverse(dib);
		}
		else {
			AfxMessageBox(L"Not supported function");
		}
	}
}

void CMFCApplication3Doc::OnMaskProcess(CDib& dib, CDib& dib1, double MaskAvg[3][3]) {
	register int i, j, n, m, size = 3;
	double S;

	int w = dib.GetWidth();
	int h = dib.GetHeight();
	
	

	if (dib.GetBitCount() == 8) {
		BYTE** ptr = dib.GetPtr();
		BYTE** ptr1 = dib1.GetPtr();
		for (i = (int)(size / 2); i < h - (int)(size / 2); i++) {
			for (j = (int)(size / 2); j < w - (int)(size / 2); j++) {
				S = 0.0;
				for (n = -(int)(size / 2); n <= (int)(size / 2); n++) {
					for (m = -(int)(size / 2); m <= (int)(size / 2); m++) {
						S += MaskAvg[n + (int)(size / 2)][m + (int)(size / 2)] * ptr[i + n][j + m];
					}
				}
				ptr1[i][j] = (BYTE)limit(S);
			}
		}
	}
	else if (dib.GetBitCount() == 24) {
		RGBBYTE** ptrrgb = dib.GetRGBPtr();
		RGBBYTE** ptrrgb1 = dib1.GetRGBPtr();

		for (i = (int)(size / 2); i < h - (int)(size / 2); i++) {
			for (j = (int)(size / 2); j < w - (int)(size / 2); j++) {
				double S_r = 0.0;
				double S_b = 0.0;
				double S_g = 0.0;
				for (n = -(int)(size / 2); n <= (int)(size / 2); n++) {
					for (m = -(int)(size / 2); m <= (int)(size / 2); m++) {
						S_r += MaskAvg[n + (int)(size / 2)][m + (int)(size / 2)] * ptrrgb[i + n][j + m].r;
						S_b += MaskAvg[n + (int)(size / 2)][m + (int)(size / 2)] * ptrrgb[i + n][j + m].b;
						S_g += MaskAvg[n + (int)(size / 2)][m + (int)(size / 2)] * ptrrgb[i + n][j + m].g;


					}
				}
				ptrrgb1[i][j].r = (BYTE)limit(S_r);
				ptrrgb1[i][j].b = (BYTE)limit(S_b);
				ptrrgb1[i][j].g = (BYTE)limit(S_g);
			}
		}
	}
}

// 영역처리 blurr
void CMFCApplication3Doc::DibImageBlur(CDib& dib, CDib& dib1){
	register int i, j;
	double Mask[3][3] = { {1. / 9, 1. / 9, 1. / 9}, {1. / 9,1. / 9,1. / 9},{1. / 9,1. / 9,1. / 9} };

	OnMaskProcess(dib, dib1, Mask);
}

void CMFCApplication3Doc::DibEdgeLaplacian(CDib& dib, CDib& dib1)
{
	// TODO: 여기에 구현 코드 추가.
	register int i, j;
	double LaplacianMask[3][3] = { {0.,1.,0.},{1.,-4.,1.},{0.,1.,0.} };

	OnMaskProcess(dib, dib1, LaplacianMask);
}

void CMFCApplication3Doc::DibAvgFilterSizeChange(CDib& dib, CDib& dib1) {
	OnMaskProcessSizeSelction(dib, dib1, MaskAvg);
}

void CMFCApplication3Doc::OnMaskProcessSizeSelction(CDib& dib, CDib& dib1, double** MaskAvg) {
	register int i, j, n, m, size;
	double S, S_r, S_b, S_g;
	CString str;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	CAvgFilterSize dlg;
	CString temp;

	if (dlg.DoModal() == IDOK) {

		switch (dlg.m_nFilterSize) {
			case 0:
				size = 3;
				MaskAvg = (double**)malloc(sizeof(double*) * size); //double* 사이즈 3개 메모리 할당
				for (i = 0; i < size; i++)
					MaskAvg[i] = (double*)malloc(sizeof(double) * size); //double 사이즈 3개 메모리 할당
				for (i = 0; i < size; i++) {
					for (j = 0; j < size; j++) {
						MaskAvg[i][j] = 1. / ((double)size * size);
					}
				}

				break;
			case 1:
				size = 5;
				MaskAvg = (double**)malloc(sizeof(double*) * size);
				for (i = 0; i < size; i++) {
					MaskAvg[i] = (double*)malloc(sizeof(double) * size);
				}
				for (i = 0; i < size; i++) {
					for (j = 0; j < size; j++) {
						MaskAvg[i][j] = 1. / ((double)size * size);
					}
				}
				break;
			case 2:
				size = 7;
				MaskAvg = (double**)malloc(sizeof(double*) * size);
				for (i = 0; i < size; i++) {
					MaskAvg[i] = (double*)malloc(sizeof(double) * size);
				}
				for (i = 0; i < size; i++) {
					for (j = 0; j < size; j++) {
						MaskAvg[i][j] = 1. / ((double)size * size);
					}
				}
				break;
		}

		if (dib.GetBitCount() == 8) {
			BYTE** ptr = dib.GetPtr();
			BYTE** ptr1 = dib1.GetPtr();

			for (i = (int)(size / 2); i < h - (int)(size / 2); i++) {
				for (j = (int)(size / 2); j < w - (int)(size / 2); j++) {
					S = 0.0;
					for (n = -(int)(size / 2); n <= (int)(size / 2); n++) {
						for (m = -(int)(size / 2); m <= (int)(size / 2); m++) {
							S += MaskAvg[n + (int)(size / 2)][m + (int)(size / 2)] * ptr[i + n][j + m];
						}
					}
					ptr1[i][j] = (BYTE)limit(S);
				}
			}
			
		}
		else if (dib.GetBitCount() == 24) {
			RGBBYTE** ptrrgb = dib.GetRGBPtr();
			RGBBYTE** ptrrgb1 = dib1.GetRGBPtr();

			for (i = (int)(size / 2); i < h - (int)(size / 2); i++) {
				for (j = (int)(size / 2); j < w - (int)(size / 2); j++) {
					S_r = S_b = S_g = 0.0;
					for (n = -(int)(size / 2); n <= (int)(size / 2); n++) {
						for (m = -(int)(size / 2); m <= (int)(size / 2); m++) {
							S_r += MaskAvg[n + (int)(size / 2)][m + (int)(size / 2)] * ptrrgb[i + n][j + m].r;
							S_b += MaskAvg[n + (int)(size / 2)][m + (int)(size / 2)] * ptrrgb[i + n][j + m].b;
							S_g += MaskAvg[n + (int)(size / 2)][m + (int)(size / 2)] * ptrrgb[i + n][j + m].g;
						}
					}
					ptrrgb1[i][j].r = (BYTE)limit(S_r);
					ptrrgb1[i][j].b = (BYTE)limit(S_b);
					ptrrgb1[i][j].g = (BYTE)limit(S_g);
				}
			}
		}
	}
}

void CMFCApplication3Doc::DibConvFilterSelection(CDib& dib, CDib& dib1) {
	register int i, j;
	double SelectedMask[3][3];

	CFilterTypeSelection dlg;

	if (dlg.DoModal() == IDOK) {
		switch (dlg.m_ListType) {
			case 0:
				for (i = 0; i < 3; i++) {
					for (j = 0; j < 3; j++) {
						SelectedMask[i][j] = 1. / ((double)3. * 3.);
					}
				}
				break;
			case 1:
				SelectedMask[0][0] = 1. / 16.; SelectedMask[0][1] = 1. / 8.; SelectedMask[0][2] = 1. / 16.;
				SelectedMask[1][0] = 1. / 8.; SelectedMask[1][1] = 1. / 4.; SelectedMask[1][2] = 1. / 8.;
				SelectedMask[2][0] = 1. / 16.; SelectedMask[2][1] = 1. / 8.; SelectedMask[2][2] = 1. / 16.;
				break;
			case 2:
				SelectedMask[0][0] = -1.; SelectedMask[0][1] = -1.; SelectedMask[0][2] = -1.;
				SelectedMask[1][0] = -1.; SelectedMask[1][1] = 9.; SelectedMask[1][2] = -1.;
				SelectedMask[2][0] = -1.; SelectedMask[2][1] = -1.; SelectedMask[2][2] = -1.;
				break;
		}
		OnMaskProcess(dib, dib1, SelectedMask);
	}
}



void CMFCApplication3Doc::DibFilterAndSizeSelection(CDib& dib, CDib& dib1, double** MaskAvg)
{
	// TODO: 여기에 구현 코드 추가.

}

void CMFCApplication3Doc::DibGeometricRotate(CDib& dib, CDib& dib1) {
	int i, j, CenterH, CenterW, newH, newW;
	ImageRotate dlg;
	int degree = 0;
	double Radian, PI, Value, Value_r, Value_g, Value_b;

	int w = dib1.GetWidth();
	int h = dib1.GetHeight();

	PI = 3.14159265358979;

	if (dlg.DoModal() == IDOK) {
		degree = dlg.m_ImageDegree;
	}

	Radian = (double)degree * PI / 180.0;

	CenterH = h / 2;
	CenterW = w / 2;

	if (dib.GetBitCount() == 8) {
		BYTE** ptr = dib.GetPtr();
		BYTE** ptr1 = dib1.GetPtr();

		for (i = 0; i < h; i++) {
			for (j = 0; j < w; j++) {
				newH = (int)((i - CenterH) * cos(Radian) - (j - CenterW) * sin(Radian) + CenterH);
				newW = (int)((i - CenterH) * sin(Radian) + (j - CenterW) * cos(Radian) + CenterW);

				if (newH < 0 || newH >= h) {
					Value = 0;
				}
				else if (newW < 0 || newW >= w) {
					Value = 0;
				}
				else {
					Value = ptr[newH][newW];
				}
				ptr1[i][j] = Value;
			}
		}
	}
	else if (dib.GetBitCount() == 24) {
		RGBBYTE** ptrrgb = dib.GetRGBPtr();
		RGBBYTE** ptrrgb1 = dib1.GetRGBPtr();

		for (i = 0; i < h; i++) {
			for (j = 0; j < w; j++) {
				newH = (int)((i - CenterH) * cos(Radian) - (j - CenterW) * sin(Radian) + CenterH);
				newW = (int)((i - CenterH) * sin(Radian) + (j - CenterW) * cos(Radian) + CenterW);

				if (newH < 0 || newH >= h) {
					Value_r = 0;
					Value_b = 0;
					Value_g = 0;
				}
				else if (newW < 0 || newW >= w) {
					Value_r = 0;
					Value_b = 0;
					Value_g = 0;
				}
				else {
					Value_r = ptrrgb[newH][newW].r;
					Value_b = ptrrgb[newH][newW].b;
					Value_g = ptrrgb[newH][newW].g;
				}
				ptrrgb1[i][j].r = Value_r;
				ptrrgb1[i][j].b = Value_b;
				ptrrgb1[i][j].g = Value_g;
			}
		}
	}

}


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
#include "CFilterSelect.h"
#include "CHWDialog.h"
#include "CXYMove.h"
#include "CFrameProcessingFileDialog.h"

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

void CMFCApplication3Doc::OnMaskProcess2(CDib& dib, CDib& dib1, double MaskAvg[5][5]) {
	register int i, j, n, m, size = 5;
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

void CMFCApplication3Doc::OnMaskProcess3(CDib& dib, CDib& dib1, double MaskAvg[7][7]) {
	register int i, j, n, m, size = 7;
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



void CMFCApplication3Doc::DibFilterAndSizeSelection(CDib& dib, CDib& dib1)
{
	// TODO: 여기에 구현 코드 추가.
	register int i, j;
	double SelectedMask[3][3];
	double SelectedMask2[5][5];
	double SelectedMask3[7][7];

	CFilterSelect dlg;

	if (dlg.DoModal() == IDOK) {
		if (dlg.m_ListType == 0 && dlg.m_nFilterSize == 0) {
			for (i = 0; i < 3; i++) {
				for (j = 0; j < 3; j++) {
					SelectedMask[i][j] = 1. / ((double)3. * 3);
				}
			}
			OnMaskProcess(dib, dib1, SelectedMask);
		}
		else if (dlg.m_ListType == 0 && dlg.m_nFilterSize == 1) {
			for (i = 0; i < 5; i++) {
				for (j = 0; j < 5; j++) {
					SelectedMask2[i][j] = 1. / ((double)5. * 5);
				}
			}
			OnMaskProcess2(dib, dib1, SelectedMask2);
		}
		else if (dlg.m_ListType == 0 && dlg.m_nFilterSize == 2) {
			for (i = 0; i < 7; i++) {
				for (j = 0; j < 7; j++) {
					SelectedMask3[i][j] = 1. / ((double)7. * 7);
				}
			}
			OnMaskProcess3(dib, dib1, SelectedMask3);
		}
		else if (dlg.m_ListType == 1 && dlg.m_nFilterSize == 0) {
			double SelectedMask[3][3] = { {1. / 16., 1. / 8., 1. / 16.},{1. / 8.,1. / 4.,1. / 8.},{1. / 16., 1. / 8., 1. / 16.} };
			OnMaskProcess(dib, dib1, SelectedMask);

		}
		else if (dlg.m_ListType == 1 && dlg.m_nFilterSize == 1) {
			double SelectedMask2[5][5] = { {1. / 256., 4. / 256., 6. / 256., 4. / 256., 1. / 256.},
										{4. / 256.,16. / 256.,24. / 256., 16. / 256., 4. / 256.},
										{6. / 256., 24. / 256., 35. / 256., 24. / 256., 6. / 256.},
										{4. / 256., 16. / 256., 24. / 256, 16. / 256., 4. / 256.},
										{1. / 256., 4. / 256., 6. / 256., 4. / 256., 1. / 256.} };
			OnMaskProcess2(dib, dib1, SelectedMask2);
		}
		else if (dlg.m_ListType == 1 && dlg.m_nFilterSize == 2) {
			double SelectedMask3[7][7] = { {0. / 1003., 0. / 1003., 1. / 1003., 2. / 1003., 1. / 1003., 0. / 1003., 0. / 1003.},
										{0. / 1003., 3. / 1003., 13. / 1003., 22. / 1003., 13. / 1003., 3. / 1003., 0. / 1003.},
										{1. / 1003., 13. / 1003., 59. / 1003., 97. / 1003., 59. / 1003., 13. / 1003., 1. / 1003.},
										{2. / 1003., 22. / 1003., 97. / 1003., 159. / 1003., 97. / 1003., 22. / 1003., 2. / 1003.},
										{1. / 1003., 13. / 1003., 59. / 1003., 97. / 1003., 59. / 1003., 13. / 1003., 1. / 1003.},
										{0. / 1003., 3. / 1003., 13. / 1003., 22. / 1003., 13. / 1003., 3. / 1003., 0. / 1003.},
										{0. / 1003., 0. / 1003., 1. / 1003., 2. / 1003., 1. / 1003., 0. / 1003., 0. / 1003.} };
			OnMaskProcess3(dib, dib1, SelectedMask3);
		}
		else if (dlg.m_ListType == 2 && dlg.m_nFilterSize == 0) {
			double SelectedMask[3][3] = { {-1.,-1.,-1.},{-1.,9.,-1.},{-1.,-1.,-1} };
			OnMaskProcess(dib, dib1, SelectedMask);
		}
		else if (dlg.m_ListType == 2 && dlg.m_nFilterSize == 1) {
			double SelectedMask2[5][5] = { {-1., -1., -1., -1., -1.},
										{-1., -1., -1., -1., -1.},
										{-1., -1., 25., -1., -1.},
										{-1., -1., -1., -1., -1.},
										{-1., -1., -1., -1., -1.} };
			OnMaskProcess2(dib, dib1, SelectedMask2);
		}
		else if (dlg.m_ListType == 2 && dlg.m_nFilterSize == 2) {
			double SelectedMask3[7][7] = { {-1., -1., -1., -1., -1.,-1.,-1.},
										{-1., -1., -1., -1., -1.,-1.,-1.},
										{-1., -1., -1., -1., -1.,-1.,-1.},
										{-1., -1., -1., 49., -1.,-1.,-1.},
										{-1., -1., -1., -1., -1.,-1.,-1.},
										{-1., -1., -1., -1., -1.,-1.,-1.},
										{-1., -1., -1., -1., -1.,-1.,-1.} };
			OnMaskProcess3(dib, dib1, SelectedMask3);
		}
	}

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

void CMFCApplication3Doc::OnBinaryErosion(CDib& dib)
{
	// TODO: 여기에 구현 코드 추가.
	register int i, j, S, n, m;
	int size = 3;
	CDib cpy = dib;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	if (dib.GetBitCount() == 8) {
		BYTE** ptr1 = dib.GetPtr();
		BYTE** ptr2 = cpy.GetPtr();

		for (j = (int)(size / 2); j < h - (int)(size / 2); j++) {
			for (i = (int)(size / 2); i < w - (int)(size / 2); i++) {
				S = 0.0;
				for (n = -(int)(size / 2); n <= (int)(size / 2); n++) {
					for (m = -(int)(size / 2); m <= (int)(size / 2); m++) {
						if ((int)(ptr2[j + n][i + m]) == 255) S++;
					}
				}

				if (S == size * size) ptr1[j][i] = 255;
				else ptr1[j][i] = 0;

			}
		}
	}
	else if(dib.GetBitCount() == 24){
		AfxMessageBox(L"Check the Bit");
	}

}


void CMFCApplication3Doc::OnBinaryDilation(CDib& dib)
{
	// TODO: 여기에 구현 코드 추가.
	register int i, j, S, n, m;
	int size = 3;
	CDib cpy = dib;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	if (dib.GetBitCount() == 8) {
		BYTE** ptr1 = dib.GetPtr();
		BYTE** ptr2 = cpy.GetPtr();

		for (j = (int)(size / 2); j < h - (int)(size / 2); j++) {
			for (i = (int)(size / 2); i < w - (int)(size / 2); i++) {
				S = 0.0;
				for (n = -(int)(size / 2); n <= (int)(size / 2); n++) {
					for (m = -(int)(size / 2); m <= (int)(size / 2); m++) {
						if ((int)(ptr2[j + n][i + m]) == 255) S++;
					}
				}

				if (S > 0) ptr1[j][i] = 255;
				else ptr1[j][i] = 0;
			}
		}
	}
	else if(dib.GetBitCount() == 24){
		AfxMessageBox(L"Check the Bit");
	}
}


void CMFCApplication3Doc::OnNearest(CDib& dib,CDib& dib1)
{
	// TODO: 여기에 구현 코드 추가.
	
	int nwinput, nhinput;

	CHWDialog dlg;

	if (dlg.DoModal() == IDOK) {
		nwinput = dlg.m_NewWidth;
		nhinput = dlg.m_NewHeight;
	}

	DibResizeNearest(dib, nwinput, nhinput);
}

void CMFCApplication3Doc::DibResizeNearest(CDib& dib, int nw, int nh) {
	CDib cpy = dib;
	register int i, j;
	
	int w = cpy.GetWidth();
	int h = cpy.GetHeight();

	if (dib.GetBitCount() == 8) {
		dib.CreateGrayImage(nw,nh);

		BYTE** ptr1 = cpy.GetPtr();
		BYTE** ptr2 = dib.GetPtr();

		int x, y;
		
		for (j = 0; j < nh; j++) {
			for (i = 0; i < nw; i++) {
				x = (int)w * i / nw;
				y = (int)h * j / nh;

				ptr2[j][i] = ptr1[y][x];
			}
		}
	}
	else if (dib.GetBitCount() == 24) {
		dib.CreateRGBImage(nw, nh);

		RGBBYTE** ptr1 = cpy.GetRGBPtr();
		RGBBYTE** ptr2 = dib.GetRGBPtr();

		int x, y;

		for (j = 0; j < nh; j++) {
			for (i = 0; i < nw; i++) {
				x = (int)w * i / nw;
				y = (int)h * j / nh;

				ptr2[j][i].r = ptr1[y][x].r;
				ptr2[j][i].b = ptr1[y][x].b;
				ptr2[j][i].g = ptr1[y][x].g;
			}
		}
	}
}


void CMFCApplication3Doc::OnFrameSum(CDib& dib)
{
	// TODO: 여기에 구현 코드 추가.
	CFile File;;
	CFileDialog OpenDlg(TRUE);
	CDib dib1;
	CDib cpy = dib;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	if (OpenDlg.DoModal() == IDOK) {
		CString filename = OpenDlg.GetPathName();
		dib1.Load(filename);

		if (dib.GetHeight() != dib1.GetHeight() || dib.GetWidth() != dib1.GetWidth()) {
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}
	AfxNewImage(dib1);

	register int i, j;
	BYTE** ptr1 = dib1.GetPtr();
	BYTE** ptr2 = cpy.GetPtr();
	BYTE** ptr3 = dib.GetPtr();

	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			ptr3[j][i] = limit(ptr1[j][i] + ptr2[j][i]);
		}
	}
}


void CMFCApplication3Doc::OnBilinear(CDib& dib, CDib& dib1)
{
	// TODO: 여기에 구현 코드 추가.
	int nwinput, nhinput;

	CHWDialog dlg;

	if (dlg.DoModal() == IDOK) {
		nwinput = dlg.m_NewWidth;
		nhinput = dlg.m_NewHeight;
	}

	DibResizeBilinear(dib, nwinput, nhinput);

}

void CMFCApplication3Doc::DibResizeBilinear(CDib& dib, int nw, int nh) {
	CDib cpy = dib;
	register int i, j;

	int w = cpy.GetWidth();
	int h = cpy.GetHeight();

	if (dib.GetBitCount() == 8) {
		dib.CreateGrayImage(nw, nh);

		BYTE** ptr1 = cpy.GetPtr();
		BYTE** ptr2 = dib.GetPtr();

		int x1, y1, x2, y2;
		double rx, ry, p, q, temp;

		for (j = 0; j < nh; j++) {
			for (i = 0; i < nw; i++) {
				rx = (double)w * i / nw;
				ry = (double)h * j / nh;

				x1 = (int)rx;
				y1 = (int)ry;

				x2 = x1 + 1; if (x2 == w) x2 = w - 1;
				y2 = y1 + 1; if (y2 == h) y2 = h - 1;

				p = rx - x1;
				q = ry - y1;

				temp = (1.0 - p) * (1.0 - q) * ptr1[y1][x1] + p * (1.0 - q) * ptr1[y1][x2] +
					(1.0 - p) * q * ptr1[y2][x1] + p * q * ptr1[y2][x2];
				ptr2[j][i] = (BYTE)limit(temp);
 			}
		}
	}
	else if (dib.GetBitCount() == 24) {
		dib.CreateRGBImage(nw, nh);

		RGBBYTE** ptr1 = cpy.GetRGBPtr();
		RGBBYTE** ptr2 = dib.GetRGBPtr();

		int x1, y1, x2, y2;
		double rx, ry, p, q, temp1, temp2, temp3;

		for (j = 0; j < nh; j++) {
			for (i = 0; i < nw; i++) {
				rx = (double)w * i / nw;
				ry = (double)h * j / nh;

				x1 = (int)rx;
				y1 = (int)ry;

				x2 = x1 + 1; if (x2 == w) x2 = w - 1;
				y2 = y1 + 1; if (y2 == h) y2 = h - 1;

				p = rx - x1;
				q = ry - y1;

				temp1 = (1.0 - p) * (1.0 - q) * ptr1[y1][x1].r + p * (1.0 - q) * ptr1[y1][x2].r +
					(1.0 - p) * q * ptr1[y2][x1].r + p * q * ptr1[y2][x2].r;
				temp2 = (1.0 - p) * (1.0 - q) * ptr1[y1][x1].b + p * (1.0 - q) * ptr1[y1][x2].b +
					(1.0 - p) * q * ptr1[y2][x1].b + p * q * ptr1[y2][x2].b;
				temp3 = (1.0 - p) * (1.0 - q) * ptr1[y1][x1].g + p * (1.0 - q) * ptr1[y1][x2].g +
					(1.0 - p) * q * ptr1[y2][x1].g + p * q * ptr1[y2][x2].g;
				ptr2[j][i].r = (BYTE)limit(temp1);
				ptr2[j][i].b = (BYTE)limit(temp2);
				ptr2[j][i].g = (BYTE)limit(temp3);
			}
		}
	}
}


void CMFCApplication3Doc::OnCubic(CDib& dib, CDib& dib1)
{
	// TODO: 여기에 구현 코드 추가.
	int nwinput, nhinput;

	CHWDialog dlg;

	if (dlg.DoModal() == IDOK) {
		nwinput = dlg.m_NewWidth;
		nhinput = dlg.m_NewHeight;
	}

	DibResizeCubic(dib, nwinput, nhinput);
}

void CMFCApplication3Doc::DibResizeCubic(CDib& dib, int nw, int nh) {
	CDib cpy = dib;
	register int i, j;

	int w = cpy.GetWidth();
	int h = cpy.GetHeight();

	if (dib.GetBitCount() == 8) {
		dib.CreateGrayImage(nw, nh);

		BYTE** ptr1 = cpy.GetPtr();
		BYTE** ptr2 = dib.GetPtr();

		int x1, x2, x3, x4, y1, y2, y3, y4;
		double v1, v2, v3, v4, v;
		double rx, ry, p, q;

		for (j = 0; j < nh; j++) {
			for (i = 0; i < nw; i++) {
				rx = (double)w * i / nw;
				ry = (double)h * j / nh;

				x2 = (int)rx;
				x1 = x2 - 1; if (x1 < 0) x1 = 0;
				x3 = x2 + 1; if (x3 >= w) x3 = 2 - 1;
				x4 = x2 + 2; if (x4 >= w) x4 = w - 1;
				p = rx - 2;

				y2 = (int)ry;
				y1 = y2 - 1; if (y1 < 0)y1 = 0;
				y3 = y2 + 1; if (y3 >= h) y3 = h - 1;
				y4 = y2 + 2; if (y4 >= h) y4 = h - 1;
				q = ry - y2;

				v1 = cubic_interpolation(ptr1[y1][x1], ptr1[y1][x2], ptr1[y1][x3], ptr1[y1][x4], p);
				v2 = cubic_interpolation(ptr1[y2][x1], ptr1[y2][x2], ptr1[y2][x3], ptr1[y2][x4], p);
				v3 = cubic_interpolation(ptr1[y3][x1], ptr1[y3][x2], ptr1[y3][x3], ptr1[y3][x4], p);
				v4 = cubic_interpolation(ptr1[y4][x1], ptr1[y4][x2], ptr1[y4][x3], ptr1[y4][x4], p);

				v = cubic_interpolation(v1, v2,v3,v4,q);
				ptr2[j][i] = (BYTE)limit(v);
			}
		}
	}
	else if (dib.GetBitCount() == 24) {
		dib.CreateRGBImage(nw, nh);

		RGBBYTE** ptr1 = cpy.GetRGBPtr();
		RGBBYTE** ptr2 = dib.GetRGBPtr();

		int x1, x2, x3, x4, y1, y2, y3, y4;
		double v1_r, v2_r, v3_r, v4_r, v_r, v1_b, v2_b, v3_b, v4_b, v_b, v1_g, v2_g, v3_g, v4_g, v_g;
		double rx, ry, p, q;

		for (j = 0; j < nh; j++) {
			for (i = 0; i < nw; i++) {
				rx = (double)w * i / nw;
				ry = (double)h * j / nh;

				x2 = (int)rx;
				x1 = x2 - 1; if (x1 < 0) x1 = 0;
				x3 = x2 + 1; if (x3 >= w) x3 = 2 - 1;
				x4 = x2 + 2; if (x4 >= w) x4 = w - 1;
				p = rx - 2;

				y2 = (int)ry;
				y1 = y2 - 1; if (y1 < 0)y1 = 0;
				y3 = y2 + 1; if (y3 >= h) y3 = h - 1;
				y4 = y2 + 2; if (y4 >= h) y4 = h - 1;
				q = ry - y2;

				v1_r = cubic_interpolation(ptr1[y1][x1].r, ptr1[y1][x2].r, ptr1[y1][x3].r, ptr1[y1][x4].r, p);
				v1_g = cubic_interpolation(ptr1[y1][x1].g, ptr1[y1][x2].g, ptr1[y1][x3].g, ptr1[y1][x4].g, p);
				v1_b = cubic_interpolation(ptr1[y1][x1].b, ptr1[y1][x2].b, ptr1[y1][x3].b, ptr1[y1][x4].b, p);

				v2_r = cubic_interpolation(ptr1[y2][x1].r, ptr1[y2][x2].r, ptr1[y2][x3].r, ptr1[y2][x4].r, p);
				v2_g = cubic_interpolation(ptr1[y2][x1].g, ptr1[y2][x2].g, ptr1[y2][x3].g, ptr1[y2][x4].g, p);
				v2_b = cubic_interpolation(ptr1[y2][x1].b, ptr1[y2][x2].b, ptr1[y2][x3].b, ptr1[y2][x4].b, p);

				v3_r = cubic_interpolation(ptr1[y3][x1].r, ptr1[y3][x2].r, ptr1[y3][x3].r, ptr1[y3][x4].r, p);
				v3_g = cubic_interpolation(ptr1[y3][x1].g, ptr1[y3][x2].g, ptr1[y3][x3].g, ptr1[y3][x4].g, p);
				v3_b = cubic_interpolation(ptr1[y3][x1].b, ptr1[y3][x2].b, ptr1[y3][x3].b, ptr1[y3][x4].b, p);

				v4_r = cubic_interpolation(ptr1[y4][x1].r, ptr1[y4][x2].r, ptr1[y4][x3].r, ptr1[y4][x4].r, p);
				v4_g = cubic_interpolation(ptr1[y4][x1].g, ptr1[y4][x2].g, ptr1[y4][x3].g, ptr1[y4][x4].g, p);
				v4_b = cubic_interpolation(ptr1[y4][x1].b, ptr1[y4][x2].b, ptr1[y4][x3].b, ptr1[y4][x4].b, p);

				v_r = cubic_interpolation(v1_r, v2_r, v3_r, v4_r, q);
				v_g = cubic_interpolation(v1_g, v2_g, v3_g, v4_g, q);
				v_b = cubic_interpolation(v1_b, v2_b, v3_b, v4_b, q);

				ptr2[j][i].r = (BYTE)limit(v_r);
				ptr2[j][i].g = (BYTE)limit(v_g);
				ptr2[j][i].b = (BYTE)limit(v_b);
			}
		}
	}
}

double CMFCApplication3Doc::cubic_interpolation(double v1, double v2, double v3, double v4, double d) {
	double v, p1, p2, p3, p4;

	p1 = v2;
	p2 = -v1 + v3;
	p3 = 2 * (v1 - v2) + v3 - v4;
	p4 = -v1 + v2 - v3 + v4;
	v = p1 + d * (p2 + d * (p3 + d * p4));

	return v;
}


void CMFCApplication3Doc::OnTranslation(CDib& dib, CDib& dib1)
{
	// TODO: 여기에 구현 코드 추가.
	register int i, j;
	int newX, newY;

	int w = dib.GetWidth();
	int h = dib.GetHeight();
	double Value;

	CXYMove dlg;

	int xMove = 0, yMove = 0;

	if (dlg.DoModal() == IDOK) {
		xMove = dlg.m_xMove;
		yMove = dlg.m_yMove;
	}

	if (dib.GetBitCount() == 8) {
		BYTE** ptr1 = dib.GetPtr();
		BYTE** ptr2 = dib1.GetPtr();

		for (j = 0; j < h; j++) {
			for (i = 0; i < w; i++) {
				ptr2[j][i] = 0;
			}
		}

		for (j = 0; j < h; j++) {
			for (i = 0; i < w; i++) {
				if (j+yMove < 0 || j+yMove >= w || i+xMove < 0 || i+xMove >= h) {
					continue;
				}
				else {
					ptr2[j+yMove][i+xMove] = ptr1[j][i];
				}
			}
		}
	}
	else if (dib.GetBitCount() == 24) {
		RGBBYTE** ptr1 = dib.GetRGBPtr();
		RGBBYTE** ptr2 = dib1.GetRGBPtr();

		for (j = 0; j < h; j++) {
			for (i = 0; i < w; i++) {
				ptr2[j][i].r = 0;
				ptr2[j][i].b = 0;
				ptr2[j][i].g = 0;
			}
		}

		for (j = 0; j < h; j++) {
			for (i = 0; i < w; i++) {
				if (j + yMove < 0 || j + yMove >= w || i + xMove < 0 || i + xMove >= h) {
					continue;
				}
				else {
					ptr2[j + yMove][i + xMove].r = ptr1[j][i].r;
					ptr2[j + yMove][i + xMove].b = ptr1[j][i].b;
					ptr2[j + yMove][i + xMove].g = ptr1[j][i].g;
				}
			}
		}
	}
}


void CMFCApplication3Doc::OnFrameMinus(CDib& dib)
{
	// TODO: 여기에 구현 코드 추가.
	CFile File;;
	CFileDialog OpenDlg(TRUE);
	CDib dib1;
	CDib cpy = dib;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	if (OpenDlg.DoModal() == IDOK) {
		CString filename = OpenDlg.GetPathName();
		dib1.Load(filename);

		if (dib.GetHeight() != dib1.GetHeight() || dib.GetWidth() != dib1.GetWidth()) {
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}
	AfxNewImage(dib1);

	register int i, j;
	BYTE** ptr1 = dib1.GetPtr();
	BYTE** ptr2 = cpy.GetPtr();
	BYTE** ptr3 = dib.GetPtr();

	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			ptr3[j][i] = limit(ptr1[j][i] - ptr2[j][i]);
		}
	}
}


void CMFCApplication3Doc::OnGrayScaleErosion(CDib& dib)
{
	// TODO: 여기에 구현 코드 추가.
	register int i, j, S, n, m;
	int size = 3;
	CDib cpy = dib;

	int w = dib.GetWidth();
	int h = dib.GetHeight();
	int MIN = 10000;

	if (dib.GetBitCount() == 8) {
		BYTE** ptr1 = dib.GetPtr();
		BYTE** ptr2 = cpy.GetPtr();

		for (j = (int)(size / 2); j < h - (int)(size / 2); j++) {
			for (i = (int)(size / 2); i < w - (int)(size / 2); i++) {
				MIN = 10000;
				for (n = -(int)(size / 2); n <= (int)(size / 2); n++) {
					for (m = -(int)(size / 2); m <= (int)(size / 2); m++) {
						if (MIN > ptr2[j + n][i + m]) MIN = ptr2[j + n][i + m];
					}
				}

				ptr1[j][i] = MIN;
			}
		}
	}
	else if (dib.GetBitCount() == 24) {
		AfxMessageBox(L"Check the bit Size");
	}

}


void CMFCApplication3Doc::OnGrayScaleDiliation(CDib& dib)
{
	// TODO: 여기에 구현 코드 추가.
	register int i, j, S, n, m;
	int size = 3;
	CDib cpy = dib;

	int w = dib.GetWidth();
	int h = dib.GetHeight();
	int MAX = 0;

	if (dib.GetBitCount() == 8) {
		BYTE** ptr1 = dib.GetPtr();
		BYTE** ptr2 = cpy.GetPtr();

		for (j = (int)(size / 2); j < h - (int)(size / 2); j++) {
			for (i = (int)(size / 2); i < w - (int)(size / 2); i++) {
				MAX = 0;
				for (n = -(int)(size / 2); n <= (int)(size / 2); n++) {
					for (m = -(int)(size / 2); m <= (int)(size / 2); m++) {
						if (MAX < ptr2[j + n][i + m]) MAX = ptr2[j + n][i + m];
					}
				}

				ptr1[j][i] = MAX;
			}
		}
	}
	else if (dib.GetBitCount() == 24) {
		AfxMessageBox(L"Check the bit Size");
	}
}


void CMFCApplication3Doc::DibFrameProcessingDialogBased(CDib& dib)
{
	// TODO: 여기에 구현 코드 추가.
	CFile File;;
	CFileDialog OpenDlg(TRUE);
	CDib dib1;
	CDib cpy = dib;

	CFrameProcessingFileDialog dlg;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	if (OpenDlg.DoModal() == IDOK) {
		CString filename = OpenDlg.GetPathName();
		dib1.Load(filename);

		if (dib.GetHeight() != dib1.GetHeight() || dib.GetWidth() != dib1.GetWidth()) {
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}
	AfxNewImage(dib1);

	register int i, j;
	BYTE** ptr1 = dib1.GetPtr();
	BYTE** ptr2 = cpy.GetPtr();
	BYTE** ptr3 = dib.GetPtr();

	if (dlg.DoModal() == IDOK) {
		if (dlg.m_intFrameOperation == 0) {
			for (j = 0; j < h; j++) {
				for (i = 0; i < w; i++) {
					ptr3[j][i] = limit(ptr1[j][i] + ptr2[j][i]);
				}
			}
		}
		else if(dlg.m_intFrameOperation == 1){
			for (j = 0; j < h; j++) {
				for (i = 0; i < w; i++) {
					ptr3[j][i] = limit(ptr1[j][i] - ptr2[j][i]);
				}
			}
		}
	}
}


void CMFCApplication3Doc::OnMedianFilter(CDib& dib)
{
	// TODO: 여기에 구현 코드 추가.
	register int i, j, n, m;
	int size = 3;
	CDib cpy = dib;

	int w = dib.GetWidth();
	int h = dib.GetHeight();
	int arr[9] = { 0,0,0,0,0,0,0,0,0 };

	if (dib.GetBitCount() == 8) {
		BYTE** ptr1 = dib.GetPtr();
		BYTE** ptr2 = cpy.GetPtr();

		for (j = (int)(size / 2); j < h - (int)(size / 2); j++) {
			for (i = (int)(size / 2); i < w - (int)(size / 2); i++) {
				int k = 0;
				for (n = -(int)(size / 2); n <= (int)(size / 2); n++) {
					for (m = -(int)(size / 2); m <= (int)(size / 2); m++) {
						arr[k] = ptr2[j + n][i + m];
						k++;
					}
				}

				sort(arr);
				ptr1[j][i] = arr[5];
			}
		}
	}
	else if (dib.GetBitCount() == 24) {
		RGBBYTE** ptr1 = dib.GetRGBPtr();
		RGBBYTE** ptr2 = cpy.GetRGBPtr();

		int arr_r[9] = { 0,0,0,0,0,0,0,0,0 };
		int arr_b[9] = { 0,0,0,0,0,0,0,0,0 };
		int arr_g[9] = { 0,0,0,0,0,0,0,0,0 };
		for (j = (int)(size / 2); j < h - (int)(size / 2); j++) {
			for (i = (int)(size / 2); i < w - (int)(size / 2); i++) {
				int k = 0;
				for (n = -(int)(size / 2); n <= (int)(size / 2); n++) {
					for (m = -(int)(size / 2); m <= (int)(size / 2); m++) {
						arr_r[k] = ptr2[j + n][i + m].r;
						arr_b[k] = ptr2[j + n][i + m].b;
						arr_g[k] = ptr2[j + n][i + m].g;
						k++;
					}
				}

				sort(arr_r);
				sort(arr_b);
				sort(arr_g);
				ptr1[j][i].r = arr_r[5];
				ptr1[j][i].b = arr_b[5];
				ptr1[j][i].g = arr_g[5];
			}
		}
	}
}

void CMFCApplication3Doc::sort(int arr[]) {
	int temp;

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 8; j++) {
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void CMFCApplication3Doc::OnWarping(CDib& dib)
{
	// TODO: 여기에 구현 코드 추가.
	float numWaves = 5.;
	CDib cpy = dib;

	int w = cpy.GetWidth();
	int h = cpy.GetHeight();

	int i, j;
	float PI = 3.14159265358979;
	float waveAmplitude = 20.;
	float yToPhase = 2 * PI * numWaves / h;

	if (dib.GetBitCount() == 8) {
		BYTE** ptr = cpy.GetPtr();
		BYTE** ptr1 = dib.GetPtr();

		for (j = 0; j < h; j++) {
			for (i = 0; i < w; i++) {
				int newX, newY;
				newY = int(j + waveAmplitude * sin(j * yToPhase));
				newX = i;

				if (newX >= w || newX < 0 || newY >= h || newY < 0) {
					ptr1[newY][newX] = 0;
				}
				else {
					ptr1[newY][newX] = ptr[j][i];
				}
			}
		}
	}
	else if (dib.GetBitCount() == 24) {
		RGBBYTE** ptr = cpy.GetRGBPtr();
		RGBBYTE** ptr1 = dib.GetRGBPtr();

		for (j = 0; j < h; j++) {
			for (i = 0; i < w; i++) {
				int newX, newY;
				newY = int(j + waveAmplitude * sin(j * yToPhase));
				newX = i;

				if (newX >= w || newX < 0 || newY >= h || newY < 0) {
					ptr1[newY][newX].r = 0;
					ptr1[newY][newX].b = 0;
					ptr1[newY][newX].g = 0;
				}
				else {
					ptr1[newY][newX].r = ptr[j][i].r;
					ptr1[newY][newX].b = ptr[j][i].b;
					ptr1[newY][newX].g = ptr[j][i].g;
				}
			}
		}
	}
}

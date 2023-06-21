
// MFCApplication3View.cpp: CMFCApplication3View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication3.h"
#endif

#include "MFCApplication3Doc.h"
#include "MFCApplication3View.h"
#include "CDib.h"
#include "CHistogramDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication3View

IMPLEMENT_DYNCREATE(CMFCApplication3View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication3View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApplication3View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_ImageInverse, &CMFCApplication3View::OnImageInverse)
	ON_COMMAND(ID_group, &CMFCApplication3View::OnGroup)
	ON_COMMAND(ID_imgBlur, &CMFCApplication3View::OnImgblur)
	ON_COMMAND(ID_HISTOGRAM_DRAW, &CMFCApplication3View::OnHistogramDraw)
	ON_COMMAND(ID_EDGE_LAPLACIAN, &CMFCApplication3View::OnEdgeLaplacian)
	ON_COMMAND(ID_FILTERSIZECHANGE, &CMFCApplication3View::OnFiltersizechange)
	ON_COMMAND(ID_FILTER_TYPE, &CMFCApplication3View::OnFilterType)
	ON_COMMAND(ID_FILTER_SIZE_TYPE, &CMFCApplication3View::OnFilterSizeType)
	ON_COMMAND(ID_ImageRotate, &CMFCApplication3View::OnImagerotate)
	ON_COMMAND(ID_Erosion, &CMFCApplication3View::OnErosion)
	ON_COMMAND(ID_Dilation, &CMFCApplication3View::OnDilation)
	ON_COMMAND(ID_Nearest, &CMFCApplication3View::OnNearest)
	ON_COMMAND(ID_Frame_Sum, &CMFCApplication3View::OnFrameSum)
	ON_COMMAND(ID_Bilinear, &CMFCApplication3View::OnBilinear)
	ON_COMMAND(ID_Cubic, &CMFCApplication3View::OnCubic)
	ON_COMMAND(ID_Translation, &CMFCApplication3View::OnTranslation)
	ON_COMMAND(ID_FrameMinus, &CMFCApplication3View::OnFrameminus)
	ON_COMMAND(ID_GErosion, &CMFCApplication3View::OnGrayErosion)
	ON_COMMAND(ID_GDiliation, &CMFCApplication3View::OnGrayDiliation)
	ON_COMMAND(ID_FrameProcessing_DialogBase, &CMFCApplication3View::OnFrameprocessingDialogbase)
	ON_COMMAND(ID_Median_Filter, &CMFCApplication3View::OnMedianFilter)
	ON_COMMAND(ID_Warping, &CMFCApplication3View::OnWarping)
	ON_COMMAND(ID_Rotate, &CMFCApplication3View::OnRotate)
	ON_COMMAND(ID_BigProcess, &CMFCApplication3View::OnBigprocess)
	ON_COMMAND(ID_Final3, &CMFCApplication3View::OnFinal3)
	ON_COMMAND(ID_StyleWarping, &CMFCApplication3View::OnStylewarping)
END_MESSAGE_MAP()

// CMFCApplication3View 생성/소멸

CMFCApplication3View::CMFCApplication3View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCApplication3View::~CMFCApplication3View()
{
}

BOOL CMFCApplication3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCApplication3View 그리기

void CMFCApplication3View::OnDraw(CDC* pDC)
{
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	/*if (pDoc->m_Dib.IsValid()) {
		pDoc->m_Dib.Draw(pDC->m_hDC);
	}*/

	//위에 것을 사용해도 되지만, 버퍼를 정확히 지정해준 것
	if (pDoc->m_Dib.IsValid()) {
		int w = pDoc->m_Dib.GetWidth();
		int h = pDoc->m_Dib.GetHeight();
		pDoc->m_Dib.Draw(pDC->m_hDC, 0, 0, w, h);
	}

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMFCApplication3View 인쇄


void CMFCApplication3View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApplication3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCApplication3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCApplication3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMFCApplication3View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApplication3View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplication3View 진단

#ifdef _DEBUG
void CMFCApplication3View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication3Doc* CMFCApplication3View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication3Doc)));
	return (CMFCApplication3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication3View 메시지 처리기


void CMFCApplication3View::OnInitialUpdate()
{
	//CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	CMFCApplication3Doc* pDoc = GetDocument();
	if (pDoc->m_Dib.IsValid()) {
		sizeTotal.cx = pDoc->m_Dib.GetWidth();
		sizeTotal.cy = pDoc->m_Dib.GetHeight();
	}
	else {
		sizeTotal.cx = sizeTotal.cy = 100;
	}

	SetScrollSizes(MM_TEXT, sizeTotal);
	ResizeParentToFit(TRUE);

}

//영상반전
void CMFCApplication3View::OnImageInverse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	CDib dib = pDoc->m_Dib;

	pDoc->DibInverse(dib);
	AfxNewImage(dib);
}


//사용자 점처리 그룹
void CMFCApplication3View::OnGroup()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDib dib = pDoc->m_Dib;
	pDoc->Group(dib);
	AfxNewImage(dib);
}


//영역처리 blurring
void CMFCApplication3View::OnImgblur()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDib dib = pDoc->m_Dib, dib1 = pDoc->m_Dib;
	pDoc->DibImageBlur(dib, dib1);
	AfxNewImage(dib1);
}


void CMFCApplication3View::OnHistogramDraw()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();

	CHistogramDlg dlg;

	dlg.SetImage(pDoc->m_Dib);
	dlg.DoModal();
	
}


void CMFCApplication3View::OnEdgeLaplacian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDib dib = pDoc->m_Dib, dib1 = pDoc->m_Dib;
	pDoc->DibEdgeLaplacian(dib, dib1);

	AfxNewImage(dib1);
}


void CMFCApplication3View::OnFiltersizechange()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDib dib = pDoc->m_Dib, dib1 = pDoc->m_Dib;
	pDoc->DibAvgFilterSizeChange(dib, dib1);

	AfxNewImage(dib1);
}



void CMFCApplication3View::OnFilterType()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDib dib = pDoc->m_Dib, dib1 = pDoc->m_Dib;
	pDoc->OnBigProcess(dib, dib1);

	AfxNewImage(dib1);
}


void CMFCApplication3View::OnFilterSizeType()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDib dib = pDoc->m_Dib, dib1 = pDoc->m_Dib;
	pDoc->DibFilterAndSizeSelection(dib, dib1);

	AfxNewImage(dib1);
}


void CMFCApplication3View::OnImagerotate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDib dib = pDoc->m_Dib, dib1 = pDoc->m_Dib;
	pDoc->DibGeometricRotate(dib, dib1);

	AfxNewImage(dib1);
}


void CMFCApplication3View::OnErosion()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDib dib = pDoc->m_Dib;
	pDoc->OnBinaryErosion(dib);
	AfxNewImage(dib);
}


void CMFCApplication3View::OnDilation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDib dib = pDoc->m_Dib;
	pDoc->OnBinaryDilation(dib);
	AfxNewImage(dib);
}


void CMFCApplication3View::OnNearest()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDib dib = pDoc->m_Dib, dib1 = pDoc->m_Dib;
	pDoc->OnNearest(dib, dib1);
	AfxNewImage(dib);
}


void CMFCApplication3View::OnFrameSum()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDib dib = pDoc->m_Dib;
	pDoc->OnFrameSum(dib);
	AfxNewImage(dib);
}


void CMFCApplication3View::OnBilinear()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDib dib = pDoc->m_Dib, dib1 = pDoc->m_Dib;
	pDoc->OnBilinear(dib, dib1);
	AfxNewImage(dib);
}


void CMFCApplication3View::OnCubic()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDib dib = pDoc->m_Dib, dib1 = pDoc->m_Dib;
	pDoc->OnCubic(dib, dib1);
	AfxNewImage(dib);
}


void CMFCApplication3View::OnTranslation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDib dib = pDoc->m_Dib, dib1 = pDoc->m_Dib;
	pDoc->OnTranslation(dib, dib1);
	AfxNewImage(dib1);
}


void CMFCApplication3View::OnFrameminus()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDib dib = pDoc->m_Dib;
	pDoc->OnFrameMinus(dib);
	AfxNewImage(dib);
}


void CMFCApplication3View::OnGrayErosion()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDib dib = pDoc->m_Dib;
	pDoc->OnGrayScaleErosion(dib);
	AfxNewImage(dib);
}


void CMFCApplication3View::OnGrayDiliation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDib dib = pDoc->m_Dib;
	pDoc->OnGrayScaleDiliation(dib);
	AfxNewImage(dib);
}


void CMFCApplication3View::OnFrameprocessingDialogbase()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDib dib = pDoc->m_Dib;
	pDoc->DibFrameProcessingDialogBased(dib);
	AfxNewImage(dib);
}


void CMFCApplication3View::OnMedianFilter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDib dib = pDoc->m_Dib;
	pDoc->OnMedianFilter(dib);
	AfxNewImage(dib);
}


void CMFCApplication3View::OnWarping()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDib dib = pDoc->m_Dib;
	pDoc->OnWarping(dib);
	AfxNewImage(dib);
}


void CMFCApplication3View::OnRotate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDib dib = pDoc->m_Dib, dib1 = pDoc->m_Dib;
	pDoc->DibGeometricRotate1(dib, dib1);

	AfxNewImage(dib1);
}


void CMFCApplication3View::OnBigprocess()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDib dib = pDoc->m_Dib, dib1 = pDoc->m_Dib;
	pDoc->OnBigProcess(dib, dib1);

	AfxNewImage(dib);
}


void CMFCApplication3View::OnFinal3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDib dib = pDoc->m_Dib, dib1 = pDoc->m_Dib;
	pDoc->OnFinal3(dib, dib1);

	AfxNewImage(dib);
}


void CMFCApplication3View::OnStylewarping()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDib dib = pDoc->m_Dib, dib1 = pDoc->m_Dib;
	pDoc->OnStyleWarping(dib, dib1);

	AfxNewImage(dib);
}

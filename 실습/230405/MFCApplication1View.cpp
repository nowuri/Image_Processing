
// MFCApplication1View.cpp: CMFCApplication1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1View

IMPLEMENT_DYNCREATE(CMFCApplication1View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication1View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApplication1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
//	ON_COMMAND(ID_BinaryImage, &CMFCApplication1View::OnBasicProcessing)
ON_COMMAND(ID_BinaryImage, &CMFCApplication1View::OnBasicProcessing)
//ON_COMMAND(ID_Binary2, &CMFApplication1View::OnBinary2)
ON_COMMAND(ID_Binary2, &CMFCApplication1View::OnBinary2)
ON_COMMAND(ID_ImgInversion, &CMFCApplication1View::OnImginversion)
ON_COMMAND(ID_plusNum, &CMFCApplication1View::OnPlusNum)
ON_COMMAND(ID_minNum, &CMFCApplication1View::OnMinNum)
ON_COMMAND(ID_AndCal, &CMFCApplication1View::OnAndCal)
ON_COMMAND(ID_Gamma, &CMFCApplication1View::OnGamma)
ON_COMMAND(ID_ConEnhance, &CMFCApplication1View::OnConstantEnhance)
ON_COMMAND(ID_histoStretch, &CMFCApplication1View::OnHistostretch)
ON_COMMAND(ID_histogram, &CMFCApplication1View::OnHistogram)
ON_COMMAND(ID_histoEqual, &CMFCApplication1View::OnHistoequal)
ON_COMMAND(ID_HistoSpec, &CMFCApplication1View::OnHistospec)
//ON_COMMAND(ID_HistoFinal, &CMFCApplication1View::OnHistofinal)
ON_COMMAND(ID_HistoFinal, &CMFCApplication1View::OnHistofinal)
ON_COMMAND(ID_mid2, &CMFCApplication1View::OnMid2)
ON_COMMAND(ID_mid3, &CMFCApplication1View::OnMid3)
ON_COMMAND(ID_mid1, &CMFCApplication1View::OnMid1)
END_MESSAGE_MAP()

// CMFCApplication1View 생성/소멸

CMFCApplication1View::CMFCApplication1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCApplication1View::~CMFCApplication1View()
{
}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCApplication1View 그리기

void CMFCApplication1View::OnDraw(CDC* pDC)
{
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	int i, j;
	unsigned char R, G, B;

	//불러온 영상을 출력하는 함수
	for (i = 0; i < pDoc->m_height; i++) {
		for (j = 0; j < pDoc->m_width; j++) {
			R = G = B = pDoc->m_InputImage[i * pDoc->m_width + j];
			pDC->SetPixel(j + 5, i + 5, RGB(R, G, B));
		}
	}

	for (i = 0; i < pDoc->m_Re_height; i++) {
		for (j = 0; j < pDoc->m_Re_width; j++) {
			R = pDoc->m_OutputImage[i * pDoc->m_Re_width + j];
			G = B = R;
			pDC->SetPixel(j + pDoc->m_width + 10, i + 5, RGB(R, G, B));
		}
	}

	/*//입력 영상 히스토그램 출력 함수
	for (i = 0; i < pDoc->m_Re_height; i++) {
		for (j = 0; j < pDoc->m_Re_width; j++) {
			R = pDoc->m_InputHisto[i * pDoc->m_Re_width + j];
			G = B = R;
			pDC->SetPixel(j + pDoc->m_width + 10, i + 5, RGB(R, G, B));
		}
	}

	// 처리 영상 출력 함수
	for (i = 0; i < pDoc->m_Re_height; i++) {
		for (j = 0; j < pDoc->m_Re_width; j++) {
			R = pDoc->m_OutputImage[i * pDoc->m_Re_width + j];
			G = B = R;
			pDC->SetPixel(j + 5, i + pDoc->m_height + 30, RGB(R, G, B));
		}
	}

	// 처리 영상 히스토그램 출력 하수

	for (i = 0; i < pDoc->m_Re_height; i++) {
		for (j = 0; j < pDoc->m_Re_width; j++) {
			R = pDoc->m_OutputHisto[i * pDoc->m_Re_width + j];
			G = B = R;
			pDC->SetPixel(j + pDoc->m_width + 10, i + pDoc->m_height + 30, RGB(R, G, B));
		}
	}*/

}


// CMFCApplication1View 인쇄


void CMFCApplication1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMFCApplication1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApplication1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplication1View 진단

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View 메시지 처리기

void CMFCApplication1View::OnBasicProcessing()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication1Doc* pDoc = GetDocument(); //Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnBinarization(); //함수 호출, Doc 클래스에 미리 구현되어 있어야 함
	Invalidate(TRUE); // 화면 갱신
}


void CMFCApplication1View::OnBinary2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBinarization2();

	Invalidate(TRUE);
}


void CMFCApplication1View::OnImginversion()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 영상 반전 코드
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnImageInversion();
	Invalidate(TRUE);
}


void CMFCApplication1View::OnPlusNum()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//상수 값 덧셈 프로그램

	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnPlusNum();
	Invalidate(TRUE);
}

//상수 뺄셈 프로그램
void CMFCApplication1View::OnMinNum()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMinNum();
	Invalidate(TRUE);
}

// AND 프로그램
void CMFCApplication1View::OnAndCal()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAndCal();
	Invalidate(TRUE);
}

//감마 보정 프로그램
void CMFCApplication1View::OnGamma()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGamma();
	Invalidate(TRUE);

}

//영상 명암 대비 변환
void CMFCApplication1View::OnConstantEnhance()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnConEnhance();
	Invalidate(TRUE);
}

//히스토그램 스트래칭
void CMFCApplication1View::OnHistostretch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoStretch();
	Invalidate(TRUE);
}

//히스토그램 Plot
void CMFCApplication1View::OnHistogram()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistogram();
	Invalidate(TRUE);
}

//히스토그램 평활화
void CMFCApplication1View::OnHistoequal()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoEqual();
	Invalidate(TRUE);
}

//히스토그램 명세화
void CMFCApplication1View::OnHistospec()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoSpec();
	Invalidate(TRUE);
}


// 입력영상, 히스토그램, 출력영상, 출력영상 히스토그램 출력
void CMFCApplication1View::OnHistofinal()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoFinal();
	Invalidate(TRUE);
}


void CMFCApplication1View::OnMid2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoFinal();
	Invalidate(TRUE);
}




void CMFCApplication1View::OnMid3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnUnSharpMask();
	Invalidate(TRUE);
}


void CMFCApplication1View::OnMid1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMid1();
	Invalidate(TRUE);
}


// MFCApplication1View.h: CMFCApplication1View 클래스의 인터페이스
//

#pragma once


class CMFCApplication1View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFCApplication1View() noexcept;
	DECLARE_DYNCREATE(CMFCApplication1View)

// 특성입니다.
public:
	CMFCApplication1Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFCApplication1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBasicProcessing();
	afx_msg void OnBasicProcessing();
	void OnBinarization();
	afx_msg void OnBinary2();
	afx_msg void OnImginversion();
	afx_msg void OnPlusNum();
	afx_msg void OnMinNum();
	afx_msg void OnAndCal();
	afx_msg void OnGamma();
	afx_msg void OnConenhance();
	afx_msg void OnConstantEnhance();
	afx_msg void OnHistostretch();
	afx_msg void OnHistogram();
	afx_msg void OnHistoequal();
	afx_msg void OnHistospec();
	afx_msg void OnEmbossing();
	afx_msg void OnBlurring();
	afx_msg void OnSharp();
	afx_msg void OnGaussianSmooth();
	afx_msg void OnHpf();
	afx_msg void OnLpf();
};

#ifndef _DEBUG  // MFCApplication1View.cpp의 디버그 버전
inline CMFCApplication1Doc* CMFCApplication1View::GetDocument() const
   { return reinterpret_cast<CMFCApplication1Doc*>(m_pDocument); }
#endif


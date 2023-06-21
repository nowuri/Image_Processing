
// MFCApplication3Doc.h: CMFCApplication3Doc 클래스의 인터페이스
//

#include "CDib.h"
#pragma once


class CMFCApplication3Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMFCApplication3Doc() noexcept;
	DECLARE_DYNCREATE(CMFCApplication3Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CMFCApplication3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	// 이미지 개체
	CDib m_Dib;
	double** MaskAvg;
	int m_Re_height;
	int m_Re_width;
	int m_Re_size;
	int m_Combo = 0;


	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);

	void DibInverse(CDib& dib);
	void Group(CDib &dib);
	void DibImageBlur(CDib& dib, CDib& dib1);
	void OnMaskProcess(CDib& dib, CDib& dib1, double MaskAvg[3][3]);
	void OnMaskProcess2(CDib& dib, CDib& dib1, double MaskAvg[5][5]);
	void OnMaskProcess3(CDib& dib, CDib& dib1, double MaskAvg[7][7]);
	void DibEdgeLaplacian(CDib& dib, CDib& dib1);
	void DibAvgFilterSizeChange(CDib& dib, CDib& dib1);
	void OnMaskProcessSizeSelction(CDib& dib, CDib& dib1, double** MaskAvg);
	void DibConvFilterSelection(CDib& dib, CDib& dib1);
	void DibFilterAndSizeSelection(CDib& dib, CDib& dib1);
	void DibGeometricRotate(CDib& dib, CDib& dib1);
	void OnBinaryErosion(CDib &dib);
	void OnBinaryDilation(CDib& dib);
	void OnNearest(CDib& dib, CDib& dib1);
	void OnFrameSum(CDib& dib);
	void DibResizeNearest(CDib& dib, int nw, int nh);
	void OnBilinear(CDib& dib, CDib& dib1);
	void DibResizeBilinear(CDib& dib, int nw, int nh);
	void OnCubic(CDib& dib, CDib& dib1);
	void DibResizeCubic(CDib& dib, int nw, int nh);
	double cubic_interpolation(double v1, double v2, double v3, double v4, double d);
	void OnTranslation(CDib& dib, CDib& dib1);
	void OnFrameMinus(CDib& dib);
	void OnGrayScaleErosion(CDib& dib);
	void OnGrayScaleDiliation(CDib& dib);
	void DibFrameProcessingDialogBased(CDib& dib);
	void OnMedianFilter(CDib& dib);
	void sort(int arr[]);
	void OnWarping(CDib& dib);
	void DibGeometricRotate1(CDib& dib, CDib& dib1);
	void OnBigProcess(CDib& dib, CDib& dib1);
	void OnFinal3(CDib& dib, CDib& dib1);
	void OnStyleWarping(CDib& dib, CDib& dib1);
};

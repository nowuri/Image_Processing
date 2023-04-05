﻿
// MFCApplication1Doc.h: CMFCApplication1Doc 클래스의 인터페이스
//


#pragma once


class CMFCApplication1Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMFCApplication1Doc() noexcept;
	DECLARE_DYNCREATE(CMFCApplication1Doc)

// 특성입니다.
public:

// 작업입니다.
public:
	int m_width;  //영상의 가로 크기
	int m_height; //영상의 세로 크기
	int m_size;  //영상 데이터 전체 바이트 수
	 
	int m_Re_width;
	int m_Re_height;
	int m_Re_size;

	unsigned char* m_InputImage; //입력 영상 버퍼
	unsigned char* m_OutputImage; //출력 영상 버퍼

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
	virtual ~CMFCApplication1Doc();
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
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	void OnBinarization();
	void OnZoomIn();
	void OnBinarization2();
};


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
	unsigned char* m_OutputImage2;//LPF에 사용
	unsigned char* m_OutputImage3;
	double** m_tempImage; //영역처리에서 convolustion한 값을 2차원으로 저장한 것 
	unsigned char* m_InputHisto; // 주석처리 한 부분에 이용
	unsigned char* m_OutputHisto; // 주석처리 한 부분에 이용

	double m_HIST[256];
	double m_Sum_Of_HIST[256];
	unsigned char m_Scale_HIST[256];

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
	// 영상 반전 코드
	void OnImageInversion();
	// //상수 덧셈 프로그램
	void OnPlusNum();
	// 상수 뺄셈 프로그램
	void OnMinNum();
	// AND 프로그램
	void OnAndCal();
	// 감마 보정 프로그램
	void OnGamma();
	// 영상 명암 대비 변환
	void OnConEnhance();
	// 히스토그램 스트레칭
	void OnHistoStretch();
	// 히스토그램 plot
	void OnHistogram();
	// 히스토그램 평활화
	void OnHistoEqual();
	// 히스토그램 명세화
	void OnHistoSpec();
	// 영역처리 엠보싱 필터
	void OnEmbossing();
	double** Image2DMen(int height, int width);
	double** OnMaskProcess(unsigned char* Target, double Mask[3][3]);
	// 영역처리 중 버리는 것
	double** OnMaskProcess2(unsigned char* Target, double Mask[3][3]);
	void OnBlurring();
	// Sharpening 필터
	void OnSharpening();
	// 가우시안 스무딩 필터
	void OnGaussianSmooth();
	// High Frequency Band-Pass Filter
	void OnHPF();
	// Low Frequency Band Pass Filter
	void OnLPF();
};

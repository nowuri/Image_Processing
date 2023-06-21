
// MFCApplication1Doc.cpp: CMFCApplication1Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"

#include <propkey.h>
#include "CDialogWoomR.h"
#include "CDialogConstant.h"
#include "CDialogMask.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCApplication1Doc

IMPLEMENT_DYNCREATE(CMFCApplication1Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFCApplication1Doc, CDocument)
END_MESSAGE_MAP()


// CMFCApplication1Doc 생성/소멸

CMFCApplication1Doc::CMFCApplication1Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMFCApplication1Doc::~CMFCApplication1Doc()
{
}

BOOL CMFCApplication1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMFCApplication1Doc serialization

void CMFCApplication1Doc::Serialize(CArchive& ar)
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
void CMFCApplication1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CMFCApplication1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCApplication1Doc::SetSearchContent(const CString& value)
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

// CMFCApplication1Doc 진단

#ifdef _DEBUG
void CMFCApplication1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCApplication1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCApplication1Doc 명령


BOOL CMFCApplication1Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CFile File;
	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);
	if (File.GetLength() == 32 * 32) {
		m_height = 32;
		m_width = 32;
	}
	else if (File.GetLength() == 64 * 64) {
		m_height = 64;
		m_width = 64;
	}
	else if (File.GetLength() == 128 * 128) {
		m_height = 128;
		m_width = 128;
	}
	else if (File.GetLength() == 256 * 256) {
		m_height = 256;
		m_width = 256;
	}
	else if (File.GetLength() == 512 * 512) {
		m_height = 512;
		m_width = 512;
	}
	else if (File.GetLength() == 640 * 480) {
		m_height = 480;
		m_width = 640;
	}
	else if (File.GetLength() == 176 * 144) {
		m_height = 144;
		m_width = 176;
	}
	else if (File.GetLength() == 176 * 216) {
		m_height = 176;
		m_width = 216;
	}
	else {
		AfxMessageBox(L"Not Support Image Size", MB_OK | MB_ICONEXCLAMATION);
	}

	m_size = m_width * m_height;

	m_InputImage = new unsigned char[m_size];

	for (int i = 0; i < m_size; i++)
		m_InputImage[i] = 255;

	File.Read(m_InputImage, m_size);
	File.Close();

	return TRUE;
}


void CMFCApplication1Doc::OnBinarization()
{
	// TODO: 여기에 구현 코드 추가.
	int i, value;
	m_size = m_height * m_width;
	m_Re_size = m_size;
	m_Re_height = m_height;
	m_Re_width = m_width;

	//inputImage에 넣으면 원본 이미지가 사라짐 => 새로 m_OutImage변수를 새로 만들어줌
	m_OutputImage = new unsigned char[m_size];

	//기본 이진화, 128을 넘어가면, 128 그렇지 않으면 50으로 모든 pixel 값을 변경
	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];
		
		if (value > 128)
			m_OutputImage[i] = (unsigned char)128;
		else
			m_OutputImage[i] = (unsigned char)50;
	}
}


void CMFCApplication1Doc::OnZoomIn()
{
	// TODO: 여기에 구현 코드 추가.
	CString msg;
	CDialogWoomR dlg;

	if (dlg.DoModal() == IDOK) {
		msg.Format(L"Input number = %2d", dlg.m_ZoomIn);
		AfxMessageBox(msg);
	}
}


void CMFCApplication1Doc::OnBinarization2()
{
	// TODO: 여기에 구현 코드 추가.
	CDialogWoomR dlg;
	
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] >= dlg.m_ZoomIn)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = 0;
		}
	}

}


// 영상 반전 코드
void CMFCApplication1Doc::OnImageInversion()
{
	// TODO: 여기에 구현 코드 추가.

	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	for (i = 0; i < m_size; i++) {
		m_OutputImage[i] = 255 - m_InputImage[i];
	}

	/*
	* for (i=0; i<m_size;i++){
	*	value = (int) m_InputImage[i];
	*	m_OutputImage[i] = (unsigned char)(255-value);
	* }
	*/
}


// //상수 덧셈 프로그램
void CMFCApplication1Doc::OnPlusNum()
{
	// TODO: 여기에 구현 코드 추가.
	CDialogWoomR dlg;

	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] + dlg.m_ZoomIn >= 255)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] + dlg.m_ZoomIn);
		}
	}
}


// 상수 뺄셈 프로그램
void CMFCApplication1Doc::OnMinNum()
{
	// TODO: 여기에 구현 코드 추가.
	CDialogWoomR dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] - dlg.m_ZoomIn < 0)
				m_OutputImage[i] = 0;
			else
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] - dlg.m_ZoomIn);
		}
	}
}


// AND 프로그램
void CMFCApplication1Doc::OnAndCal()
{
	// TODO: 여기에 구현 코드 추가.
	CDialogWoomR dlg;
	int i;
	
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_height * m_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if ((m_InputImage[i] & (unsigned char)dlg.m_ZoomIn) >= 255)
				m_OutputImage[i] = 255;
			else if ((m_InputImage[i] & (unsigned char)dlg.m_ZoomIn) < 0)
				m_OutputImage[i] = 0;
			else
				m_OutputImage[i] = (m_InputImage[i] & (unsigned char)dlg.m_ZoomIn);
		}
	}
}


// 감마 보정 프로그램
void CMFCApplication1Doc::OnGamma()
{
	// TODO: 여기에 구현 코드 추가.
	CDialogWoomR dlg;
	int i;
	double temp;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			temp = pow(m_InputImage[i], 1 / dlg.m_ZoomIn);
			if (temp < 0)
				m_OutputImage[i] = 0;
			else if (temp > 255)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = (unsigned char)temp;
		}
	}
}


// 영상 명암 대비 변환
void CMFCApplication1Doc::OnConEnhance()
{
	// TODO: 여기에 구현 코드 추가.
	CDialogConstant dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] <= dlg.m_Input1)
				m_OutputImage[i] = (unsigned char)m_InputImage[i] * 0.5;
			else if (m_InputImage[i] > dlg.m_Input1 && m_InputImage[i] < dlg.m_Input2) {
				int a = (0.5 * dlg.m_Input2 - 0.5 * dlg.m_Input1) / (dlg.m_Input2 - dlg.m_Input1);
				m_OutputImage[i] = a * (m_InputImage[i] - dlg.m_Input1) + 0.5 * dlg.m_Input1;
			}
			else
				m_OutputImage[i] = (unsigned char)m_InputImage[i] * 0.5;

		}
	}
}


// 히스토그램 스트레칭
void CMFCApplication1Doc::OnHistoStretch()
{
	// TODO: 여기에 구현 코드 추가.
	int i;
	unsigned char LOW, HIGH, MAX, MIN;
	
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	LOW = 0;
	HIGH = 255;
	
	//MIN, MAX 값 초기화
	MIN = m_InputImage[0];
	MAX = m_InputImage[0];

	//입력 영상의 최소값, 최대값 찾기
	for (i = 0; i < m_size; i++) {
		if (MIN > m_InputImage[i])
			MIN = m_InputImage[i];
	}

	for (i = 0; i < m_size; i++) {
		if (MAX < m_InputImage[i])
			MAX = m_InputImage[i];
	}

	//출력영상 버퍼 할당
	m_OutputImage = new unsigned char[m_Re_size];

	//히스토그램 스트레칭
	for (i = 0; i < m_size; i++) {
		m_OutputImage[i] = (unsigned char)((m_InputImage[i] - MIN) * HIGH / (MAX- MIN));
	}
}


// 히스토그램 plot
void CMFCApplication1Doc::OnHistogram()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, value;
	unsigned char LOW, HIGH;
	double MAX, MIN, DIF;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	LOW = 0;
	HIGH = 255;

	//초기화
	for (i = 0; i < 256; i++) {
		m_HIST[i] = LOW;
	}

	//빈도수 조사: 히스토그램 형성
	for (i = 0; i < 256; i++) {
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}

	//초기화
	MAX = m_HIST[0];
	MIN = m_HIST[0];

	//정규화
	for (i = 0; i < 256; i++) {
		if (MAX < m_HIST[i])
			MAX = m_HIST[i];
	}

	for (i = 0; i < 256; i++) {
		if (MIN > m_HIST[i])
			MIN = m_HIST[i];
	}

	DIF = MAX - MIN;

	//정규화된 히스토그램
	for (i = 0; i < 256; i++) {
		m_Scale_HIST[i] = (unsigned char)((m_HIST[i] - MIN) * HIGH / DIF);
	}

	//처리 영상 출력을 위한 버퍼 및 초기화
	//(256*20): 밝기밴드 + 빈공간을 위한 버퍼임
	m_OutputImage = new unsigned char[m_Re_size + (256 * 20)];

	for (i = 0; i < m_Re_size; i++) {
		m_OutputImage[i] = 255;
	}

	//정규화된 히스토그램의 값은 출력 배열에 검은 점으로 표현
	for (i = 0; i < 256; i++) { //색의 개수 0~255 총 256개
		for (j = 0; j < m_Scale_HIST[i]; j++) //0부터 각 밝기 값의 개수까지 ex. 밝기 0의 픽셀이 5개면 0부터 4까지
			//색칠할 영역 표기
			// width * height인데 높이의 경우, 원점이 왼쪽 상단이기 때문에 칠하는 시작점을 아래로 두기 위함
			m_OutputImage[m_Re_width * (m_Re_height - j - 1) + i] = 0; 
	}

	//히스토그램과 밝기 밴드 사이 공간 마련
	for (i = m_Re_height; i < m_Re_height + 5; i++) { //세로
		for (j = 0; j < 256; j++) { //가로
			m_OutputImage[m_Re_height * i + j] = 255;
		}
	}

	//밝기 밴드 그리기
	for (i = m_Re_height + 5; i < m_Re_height + 20; i++) { //세로
		for (j = 0; j < 256; j++) { // 가로
			m_OutputImage[m_Re_height * i + j] = j;
		}
	}

	m_Re_height = m_Re_height + 20;
	m_Re_size = m_Re_height * m_Re_width;
}


// 히스토그램 평활화
void CMFCApplication1Doc::OnHistoEqual()
{
	// TODO: 여기에 구현 코드 추가.
	int i, value;
	unsigned char LOW, HIGH, Temp;
	double SUM = 0.0;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	LOW = 0;
	HIGH = 255;

	//초기화
	for (i = 0; i < 256; i++) {
		m_HIST[i] = LOW;
	}

	//빈도 수 조사: 히스토그램 생성
	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}

	//누적 히스토그램 생성
	for (i = 0; i < 256; i++) {
		SUM += m_HIST[i];
		m_Sum_Of_HIST[i] = SUM;
	}

	m_OutputImage = new unsigned char[m_Re_size];

	//입력 영상을 평활화된 영상으로 출력
	//히스토그램을 만드는게 아니라 영상을 출력한다는 점 생각 => Temp를 m_InputImage[i]로 두는 이유!
	for (i = 0; i < m_size; i++) {
		Temp = m_InputImage[i];
		m_OutputImage[i] = (unsigned char)(m_Sum_Of_HIST[Temp] * HIGH / m_size); 
	}
}


// 히스토그램 명세화
void CMFCApplication1Doc::OnHistoSpec()
{
	// TODO: 여기에 구현 코드 추가.
	int i, value, Dvalue, top, bottom, DADD;
	unsigned char* m_DTEMP, m_Sum_Of_ScHIST[256], m_TABLE[256];
	unsigned char LOW, HIGH, Temp, * m_Org_Temp;
	double m_DHIST[256], m_Sum_Of_DHIST[256], SUM = 0.0, DSUM = 0.0;
	double DMAX, DMIN;

	top = 255;
	bottom = top - 1;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];
	m_Org_Temp = new unsigned char[m_size];
	m_DTEMP = new unsigned char[m_size];

	CFile File;
	CFileDialog OpenDlg(TRUE);

	//원하는 히스토그램이 있는 영상을 입력받음
	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);

		if (File.GetLength() == (unsigned char)m_size) {
			File.Read(m_DTEMP, m_size);
			File.Close();
		}
		else {
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}

	LOW = 0;
	HIGH = 255;

	//초기화
	for (i = 0; i < 256; i++) {
		m_HIST[i] = LOW;
		m_DHIST[i] = LOW;
		m_TABLE[i] = LOW;
	}

	//빈도수 조사
	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];
		m_HIST[value]++;
		Dvalue = (int)m_DTEMP[i];
		m_DHIST[Dvalue]++;
	}

	//누적 히스토그램 조사
	for (i = 0; i < 256; i++) {
		SUM += m_HIST[i];
		m_Sum_Of_HIST[i] = SUM;
		DSUM + m_DHIST[i];
		m_Sum_Of_DHIST[i] = DSUM;
	}

	//원본 영상 평활화
	for (i = 0; i < m_size; i++) {
		Temp = m_InputImage[i];
		m_Org_Temp[i] = (unsigned char)(m_Sum_Of_HIST[Temp] * HIGH / m_size);
	}

	//누적 히스토그램에서 최소값과 최대값 지정
	DMIN = m_Sum_Of_DHIST[0];
	DMAX = m_Sum_Of_DHIST[255];

	//원하는 영상 평활화
	for (i = 0; i < 256; i++) {
		m_Sum_Of_ScHIST[i] = (unsigned char)((m_Sum_Of_DHIST[i] - DMIN) * HIGH / (DMAX - DMIN));
	}

	//룩업 테이블을 이용한 명세화
	for (;;) {
		for (i = m_Sum_Of_ScHIST[bottom]; i <= m_Sum_Of_ScHIST[top]; i++) {
			m_TABLE[i] = top;
		}
		top = bottom;
		bottom = bottom - 1;

		if (bottom < -1)
			break;
	}

	//역변환 함수를 이용해 평활화한 입력 영상을 원하는 히스토그램으로 만들어줌
	for (i = 0; i < m_size; i++) {
		DADD = (int)m_Org_Temp[i];
		m_OutputImage[i] = m_TABLE[DADD];
	}
}


// 입력영상, 히스토그램, 출력영상, 출력영상 히스토그램 출력
void CMFCApplication1Doc::OnHistoFinal()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, value;
	unsigned char LOW, HIGH;
	double MAX, MIN, DIF;

	m_Re_height = 256;
	m_Re_width = 256;
	m_Re_size = m_Re_height * m_Re_width;

	LOW = 256;
	HIGH = 255;

	for (i = 0; i < 256; i++)
		m_HIST[i] = LOW;
	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}

	MAX = m_HIST[0];
	MIN = m_HIST[0];

	for (i = 0; i < 256; i++) {
		if (m_HIST[i] > MAX)
			MAX = m_HIST[i];
	}

	for (i = 0; i < 256; i++) {
		if (m_HIST[i] < MIN)
			MIN = m_HIST[i];
	}

	DIF = MAX - MIN;

	for (i = 0; i < 256; i++)
		m_Scale_HIST[i] = (unsigned char)((m_HIST[i] - MIN) * HIGH / DIF);

	m_InputHisto = new unsigned char[m_Re_size + (256*20)];

	for (i = 0; i < m_Re_size; i++) {
		m_InputHisto[i] = 255;
	}

	for (i = 0; i < 256; i++) {
		for (j = 0; j < m_Scale_HIST[i]; j++) {
			m_InputHisto[m_Re_width * (m_Re_height - j - 1) + i] = 0;
		}
	}

	for (i = m_Re_height; i < m_Re_height + 5; i++) {
		for (j = 0; j < 256; j++) {
			m_InputHisto[m_Re_height * i + j] = 255;
		}

		for (i = m_Re_height + 5; i < m_Re_height + 20; i++) {
			for (j = 0; j < 256; j++) {
				m_InputHisto[m_Re_height * i + j] = j;
			}
		}

		m_Re_height = m_Re_height + 20;
		m_Re_size = m_Re_height * m_Re_width;

		//히스토그램 평활화
		unsigned char LOW2, HIGH2, Temp;
		double SUM = 0.0;
		int m_Re_height2;
		int m_Re_width2;
		int m_Re_size2;
		double m_HIST2[256];

		m_Re_height2 = m_height;
		m_Re_width2 = m_width;
		m_Re_size2 = m_Re_height2 * m_Re_width2;

		LOW2 = 0;
		HIGH2 = 255;

		for (i = 0; i < 256; i++)
			m_HIST2[i] = LOW;

		for (i = 0; i < m_size; i++) {
			value = (int)m_InputImage[i];
			m_HIST2[value]++;
		}

		for (i = 0; i < 256; i++) {
			SUM += m_HIST2[i];
			m_Sum_Of_HIST[i] = SUM;
		}

		m_OutputImage = new unsigned char[m_Re_size2];

		for (i = 0; i < m_size; i++) {
			Temp = m_InputImage[i];
			m_OutputImage[i] = (unsigned char)(m_Sum_Of_HIST[Temp] * HIGH2 / m_size);
		}
	}

	// 평활화 된 영상 히스토그램
	double m_HIST3[256];
	unsigned char LOW3, HIGH3;
	double MAX3, MIN3, DIF3;
	int m_Re_height3;
	int m_Re_width3;
	int m_Re_size3;
	unsigned char m_Scale_HIST3[256];

	m_Re_height3 = 256;
	m_Re_width3 = 256;
	m_Re_size3 = m_Re_height3 * m_Re_width3;

	LOW3 = 0;
	HIGH3 = 255;

	for (i = 0; i < 256; i++)
		m_HIST3[i] = LOW;

	for (i = 0; i < m_size; i++) {
		value = (int)m_OutputImage[i];
		m_HIST3[value]++;
	}

	MAX3 = m_HIST[0];
	MIN3 = m_HIST[0];

	for (i = 0; i < 256; i++) {
		if (m_HIST3[i] > MAX3)
			MAX3 = m_HIST3[i];
	}

	for (i = 0; i < 256; i++) {
		if (m_HIST[i] < MIN3)
			MIN3 = m_HIST[i];
	}

	DIF3 = MAX3 - MIN3;

	for (i = 0; i < 256; i++)
		m_Scale_HIST3[i] = (unsigned char)((m_HIST3[i] - MIN3) * HIGH3 / DIF3);

	m_OutputHisto = new unsigned char[m_Re_size3 + (256 * 20)];
	
	for (i = 0; i < m_Re_size3; i++)
		m_OutputHisto[i] = 255;

	for (i = 0; i < 256; i++) {
		for (j = 0; j < m_Scale_HIST3[i]; j++) {
			m_OutputHisto[m_Re_width3 * (m_Re_height3 - j - 1) + i] = 0;
		}
	}

	for (i = m_Re_height3; i < m_Re_height3 + 5; i++) {
		for (j = 0; j < 256; j++)
			m_OutputHisto[m_Re_height3 * i + j] = 255;
	}

	for (i = m_Re_height3 + 5; i < m_Re_height3 + 20; i++) {
		for (j = 0; j < 256; j++) {
			m_OutputHisto[m_Re_height3 * i + j] = j;
		}
	}

	m_Re_height3 = m_Re_height3 + 20;
	m_Re_size3 = m_Re_height3 * m_Re_width3;
}

double** CMFCApplication1Doc::OnMaskProcess(unsigned char* Target, double Mask[3][3]) {
	int i, j, m, n;
	double** tempInputImage, ** tempOutputImage, S = 0.0;

	tempInputImage = Image2DMen(m_height + 2, m_width + 2);
	tempOutputImage = Image2DMen(m_height, m_width);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			tempInputImage[i + 1][j + 1] = (double)Target[i * m_width + j];
		}
	}

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					S += Mask[n][m] * tempInputImage[i + n][j + m];
				}
			}
			tempOutputImage[i][j] = S;
			S = 0.0;
		}
	}

	return tempOutputImage;
}

double** CMFCApplication1Doc::Image2DMen(int height, int width) {
	double** temp;
	int i, j;

	temp = new double* [height];
	for (i = 0; i < height; i++) {
		temp[i] = new double[width];
	}

	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			temp[i][j] = 0.0;
		}
	}

	return temp;

}

void CMFCApplication1Doc::OnUnSharpMask()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, alpha;
	double LpfSharpMask[3][3] = { {1. / 9.,1. / 9.,1. / 9.},{1. / 9.,1. / 9.,1. / 9.}, {1. / 9.,1. / 9.,1. / 9.} };

	CDialogWoomR dlg;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		alpha = (int)dlg.m_ZoomIn;
		// 대화상자를 이용하여 상수를 입력받는다.
	}
	m_tempImage = OnMaskProcess(m_InputImage, LpfSharpMask);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (alpha * m_InputImage[i * m_width + j]) - (unsigned char)m_tempImage[i][j];
		}
	}

	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j]= (unsigned char)m_tempImage[i][j];
		}
	}
}


void CMFCApplication1Doc::OnMid1()
{
	// TODO: 여기에 구현 코드 추가.
	CDialogConstant dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (dlg.m_Input1 == 1 && dlg.m_Input2 == 245) {
				m_OutputImage[i] = (unsigned char)m_InputImage[i];
			}
			else {
				if (m_InputImage[i] <= dlg.m_Input1)
					m_OutputImage[i] = (unsigned char)m_InputImage[i] * 0.5;
				else if (m_InputImage[i] > dlg.m_Input1 && m_InputImage[i] < dlg.m_Input2) {
					// a = 기울기
					int a = (0.5 * dlg.m_Input2 - 0.5 * dlg.m_Input1) / (dlg.m_Input2 - dlg.m_Input1);
					m_OutputImage[i] = a * (m_InputImage[i] - dlg.m_Input1) + 0.5 * dlg.m_Input1;
				}
				else
					m_OutputImage[i] = (unsigned char)m_InputImage[i] * 0.5;
			}
		}
	}
}

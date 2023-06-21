// ImageRotate.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication3.h"
#include "afxdialogex.h"
#include "ImageRotate.h"


// ImageRotate 대화 상자

IMPLEMENT_DYNAMIC(ImageRotate, CDialogEx)

ImageRotate::ImageRotate(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, m_ImageDegree(0)
{

}

ImageRotate::~ImageRotate()
{
}

void ImageRotate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Degree, m_ImageDegree);
}


BEGIN_MESSAGE_MAP(ImageRotate, CDialogEx)
END_MESSAGE_MAP()


// ImageRotate 메시지 처리기


// GrayScaleColorImageProcessingDoc.cpp: CGrayScaleColorImageProcessingDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GrayScaleColorImageProcessing.h"
#endif

#include "GrayScaleColorImageProcessingDoc.h"

#include <propkey.h>
#include "ConstantDlg.h"
#include <algorithm>
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGrayScaleColorImageProcessingDoc

IMPLEMENT_DYNCREATE(CGrayScaleColorImageProcessingDoc, CDocument)

BEGIN_MESSAGE_MAP(CGrayScaleColorImageProcessingDoc, CDocument)
END_MESSAGE_MAP()


// CGrayScaleColorImageProcessingDoc 생성/소멸

CGrayScaleColorImageProcessingDoc::CGrayScaleColorImageProcessingDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CGrayScaleColorImageProcessingDoc::~CGrayScaleColorImageProcessingDoc()
{
}

BOOL CGrayScaleColorImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CGrayScaleColorImageProcessingDoc serialization

void CGrayScaleColorImageProcessingDoc::Serialize(CArchive& ar)
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
void CGrayScaleColorImageProcessingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CGrayScaleColorImageProcessingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CGrayScaleColorImageProcessingDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGrayScaleColorImageProcessingDoc 진단

#ifdef _DEBUG
void CGrayScaleColorImageProcessingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGrayScaleColorImageProcessingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGrayScaleColorImageProcessingDoc 명령


unsigned char** CGrayScaleColorImageProcessingDoc::OnMalloc2D(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	unsigned char** retMemoy;
	retMemoy = new unsigned char* [h];
	for (int i = 0; i < h; i++)
		retMemoy[i] = new unsigned char[w];
	return retMemoy;
}

template <typename T>
void CGrayScaleColorImageProcessingDoc::OnFree2D(T** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		delete memory[i];
	delete[] memory;
}


double** CGrayScaleColorImageProcessingDoc::OnMallocDouble2D(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	double** retMemoy;
	retMemoy = new double* [h];
	for (int i = 0; i < h; i++)
		retMemoy[i] = new double[w];
	return retMemoy;
}


void CGrayScaleColorImageProcessingDoc::OnFreeOutImage()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImageR, m_outH);
	OnFree2D(m_outImageG, m_outH);
	OnFree2D(m_outImageB, m_outH);
	m_outImageR = m_outImageG = m_outImageB = NULL;
	m_outH = m_outW = 0;
}


BOOL CGrayScaleColorImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// 기존 메모리 해제
	if (m_inImageR != NULL)
	{
		OnFreeOutImage();
	}
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	// 선택된 파일 열기
	CImage image;
	image.Load(lpszPathName);
	// (중요!) 입력 영상 크기 알아내기
	m_inH = image.GetHeight();
	m_inW = image.GetWidth();
	// 메모리 할당
	m_inImageR = OnMalloc2D(m_inH, m_inW);
	m_inImageG = OnMalloc2D(m_inH, m_inW);
	m_inImageB = OnMalloc2D(m_inH, m_inW);
	// CImage 객체값 --> 메모리
	COLORREF px;
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
		{
			px = image.GetPixel(k, i);
			m_inImageR[i][k] = GetRValue(px);
			m_inImageG[i][k] = GetGValue(px);
			m_inImageB[i][k] = GetBValue(px);
		}
	return TRUE;
}


void CGrayScaleColorImageProcessingDoc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	// 기존 메모리 모두 해제, 관련값 초기화
	OnFree2D(m_inImageR, m_inH);
	OnFree2D(m_inImageG, m_inH);
	OnFree2D(m_inImageB, m_inH);
	m_inImageR = m_inImageG = m_inImageB = NULL;
	m_inH = m_inW = 0;

	OnFree2D(m_outImageR, m_outH);
	OnFree2D(m_outImageG, m_outH);
	OnFree2D(m_outImageB, m_outH);
	m_outImageR = m_outImageG = m_outImageB = NULL;
	m_outH = m_outW = 0;
	CDocument::OnCloseDocument();
}


BOOL CGrayScaleColorImageProcessingDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (m_outImageR == NULL)
		return FALSE;
	CImage image;
	image.Create(m_outW, m_outH, 32);

	unsigned char R, G, B;
	COLORREF px;
	for (int i = 0; i < m_outW; i++)
		for (int k = 0; k < m_outH; k++)
		{
			R = m_outImageR[k][i];
			G = m_outImageG[k][i];
			B = m_outImageB[k][i];
			px = RGB(R, G, B);
			image.SetPixel(i, k, px);
		}
	image.Save(lpszPathName, Gdiplus::ImageFormatPNG);
	MessageBox(NULL, L"저장", L"성공", NULL);
	return TRUE;
}


bool CGrayScaleColorImageProcessingDoc::OnOpenOtherDocument()
{
	// TODO: 여기에 구현 코드 추가.
	// 선택된 파일 열기
	CFile File;
	CFileDialog OpenDlg(FALSE, NULL, NULL, OFN_HIDEREADONLY);
	if (OpenDlg.DoModal() == IDOK)
	{
		// 선택된 파일 열기
		CImage image;
		image.Load(OpenDlg.GetPathName());
		// 입력 이미지의 높이와 폭을 결정
		// 기존 메모리 모두 해제, 관련값 초기화
		OnFree2D(m_otherImageR, m_otherH);
		OnFree2D(m_otherImageG, m_otherH);
		OnFree2D(m_otherImageB, m_otherH);
		m_otherImageR, m_otherImageG, m_otherImageB = NULL;
		m_otherH = m_otherW = 0;
		// (중요) 입력 이미지의 높이와 폭을 결정 + 메모리 할당
		m_otherH = image.GetHeight();
		m_otherW = image.GetWidth();
		m_otherImageR = OnMalloc2D(m_otherH, m_otherW);
		m_otherImageG = OnMalloc2D(m_otherH, m_otherW);
		m_otherImageB = OnMalloc2D(m_otherH, m_otherW);
		// CImage 객체값 --> 메모리
		COLORREF px;
		for (int i = 0; i < m_otherH; i++)
			for (int k = 0; k < m_otherW; k++)
			{
				px = image.GetPixel(k, i);
				m_otherImageR[i][k] = GetRValue(px);
				m_otherImageG[i][k] = GetGValue(px);
				m_otherImageB[i][k] = GetBValue(px);
			}
		return TRUE;
	}
	return FALSE;
}


void CGrayScaleColorImageProcessingDoc::OnEqualImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// *** 영상처리 알고리즘 ***
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			m_outImageR[i][k] = m_inImageR[i][k];
			m_outImageG[i][k] = m_inImageG[i][k];
			m_outImageB[i][k] = m_inImageB[i][k];
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnGrayScaleImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// *** 영상처리 알고리즘 ***
	double avg;
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = (unsigned char)avg;
		}
	}
}

void CGrayScaleColorImageProcessingDoc::OnAddImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		// 기존 메모리 해제
		OnFreeOutImage();
		// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 메모리 할당	
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// *** 영상처리 알고리즘 ***
		int value = (int)dlg.m_constant;
		for (int i = 0; i < m_inH; i++)
		{
			for (int k = 0; k < m_inW; k++)
			{
				if (m_inImageR[i][k] + value > 255)
					m_outImageR[i][k] = 255;
				else if (m_inImageR[i][k] + value < 0)
					m_outImageR[i][k] = 0;
				else
					m_outImageR[i][k] = m_inImageR[i][k] + value;

				if (m_inImageG[i][k] + value > 255)
					m_outImageG[i][k] = 255;
				else if (m_inImageG[i][k] + value < 0)
					m_outImageG[i][k] = 0;
				else
					m_outImageG[i][k] = m_inImageG[i][k] + value;

				if (m_inImageB[i][k] + value > 255)
					m_outImageB[i][k] = 255;
				else if (m_inImageB[i][k] + value < 0)
					m_outImageB[i][k] = 0;
				else
					m_outImageB[i][k] = m_inImageB[i][k] + value;
			}
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnReverseImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// *** 영상처리 알고리즘 ***
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			m_outImageR[i][k] = 255 - m_inImageR[i][k];
			m_outImageG[i][k] = 255 - m_inImageG[i][k];
			m_outImageB[i][k] = 255 - m_inImageB[i][k];
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnBwImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// *** 영상처리 알고리즘 ***
	double avg;
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			if (avg > 127)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = 0;

			if (avg > 127)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = 0;

			if (avg > 127)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = 0;
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnBwAvgImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	//	평균값 계산
	int hapR = 0;
	int hapG = 0;
	int hapB = 0;
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			hapR += m_inImageR[i][k];
			hapG += m_inImageG[i][k];
			hapB += m_inImageB[i][k];
		}
	}
	int avrR = hapR / (m_outH * m_outW);
	int avrG = hapG / (m_outH * m_outW);
	int avrB = hapB / (m_outH * m_outW);
	int avr = (avrR + avrG + avrB) / 3;
	// *** 영상처리 알고리즘 ***
	double avg;
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			if (avg > avr)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = 0;

			if (avg > avr)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = 0;

			if (avg > avr)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = 0;
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnBwMedImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	//	평균값 계산
	// 2차원 배열 값을 1차원 배열로 전환
	unsigned char* aryR;
	unsigned char* aryG;
	unsigned char* aryB;
	aryR = new unsigned char[m_inH * m_inW];
	aryG = new unsigned char[m_inH * m_inW];
	aryB = new unsigned char[m_inH * m_inW];
	int cnt = 0;
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			aryR[cnt] = m_inImageR[i][k];
			aryG[cnt] = m_inImageG[i][k];
			aryB[cnt] = m_inImageB[i][k];
			cnt++;
		}
	}
	// 1차원 배열을 오름차 순으로 정렬 후 배열의 중앙 값 계산
	std::sort(aryR, aryR + (m_inH * m_inW));
	std::sort(aryG, aryG + (m_inH * m_inW));
	std::sort(aryB, aryB + (m_inH * m_inW));
	int midR = aryR[(m_inH * m_inW) / 2];
	int midG = aryG[(m_inH * m_inW) / 2];
	int midB = aryB[(m_inH * m_inW) / 2];
	int mid = (midR + midG + midB) / 3;
	// *** 영상처리 알고리즘 ***
	double avg;
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			if (avg > mid)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = 0;

			if (avg > mid)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = 0;

			if (avg > mid)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = 0;
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnGammaImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		// 기존 메모리 해제
		OnFreeOutImage();
		// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 메모리 할당	
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// *** 영상처리 알고리즘 ***
		double value = (double)dlg.m_constant;
		for (int i = 0; i < m_inH; i++)
		{
			for (int k = 0; k < m_inW; k++)
			{
				double mR = (double)m_inImageR[i][k];
				double mG = (double)m_inImageG[i][k];
				double mB = (double)m_inImageB[i][k];
				m_outImageR[i][k] = (unsigned char)(255.0 * pow((mR / 255.0), value));
				m_outImageG[i][k] = (unsigned char)(255.0 * pow((mG / 255.0), value));
				m_outImageB[i][k] = (unsigned char)(255.0 * pow((mB / 255.0), value));
			}
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnParaCapImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// *** 영상처리 알고리즘 ***
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			double mR = (double)m_inImageR[i][k];
			double mG = (double)m_inImageG[i][k];
			double mB = (double)m_inImageB[i][k];
			m_outImageR[i][k] = 255.0 - 255.0 * pow((mR / 128.0 - 1.0), 2);
			m_outImageG[i][k] = 255.0 - 255.0 * pow((mG / 128.0 - 1.0), 2);
			m_outImageB[i][k] = 255.0 - 255.0 * pow((mB / 128.0 - 1.0), 2);
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnParaCupImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// *** 영상처리 알고리즘 ***
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			double mR = (double)m_inImageR[i][k];
			double mG = (double)m_inImageG[i][k];
			double mB = (double)m_inImageB[i][k];
			m_outImageR[i][k] = 255.0 * pow((mR / 128.0 - 1.0), 2);
			m_outImageG[i][k] = 255.0 * pow((mG / 128.0 - 1.0), 2);
			m_outImageB[i][k] = 255.0 * pow((mB / 128.0 - 1.0), 2);
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnAndImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 논리 연산을 하기 위한 이미지 가져오기
	if (OnOpenOtherDocument() == FALSE)
	{
		AfxMessageBox(L"이미지를 불러오지 못했습니다.");
		return;
	}
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// *** 영상처리 알고리즘 ***
	for (int i = 0; i < m_outH; i++)
	{
		for (int k = 0; k < m_outW; k++)
		{
			if (m_inH > i && m_inW > k && m_otherH > i && m_otherW > k)
			{
				m_outImageR[i][k] = m_inImageR[i][k] & m_otherImageR[i][k];
				m_outImageG[i][k] = m_inImageG[i][k] & m_otherImageG[i][k];
				m_outImageB[i][k] = m_inImageB[i][k] & m_otherImageB[i][k];
			}
			else
			{
				m_outImageR[i][k] = m_inImageR[i][k];
				m_outImageG[i][k] = m_inImageG[i][k];
				m_outImageB[i][k] = m_inImageB[i][k];
			}
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnOrImage()
{
	// TODO: 여기에 구현 코드 추가.
		// 기존 메모리 해제
	OnFreeOutImage();
	// 논리 연산을 하기 위한 이미지 가져오기
	if (OnOpenOtherDocument() == FALSE)
	{
		AfxMessageBox(L"이미지를 불러오지 못했습니다.");
		return;
	}
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// *** 영상처리 알고리즘 ***
	for (int i = 0; i < m_outH; i++)
	{
		for (int k = 0; k < m_outW; k++)
		{
			if (m_inH > i && m_inW > k && m_otherH > i && m_otherW > k)
			{
				m_outImageR[i][k] = m_inImageR[i][k] | m_otherImageR[i][k];
				m_outImageG[i][k] = m_inImageG[i][k] | m_otherImageG[i][k];
				m_outImageB[i][k] = m_inImageB[i][k] | m_otherImageB[i][k];
			}
			else
			{
				m_outImageR[i][k] = m_inImageR[i][k];
				m_outImageG[i][k] = m_inImageG[i][k];
				m_outImageB[i][k] = m_inImageB[i][k];
			}
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnXorImage()
{
	// TODO: 여기에 구현 코드 추가.
		// 기존 메모리 해제
	OnFreeOutImage();
	// 논리 연산을 하기 위한 이미지 가져오기
	if (OnOpenOtherDocument() == FALSE)
	{
		AfxMessageBox(L"이미지를 불러오지 못했습니다.");
		return;
	}
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// *** 영상처리 알고리즘 ***
	for (int i = 0; i < m_outH; i++)
	{
		for (int k = 0; k < m_outW; k++)
		{
			if (m_inH > i && m_inW > k && m_otherH > i && m_otherW > k)
			{
				m_outImageR[i][k] = m_inImageR[i][k] ^ m_otherImageR[i][k];
				m_outImageG[i][k] = m_inImageG[i][k] ^ m_otherImageG[i][k];
				m_outImageB[i][k] = m_inImageB[i][k] ^ m_otherImageB[i][k];
			}
			else
			{
				m_outImageR[i][k] = m_inImageR[i][k];
				m_outImageG[i][k] = m_inImageG[i][k];
				m_outImageB[i][k] = m_inImageB[i][k];
			}
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnZoomOutImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		// 배율 결정
		int scale = (int)dlg.m_constant;
		if (scale <= 0)
		{
			AfxMessageBox(L"0보다 큰 값을 넣으셔야 합니다.");
			return;
		}
		// 기존 메모리 해제
		OnFreeOutImage();
		// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
		m_outH = (int)round((m_inH / scale + 0.5));
		m_outW = (int)round((m_inW / scale + 0.5));
		// 메모리 할당	
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// *** 영상처리 알고리즘 ***
		for (int i = 0; i < m_inH; i++)
		{
			for (int k = 0; k < m_inW; k++)
			{
				m_outImageR[(int)(i / scale)][(int)(k / scale)] = m_inImageR[i][k];
				m_outImageG[(int)(i / scale)][(int)(k / scale)] = m_inImageG[i][k];
				m_outImageB[(int)(i / scale)][(int)(k / scale)] = m_inImageB[i][k];
			}
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnZoomOutAvgImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		// 배율 결정
		int scale = (int)dlg.m_constant;
		if (scale <= 0)
		{
			AfxMessageBox(L"0보다 큰 값을 넣으셔야 합니다.");
			return;
		}
		// 기존 메모리 해제
		OnFreeOutImage();
		// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
		m_outH = (int)round((m_inH / scale + 0.5));
		m_outW = (int)round((m_inW / scale + 0.5));
		// 메모리 할당	
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// *** 영상처리 알고리즘 ***
		for (int i = 0; i < m_inH; i++)
		{
			for (int k = 0; k < m_inW; k++)
			{
				int hapR = 0;
				int hapG = 0;
				int hapB = 0;
				int cnt = 0;
				for (int n = -1; n < 2; n++)
				{
					for (int m = -1; m < 2; m++)
					{
						if (0 <= i + n && i + n < m_inH && 0 <= k + m && k + m < m_inW)
						{
							hapR += (int)m_inImageR[i + n][k + m];
							hapG += (int)m_inImageG[i + n][k + m];
							hapB += (int)m_inImageB[i + n][k + m];
							cnt++;
						}
					}
				}
				double ValueR = (double)(hapR / cnt);
				double ValueG = (double)(hapG / cnt);
				double ValueB = (double)(hapB / cnt);
				m_outImageR[(int)(i / scale)][(int)(k / scale)] = (unsigned char)ValueR;
				m_outImageG[(int)(i / scale)][(int)(k / scale)] = (unsigned char)ValueG;
				m_outImageB[(int)(i / scale)][(int)(k / scale)] = (unsigned char)ValueB;
			}
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnZoomOutMedMage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		// 배율 결정
		int scale = (int)dlg.m_constant;
		if (scale <= 0)
		{
			AfxMessageBox(L"0보다 큰 값을 넣으셔야 합니다.");
			return;
		}
		// 기존 메모리 해제
		OnFreeOutImage();
		// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
		m_outH = (int)round((m_inH / scale + 0.5));
		m_outW = (int)round((m_inW / scale + 0.5));
		// 메모리 할당	
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// *** 영상처리 알고리즘 ***
		for (int i = 0; i < m_inH; i++)
		{
			for (int k = 0; k < m_inW; k++)
			{
				// 2차원 배열 값을 담을 1차원 배열 생성
				unsigned char* aryR;
				unsigned char* aryG;
				unsigned char* aryB;
				aryR = new unsigned char[3 * 3];
				aryG = new unsigned char[3 * 3];
				aryB = new unsigned char[3 * 3];
				int cnt = 0;
				for (int n = -1; n < 2; n++)
				{
					for (int m = -1; m < 2; m++)
					{
						if (0 <= i + n && i + n < m_inH && 0 <= k + m && k + m < m_inW)
						{
							aryR[cnt] = m_inImageR[i + n][k + m];
							aryG[cnt] = m_inImageG[i + n][k + m];
							aryB[cnt] = m_inImageB[i + n][k + m];
							cnt++;
						}
					}
				}
				std::sort(aryR, aryR + cnt);
				std::sort(aryG, aryG + cnt);
				std::sort(aryB, aryB + cnt);
				int midR = aryR[cnt / 2];
				int midG = aryG[cnt / 2];
				int midB = aryB[cnt / 2];
				m_outImageR[(int)(i / scale)][(int)(k / scale)] = (unsigned char)midR;
				m_outImageG[(int)(i / scale)][(int)(k / scale)] = (unsigned char)midG;
				m_outImageB[(int)(i / scale)][(int)(k / scale)] = (unsigned char)midB;
				free(aryR);
				free(aryG);
				free(aryB);
			}
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnZoomInImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		// 배율 결정
		int scale = (int)dlg.m_constant;
		if (scale <= 0)
		{
			AfxMessageBox(L"0보다 큰 값을 넣으셔야 합니다.");
			return;
		}
		// 기존 메모리 해제
		OnFreeOutImage();
		// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
		m_outH = (int)(m_inH * scale);
		m_outW = (int)(m_inW * scale);
		// 메모리 할당	
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// *** 영상처리 알고리즘 ***
		for (int i = 0; i < m_inH; i++)
		{
			for (int k = 0; k < m_inW; k++)
			{
				m_outImageR[(int)(i * scale)][(int)(k * scale)] = m_inImageR[i][k];
				m_outImageG[(int)(i * scale)][(int)(k * scale)] = m_inImageG[i][k];
				m_outImageB[(int)(i * scale)][(int)(k * scale)] = m_inImageB[i][k];
			}
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnZoomIn2Image()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		// 배율 결정
		int scale = (int)dlg.m_constant;
		if (scale <= 0)
		{
			AfxMessageBox(L"0보다 큰 값을 넣으셔야 합니다.");
			return;
		}
		// 기존 메모리 해제
		OnFreeOutImage();
		// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
		m_outH = (int)(m_inH * scale);
		m_outW = (int)(m_inW * scale);
		// 메모리 할당	
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// *** 영상처리 알고리즘 ***
		for (int i = 0; i < m_outH; i++)
		{
			for (int k = 0; k < m_outW; k++)
			{
				m_outImageR[i][k] = m_inImageR[(int)(i / scale)][(int)(k / scale)];
				m_outImageG[i][k] = m_inImageG[(int)(i / scale)][(int)(k / scale)];
				m_outImageB[i][k] = m_inImageB[(int)(i / scale)][(int)(k / scale)];
			}
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnZoomIn3Image()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		// 배율 결정
		int scale = (int)dlg.m_constant;
		if (scale <= 0)
		{
			AfxMessageBox(L"0보다 큰 값을 넣으셔야 합니다.");
			return;
		}
		// 기존 메모리 해제
		OnFreeOutImage();
		// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
		m_outH = (int)(m_inH * scale);
		m_outW = (int)(m_inW * scale);
		// 메모리 할당	
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// *** 영상처리 알고리즘 ***
		for (int i = 0; i < m_outH; i++)
		{
			for (int k = 0; k < m_outW; k++)
			{
				double rH = i / scale;
				double rW = k / scale;
				int iH = (int)floor(rH);
				int iW = (int)floor(rW);
				// 0 ~ 1 사이의 값을 가지는 실수형 변수
				double sH = rH - iH;
				double sW = rW - iW;
				if (iH < 0 || iH >= (m_inH - 1) || iW < 0 || iW >= (m_inW - 1))
				{
					m_outImageR[i][k] = 255;
					m_outImageG[i][k] = 255;
					m_outImageB[i][k] = 255;
				}
				else
				{
					double cR1 = (double)m_inImageR[iH][iW];
					double cR2 = (double)m_inImageR[iH][iW + 1];
					double cR3 = (double)m_inImageR[iH + 1][iW + 1];
					double cR4 = (double)m_inImageR[iH + 1][iW];

					unsigned char valueR = (unsigned char)(
						cR1 * (1 - sH) * (1 - sW)
						+ cR2 * sW * (1 - sH)
						+ cR3 * sW * sH
						+ cR4 * (1 - sW) * sH);
					m_outImageR[i][k] = valueR;

					double cG1 = (double)m_inImageG[iH][iW];
					double cG2 = (double)m_inImageG[iH][iW + 1];
					double cG3 = (double)m_inImageG[iH + 1][iW + 1];
					double cG4 = (double)m_inImageG[iH + 1][iW];

					unsigned char valueG = (unsigned char)(
						cG1 * (1 - sH) * (1 - sW)
						+ cG2 * sW * (1 - sH)
						+ cG3 * sW * sH
						+ cG4 * (1 - sW) * sH);
					m_outImageG[i][k] = valueG;

					double cB1 = (double)m_inImageB[iH][iW];
					double cB2 = (double)m_inImageB[iH][iW + 1];
					double cB3 = (double)m_inImageB[iH + 1][iW + 1];
					double cB4 = (double)m_inImageB[iH + 1][iW];

					unsigned char valueB = (unsigned char)(
						cB1 * (1 - sH) * (1 - sW)
						+ cB2 * sW * (1 - sH)
						+ cB3 * sW * sH
						+ cB4 * (1 - sW) * sH);
					m_outImageB[i][k] = valueB;
				}
			}
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnRotateImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		// 기존 메모리 해제
		OnFreeOutImage();
		// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 메모리 할당	
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// 입력 배열 --> 출력 배열
		int degree = (int)dlg.m_constant;
		double radian = -(degree * 3.141592 / 180);
		// *** 영상처리 알고리즘 ***
		for (int i = 0; i < m_inH; i++)
		{
			for (int k = 0; k < m_inW; k++)
			{
				int xs = i;
				int ys = k;
				int xd = (int)(cos(radian) * xs - sin(radian) * ys);
				int yd = (int)(sin(radian) * xs + cos(radian) * ys);
				if (0 <= xd && xd < m_outH && 0 <= yd && yd < m_outW)
				{
					m_outImageR[xd][yd] = m_inImageR[xs][ys];
					m_outImageG[xd][yd] = m_inImageG[xs][ys];
					m_outImageB[xd][yd] = m_inImageB[xs][ys];
				}
			}
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnRotate2Image()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		// 기존 메모리 해제
		OnFreeOutImage();
		// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 메모리 할당	
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// 입력 배열 --> 출력 배열
		int degree = (int)dlg.m_constant;
		double radian = -(degree * 3.141592 / 180);
		// 입력 전 이미지 중앙 좌표
		int cx = m_inH / 2;
		int cy = m_inW / 2;
		// *** 영상처리 알고리즘 ***
		for (int i = 0; i < m_inH; i++)
		{
			for (int k = 0; k < m_inW; k++)
			{
				int xd = i;
				int yd = k;
				int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
				int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));
				xs += cx;
				ys += cy;
				if ((0 <= xs && xs < m_inH) && (0 <= ys && ys < m_inW))
				{
					m_outImageR[xd][yd] = m_inImageR[xs][ys];
					m_outImageG[xd][yd] = m_inImageG[xs][ys];
					m_outImageB[xd][yd] = m_inImageB[xs][ys];
				}
				else
				{
					m_outImageR[xd][yd] = 255;
					m_outImageG[xd][yd] = 255;
					m_outImageB[xd][yd] = 255;
				}
			}
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnRotate3Image()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		// 입력 배열 --> 출력 배열
		int degree = (int)dlg.m_constant;
		double radian = -(degree * 3.141592 / 180);
		double radian90 = -((90 - degree) * 3.141592 / 180);
		// 기존 메모리 해제
		OnFreeOutImage();
		// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
		m_outH = (int)(m_inH * cos(radian90) + m_inW * cos(radian));
		m_outW = (int)(m_inW * cos(radian) + m_inH * cos(radian90));
		// 메모리 할당	
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// 입력 전 이미지 중앙 좌표
		int cx = m_inH / 2;
		int cy = m_inW / 2;
		// 입력 후 이미지 중앙 좌표
		int cx2 = m_outH / 2;
		int cy2 = m_outW / 2;
		// *** 영상처리 알고리즘 ***
		for (int i = 0; i < m_outH; i++)
		{
			for (int k = 0; k < m_outW; k++)
			{
				int xd = i;
				int yd = k;
				int xs = (int)(cos(radian) * (xd - cx2) + sin(radian) * (yd - cy2));
				int ys = (int)(-sin(radian) * (xd - cx2) + cos(radian) * (yd - cy2));
				xs += cx;
				ys += cy;
				if ((0 <= xs && xs < m_inH) && (0 <= ys && ys < m_inW))
				{
					m_outImageR[xd][yd] = m_inImageR[xs][ys];
					m_outImageG[xd][yd] = m_inImageG[xs][ys];
					m_outImageB[xd][yd] = m_inImageB[xs][ys];
				}
				else
				{
					m_outImageR[xd][yd] = 255;
					m_outImageG[xd][yd] = 255;
					m_outImageB[xd][yd] = 255;
				}
			}
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnMoveImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg1;
	CConstantDlg dlg2;
	if (dlg1.DoModal() == IDOK && dlg2.DoModal() == IDOK)
	{
		// 기존 메모리 해제
		OnFreeOutImage();
		// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 메모리 할당	
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// *** 영상처리 알고리즘 ***
		int valueW = (int)dlg1.m_constant;
		int valueH = (int)dlg2.m_constant;
		for (int i = 0; i < m_inH; i++)
		{
			for (int k = 0; k < m_inW; k++)
			{
				if (0 <= i - valueH && i - valueH < m_outH && 0 <= k - valueW && k - valueW < m_outW)
				{
					m_outImageR[i][k] = m_inImageR[i - valueH][k - valueW];
					m_outImageG[i][k] = m_inImageG[i - valueH][k - valueW];
					m_outImageB[i][k] = m_inImageB[i - valueH][k - valueW];
				}
			}
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnMirrorUdImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// *** 영상처리 알고리즘 ***
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			m_outImageR[i][k] = m_inImageR[m_inH - i - 1][k];
			m_outImageG[i][k] = m_inImageG[m_inH - i - 1][k];
			m_outImageB[i][k] = m_inImageB[m_inH - i - 1][k];
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnMirrorLrImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// *** 영상처리 알고리즘 ***
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			m_outImageR[i][k] = m_inImageR[i][m_inW - k - 1];
			m_outImageG[i][k] = m_inImageG[i][m_inW - k - 1];
			m_outImageB[i][k] = m_inImageB[i][m_inW - k - 1];
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnHistoStretchImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// High, Low 값 할당
	// new = (old - low) / (high - low) * 255.0
	int highR = m_inImageR[0][0], lowR = m_inImageR[0][0];
	int highG = m_inImageG[0][0], lowG = m_inImageG[0][0];
	int highB = m_inImageB[0][0], lowB = m_inImageB[0][0];
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			if (m_inImageR[i][k] < lowR)
				lowR = m_inImageR[i][k];
			if (m_inImageR[i][k] > highR)
				highR = m_inImageR[i][k];
			if (m_inImageG[i][k] < lowG)
				lowG = m_inImageG[i][k];
			if (m_inImageG[i][k] > highG)
				highG = m_inImageG[i][k];
			if (m_inImageB[i][k] < lowB)
				lowB = m_inImageB[i][k];
			if (m_inImageB[i][k] > highB)
				highB = m_inImageB[i][k];
		}
	}
	// *** 영상처리 알고리즘 ***
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			int m_oldR = m_inImageR[i][k];
			int m_newR = (int)((double)(m_oldR - lowR) / (double)(highR - lowR) * 255.0);
			int m_oldG = m_inImageG[i][k];
			int m_newG = (int)((double)(m_oldG - lowG) / (double)(highG - lowG) * 255.0);
			int m_oldB = m_inImageB[i][k];
			int m_newB = (int)((double)(m_oldB - lowB) / (double)(highB - lowB) * 255.0);
			if (m_newR > 255)
				m_newR = 255;
			if (m_newR < 0)
				m_newR = 0;
			m_outImageR[i][k] = m_newR;
			if (m_newG > 255)
				m_newG = 255;
			if (m_newG < 0)
				m_newG = 0;
			m_outImageG[i][k] = m_newG;
			if (m_newB > 255)
				m_newB = 255;
			if (m_newB < 0)
				m_newB = 0;
			m_outImageB[i][k] = m_newB;
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnEndInImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// High, Low 값 할당
	// new = (old - low) / (high - low) * 255.0
	int highR = m_inImageR[0][0], lowR = m_inImageR[0][0];
	int highG = m_inImageG[0][0], lowG = m_inImageG[0][0];
	int highB = m_inImageB[0][0], lowB = m_inImageB[0][0];
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			if (m_inImageR[i][k] < lowR)
				lowR = m_inImageR[i][k];
			if (m_inImageR[i][k] > highR)
				highR = m_inImageR[i][k];
			if (m_inImageG[i][k] < lowG)
				lowG = m_inImageG[i][k];
			if (m_inImageG[i][k] > highG)
				highG = m_inImageG[i][k];
			if (m_inImageB[i][k] < lowB)
				lowB = m_inImageB[i][k];
			if (m_inImageB[i][k] > highB)
				highB = m_inImageB[i][k];
		}
	}
	highR -= 50; lowR += 50;
	highG -= 50; lowG += 50;
	highB -= 50; lowB += 50;
	// *** 영상처리 알고리즘 ***
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			int m_oldR = m_inImageR[i][k];
			int m_newR = (int)((double)(m_oldR - lowR) / (double)(highR - lowR) * 255.0);
			int m_oldG = m_inImageG[i][k];
			int m_newG = (int)((double)(m_oldG - lowG) / (double)(highG - lowG) * 255.0);
			int m_oldB = m_inImageB[i][k];
			int m_newB = (int)((double)(m_oldB - lowB) / (double)(highB - lowB) * 255.0);
			if (m_newR > 255)
				m_newR = 255;
			if (m_newR < 0)
				m_newR = 0;
			m_outImageR[i][k] = m_newR;
			if (m_newG > 255)
				m_newG = 255;
			if (m_newG < 0)
				m_newG = 0;
			m_outImageG[i][k] = m_newG;
			if (m_newB > 255)
				m_newB = 255;
			if (m_newB < 0)
				m_newB = 0;
			m_outImageB[i][k] = m_newB;
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnHistoEqualImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// 1단계 : 반도수 세기(=히스토그렘)
	int histoR[256] = { 0, };
	int histoG[256] = { 0, };
	int histoB[256] = { 0, };
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
		{
			histoR[m_inImageR[i][k]]++;
			histoG[m_inImageG[i][k]]++;
			histoB[m_inImageB[i][k]]++;
		}
	// 2단계 : 누적 히스토그렘 생성
	int sumHistoR[256] = { 0, };
	int sumHistoG[256] = { 0, };
	int sumHistoB[256] = { 0, };
	sumHistoR[0] = histoR[0];
	sumHistoG[0] = histoG[0];
	sumHistoB[0] = histoB[0];
	for (int i = 1; i < 256; i++)
	{
		sumHistoR[i] = sumHistoR[i - 1] + histoR[i];
		sumHistoG[i] = sumHistoG[i - 1] + histoG[i];
		sumHistoB[i] = sumHistoB[i - 1] + histoB[i];
	}
	// 3단계 : 정규화된 히스토그렘 생성
	double normalHistoR[256] = { 1.0, };
	double normalHistoG[256] = { 1.0, };
	double normalHistoB[256] = { 1.0, };
	for (int i = 0; i < 256; i++)
	{
		normalHistoR[i] = sumHistoR[i] * (1.0 / (m_inH * m_inW) * 255.0);
		normalHistoG[i] = sumHistoG[i] * (1.0 / (m_inH * m_inW) * 255.0);
		normalHistoB[i] = sumHistoB[i] * (1.0 / (m_inH * m_inW) * 255.0);
	}
	// *** 영상처리 알고리즘 ***
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			m_outImageR[i][k] = (unsigned char)normalHistoR[m_inImageR[i][k]];
			m_outImageG[i][k] = (unsigned char)normalHistoG[m_inImageG[i][k]];
			m_outImageB[i][k] = (unsigned char)normalHistoB[m_inImageB[i][k]];
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnEmbossRgbImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	/////////////////
	// 회소 영역 처리
	/////////////////
	double mask[3][3] = { // 엠보싱 마스크
		{ -1.0 , 0.0 ,0.0 },
		{ 0.0 , 0.0 ,0.0 },
		{ 0.0 , 0.0 ,1.0 }
	};
	// 임시 메모리 할당(실수형)
	double** tmpInImageR = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageR = OnMallocDouble2D(m_outH, m_outW);
	double** tmpInImageG = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageG = OnMallocDouble2D(m_outH, m_outW);
	double** tmpInImageB = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageB = OnMallocDouble2D(m_outH, m_outW);
	// 임시 입력 메모리 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
	{
		for (int k = 0; k < m_inW + 2; k++)
		{
			tmpInImageR[i][k] = 127;
			tmpInImageG[i][k] = 127;
			tmpInImageB[i][k] = 127;
		}
	}
	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}
	}
	// 회선 연산
	double SR, SG, SB;
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			// 마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			SR = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값
			SG = 0.0;
			SB = 0.0;
			for (int n = 0; n < 3; n++)
				for (int m = 0; m < 3; m++)
				{
					SR += tmpInImageR[i + n][k + m] * mask[n][m];
					SG += tmpInImageG[i + n][k + m] * mask[n][m];
					SB += tmpInImageB[i + n][k + m] * mask[n][m];
				}

			tmpOutImageR[i][k] = SR;
			tmpOutImageG[i][k] = SG;
			tmpOutImageB[i][k] = SB;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서)
	for (int i = 0; i < m_outH; i++)
	{
		for (int k = 0; k < m_outW; k++)
		{
			tmpOutImageR[i][k] += 127.0;
			tmpOutImageG[i][k] += 127.0;
			tmpOutImageB[i][k] += 127.0;
		}
	}
	// *** 영상처리 알고리즘 ***
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageB, m_outH);
}


void CGrayScaleColorImageProcessingDoc::OnEmbossHsiImage()
{
	// TODO: 여기에 구현 코드 추가.
		// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	/////////////////
	// 회소 영역 처리
	/////////////////
	double mask[3][3] = { // 엠보싱 마스크
		{ -1.0 , 0.0 ,0.0 },
		{ 0.0 , 0.0 ,0.0 },
		{ 0.0 , 0.0 ,1.0 }
	};
	// 임시 메모리 할당(실수형)
	double** tmpInImageR = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageR = OnMallocDouble2D(m_outH, m_outW);
	double** tmpInImageG = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageG = OnMallocDouble2D(m_outH, m_outW);
	double** tmpInImageB = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageB = OnMallocDouble2D(m_outH, m_outW);
	double** tmpInImageH = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpInImageS = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpInImageI = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	// 임시 입력 메모리 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
	{
		for (int k = 0; k < m_inW + 2; k++)
		{
			tmpInImageR[i][k] = 127;
			tmpInImageG[i][k] = 127;
			tmpInImageB[i][k] = 127;
		}
	}
	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}
	}
	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// 회선 연산
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageI[i][k] += 127;
		}
	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}
	// *** 영상처리 알고리즘 ***
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageB, m_outH);
}


void CGrayScaleColorImageProcessingDoc::OnBlurImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		// 기존 메모리 해제
		OnFreeOutImage();
		// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 메모리 할당	
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		/////////////////
		// 회소 영역 처리
		/////////////////
		int value = (int)dlg.m_constant;
		if (value < 1)
		{
			for (int i = 0; i < m_inH; i++)
				for (int k = 0; k < m_inW; k++)
				{
					m_outImageR[i][k] = m_inImageR[i][k];
					m_outImageG[i][k] = m_inImageG[i][k];
					m_outImageB[i][k] = m_inImageB[i][k];
				}
			return;
		}
		// 엠보싱 마스크 할당
		double** mask = OnMallocDouble2D(value, value);
		for (int i = 0; i < value; i++)
		{
			for (int k = 0; k < value; k++)
			{
				mask[i][k] = 1.0 / (double)(value * value);
			}
		}
		// 임시 메모리 할당(실수형)
		double** tmpInImageR = OnMallocDouble2D(m_inH + 2, m_inW + 2);
		double** tmpOutImageR = OnMallocDouble2D(m_outH, m_outW);
		double** tmpInImageG = OnMallocDouble2D(m_inH + 2, m_inW + 2);
		double** tmpOutImageG = OnMallocDouble2D(m_outH, m_outW);
		double** tmpInImageB = OnMallocDouble2D(m_inH + 2, m_inW + 2);
		double** tmpOutImageB = OnMallocDouble2D(m_outH, m_outW);
		// 임시 입력 메모리 초기화(127) : 필요시 평균값
		for (int i = 0; i < m_inH + 2; i++)
		{
			for (int k = 0; k < m_inW + 2; k++)
			{
				tmpInImageR[i][k] = 127;
				tmpInImageG[i][k] = 127;
				tmpInImageB[i][k] = 127;
			}
		}
		// 입력 이미지 --> 임시 입력 이미지
		for (int i = 0; i < m_inH; i++)
		{
			for (int k = 0; k < m_inW; k++)
			{
				tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
				tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
				tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
			}
		}
		// 회선 연산
		double SR, SG, SB;
		for (int i = 0; i < m_inH; i++)
		{
			for (int k = 0; k < m_inW; k++)
			{
				// 마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
				SR = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값
				SG = 0.0;
				SB = 0.0;
				for (int n = 0; n < 3; n++)
					for (int m = 0; m < 3; m++)
					{
						SR += tmpInImageR[i + n][k + m] * mask[n][m];
						SG += tmpInImageG[i + n][k + m] * mask[n][m];
						SB += tmpInImageB[i + n][k + m] * mask[n][m];
					}

				tmpOutImageR[i][k] = SR;
				tmpOutImageG[i][k] = SG;
				tmpOutImageB[i][k] = SB;
			}
		}
		// *** 영상처리 알고리즘 ***
		for (int i = 0; i < m_inH; i++)
		{
			for (int k = 0; k < m_inW; k++)
			{
				if (tmpOutImageR[i][k] < 0.0)
					m_outImageR[i][k] = 0;
				else if (tmpOutImageR[i][k] > 255.0)
					m_outImageR[i][k] = 255;
				else
					m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

				if (tmpOutImageG[i][k] < 0.0)
					m_outImageG[i][k] = 0;
				else if (tmpOutImageG[i][k] > 255.0)
					m_outImageG[i][k] = 255;
				else
					m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

				if (tmpOutImageB[i][k] < 0.0)
					m_outImageB[i][k] = 0;
				else if (tmpOutImageB[i][k] > 255.0)
					m_outImageB[i][k] = 255;
				else
					m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
			}
		}
		OnFree2D(tmpInImageR, m_inH + 2);
		OnFree2D(tmpOutImageR, m_outH);
		OnFree2D(tmpInImageG, m_inH + 2);
		OnFree2D(tmpOutImageG, m_outH);
		OnFree2D(tmpInImageB, m_inH + 2);
		OnFree2D(tmpOutImageB, m_outH);
	}
}


void CGrayScaleColorImageProcessingDoc::OnSharpImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	/////////////////
	// 회소 영역 처리
	/////////////////
	double mask[3][3] = { // 엠보싱 마스크
		{ 0 , -1  , 0 },
		{ -1 , 5  , -1 },
		{ 0 , -1  , 0 }
	};
	// 임시 메모리 할당(실수형)
	double** tmpInImageR = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageR = OnMallocDouble2D(m_outH, m_outW);
	double** tmpInImageG = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageG = OnMallocDouble2D(m_outH, m_outW);
	double** tmpInImageB = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageB = OnMallocDouble2D(m_outH, m_outW);
	// 임시 입력 메모리 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
	{
		for (int k = 0; k < m_inW + 2; k++)
		{
			tmpInImageR[i][k] = 127;
			tmpInImageG[i][k] = 127;
			tmpInImageB[i][k] = 127;
		}
	}
	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}
	}
	// 회선 연산
	double SR, SG, SB;
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			// 마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			SR = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값
			SG = 0.0;
			SB = 0.0;
			for (int n = 0; n < 3; n++)
				for (int m = 0; m < 3; m++)
				{
					SR += tmpInImageR[i + n][k + m] * mask[n][m];
					SG += tmpInImageG[i + n][k + m] * mask[n][m];
					SB += tmpInImageB[i + n][k + m] * mask[n][m];
				}

			tmpOutImageR[i][k] = SR;
			tmpOutImageG[i][k] = SG;
			tmpOutImageB[i][k] = SB;
		}
	}
	// *** 영상처리 알고리즘 ***
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageB, m_outH);
}


void CGrayScaleColorImageProcessingDoc::OnGausImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	/////////////////
	// 회소 영역 처리
	/////////////////
	double mask[3][3] = { // 엠보싱 마스크
		{ 1. / 16 , 1. / 8  , 1. / 16 },
		{ 1. / 8 , 1. / 4  , 1. / 8 },
		{ 1. / 16 , 1. / 8  , 1. / 16 }
	};
	// 임시 메모리 할당(실수형)
	double** tmpInImageR = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageR = OnMallocDouble2D(m_outH, m_outW);
	double** tmpInImageG = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageG = OnMallocDouble2D(m_outH, m_outW);
	double** tmpInImageB = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageB = OnMallocDouble2D(m_outH, m_outW);
	// 임시 입력 메모리 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
	{
		for (int k = 0; k < m_inW + 2; k++)
		{
			tmpInImageR[i][k] = 127;
			tmpInImageG[i][k] = 127;
			tmpInImageB[i][k] = 127;
		}
	}
	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}
	}
	// 회선 연산
	double SR, SG, SB;
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			// 마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			SR = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값
			SG = 0.0;
			SB = 0.0;
			for (int n = 0; n < 3; n++)
				for (int m = 0; m < 3; m++)
				{
					SR += tmpInImageR[i + n][k + m] * mask[n][m];
					SG += tmpInImageG[i + n][k + m] * mask[n][m];
					SB += tmpInImageB[i + n][k + m] * mask[n][m];
				}

			tmpOutImageR[i][k] = SR;
			tmpOutImageG[i][k] = SG;
			tmpOutImageB[i][k] = SB;
		}
	}
	// *** 영상처리 알고리즘 ***
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageB, m_outH);
}


void CGrayScaleColorImageProcessingDoc::OnHpfSharpImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	/////////////////
	// 회소 영역 처리
	/////////////////
	double mask[3][3] = { // 엠보싱 마스크
		{ -1. / 9 , -1. / 9  , -1. / 9 },
		{ -1. / 9 , 8. / 9  , -1. / 9 },
		{ -1. / 9 , -1. / 9  , -1. / 9 }
	};
	// 임시 메모리 할당(실수형)
	double** tmpInImageR = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageR = OnMallocDouble2D(m_outH, m_outW);
	double** tmpInImageG = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageG = OnMallocDouble2D(m_outH, m_outW);
	double** tmpInImageB = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageB = OnMallocDouble2D(m_outH, m_outW);
	// 임시 입력 메모리 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
	{
		for (int k = 0; k < m_inW + 2; k++)
		{
			tmpInImageR[i][k] = 127;
			tmpInImageG[i][k] = 127;
			tmpInImageB[i][k] = 127;
		}
	}
	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}
	}
	// 회선 연산
	double SR, SG, SB;
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			// 마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			SR = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값
			SG = 0.0;
			SB = 0.0;
			for (int n = 0; n < 3; n++)
				for (int m = 0; m < 3; m++)
				{
					SR += tmpInImageR[i + n][k + m] * mask[n][m];
					SG += tmpInImageG[i + n][k + m] * mask[n][m];
					SB += tmpInImageB[i + n][k + m] * mask[n][m];
				}
			tmpOutImageR[i][k] = SR;
			tmpOutImageG[i][k] = SG;
			tmpOutImageB[i][k] = SB;
		}
	}
	// *** 영상처리 알고리즘 ***
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageB, m_outH);
}


void CGrayScaleColorImageProcessingDoc::OnLpfSharpImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	/////////////////
	// 회소 영역 처리
	/////////////////
	double mask[3][3] = { // 엠보싱 마스크
		{ 1. / 9 , 1. / 9  , 1. / 9 },
		{ 1. / 9 , 1. / 9  , 1. / 9 },
		{ 1. / 9 , 1. / 9  , 1. / 9 }
	};
	// 임시 메모리 할당(실수형)
	double** tmpInImageR = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageR = OnMallocDouble2D(m_outH, m_outW);
	double** tmpInImageG = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageG = OnMallocDouble2D(m_outH, m_outW);
	double** tmpInImageB = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageB = OnMallocDouble2D(m_outH, m_outW);
	// 임시 입력 메모리 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
	{
		for (int k = 0; k < m_inW + 2; k++)
		{
			tmpInImageR[i][k] = 127;
			tmpInImageG[i][k] = 127;
			tmpInImageB[i][k] = 127;
		}
	}
	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}
	}
	// 회선 연산
	double SR, SG, SB;
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			// 마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			SR = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값
			SG = 0.0;
			SB = 0.0;
			for (int n = 0; n < 3; n++)
				for (int m = 0; m < 3; m++)
				{
					SR += tmpInImageR[i + n][k + m] * mask[n][m];
					SG += tmpInImageG[i + n][k + m] * mask[n][m];
					SB += tmpInImageB[i + n][k + m] * mask[n][m];
				}

			tmpOutImageR[i][k] = m_inImageR[i][k] - SR;
			tmpOutImageG[i][k] = m_inImageG[i][k] - SG;
			tmpOutImageB[i][k] = m_inImageB[i][k] - SB;
		}
	}
	// *** 영상처리 알고리즘 ***
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageB, m_outH);
}


void CGrayScaleColorImageProcessingDoc::OnEdgeHorImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	/////////////////
	// 회소 영역 처리
	/////////////////
	double mask[3][3] =
	{ {0.0, -1.0, 0.0}, // 엠보싱 마스크
	{ 0.0, 1.0, 0.0},
	{ 0.0, 0.0, 0.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImageR = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageR = OnMallocDouble2D(m_outH, m_outW);
	double** tmpInImageG = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageG = OnMallocDouble2D(m_outH, m_outW);
	double** tmpInImageB = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageB = OnMallocDouble2D(m_outH, m_outW);
	// 임시 입력 메모리 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
	{
		for (int k = 0; k < m_inW + 2; k++)
		{
			tmpInImageR[i][k] = 127;
			tmpInImageG[i][k] = 127;
			tmpInImageB[i][k] = 127;
		}
	}
	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}
	}
	// 회선 연산
	double SR, SG, SB;
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			// 마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			SR = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값
			SG = 0.0;
			SB = 0.0;
			for (int n = 0; n < 3; n++)
				for (int m = 0; m < 3; m++)
				{
					SR += tmpInImageR[i + n][k + m] * mask[n][m];
					SG += tmpInImageG[i + n][k + m] * mask[n][m];
					SB += tmpInImageB[i + n][k + m] * mask[n][m];
				}

			tmpOutImageR[i][k] = SR;
			tmpOutImageG[i][k] = SG;
			tmpOutImageB[i][k] = SB;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서)
	for (int i = 0; i < m_outH; i++)
	{
		for (int k = 0; k < m_outW; k++)
		{
			tmpOutImageR[i][k] += 127.0;
			tmpOutImageG[i][k] += 127.0;
			tmpOutImageB[i][k] += 127.0;
		}
	}
	// *** 영상처리 알고리즘 ***
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageB, m_outH);
}


void CGrayScaleColorImageProcessingDoc::OnEdgeVerImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	/////////////////
	// 회소 영역 처리
	/////////////////
	double mask[3][3] =
	{ {0.0, 0.0, 0.0}, // 엠보싱 마스크
	{ -1.0, 1.0, 0.0},
	{ 0.0, 0.0, 0.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImageR = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageR = OnMallocDouble2D(m_outH, m_outW);
	double** tmpInImageG = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageG = OnMallocDouble2D(m_outH, m_outW);
	double** tmpInImageB = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageB = OnMallocDouble2D(m_outH, m_outW);
	// 임시 입력 메모리 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
	{
		for (int k = 0; k < m_inW + 2; k++)
		{
			tmpInImageR[i][k] = 127;
			tmpInImageG[i][k] = 127;
			tmpInImageB[i][k] = 127;
		}
	}
	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}
	}
	// 회선 연산
	double SR, SG, SB;
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			// 마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			SR = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값
			SG = 0.0;
			SB = 0.0;
			for (int n = 0; n < 3; n++)
				for (int m = 0; m < 3; m++)
				{
					SR += tmpInImageR[i + n][k + m] * mask[n][m];
					SG += tmpInImageG[i + n][k + m] * mask[n][m];
					SB += tmpInImageB[i + n][k + m] * mask[n][m];
				}

			tmpOutImageR[i][k] = SR;
			tmpOutImageG[i][k] = SG;
			tmpOutImageB[i][k] = SB;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서)
	for (int i = 0; i < m_outH; i++)
	{
		for (int k = 0; k < m_outW; k++)
		{
			tmpOutImageR[i][k] += 127.0;
			tmpOutImageG[i][k] += 127.0;
			tmpOutImageB[i][k] += 127.0;
		}
	}
	// *** 영상처리 알고리즘 ***
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageB, m_outH);
}


void CGrayScaleColorImageProcessingDoc::OnEdgeHomogenImage()
{
	// TODO: 여기에 구현 코드 추가.
		// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	/////////////////
	// 회소 영역 처리
	/////////////////
	// 임시 메모리 할당(실수형)
	double** tmpInImageR = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageR = OnMallocDouble2D(m_outH, m_outW);
	double** tmpInImageG = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageG = OnMallocDouble2D(m_outH, m_outW);
	double** tmpInImageB = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageB = OnMallocDouble2D(m_outH, m_outW);
	// 임시 입력 메모리 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
	{
		for (int k = 0; k < m_inW + 2; k++)
		{
			tmpInImageR[i][k] = 127;
			tmpInImageG[i][k] = 127;
			tmpInImageB[i][k] = 127;
		}
	}
	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}
	}
	// 회선 연산
	double maxR, maxG, maxB;
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			maxR = 0.0; // 블록이 이동할 때마다 최대값 초기화
			maxG = 0.0;
			maxB = 0.0;
			for (int n = 0; n < 3; n++)
			{
				for (int m = 0; m < 3; m++)
				{
					if (fabs(tmpInImageR[i + 1][k + 1] - tmpInImageR[i + n][k + m]) >= maxR)
						maxR = fabs(tmpInImageR[i + 1][k + 1] - tmpInImageR[i + n][k + m]);
					if (fabs(tmpInImageG[i + 1][k + 1] - tmpInImageG[i + n][k + m]) >= maxG)
						maxG = fabs(tmpInImageG[i + 1][k + 1] - tmpInImageG[i + n][k + m]);
					if (fabs(tmpInImageB[i + 1][k + 1] - tmpInImageB[i + n][k + m]) >= maxB)
						maxB = fabs(tmpInImageB[i + 1][k + 1] - tmpInImageB[i + n][k + m]);
					// 블록의 가운데 값 - 블록의 주변 픽셀 값의 절대 값 중에서 최대값을 찾는다.
				}
			}

			tmpOutImageR[i][k] = maxR;
			tmpOutImageG[i][k] = maxG;
			tmpOutImageB[i][k] = maxB;
		}
	}
	// *** 영상처리 알고리즘 ***
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageB, m_outH);
}


void CGrayScaleColorImageProcessingDoc::OnLaplacianImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당	
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	/////////////////
	// 회소 영역 처리
	/////////////////
	double mask[3][3] =
	{ {0.0, 1.0, 0.0}, // 엠보싱 마스크
	{ 1.0, -4.0, 1.0},
	{ 0.0, 1.0, 0.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImageR = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageR = OnMallocDouble2D(m_outH, m_outW);
	double** tmpInImageG = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageG = OnMallocDouble2D(m_outH, m_outW);
	double** tmpInImageB = OnMallocDouble2D(m_inH + 2, m_inW + 2);
	double** tmpOutImageB = OnMallocDouble2D(m_outH, m_outW);
	// 임시 입력 메모리 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
	{
		for (int k = 0; k < m_inW + 2; k++)
		{
			tmpInImageR[i][k] = 127;
			tmpInImageG[i][k] = 127;
			tmpInImageB[i][k] = 127;
		}
	}
	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}
	}
	// 회선 연산
	double SR, SG, SB;
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			// 마스크(3x3)와 한점을 중심으로한 3x3을 곱하기
			SR = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값
			SG = 0.0;
			SB = 0.0;
			for (int n = 0; n < 3; n++)
				for (int m = 0; m < 3; m++)
				{
					SR += tmpInImageR[i + n][k + m] * mask[n][m];
					SG += tmpInImageG[i + n][k + m] * mask[n][m];
					SB += tmpInImageB[i + n][k + m] * mask[n][m];
				}

			tmpOutImageR[i][k] = SR;
			tmpOutImageG[i][k] = SG;
			tmpOutImageB[i][k] = SB;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서)
	for (int i = 0; i < m_outH; i++)
	{
		for (int k = 0; k < m_outW; k++)
		{
			tmpOutImageR[i][k] += 127.0;
			tmpOutImageG[i][k] += 127.0;
			tmpOutImageB[i][k] += 127.0;
		}
	}
	// *** 영상처리 알고리즘 ***
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageB, m_outH);
}


void CGrayScaleColorImageProcessingDoc::OnChangeSaturImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		// *** 영상처리 알고리즘 ***
		double value = (double)dlg.m_constant;
		if (-1.0 > value && value > 1.0)
		{
			AfxMessageBox(L"-1.0 ~ 1.0 사이의 값을 입력하시오.");
			return;
		}
		// 기존 메모리 해제
		OnFreeOutImage();
		// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 메모리 할당	
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// *** 영상처리 알고리즘 ***
		for (int i = 0; i < m_inH; i++)
		{
			for (int k = 0; k < m_inW; k++)
			{
				// HSI 모델 값
				// H(색상) : 0 ~ 360
				// S(채도) : 0.0 ~ 1.0
				// I(명도) : 0 ~ 255
				double H, S, I;
				unsigned char R, G, B;
				R = m_inImageR[i][k];
				G = m_inImageG[i][k];
				B = m_inImageB[i][k];

				double* hsi = RGB2HSI(R, G, B);
				H = hsi[0]; S = hsi[1]; I = hsi[2];

				// 채도 (S) 조리개
				S = S + value;
				if (S < 0)
					S = 0.0;
				if (S > 1.0)
					S = 1.0;

				// HSI --> RGB
				unsigned char* rgb = HSI2RGB(H, S, I);
				R = rgb[0]; G = rgb[1]; B = rgb[2];
				m_outImageR[i][k] = R;
				m_outImageG[i][k] = G;
				m_outImageB[i][k] = B;
				delete hsi;
				delete rgb;
			}
		}
	}
}


void CGrayScaleColorImageProcessingDoc::OnChangeIntenImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg1;
	CConstantDlg dlg2;
	if (dlg1.DoModal() == IDOK && dlg2.DoModal() == IDOK)
	{
		int minValue = (int)dlg1.m_constant;
		int maxValue = (int)dlg2.m_constant;
		if (0 > minValue && minValue > 360 && 0 > maxValue && maxValue > 360)
		{
			AfxMessageBox(L"0 ~ 360 사이의 값을 입력하시오.");
			return;
		}
		// 기존 메모리 해제
		OnFreeOutImage();
		// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 메모리 할당	
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// *** 영상처리 알고리즘 ***
		for (int i = 0; i < m_inH; i++)
		{
			for (int k = 0; k < m_inW; k++)
			{
				// HIS 모델 값
				// H(색상) : 0~360
				// S(채도) : 0.0 ~ 1.0
				// I(명도) : 0 ~ 255

				// RGB --> HSI
				double H, S, I;
				unsigned char R, G, B;
				R = m_inImageR[i][k];
				G = m_inImageG[i][k];
				B = m_inImageB[i][k];

				double* hsi = RGB2HSI(R, G, B);
				H = hsi[0];	S = hsi[1];	I = hsi[2];

				// 색상 추출
				if (minValue <= H && H <= maxValue)
				{
					m_outImageR[i][k] = m_inImageR[i][k];
					m_outImageG[i][k] = m_inImageG[i][k];
					m_outImageB[i][k] = m_inImageB[i][k];
				}
				else
				{
					double avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
					m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = (unsigned char)avg;
				}
				delete hsi;
			}
		}
	}
}


double* CGrayScaleColorImageProcessingDoc::RGB2HSI(int R, int G, int B)
{
	// TODO: 여기에 구현 코드 추가.
	double H, S, I;
	double* HSI = new double[3];
	double min_value, angle;
	I = (R + G + B) / 3.0; // 밝기
	if ((R == G) && (G == B)) { // 그레이
		S = 0.0;
		H = 0.0;
	}
	else {

		min_value = min(min(R, G), B); //최소값 추출
		angle = (R - 0.5 * G - 0.5 * B) / (double)sqrt((R - G) * (R - G) + (R - B) * (G - B));

		H = (double)acos(angle) * 57.29577951;
		S = 1.0f - (3.0 / (R + G + B)) * min_value;
	}
	if (B > G) H = 360. - H;

	HSI[0] = H;
	HSI[1] = S;
	HSI[2] = I;

	return HSI;
}


unsigned char* CGrayScaleColorImageProcessingDoc::HSI2RGB(double H, double S, double I)
{
	// TODO: 여기에 구현 코드 추가.
	double R, G, B;
	unsigned char* RGB = new unsigned char[3];
	double angle1, angle2, scale;

	if (I == 0.0) { // Black
		RGB[0] = 0;
		RGB[1] = 0;
		RGB[2] = 0;
		return RGB;
	}

	if (H <= 0.0) H += 360.0f;

	scale = 3.0 * I;
	if (H <= 120.0)
	{
		angle1 = H * 0.017453293;
		angle2 = (60.0 - H) * 0.017453293;
		B = (1.0 - S) / 3.0f;
		R = (double)(1.0 + (S * cos(angle1) / cos(angle2))) / 3.0;
		G = 1.0 - R - B;
		B *= scale;
		R *= scale;
		G *= scale;
	}


	else if ((H > 120.0) && (H <= 240.0)) {
		H -= 120.0;
		angle1 = H * 0.017453293;

		angle2 = (60.0 - H) * 0.017453293;
		R = (1.0 - S) / 3.0;
		G = (double)(1.0f + (S * cos(angle1) / cos(angle2))) / 3.0;
		B = 1.0 - R - G;
		R *= scale;
		G *= scale;
		B *= scale;
	}
	else {
		H -= 240.0;
		angle1 = H * 0.017453293;
		angle2 = (60.0 - H) * 0.017453293;
		G = (1.0f - S) / 3.0;
		B = (double)(1.0 + (S * cos(angle1) / cos(angle2))) / 3.0;
		R = 1.0 - G - B;

		R *= scale;
		G *= scale;
		B *= scale;
	}

	RGB[0] = (unsigned char)R;
	RGB[1] = (unsigned char)G;
	RGB[2] = (unsigned char)B;
	return RGB;
}
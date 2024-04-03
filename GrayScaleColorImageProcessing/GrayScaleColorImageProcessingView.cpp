
// GrayScaleColorImageProcessingView.cpp: CGrayScaleColorImageProcessingView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GrayScaleColorImageProcessing.h"
#endif

#include "GrayScaleColorImageProcessingDoc.h"
#include "GrayScaleColorImageProcessingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGrayScaleColorImageProcessingView

IMPLEMENT_DYNCREATE(CGrayScaleColorImageProcessingView, CView)

BEGIN_MESSAGE_MAP(CGrayScaleColorImageProcessingView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_EQUAL_IMAGE, &CGrayScaleColorImageProcessingView::OnEqualImage)
	ON_COMMAND(IDM_GRAY_SCALE_IMAGE, &CGrayScaleColorImageProcessingView::OnGrayScaleImage)
	ON_COMMAND(IDW_ADD_IMAGE, &CGrayScaleColorImageProcessingView::OnAddImage)
	ON_COMMAND(IDW_REVERSE_IMAGE, &CGrayScaleColorImageProcessingView::OnReverseImage)
	ON_COMMAND(IDW_BW_IMAGE, &CGrayScaleColorImageProcessingView::OnBwImage)
	ON_COMMAND(IDW_BW_AVG_IMAGE, &CGrayScaleColorImageProcessingView::OnBwAvgImage)
	ON_COMMAND(IDW_BW_MED_IMAGE, &CGrayScaleColorImageProcessingView::OnBwMedImage)
	ON_COMMAND(IDW_GAMMA_IMAGE, &CGrayScaleColorImageProcessingView::OnGammaImage)
	ON_COMMAND(IDW_PARA_CAP_IMAGE, &CGrayScaleColorImageProcessingView::OnParaCapImage)
	ON_COMMAND(IDW_PARA_CUP_IMAGE, &CGrayScaleColorImageProcessingView::OnParaCupImage)
	ON_COMMAND(IDW_AND_IMAGE, &CGrayScaleColorImageProcessingView::OnAndImage)
	ON_COMMAND(IDW_OR_IMAGE, &CGrayScaleColorImageProcessingView::OnOrImage)
	ON_COMMAND(IDW_XOR_IMAGE, &CGrayScaleColorImageProcessingView::OnXorImage)
	ON_COMMAND(IDW_ZOOM_OUT_IMAGE, &CGrayScaleColorImageProcessingView::OnZoomOutImage)
	ON_COMMAND(IDW_ZOOM_OUT_AVG_IMAGE, &CGrayScaleColorImageProcessingView::OnZoomOutAvgImage)
	ON_COMMAND(IDW_ZOOM_OUT_MED_MAGE, &CGrayScaleColorImageProcessingView::OnZoomOutMedMage)
	ON_COMMAND(IDW_ZOOM_IN_IMAGE, &CGrayScaleColorImageProcessingView::OnZoomInImage)
	ON_COMMAND(IDW_ZOOM_IN2_IMAGE, &CGrayScaleColorImageProcessingView::OnZoomIn2Image)
	ON_COMMAND(IDW_ZOOM_IN3_IMAGE, &CGrayScaleColorImageProcessingView::OnZoomIn3Image)
	ON_COMMAND(IDW_ROTATE_IMAGE, &CGrayScaleColorImageProcessingView::OnRotateImage)
	ON_COMMAND(IDW_ROTATE2_IMAGE, &CGrayScaleColorImageProcessingView::OnRotate2Image)
	ON_COMMAND(IDW_ROTATE3_IMAGE, &CGrayScaleColorImageProcessingView::OnRotate3Image)
	ON_COMMAND(IDW_MOVE_IMAGE, &CGrayScaleColorImageProcessingView::OnMoveImage)
	ON_COMMAND(IDW_MIRROR_UD_IMAGE, &CGrayScaleColorImageProcessingView::OnMirrorUdImage)
	ON_COMMAND(IDW_MIRROR_LR_IMAGE, &CGrayScaleColorImageProcessingView::OnMirrorLrImage)
	ON_COMMAND(IDW_HISTO_STRETCH_IMAGE, &CGrayScaleColorImageProcessingView::OnHistoStretchImage)
	ON_COMMAND(IDW_END_IN_IMAGE, &CGrayScaleColorImageProcessingView::OnEndInImage)
	ON_COMMAND(IDW_HISTO_EQUAL_IMAGE, &CGrayScaleColorImageProcessingView::OnHistoEqualImage)
	ON_COMMAND(IDW_EMBOSS_RGB_IMAGE, &CGrayScaleColorImageProcessingView::OnEmbossRgbImage)
	ON_COMMAND(IDW_EMBOSS_HSI_IMAGE, &CGrayScaleColorImageProcessingView::OnEmbossHsiImage)
	ON_COMMAND(IDW_BLUR_IMAGE, &CGrayScaleColorImageProcessingView::OnBlurImage)
	ON_COMMAND(IDW_SHARP_IMAGE, &CGrayScaleColorImageProcessingView::OnSharpImage)
	ON_COMMAND(IDW_GAUS_IMAGE, &CGrayScaleColorImageProcessingView::OnGausImage)
	ON_COMMAND(IDW_HPF_SHARP_IMAGE, &CGrayScaleColorImageProcessingView::OnHpfSharpImage)
	ON_COMMAND(IDW_LPF_SHARP_IMAGE, &CGrayScaleColorImageProcessingView::OnLpfSharpImage)
	ON_COMMAND(IDW_EDGE_HOR_IMAGE, &CGrayScaleColorImageProcessingView::OnEdgeHorImage)
	ON_COMMAND(IDW_EDGE_VER_IMAGE, &CGrayScaleColorImageProcessingView::OnEdgeVerImage)
	ON_COMMAND(IDW_EDGE_HOMOGEN_IMAGE, &CGrayScaleColorImageProcessingView::OnEdgeHomogenImage)
	ON_COMMAND(IDW_LAPLACIAN_IMAGE, &CGrayScaleColorImageProcessingView::OnLaplacianImage)
	ON_COMMAND(IDW_CHANGE_SATUR_IMAGE, &CGrayScaleColorImageProcessingView::OnChangeSaturImage)
	ON_COMMAND(IDW_CHANGE_INTEN_IMAGE, &CGrayScaleColorImageProcessingView::OnChangeIntenImage)
END_MESSAGE_MAP()

// CGrayScaleColorImageProcessingView 생성/소멸

CGrayScaleColorImageProcessingView::CGrayScaleColorImageProcessingView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CGrayScaleColorImageProcessingView::~CGrayScaleColorImageProcessingView()
{
}

BOOL CGrayScaleColorImageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGrayScaleColorImageProcessingView 그리기

void CGrayScaleColorImageProcessingView::OnDraw(CDC* pDC)
{
	//CGrayScaleColorImageProcessingView* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//if (!pDoc)
	//	return;

	//// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	//int R, G, B;
	//for (int i=0; i<pDoc->m_inH; i++)
	//	for (int k = 0; k < pDoc->m_inW; k++) {
	//		R = pDoc->m_inImageR[i][k];
	//		G = pDoc->m_inImageG[i][k];
	//		B = pDoc->m_inImageB[i][k];
	//		pDC->SetPixel(k + 5, i + 5, RGB(R, G, B));
	//	}

	//for (int i = 0; i < pDoc->m_outH; i++)
	//	for (int k = 0; k < pDoc->m_outW; k++) {
	//		R = pDoc->m_outImageR[i][k];
	//		G = pDoc->m_outImageG[i][k];
	//		B = pDoc->m_outImageB[i][k];
	//		pDC->SetPixel(pDoc->m_inW + k + 5 + 5, i + 5, RGB(R, G, B));
	//	}

	///////////////////
	/// ** 더블 버퍼링 **
	///////////////////
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	/////////////////////
	/// 성능 개선을 위한 더블 버퍼링 
	////////////////////
	int i, k;
	unsigned char R, G, B;
	// 메모리 DC 선언
	CDC memDC;
	CBitmap* pOldBitmap, bitmap;

	// 화면 DC와 호환되는 메모리 DC 객체를 생성
	memDC.CreateCompatibleDC(pDC);

	// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	bitmap.CreateCompatibleBitmap(pDC, pDoc->m_inW, pDoc->m_inH);

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, pDoc->m_inW, pDoc->m_inH, WHITENESS); // 흰색으로 초기화
	// 출력 영상의 크기를 자동 조절
	double MAXSIZE = 800;  // 필요시 실 모니터 또는 화면의 해상도에 따라서 변경 가능!
	int inH = pDoc->m_inH;
	int inW = pDoc->m_inW;
	double hop = 1.0; // 기본

	if (inH > MAXSIZE || inW > MAXSIZE) {
		// hop을 새로 계산.
		if (inW > inH)
			hop = (inW / MAXSIZE);
		else
			hop = (inH / MAXSIZE);

		inW = (int)(inW / hop);
		inH = (int)(inH / hop);
	}

	// 메모리 DC에 그리기
	for (i = 0; i < inH; i++) {
		for (k = 0; k < inW; k++) {
			R = pDoc->m_inImageR[(int)(i * hop)][(int)(k * hop)];
			G = pDoc->m_inImageG[(int)(i * hop)][(int)(k * hop)];
			B = pDoc->m_inImageB[(int)(i * hop)][(int)(k * hop)];
			memDC.SetPixel(k, i, RGB(R, G, B));
		}
	}

	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(5, 5, pDoc->m_inW, pDoc->m_inH, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();

	///////////////////

	// 화면 DC와 호환되는 메모리 DC 객체를 생성
	memDC.CreateCompatibleDC(pDC);

	// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	bitmap.CreateCompatibleBitmap(pDC, pDoc->m_outW, pDoc->m_outH);

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, pDoc->m_outW, pDoc->m_outH, WHITENESS); // 흰색으로 초기화

	int outH = pDoc->m_outH;
	int outW = pDoc->m_outW;
	hop = 1.0; // 기본

	if (outH > MAXSIZE || outW > MAXSIZE) {
		// hop을 새로 계산.
		if (outW > outH)
			hop = (outW / MAXSIZE);
		else
			hop = (outH / MAXSIZE);

		outW = (int)(outW / hop);
		outH = (int)(outH / hop);
	}

	// 메모리 DC에 그리기
	for (i = 0; i < outH; i++) {
		for (k = 0; k < outW; k++) {
			R = pDoc->m_outImageR[(int)(i * hop)][(int)(k * hop)];
			G = pDoc->m_outImageG[(int)(i * hop)][(int)(k * hop)];
			B = pDoc->m_outImageB[(int)(i * hop)][(int)(k * hop)];
			memDC.SetPixel(k, i, RGB(R, G, B));
		}
	}
	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(inW + 10, 5, pDoc->m_outW, pDoc->m_outH, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();
}


// CGrayScaleColorImageProcessingView 인쇄

BOOL CGrayScaleColorImageProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGrayScaleColorImageProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGrayScaleColorImageProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CGrayScaleColorImageProcessingView 진단

#ifdef _DEBUG
void CGrayScaleColorImageProcessingView::AssertValid() const
{
	CView::AssertValid();
}

void CGrayScaleColorImageProcessingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGrayScaleColorImageProcessingDoc* CGrayScaleColorImageProcessingView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGrayScaleColorImageProcessingDoc)));
	return (CGrayScaleColorImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CGrayScaleColorImageProcessingView 메시지 처리기


void CGrayScaleColorImageProcessingView::OnEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEqualImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnGrayScaleImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->OnGrayScaleImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnAddImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAddImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnReverseImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnReverseImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnBwImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBwImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnBwAvgImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBwAvgImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnBwMedImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBwMedImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnGammaImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGammaImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnParaCapImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnParaCapImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnParaCupImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnParaCupImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnAndImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAndImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnOrImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnOrImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnXorImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnXorImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnZoomOutImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomOutImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnZoomOutAvgImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomOutAvgImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnZoomOutMedMage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomOutMedMage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnZoomInImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomInImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnZoomIn2Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomIn2Image();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnZoomIn3Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomIn3Image();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnRotateImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRotateImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnRotate2Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRotate2Image();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnRotate3Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRotate3Image();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnMoveImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMoveImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnMirrorUdImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMirrorUdImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnMirrorLrImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMirrorLrImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnHistoStretchImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoStretchImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnEndInImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEndInImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnHistoEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoEqualImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}



void CGrayScaleColorImageProcessingView::OnEmbossRgbImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEmbossRgbImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnEmbossHsiImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEmbossHsiImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnBlurImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBlurImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnSharpImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSharpImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnGausImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGausImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnHpfSharpImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHpfSharpImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnLpfSharpImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLpfSharpImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnEdgeHorImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdgeHorImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnEdgeVerImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdgeVerImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnEdgeHomogenImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdgeHomogenImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnLaplacianImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLaplacianImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnChangeSaturImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnChangeSaturImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleColorImageProcessingView::OnChangeIntenImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnChangeIntenImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}

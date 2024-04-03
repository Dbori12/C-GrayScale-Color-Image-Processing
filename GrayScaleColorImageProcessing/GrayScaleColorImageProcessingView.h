
// GrayScaleColorImageProcessingView.h: CGrayScaleColorImageProcessingView 클래스의 인터페이스
//

#pragma once
#include "GrayScaleColorImageProcessingDoc.h"


class CGrayScaleColorImageProcessingView : public CView
{
protected: // serialization에서만 만들어집니다.
	CGrayScaleColorImageProcessingView() noexcept;
	DECLARE_DYNCREATE(CGrayScaleColorImageProcessingView)

// 특성입니다.
public:
	CGrayScaleColorImageProcessingDoc* GetDocument() const;

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
	virtual ~CGrayScaleColorImageProcessingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEqualImage();
	afx_msg void OnGrayScaleImage();
	afx_msg void OnAddImage();
	afx_msg void OnReverseImage();
	afx_msg void OnBwImage();
	afx_msg void OnBwAvgImage();
	afx_msg void OnBwMedImage();
	afx_msg void OnGammaImage();
	afx_msg void OnParaCapImage();
	afx_msg void OnParaCupImage();
	afx_msg void OnAndImage();
	afx_msg void OnOrImage();
	afx_msg void OnXorImage();
	afx_msg void OnZoomOutImage();
	afx_msg void OnZoomOutAvgImage();
	afx_msg void OnZoomOutMedMage();
	afx_msg void OnZoomInImage();
	afx_msg void OnZoomIn2Image();
	afx_msg void OnZoomIn3Image();
	afx_msg void OnRotateImage();
	afx_msg void OnRotate2Image();
	afx_msg void OnRotate3Image();
	afx_msg void OnMoveImage();
	afx_msg void OnMirrorUdImage();
	afx_msg void OnMirrorLrImage();
	afx_msg void OnHistoStretchImage();
	afx_msg void OnEndInImage();
	afx_msg void OnHistoEqualImage();
	afx_msg void OnEmbossRgbImage();
	afx_msg void OnEmbossHsiImage();
	afx_msg void OnBlurImage();
	afx_msg void OnSharpImage();
	afx_msg void OnGausImage();
	afx_msg void OnHpfSharpImage();
	afx_msg void OnLpfSharpImage();
	afx_msg void OnEdgeHorImage();
	afx_msg void OnEdgeVerImage();
	afx_msg void OnEdgeHomogenImage();
	afx_msg void OnLaplacianImage();
	afx_msg void OnChangeSaturImage();
	afx_msg void OnChangeIntenImage();
};

#ifndef _DEBUG  // GrayScaleColorImageProcessingView.cpp의 디버그 버전
inline CGrayScaleColorImageProcessingDoc* CGrayScaleColorImageProcessingView::GetDocument() const
   { return reinterpret_cast<CGrayScaleColorImageProcessingDoc*>(m_pDocument); }
#endif


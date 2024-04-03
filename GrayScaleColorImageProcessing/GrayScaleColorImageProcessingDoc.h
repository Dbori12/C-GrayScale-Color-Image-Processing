
// GrayScaleColorImageProcessingDoc.h: CGrayScaleColorImageProcessingDoc 클래스의 인터페이스
//


#pragma once


class CGrayScaleColorImageProcessingDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CGrayScaleColorImageProcessingDoc() noexcept;
	DECLARE_DYNCREATE(CGrayScaleColorImageProcessingDoc)

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
	virtual ~CGrayScaleColorImageProcessingDoc();
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
	unsigned char** m_inImageR = NULL;
	unsigned char** m_inImageG = NULL;
	unsigned char** m_inImageB = NULL;
	unsigned char** m_outImageR = NULL;
	unsigned char** m_outImageG = NULL;
	unsigned char** m_outImageB = NULL;
	unsigned char** m_otherImageR = NULL;
	unsigned char** m_otherImageG = NULL;
	unsigned char** m_otherImageB = NULL;
	int m_inH = 0;
	int m_inW = 0;
	int m_outH = 0;
	int m_outW = 0;
	int m_otherH = 0;
	int m_otherW = 0;
	unsigned char** OnMalloc2D(int h, int w);
	template <typename T>
	void OnFree2D(T** memory, int h);
	void OnFreeOutImage();
	double** OnMallocDouble2D(int h, int w);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	bool OnOpenOtherDocument();
public:
	void OnEqualImage();
	void OnGrayScaleImage();
	void OnAddImage();
	void OnReverseImage();
	void OnBwImage();
	void OnBwAvgImage();
	void OnBwMedImage();
	void OnGammaImage();
	void OnParaCapImage();
	void OnParaCupImage();
	void OnAndImage();
	void OnOrImage();
	void OnXorImage();
	void OnZoomOutImage();
	void OnZoomOutAvgImage();
	void OnZoomOutMedMage();
	void OnZoomInImage();
	void OnZoomIn2Image();
	void OnZoomIn3Image();
	void OnRotateImage();
	void OnRotate2Image();
	void OnRotate3Image();
	void OnMoveImage();
	void OnMirrorUdImage();
	void OnMirrorLrImage();
	void OnHistoStretchImage();
	void OnEndInImage();
	void OnHistoEqualImage();
	void OnEmbossRgbImage();
	void OnEmbossHsiImage();
	void OnBlurImage();
	void OnSharpImage();
	void OnGausImage();
	void OnHpfSharpImage();
	void OnLpfSharpImage();
	void OnEdgeHorImage();
	void OnEdgeVerImage();
	void OnEdgeHomogenImage();
	void OnLaplacianImage();
	void OnChangeSaturImage();
	double* RGB2HSI(int R, int G, int B);
	unsigned char* HSI2RGB(double H, double S, double I);
	void OnChangeIntenImage();
};

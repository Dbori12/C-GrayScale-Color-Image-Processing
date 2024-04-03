// ConstantDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GrayScaleColorImageProcessing.h"
#include "afxdialogex.h"
#include "ConstantDlg.h"
#include "GrayScaleColorImageProcessingView.h"


// CConstantDlg 대화 상자

IMPLEMENT_DYNAMIC(CConstantDlg, CDialogEx)

CConstantDlg::CConstantDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONSTANT, pParent)
	, m_constant(0)
{

}

CConstantDlg::~CConstantDlg()
{
}

void CConstantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT, m_constant);
	DDV_MinMaxDouble(pDX, m_constant, -360, 360);
}


BEGIN_MESSAGE_MAP(CConstantDlg, CDialogEx)
END_MESSAGE_MAP()


// CConstantDlg 메시지 처리기
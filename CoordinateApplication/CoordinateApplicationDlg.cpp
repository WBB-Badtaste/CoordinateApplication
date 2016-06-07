
// CoordinateApplicationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CoordinateApplication.h"
#include "CoordinateApplicationDlg.h"
#include "afxdialogex.h"

//#include<afxwin.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCoordinateApplicationDlg 对话框



CCoordinateApplicationDlg::CCoordinateApplicationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCoordinateApplicationDlg::IDD, pParent)
	, m_radio_setType(0)
	, m_trans_x(0)
	, m_trans_y(0)
	, m_trans_z(0)
	, m_ratio(1.0)
	, m_rotate_z(0)
	, m_rotate_y(0)
	, m_rotate_x(0)
	, coordinate_point1_x(0)
	, coordinate_point1_y(0)
	, coordinate_point1_z(0)
	, coordinate_point2_x(0)
	, coordinate_point2_y(0)
	, coordinate_point2_z(0)
	, coordinate_point3_x(0)
	, coordinate_point3_y(0)
	, coordinate_point3_z(0)
	, m_pallet_use_base_coordinate(TRUE)
	, m_point1_pallet_x(0)
	, m_point1_pallet_y(0)
	, m_point1_pallet_z(0)
	, m_point2_pallet_x(0)
	, m_point2_pallet_y(0)
	, m_point2_pallet_z(0)
	, m_point3_pallet_x(0)
	, m_point3_pallet_y(0)
	, m_point3_pallet_z(0)
	, m_x_amount_pallet(0)
	, m_y_amount_pallet(0)
//	, m_id_pallet(0)
	, m_x_lenght_pallet(0)
	, m_y_lenght_pallet(0)
	, m_coordinate_note(_T("机构坐标系"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CCoordinateApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_MANUAL, m_radio_setType);
	DDX_Text(pDX, IDC_EDIT_TRANS_X, m_trans_x);
	DDX_Text(pDX, IDC_EDIT_TRANS_Y, m_trans_y);
	DDX_Text(pDX, IDC_EDIT_TRANS_Z, m_trans_z);
	DDX_Text(pDX, IDC_EDIT_RATIO, m_ratio);
	DDX_Text(pDX, IDC_EDIT_ROTATE_Z, m_rotate_z);
	DDX_Text(pDX, IDC_EDIT_ROTATE_Y, m_rotate_y);
	DDX_Text(pDX, IDC_EDIT_ROTATE_X, m_rotate_x);
	DDX_Text(pDX, IDC_EDIT_POINT1_BASE_X, coordinate_point1_x);
	DDX_Text(pDX, IDC_EDIT_POINT1_BASE_Y, coordinate_point1_y);
	DDX_Text(pDX, IDC_EDIT_POINT1_BASE_Z, coordinate_point1_z);
	DDX_Text(pDX, IDC_EDIT_POINT2_BASE_X, coordinate_point2_x);
	DDX_Text(pDX, IDC_EDIT_POINT2_BASE_Y, coordinate_point2_y);
	DDX_Text(pDX, IDC_EDIT_POINT2_BASE_Z, coordinate_point2_z);
	DDX_Text(pDX, IDC_EDIT_POINT3_BASE_X, coordinate_point3_x);
	DDX_Text(pDX, IDC_EDIT_POINT3_BASE_Y, coordinate_point3_y);
	DDX_Text(pDX, IDC_EDIT_POINT3_BASE_Z, coordinate_point3_z);
	DDX_Control(pDX, IDC_COMBO_BASE_COORD, m_comboBox_base_coordinate);
	//  DDX_Control(pDX, IDC_COMBO_CHANGE_COORD, m);
	DDX_Control(pDX, IDC_COMBO_CHANGE_COORD, m_comboBox_change_coordinate);
	DDX_Check(pDX, IDC_CHECK_PALLET_USE_BASE, m_pallet_use_base_coordinate);
	//	DDX_Control(pDX, IDC_LIST2, m_listBox_coordinate);
//	DDX_Control(pDX, IDC_COMBO_COORDINATE_TYPE, m_combo_coordinate_type);
	DDX_Control(pDX, IDC_COMBO_PALLET_IN_COORD, m_combo_pallet_in_coordinate);
	DDX_Control(pDX, IDC_COMBO_PALLET_BASE_COORD, m_combo_pallet_base_coordinate);
	DDX_Control(pDX, IDC_COMBO_SEL_PALLET, m_combo_show_pallet);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl_coordinate);
	DDX_Text(pDX, IDC_EDIT_POINT1_PALLET_X, m_point1_pallet_x);
	DDX_Text(pDX, IDC_EDIT_POINT1_PALLET_Y, m_point1_pallet_y);
	DDX_Text(pDX, IDC_EDIT_POINT1_PALLET_Z, m_point1_pallet_z);
	//  DDX_Control(pDX, IDC_EDIT_POINT2_PALLET_X, m_point2_pallet_x);
	DDX_Text(pDX, IDC_EDIT_POINT2_PALLET_X, m_point2_pallet_x);
	DDX_Text(pDX, IDC_EDIT_POINT2_PALLET_Y, m_point2_pallet_y);
	DDX_Text(pDX, IDC_EDIT_POINT2_PALLET_Z, m_point2_pallet_z);
	DDX_Text(pDX, IDC_EDIT_POINT3_PALLET_X, m_point3_pallet_x);
	DDX_Text(pDX, IDC_EDIT_POINT3_PALLET_Y, m_point3_pallet_y);
	DDX_Text(pDX, IDC_EDIT_POINT3_PALLET_Z, m_point3_pallet_z);
	DDX_Text(pDX, IDC_EDIT_X_NUM, m_x_amount_pallet);
	DDX_Text(pDX, IDC_EDIT_Y_NUM, m_y_amount_pallet);
	//	DDX_Text(pDX, IDC_EDIT_PALLET_ID, m_id_pallet);
	//  DDX_Control(pDX, IDC_EDIT_PALLET_X_LENGHT, m_x_lenght_pallet);
	DDX_Text(pDX, IDC_EDIT_PALLET_X_LENGHT, m_x_lenght_pallet);
	DDX_Text(pDX, IDC_EDIT_PALLET_Y_LENGHT, m_y_lenght_pallet);
	DDX_Control(pDX, IDC_LIST2, m_listCtrl_pallets);
	DDX_Control(pDX, IDC_COMBO_PALLET_SHOW_COORDINATE, m_comboBox_pallet_show_coordinate);
	DDX_Text(pDX, IDC_EDIT1, m_coordinate_note);
}

BEGIN_MESSAGE_MAP(CCoordinateApplicationDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO_MANUAL, &CCoordinateApplicationDlg::OnBnClickedRadioManual)
	ON_BN_CLICKED(IDC_RADIO_AUTO, &CCoordinateApplicationDlg::OnBnClickedRadioAuto)
	ON_BN_CLICKED(IDC_CHECK_PALLET_USE_BASE, &CCoordinateApplicationDlg::OnBnClickedCheckPalletUseBase)
	ON_BN_CLICKED(IDC_BUTTON_CREATE_COORD, &CCoordinateApplicationDlg::OnBnClickedButtonCreateCoord)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CHANGE_COORD, &CCoordinateApplicationDlg::OnBnClickedButtonChangeCoord)
	ON_BN_CLICKED(IDC_BUTTON_CREATE_PALLET, &CCoordinateApplicationDlg::OnBnClickedButtonCreatePallet)
	ON_CBN_SELCHANGE(IDC_COMBO_SEL_PALLET, &CCoordinateApplicationDlg::OnCbnSelchangeComboSelPallet)
	ON_CBN_SELCHANGE(IDC_COMBO_PALLET_SHOW_COORDINATE, &CCoordinateApplicationDlg::OnCbnSelchangeComboPalletShowCoordinate)
END_MESSAGE_MAP()


// CCoordinateApplicationDlg 消息处理程序

BOOL CCoordinateApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	m_pCoordinateOperator = new CCoordinateOperator;
	m_pPallerOperator = new CPalletOperator(m_pCoordinateOperator);

	//setup the coordinate list control
	m_listCtrl_coordinate.InsertColumn(0, _T("ID"), LVCFMT_CENTER, 100, -1);
	m_listCtrl_coordinate.InsertColumn(1, _T("坐标系备注"), LVCFMT_CENTER, 100, -1);
	m_listCtrl_coordinate.InsertColumn(2, _T("平移矩阵X"), LVCFMT_CENTER, 100, -1);
	m_listCtrl_coordinate.InsertColumn(3, _T("平移矩阵Y"), LVCFMT_CENTER, 100, -1);
	m_listCtrl_coordinate.InsertColumn(4, _T("平移矩阵Z"), LVCFMT_CENTER, 100, -1);
	m_listCtrl_coordinate.InsertColumn(5, _T("旋转矩阵X"), LVCFMT_CENTER, 100, -1);
	m_listCtrl_coordinate.InsertColumn(6, _T("旋转矩阵Y"), LVCFMT_CENTER, 100, -1);
	m_listCtrl_coordinate.InsertColumn(7, _T("旋转矩阵Z"), LVCFMT_CENTER, 100, -1);
	m_listCtrl_coordinate.InsertColumn(8, _T("比例系数"), LVCFMT_CENTER, 100, -1);

	//setup the pallet list control
	m_listCtrl_pallets.InsertColumn(0, _T("行号"), LVCFMT_CENTER, 100, -1);
	m_listCtrl_pallets.InsertColumn(1, _T("列号"), LVCFMT_CENTER, 100, -1);
	m_listCtrl_pallets.InsertColumn(2, _T("所在坐标系ID"), LVCFMT_CENTER, 100, -1);
	m_listCtrl_pallets.InsertColumn(3, _T("所在坐标系备注"), LVCFMT_CENTER, 100, -1);
	m_listCtrl_pallets.InsertColumn(4, _T("X坐标"), LVCFMT_CENTER, 100, -1);
	m_listCtrl_pallets.InsertColumn(5, _T("Y坐标"), LVCFMT_CENTER, 100, -1);
	m_listCtrl_pallets.InsertColumn(6, _T("Z坐标"), LVCFMT_CENTER, 100, -1);

	//m_listCtrl_coordinate.EnsureVisible(m_List.GetItemCount() - 1, FALSE);

	UpdateCoordinate();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCoordinateApplicationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCoordinateApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCoordinateApplicationDlg::OnBnClickedRadioManual()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_radio_setType = 0;
	SetManualEnable(TRUE);
	SetAutoEnable(FALSE);
	UpdateData(FALSE);
}


void CCoordinateApplicationDlg::OnBnClickedRadioAuto()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_radio_setType = 1;
	SetManualEnable(FALSE);
	SetAutoEnable(TRUE);
	UpdateData(FALSE);
}

void CCoordinateApplicationDlg::SetManualEnable(const BOOL &singal)
{
	GetDlgItem(IDC_EDIT_TRANS_X)->EnableWindow(singal);
	GetDlgItem(IDC_EDIT_TRANS_Y)->EnableWindow(singal);
	GetDlgItem(IDC_EDIT_TRANS_Z)->EnableWindow(singal);
	GetDlgItem(IDC_EDIT_ROTATE_X)->EnableWindow(singal);
	GetDlgItem(IDC_EDIT_ROTATE_Y)->EnableWindow(singal);
	GetDlgItem(IDC_EDIT_ROTATE_Z)->EnableWindow(singal);
	GetDlgItem(IDC_EDIT_RATIO)->EnableWindow(singal);
}

void CCoordinateApplicationDlg::SetAutoEnable(const BOOL &singal)
{
	GetDlgItem(IDC_EDIT_POINT1_BASE_X)->EnableWindow(singal);
	GetDlgItem(IDC_EDIT_POINT1_BASE_Y)->EnableWindow(singal);
	GetDlgItem(IDC_EDIT_POINT1_BASE_Z)->EnableWindow(singal);
	GetDlgItem(IDC_EDIT_POINT2_BASE_X)->EnableWindow(singal);
	GetDlgItem(IDC_EDIT_POINT2_BASE_Y)->EnableWindow(singal);
	GetDlgItem(IDC_EDIT_POINT2_BASE_Z)->EnableWindow(singal);
	GetDlgItem(IDC_EDIT_POINT3_BASE_X)->EnableWindow(singal);
	GetDlgItem(IDC_EDIT_POINT3_BASE_Y)->EnableWindow(singal);
	GetDlgItem(IDC_EDIT_POINT3_BASE_Z)->EnableWindow(singal);
	GetDlgItem(IDC_COMBO_BASE_COORD)->EnableWindow(singal);
}

void CCoordinateApplicationDlg::SetUseBaseEnable(const BOOL &singal)
{
	GetDlgItem(IDC_EDIT_POINT1_PALLET_X)->EnableWindow(singal);
	GetDlgItem(IDC_EDIT_POINT1_PALLET_Y)->EnableWindow(singal);
	GetDlgItem(IDC_EDIT_POINT1_PALLET_Z)->EnableWindow(singal);

	GetDlgItem(IDC_EDIT_POINT2_PALLET_X)->EnableWindow(singal);
	GetDlgItem(IDC_EDIT_POINT2_PALLET_Y)->EnableWindow(singal);
	GetDlgItem(IDC_EDIT_POINT2_PALLET_Z)->EnableWindow(singal);

	GetDlgItem(IDC_EDIT_POINT3_PALLET_X)->EnableWindow(singal);
	GetDlgItem(IDC_EDIT_POINT3_PALLET_Y)->EnableWindow(singal);
	GetDlgItem(IDC_EDIT_POINT3_PALLET_Z)->EnableWindow(singal);

	GetDlgItem(IDC_COMBO_PALLET_IN_COORD)->EnableWindow(!singal);
	GetDlgItem(IDC_COMBO_PALLET_BASE_COORD)->EnableWindow(singal);

	GetDlgItem(IDC_EDIT_PALLET_X_LENGHT)->EnableWindow(!singal);
	GetDlgItem(IDC_EDIT_PALLET_Y_LENGHT)->EnableWindow(!singal);

}


void CCoordinateApplicationDlg::OnBnClickedCheckPalletUseBase()
{
	// TODO:  在此添加控件通知处理程序代码
	m_pallet_use_base_coordinate = !m_pallet_use_base_coordinate;

	SetUseBaseEnable(m_pallet_use_base_coordinate);
	
}


void CCoordinateApplicationDlg::OnBnClickedButtonCreateCoord()
{
	// TODO:  在此添加控件通知处理程序代码

	unsigned coordinateId_target(0);

	UpdateData(TRUE);

	unsigned strSize(m_coordinate_note.GetLength() * sizeof(TCHAR));


	if (!m_radio_setType)
	{//manual
		E3_VECTOR r;
		r.x = m_rotate_x;
		r.y = m_rotate_y;
		r.z = m_rotate_z;

		E3_VECTOR t;
		t.x = m_trans_x;
		t.y = m_trans_y;
		t.z = m_trans_z;

		double zoom = m_ratio;

		m_pCoordinateOperator->SetCoordinate(coordinateId_target, t, r, zoom, (TCHAR*)m_coordinate_note.GetBuffer(0), strSize);
	}
	else
	{//auto
		unsigned coordinateId_base(0);
		if (!m_pCoordinateOperator->GetCoordianteId(m_comboBox_base_coordinate.GetCurSel(), coordinateId_base))
		{
			DOBOT_POSITION p1(coordinateId_base), p2(coordinateId_base), p3(coordinateId_base);
			p1.position.x = coordinate_point1_x;
			p1.position.y = coordinate_point1_y;
			p1.position.z = coordinate_point1_z;
			p2.position.x = coordinate_point2_x;
			p2.position.y = coordinate_point2_y;
			p2.position.z = coordinate_point2_z;
			p3.position.x = coordinate_point3_x;
			p3.position.y = coordinate_point3_y;
			p3.position.z = coordinate_point3_z;

			m_pCoordinateOperator->SetCoordinate(coordinateId_target, p1, p2, p3, (TCHAR*)m_coordinate_note.GetBuffer(0), strSize);
		}
		else
		{
			//error handler
		}
		

	}

	UpdateCoordinate();

	UpdateData(FALSE);
}

void CCoordinateApplicationDlg::AddCoordinate2List(const COORDINATE &coordinate)
{
	CString str("");
	str.Format(_T("%03u"), coordinate.coordinate_id);
	m_listCtrl_coordinate.InsertItem(coordinate.coordinate_id, str);
	str.Format(_T("%s"), coordinate.note.str);
	m_listCtrl_coordinate.SetItemText(coordinate.coordinate_id, 1, str);
	str.Format(_T("%f"), coordinate.t.x);
	m_listCtrl_coordinate.SetItemText(coordinate.coordinate_id, 2, str);
	str.Format(_T("%f"), coordinate.t.y);
	m_listCtrl_coordinate.SetItemText(coordinate.coordinate_id, 3, str);
	str.Format(_T("%f"), coordinate.t.z);
	m_listCtrl_coordinate.SetItemText(coordinate.coordinate_id, 4, str);
	str.Format(_T("%f"), coordinate.r.x);
	m_listCtrl_coordinate.SetItemText(coordinate.coordinate_id, 5, str);
	str.Format(_T("%f"), coordinate.r.y);
	m_listCtrl_coordinate.SetItemText(coordinate.coordinate_id, 6, str);
	str.Format(_T("%f"), coordinate.r.z);
	m_listCtrl_coordinate.SetItemText(coordinate.coordinate_id, 7, str);
	str.Format(_T("%f"), coordinate.zoom);
	m_listCtrl_coordinate.SetItemText(coordinate.coordinate_id, 8, str);
}

void CCoordinateApplicationDlg::UpdateCoordinate()
{
	m_comboBox_base_coordinate.ResetContent();
	m_comboBox_change_coordinate.ResetContent();
	m_combo_pallet_in_coordinate.ResetContent();
	m_combo_pallet_base_coordinate.ResetContent();
	m_comboBox_pallet_show_coordinate.ResetContent();

	m_listCtrl_coordinate.DeleteAllItems();

	COORDINATE coordinate;
	CString str;

	if (!m_pCoordinateOperator->ErgodicAllCoordinate(coordinate, true))
	{
		str.Format(_T("%03u"), coordinate.coordinate_id);
		m_comboBox_base_coordinate.AddString(str);
		m_comboBox_change_coordinate.AddString(str);
		m_combo_pallet_in_coordinate.AddString(str);
		m_combo_pallet_base_coordinate.AddString(str);
		m_comboBox_pallet_show_coordinate.AddString(str);
		AddCoordinate2List(coordinate);

		while (!m_pCoordinateOperator->ErgodicAllCoordinate(coordinate))
		{
			str.Format(_T("%03u"), coordinate.coordinate_id);
			m_comboBox_base_coordinate.AddString(str);
			m_comboBox_change_coordinate.AddString(str);
			m_combo_pallet_in_coordinate.AddString(str);
			m_combo_pallet_base_coordinate.AddString(str);
			m_comboBox_pallet_show_coordinate.AddString(str);
			AddCoordinate2List(coordinate);
		}
	}

	m_comboBox_base_coordinate.SetCurSel(0);
	m_comboBox_change_coordinate.SetCurSel(0);
	m_combo_pallet_in_coordinate.SetCurSel(0);
	m_combo_pallet_base_coordinate.SetCurSel(0);
	m_comboBox_pallet_show_coordinate.SetCurSel(0);
}

void CCoordinateApplicationDlg::UpadtePallet()
{
	PALLET pallet;
	CString str;

	m_combo_show_pallet.ResetContent();

	if (!m_pPallerOperator->ErgodicAllPallet(pallet, true))
	{
		str.Format(_T("%03u"), pallet.id_pallet);
		m_combo_show_pallet.AddString(str);

		while (!m_pPallerOperator->ErgodicAllPallet(pallet))
		{
			str.Format(_T("%03u"), pallet.id_pallet);
			m_combo_show_pallet.AddString(str);
		}
	}

	m_combo_show_pallet.SetCurSel(0);

	AddPallets2List();
}

void CCoordinateApplicationDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  在此处添加消息处理程序代码

	delete m_pPallerOperator;
	delete m_pCoordinateOperator;
}


void CCoordinateApplicationDlg::OnBnClickedButtonChangeCoord()
{
	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);

	unsigned coordinateId_target(0);
	m_pCoordinateOperator->GetCoordianteId(m_comboBox_change_coordinate.GetCurSel(), coordinateId_target);

	unsigned strSize(m_coordinate_note.GetLength() * sizeof(TCHAR));

	if (!m_radio_setType)
	{//manual
		E3_VECTOR r;
		r.x = m_rotate_x;
		r.y = m_rotate_y;
		r.z = m_rotate_z;

		E3_VECTOR t;
		t.x = m_trans_x;
		t.y = m_trans_y;
		t.z = m_trans_z;

		double zoom = m_ratio;

		m_pCoordinateOperator->SetCoordinate(coordinateId_target, t, r, zoom, (TCHAR*)m_coordinate_note.GetBuffer(0), strSize);
	}
	else
	{//auto

		unsigned coordinateId_base(0);
		unsigned index(m_comboBox_base_coordinate.GetCurSel());
		if (!m_pCoordinateOperator->GetCoordianteId(index, coordinateId_base))
		{
			DOBOT_POSITION p1(coordinateId_base), p2(coordinateId_base), p3(coordinateId_base);
			p1.position.x = coordinate_point1_x;
			p1.position.y = coordinate_point1_y;
			p1.position.z = coordinate_point1_z;
			p2.position.x = coordinate_point2_x;
			p2.position.y = coordinate_point2_y;
			p2.position.z = coordinate_point2_z;
			p3.position.x = coordinate_point3_x;
			p3.position.y = coordinate_point3_y;
			p3.position.z = coordinate_point3_z;

			m_pCoordinateOperator->SetCoordinate(coordinateId_target, p1, p2, p3, (TCHAR*)m_coordinate_note.GetBuffer(0), strSize);
		}
		else
		{
			//error handler
		}


	}

	UpdateCoordinate();

	UpdateData(FALSE);
}


void CCoordinateApplicationDlg::OnBnClickedButtonCreatePallet()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	unsigned idOfPallet(0);

	if (m_pallet_use_base_coordinate)
	{
		unsigned baseCoordinateIdOfPoint(0);
		unsigned index(m_combo_pallet_base_coordinate.GetCurSel());
		if (!m_pCoordinateOperator->GetCoordianteId(index, baseCoordinateIdOfPoint))
		{
			DOBOT_POSITION
				p1(baseCoordinateIdOfPoint), 
				p2(baseCoordinateIdOfPoint), 
				p3(baseCoordinateIdOfPoint);

			p1.position.x = m_point1_pallet_x;
			p1.position.y = m_point1_pallet_y;
			p1.position.z = m_point1_pallet_z;
			p2.position.x = m_point2_pallet_x;
			p2.position.y = m_point2_pallet_y;
			p2.position.z = m_point2_pallet_z;
			p3.position.x = m_point3_pallet_x;
			p3.position.y = m_point3_pallet_y;
			p3.position.z = m_point3_pallet_z;

			m_pPallerOperator->CreatePallet(idOfPallet, p1, p2, p3, m_x_amount_pallet, m_y_amount_pallet);

			UpdateCoordinate();
		}
	}
	else
	{
		unsigned baseCoordinateIdOfPallet(0);

		if (m_pCoordinateOperator->GetCoordianteId(m_combo_pallet_in_coordinate.GetCurSel(), baseCoordinateIdOfPallet))
			return;

		m_pPallerOperator->CreatePallet(idOfPallet, baseCoordinateIdOfPallet, m_x_lenght_pallet, m_y_lenght_pallet, m_x_amount_pallet, m_y_amount_pallet);
	}

	UpadtePallet();

	UpdateData(FALSE);
}




void CCoordinateApplicationDlg::OnCbnSelchangeComboSelPallet()
{
	// TODO: Add your control notification handler code here
	AddPallets2List();
}

void CCoordinateApplicationDlg::AddPallets2List()
{
	UpdateData(TRUE);

	unsigned indexOfPallet(m_combo_show_pallet.GetCurSel());
	PALLET pallet;

	m_pPallerOperator->GetPalletByIndex(indexOfPallet, pallet);

	m_listCtrl_pallets.DeleteAllItems();

	CString str("");
	for (unsigned i = 0; i < pallet.zoneNumX; ++i)
	for (unsigned j = 0; j < pallet.zoneNumY; ++j)
	{
		TCHAR note[20];
		unsigned strSize(0);
		DOBOT_POSITION position;
		m_pCoordinateOperator->GetCoordianteIdAndNote(m_comboBox_pallet_show_coordinate.GetCurSel(), position.coordinate_id, note, strSize);

		m_pCoordinateOperator->ConvertCoordinate(pallet.user_points[i][j], position);

		str.Format(_T("%03u"), i);
		m_listCtrl_pallets.InsertItem(i + j, str);
		str.Format(_T("%03u"), j);
		m_listCtrl_pallets.SetItemText(i + j, 1, str);
		str.Format(_T("%03u"), position.coordinate_id);
		m_listCtrl_pallets.SetItemText(i + j, 2, str);
		str.Format(_T("%s"), note);
		m_listCtrl_pallets.SetItemText(i + j, 3, str);
		str.Format(_T("%f"), position.position.x);
		m_listCtrl_pallets.SetItemText(i + j, 4, str);
		str.Format(_T("%f"), position.position.y);
		m_listCtrl_pallets.SetItemText(i + j, 5, str);
		str.Format(_T("%f"), position.position.z);
		m_listCtrl_pallets.SetItemText(i + j, 6, str);
	}

	UpdateData(FALSE);
}

void CCoordinateApplicationDlg::OnCbnSelchangeComboPalletShowCoordinate()
{
	// TODO: Add your control notification handler code here
	AddPallets2List();
}

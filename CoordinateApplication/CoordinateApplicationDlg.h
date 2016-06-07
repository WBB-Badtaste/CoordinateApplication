
// CoordinateApplicationDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

#include "CoordinateOperator.h"
#include "PalletOperator.h"
#include "afxcmn.h"

// CCoordinateApplicationDlg 对话框
class CCoordinateApplicationDlg : public CDialogEx
{
// 构造
public:
	CCoordinateApplicationDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_COORDINATEAPPLICATION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadioManual();
	afx_msg void OnBnClickedRadioAuto();
	int m_radio_setType;
	double m_trans_x;
	double m_trans_y;
	double m_trans_z;
	double m_ratio;
	double m_rotate_z;
	double m_rotate_y;
	double m_rotate_x;
	double coordinate_point1_x;
	double coordinate_point1_y;
	double coordinate_point1_z;
	double coordinate_point2_x;
	double coordinate_point2_y;
	double coordinate_point2_z;
	double coordinate_point3_x;
	double coordinate_point3_y;
	double coordinate_point3_z;
	CComboBox m_comboBox_base_coordinate;
	CComboBox m_comboBox_change_coordinate;

private:
	void SetCoordinateManualEnable(const BOOL &singal);
	void SetCoordinateAutoEnable(const BOOL &singal);

	void SetPalletManualEnable(const BOOL &singal);
	void SetPalletAutoEnable(const BOOL &singal);
	void SetPalletCopyEnable(const BOOL &singal);

	void AddCoordinate2List(const COORDINATE&);
	void AddPallets2List();
	void UpdateCoordinate();
	void UpadtePallet();
	CCoordinateOperator *m_pCoordinateOperator;
	CPalletOperator *m_pPallerOperator;
public:
	afx_msg void OnBnClickedButtonCreateCoord();
	afx_msg void OnDestroy();
	CComboBox m_combo_pallet_in_coordinate;
	CComboBox m_combo_pallet_base_coordinate;
	CComboBox m_combo_show_pallet;
	afx_msg void OnBnClickedButtonChangeCoord();
	CListCtrl m_listCtrl_coordinate;
	double m_point1_pallet_x;
	double m_point1_pallet_y;
	double m_point1_pallet_z;
	double m_point2_pallet_x;
	double m_point2_pallet_y;
	double m_point2_pallet_z;
	double m_point3_pallet_x;
	double m_point3_pallet_y;
	double m_point3_pallet_z;
	UINT m_x_amount_pallet;
	UINT m_y_amount_pallet;
	afx_msg void OnBnClickedButtonCreatePallet();
	double m_x_lenght_pallet;
	double m_y_lenght_pallet;
	afx_msg void OnCbnSelchangeComboSelPallet();
	CListCtrl m_listCtrl_pallets;
	CComboBox m_comboBox_pallet_show_coordinate;
	afx_msg void OnCbnSelchangeComboPalletShowCoordinate();
	CString m_coordinate_note;
	int m_radio_set_pallet_mode;
	CComboBox m_comboBox_copy_pallet;
	CComboBox m_comboBox_change_pallet;
	afx_msg void OnBnClickedRadioSetPalletAuto();
	afx_msg void OnBnClickedRadioSetPalletManual();
	afx_msg void OnBnClickedRadioSetPalletCopy();
};

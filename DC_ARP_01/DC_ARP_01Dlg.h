
// DC_ARP_01Dlg.h : ��� ����
//

#pragma once
#include "LayerManager.h"	// Added by ClassView
#include "ApplicationLayer.h"	// Added by ClassView
#include "EthernetLayer.h"	// Added by ClassView
#include "IPLayer.h"		// Added by ClassView
#include "NILayer.h"		// Added by ClassView

// CDC_ARP_01Dlg ��ȭ ����
class CDC_ARP_01Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	CDC_ARP_01Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DC_ARP_01_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton5();
};

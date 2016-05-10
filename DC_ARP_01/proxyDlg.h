#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// proxyDlg ��ȭ �����Դϴ�.

class proxyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(proxyDlg)

public:
	proxyDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~proxyDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PROXY_Dlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	
	

	DECLARE_MESSAGE_MAP()
public:
	CComboBox			device;
	CIPAddressCtrl		proxyIPAddr;
	CEdit				proxyEthAddr;
	unsigned char		proxyIPAddrString[4];
	unsigned char		proxyMACAddr[12];
	CString				proxyAddr;
	CString				selectedDevice;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};

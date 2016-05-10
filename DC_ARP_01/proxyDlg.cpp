// proxyDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "DC_ARP_01.h"
#include "proxyDlg.h"
#include "afxdialogex.h"


// proxyDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(proxyDlg, CDialogEx)

proxyDlg::proxyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(proxyDlg::IDD, pParent)
{
	
}

proxyDlg::~proxyDlg()
{
}

void proxyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROXY_INTERFACE_COMBO, device);
	DDX_Control(pDX, IDC_PROXY_IPADDRESS_BOX, proxyIPAddr);
	DDX_Control(pDX, IDC_PROXY_ETHERNET_ADDRESS_EDIT, proxyEthAddr);
	DDX_Text(pDX, IDC_PROXY_ETHERNET_ADDRESS_EDIT, proxyAddr);
}


BEGIN_MESSAGE_MAP(proxyDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &proxyDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &proxyDlg::OnBnClickedOk)
END_MESSAGE_MAP()


BOOL proxyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	this->device.AddString("interface");

	return TRUE;
}

// proxyDlg �޽��� ó�����Դϴ�.


void proxyDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}


void proxyDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData( TRUE );
	int n = device.GetCurSel();
	device.GetLBText(n,selectedDevice);
	proxyIPAddr.GetAddress(proxyIPAddrString[0],proxyIPAddrString[1],proxyIPAddrString[2],proxyIPAddrString[3]);
	sscanf(proxyAddr, "%02x%02x%02x%02x%02x%02x", &proxyMACAddr[0],&proxyMACAddr[1],&proxyMACAddr[2],&proxyMACAddr[3],&proxyMACAddr[4],&proxyMACAddr[5]);
	
	UpdateData( FALSE );

	CDialogEx::OnOK();
}

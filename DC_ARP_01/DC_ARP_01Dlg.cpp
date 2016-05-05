
// DC_ARP_01Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "DC_ARP_01.h"
#include "DC_ARP_01Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDC_ARP_01Dlg ��ȭ ����




CDC_ARP_01Dlg::CDC_ARP_01Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDC_ARP_01Dlg::IDD, pParent),
	CBaseLayer( "ArpDlg" ),
	m_bSendReady(FALSE)
{

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_LayerMgr.AddLayer( this ) ;
	m_LayerMgr.AddLayer( new CNILayer( "NI" ) ) ;
	m_LayerMgr.AddLayer( new CEthernetLayer( "Ethernet" ) ) ;
	m_LayerMgr.AddLayer( new CARPLayer( "ARP" ) );
	m_LayerMgr.AddLayer( new CIPLayer( "IP" ) );
	m_LayerMgr.AddLayer( new CApplicationLayer( "APP" ) ) ;

	m_LayerMgr.ConnectLayers("NI ( *Ethernet ( *ARP ( *IP ( *APP ) ) ) )");

	m_APP = (CApplicationLayer *)m_LayerMgr.GetLayer("APP");
	m_IP = (CIPLayer *)m_LayerMgr.GetLayer("IP");
	m_ARP = (CARPLayer *)m_LayerMgr.GetLayer("ARP");
	m_ETH = (CEthernetLayer *)m_LayerMgr.GetLayer("Ethernet");
	m_NI = (CNILayer *)m_LayerMgr.GetLayer("NI");
}

void CDC_ARP_01Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ARP_CACHE_TABLE_LIST, m_ArpTable);
	DDX_Control(pDX, IDC_ARP_SEND_IP, m_unDstIPAddr);
	DDX_Control(pDX, IDC_NICARD_COMBO, m_ComboEnetName);
	DDX_Control(pDX, IDC_OWN_IP_ADDRESS, m_unSrcIPAddr);
	DDX_Control(pDX, IDC_GRATUITOUS_ADDRESS_BOX, m_unGratuitousAddresss);
	DDX_Control(pDX, IDC_PROXY_ARP_ENTRY_LIST, m_proxyARPEntry);
}

BEGIN_MESSAGE_MAP(CDC_ARP_01Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_ARP_ITEM_DELETE_BUTTON, &CDC_ARP_01Dlg::OnBnClickedArpItemDeleteButton)
	ON_BN_CLICKED(IDC_ARP_ALL_DELETE_BUTTON, &CDC_ARP_01Dlg::OnBnClickedArpAllDeleteButton)
	ON_BN_CLICKED(IDC_ARP_SEND_BUTTON, &CDC_ARP_01Dlg::OnBnClickedArpSendButton)
	ON_BN_CLICKED(IDC_WINDOW_OK_BUTTON, &CDC_ARP_01Dlg::OnBnClickedWindowOkButton)
	ON_BN_CLICKED(IDC_ARP_SETTING_BUTTON, &CDC_ARP_01Dlg::OnBnClickedArpSettingButton)
	ON_BN_CLICKED(IDC_GRATUITOUS_SEND_BUTTON, &CDC_ARP_01Dlg::OnBnClickedGratuitousSendButton)
	ON_CBN_SELCHANGE(IDC_NICARD_COMBO, &CDC_ARP_01Dlg::OnCbnSelchangeNicardCombo)

	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDC_ARP_01Dlg �޽��� ó����

BOOL CDC_ARP_01Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetRegstryMessage( ) ;
	SetDlgState(IPC_INITIALIZING);
	SetDlgState(CFT_COMBO_SET);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CDC_ARP_01Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ( nID == SC_CLOSE )
	{
		if ( MessageBox( "Are you sure ?", 
			"Question", 
			MB_YESNO | MB_ICONQUESTION ) 
			== IDNO )
			return ;
		else EndofProcess( ) ;
	}

	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CDC_ARP_01Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CDC_ARP_01Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDC_ARP_01Dlg::OnSendMessage()  
{
	// TODO: Add your control notification handler code here
	UpdateData( TRUE ) ;

	SetTimer(1,3000,NULL);

	SendData( ) ;

	UpdateData( FALSE ) ;
}
void CDC_ARP_01Dlg::OnButtonAddrSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData( TRUE ) ;
	unsigned char src_ip[4];
	unsigned char dst_ip[4];
	unsigned char src_mac[12];
	unsigned char dst_mac[12];


	if ( !m_unDstEnetAddr || 
		!m_unSrcEnetAddr  )
	{
		MessageBox( "�ּҸ� ���� �����߻�", 
			"���", 
			MB_OK | MB_ICONSTOP ) ;

		return ;
	}

	if ( m_bSendReady ){
		SetDlgState( IPC_ADDR_RESET ) ;
		SetDlgState( IPC_INITIALIZING ) ;
	}
	else{
		m_unSrcIPAddr.GetAddress(src_ip[0],src_ip[1],src_ip[2],src_ip[3]);
		m_unDstIPAddr.GetAddress(dst_ip[0],dst_ip[1],dst_ip[2],dst_ip[3]);

		m_IP->SetSrcIPAddress(src_ip);
		m_IP->SetDstIPAddress(dst_ip);

		sscanf(m_unSrcEnetAddr, "%02x%02x%02x%02x%02x%02x", &src_mac[0],&src_mac[1],&src_mac[2],&src_mac[3],&src_mac[4],&src_mac[5]);
		sscanf(m_unDstEnetAddr, "%02x%02x%02x%02x%02x%02x", &dst_mac[0],&dst_mac[1],&dst_mac[2],&dst_mac[3],&dst_mac[4],&dst_mac[5]);

		m_ETH->SetEnetSrcAddress(src_mac);
		m_ETH->SetEnetDstAddress(dst_mac);

		int nIndex = m_ComboEnetName.GetCurSel();
		m_NI->SetAdapterNumber(nIndex);

		m_NI->PacketStartDriver();

		SetDlgState( IPC_ADDR_SET ) ;
		SetDlgState( IPC_READYTOSEND ) ;		
	}

	m_bSendReady = !m_bSendReady ;
}

void CDC_ARP_01Dlg::SendData()
{
	CString MsgHeader ; 
	if ( m_unDstEnetAddr == (unsigned int)0xff )
		MsgHeader.Format( "[%s:BROADCAST] ", m_unSrcEnetAddr ) ;
	else
		MsgHeader.Format( "[%s:%s] ", m_unSrcEnetAddr, m_unDstEnetAddr ) ;
	MsgHeader.Format();

	int nlength = m_stMessage.GetLength();
	unsigned char* ppayload = new unsigned char[nlength+1];
	memcpy(ppayload,(unsigned char*)(LPCTSTR)m_stMessage,nlength);
	ppayload[nlength] = '\0';

	m_APP->Send(ppayload,m_stMessage.GetLength());
}

BOOL CDC_ARP_01Dlg::Receive(unsigned char *ppayload)
{
	CString Msg;
	int len_ppayload = strlen((char *)ppayload); 

	unsigned char *GetBuff = (unsigned char *)malloc(len_ppayload);
	memset(GetBuff,0,len_ppayload);
	memcpy(GetBuff,ppayload,len_ppayload);
	GetBuff[len_ppayload] = '\0';
	
	if( m_unSrcEnetAddr == (unsigned int)0xff )
		Msg.Format("[%s:BROADCAST] %s",m_unDstEnetAddr,(char *)GetBuff);
	else
		Msg.Format("[%s:%s] %s",m_unDstEnetAddr,m_unSrcEnetAddr,(char *)GetBuff);

	KillTimer(1);
	return TRUE ;
}

void CDC_ARP_01Dlg::SetDlgState(int state) // ���̾�α� �ʱ�ȭ �κ�
{
	UpdateData( TRUE ) ;
	int i;
	CString device_description;

	CButton*			pARPItemDeleteButton = (CButton*) GetDlgItem( IDC_ARP_ITEM_DELETE_BUTTON ) ;
	CButton*			pARPAllDeleteButton = (CButton*) GetDlgItem( IDC_ARP_ALL_DELETE_BUTTON ) ;
	CButton*			pWindowOkButton = (CButton*) GetDlgItem( IDC_WINDOW_OK_BUTTON ) ;
	CButton*			pWindowCloseButton = (CButton*) GetDlgItem( IDC_WINDOW_CLOSE_BUTTON ) ;
	CButton*			pARPSendButton = (CButton*) GetDlgItem( IDC_ARP_SEND_BUTTON ) ;
	CButton*			pProxyDeleteButton = (CButton*) GetDlgItem( IDC_PROXY_DELETE_BUTTON ) ;
	CButton*			pProxyAddButton = (CButton*) GetDlgItem( IDC_PROXY_ADD_BUTTON  ) ;
	CButton*			pGratuitousSendButton = (CButton*) GetDlgItem( IDC_GRATUITOUS_SEND_BUTTON ) ;
	CButton*			pARPSettingButton = (CButton*) GetDlgItem( IDC_ARP_SETTING_BUTTON ) ;

	CIPAddressCtrl*		pARPSendIP = (CIPAddressCtrl*) GetDlgItem( IDC_ARP_SEND_IP );
	CIPAddressCtrl*		pOWNIPAddress = (CIPAddressCtrl*) GetDlgItem( IDC_OWN_IP_ADDRESS );

	CEdit*				pGratuitousARPAddress = (CEdit*) GetDlgItem( IDC_GRATUITOUS_ADDRESS_BOX ) ;

	CComboBox*			pEnetNameCombo = (CComboBox*)GetDlgItem( IDC_NICARD_COMBO );

	switch( state )
	{
	case IPC_INITIALIZING : // ù ȭ�� ����
		pARPAllDeleteButton->EnableWindow( FALSE ) ;
		pARPItemDeleteButton->EnableWindow( FALSE ) ;
		pWindowOkButton->EnableWindow( FALSE );
		pARPSendButton->EnableWindow( FALSE );
		pProxyDeleteButton->EnableWindow( FALSE );
		pProxyAddButton->EnableWindow( FALSE );
		pGratuitousSendButton->EnableWindow( FALSE );
		pARPSettingButton->EnableWindow( FALSE );
		pARPSendIP->EnableWindow( FALSE );
		pOWNIPAddress->EnableWindow( FALSE );
		pGratuitousARPAddress->EnableWindow ( FALSE );
		m_proxyARPEntry.EnableWindow( FALSE );
		m_ArpTable.EnableWindow( FALSE ) ;
		break ;
	case IPC_READYTOSEND : // Send(S)��ư�� ������ �� ����
		pARPAllDeleteButton->EnableWindow( TRUE ) ;
		pARPItemDeleteButton->EnableWindow( TRUE ) ;
		pWindowOkButton->EnableWindow( TRUE );
		pARPSendButton->EnableWindow( TRUE );
		pProxyDeleteButton->EnableWindow( TRUE );
		pProxyAddButton->EnableWindow( TRUE );
		pGratuitousSendButton->EnableWindow( TRUE );
		pARPSettingButton->EnableWindow( TRUE );
		pARPSendIP->EnableWindow( TRUE );
		pOWNIPAddress->EnableWindow( TRUE );
		pGratuitousARPAddress->EnableWindow ( TRUE );
		m_proxyARPEntry.EnableWindow( TRUE );
		m_ArpTable.EnableWindow( TRUE ) ;
		break ;
	case IPC_WAITFORACK :	break ;
	case IPC_ERROR :		break ;
	case IPC_ADDR_SET :	// Setting ��ư�� ������ ��
		pARPSettingButton->SetWindowText( "Reset" ) ; 
		pARPSendIP->EnableWindow( FALSE ) ;
		pOWNIPAddress->EnableWindow( FALSE ) ;
		pEnetNameCombo->EnableWindow( FALSE );
		m_NI->m_thrdSwitch = TRUE;
		break ;
	case IPC_ADDR_RESET : // Reset ��ư�� ������ ��
		pARPSettingButton->SetWindowText( "Setting" ) ; 
		pSrcEdit->EnableWindow( TRUE ) ;
		if ( !pChkButton->GetCheck( ) )
			pDstEdit->EnableWindow( TRUE ) ;
		pChkButton->EnableWindow( TRUE ) ;
		pSrcIPEdit->EnableWindow( TRUE );
		pDstIPEdit->EnableWindow( TRUE );
		pEnetNameCombo->EnableWindow( TRUE );
		m_NI->m_thrdSwitch = FALSE;
		break ;
	case CFT_COMBO_SET :
		for(i=0;i<NI_COUNT_NIC;i++){
			if(!m_NI->GetAdapterObject(i))
				break;
			device_description = m_NI->GetAdapterObject(i)->description;
			device_description.Trim();
			pEnetNameCombo->AddString(device_description);
			pEnetNameCombo->SetCurSel(0);

			PPACKET_OID_DATA OidData;
			OidData = (PPACKET_OID_DATA)malloc(sizeof(PACKET_OID_DATA));
			OidData->Oid = 0x01010101;
			OidData->Length = 6;

			LPADAPTER adapter = PacketOpenAdapter(m_NI->GetAdapterObject(0)->name);
			PacketRequest(adapter, FALSE, OidData);

			m_unSrcEnetAddr.Format("%.2X%.2X%.2X%.2X%.2X%.2X",OidData->Data[0],OidData->Data[1],OidData->Data[2],OidData->Data[3],OidData->Data[4],OidData->Data[5]) ;
		}
		break;
	}

	UpdateData( FALSE ) ;
}
void CDC_ARP_01Dlg::OnBnClickedArpItemDeleteButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int index = m_ArpTable.GetCurSel();
	if(index != LB_ERR) {
		m_ArpTable.DeleteString(index);
	}
}


void CDC_ARP_01Dlg::OnBnClickedArpAllDeleteButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_ArpTable.ResetContent();
}


void CDC_ARP_01Dlg::OnBnClickedArpSendButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SendData();
}


void CDC_ARP_01Dlg::OnBnClickedWindowOkButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	AfxGetMainWnd()->PostMessage(WM_COMMAND,ID_APP_EXIT,0);
}


void CDC_ARP_01Dlg::OnBnClickedArpSettingButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CDC_ARP_01Dlg::OnBnClickedGratuitousSendButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CDC_ARP_01Dlg::OnCbnSelchangeNicardCombo()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

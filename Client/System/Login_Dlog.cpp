// Login_Dlog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LINK_DATABASE.h"
#include "Login_Dlog.h"
#include "afxdialogex.h"
#include "CvvImage.h"
#include"opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <imgproc/imgproc_c.h>
#include <afxwin.h>
#include <atlconv.h>
#include <string>
#include <system_error>
using namespace  cv;

#define SERIAL_RECV_BUFFER 1024
#define SERIAL_SEND_BUFFER 1024
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HDC hDC;
CDC *pDC = NULL;
CvvImage m_CvvImage;
cv::VideoCapture MyCapture;
cv::Mat Matframe;
cv::Mat MatResult;
cv::Mat MatConvert;
cv::Mat MatFluse;
CvMemStorage* storage = NULL;
CvPoint pt[4];
CWnd *pwnd = NULL;
OVERLAPPED m_ov;
// Login_Dlog �Ի���

IMPLEMENT_DYNAMIC(Login_Dlog, CDialogEx)

Login_Dlog::Login_Dlog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, nMyRadioButton(1)
{
	nMySign = 0;
	nHeight = 0;
	nWidth = 0;
	CString strGetport = NULL;
	CString strGetFrequence = NULL;
	CString strGetCorrect = NULL;
	CString strGetData = NULL;
	CString strGetStop = NULL;
	CString strComProtocol = NULL;
	flage = false;
	PortSendSign = 0;
}

Login_Dlog::~Login_Dlog()
{
}

void Login_Dlog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, CameraButton);
	DDX_Control(pDX, IDC_EDIT1, CarHeight);
	DDX_Control(pDX, IDC_EDIT2, CarWidth);
	DDX_Control(pDX, IDC_COMBO1, Cport);
	DDX_Control(pDX, IDC_COMBO2, Cfrequence);
	DDX_Control(pDX, IDC_COMBO3, Ccorrect);
	DDX_Control(pDX, IDC_COMBO4, Cdata);
	DDX_Control(pDX, IDC_COMBO5, Cstop);
	DDX_Control(pDX, IDC_BUTTON2, CPortButton);
	DDX_Control(pDX, IDC_BUTTON3, CPortSendButton);
	DDX_Control(pDX, IDC_EDIT4, CPortState);
	DDX_Control(pDX, IDC_EDIT5, CPortTX);
	DDX_Control(pDX, IDC_EDIT6, CPortRX);
	DDX_Control(pDX, IDC_EDIT3, CSendText);
	DDX_Control(pDX, IDC_RADIO7, CMyRadioButton);
	DDX_Radio(pDX, IDC_RADIO7, nMyRadioButton);
}


BEGIN_MESSAGE_MAP(Login_Dlog, CDialogEx)
	ON_BN_CLICKED(IDOK, &Login_Dlog::OnBnClickedOk)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &Login_Dlog::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT1, &Login_Dlog::OnEnChangeEdit1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &Login_Dlog::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON2, &Login_Dlog::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Login_Dlog::OnBnClickedButton3)
	
END_MESSAGE_MAP()


// Login_Dlog ��Ϣ�������


void Login_Dlog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


HBRUSH Login_Dlog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	return hbr;
}


void Login_Dlog::OnBnClickedButton1()
{
	if (nMySign == 0)
	{
		
		IplImage *frame = NULL;
		IplImage*Img=NULL;
		IplImage ** Cpy = &Img;
		MyCapture.open(1);
		storage = cvCreateMemStorage(0);
		//MyCapture.open("E:\\��\\��.avi");
		if (MyCapture.isOpened())
		{
			nMySign = 1;

			CameraButton.SetWindowTextW(_T("�ر�����ͷ"));

			if (!MyCapture.read(Matframe))//�Ƿ��ȡ��һ֡ͼ������
			{
				return;
			}
			else
			{
				frame = &IplImage(Matframe);  //mat ����ת����IplImage	
				drawSquares(Cpy,frame, findSquares(frame, storage)); 
				//Canny(Matframe, MatResult, 50, 150,3);//���ӱ߿���ȡ
				//frame = &IplImage(MatResult);
				/****************************ͼ���ֵ��***************************/

				/*threshold(Matframe, MatResult, 170, 255, CV_THRESH_BINARY);
				frame = &IplImage(MatResult);  //mat ����ת����IplImage

				/****************************ͼ��Ҷ�ת��***************************/

				/*int channel = 1;//image->nChannels;
				IplImage  *result;
				int depth = frame->depth;
				CvSize sz;
				sz.width = frame->width;//���
				sz.height = frame->height;//�߶�
				result = cvCreateImage(sz, depth, channel);//����image
				cvCvtColor(frame, result, CV_BGR2GRAY);//ת���ɻҶ�ͼ */


				m_CvvImage.CopyOf(Img, 1);  //���Ƹ�֡ͼ�� 
				m_CvvImage.DrawToHDC(hDC, &rect);
				m_CvvImage.Destroy();
				cvReleaseImage(&Img);
				cvReleaseImage(Cpy);
				waitKey(7);
				SetTimer(1, 3, NULL);
				SetTimer(2, 1000, NULL);
			}
		}
		else
		{
			AfxMessageBox(_T("����ͷ��ʼ��ʧ��!!!\n��������ͷ�Ƿ�����"));
		}
	}
	else
	{
		CameraButton.SetWindowTextW(_T("������ͷ"));
		MyCapture.release();
		KillTimer(1);
		KillTimer(2);
		CarHeight.SetWindowTextW(_T("0"));
		CarWidth.SetWindowTextW(_T("0"));
		IplImage *image = NULL;
		if (image) cvReleaseImage(&image);
		image = cvLoadImage("C:\\Users\\jun\\Desktop\\6.jpg", 1); //��ʾͼƬ
		m_CvvImage.CopyOf(image, 3);
		m_CvvImage.DrawToHDC(hDC, &rect);
		m_CvvImage.Destroy();
		cvReleaseImage(&image);
		nMySign = 0;
	}
}


void Login_Dlog::OnTimer(UINT_PTR nIDEvent)
{
	if (1==nIDEvent)
	{
		IplImage *frame = NULL;
		IplImage*Img = NULL;
		IplImage ** Cpy = &Img;//��ָֹ�뷵���޷��ͷ��ڴ� ���Ӷ���ӿ���ָ���ָ�������ͷ��ڴ�
		storage = cvCreateMemStorage(0);
		if (!MyCapture.read(Matframe))
		{
			return;
		}
		else
		{
			frame = &IplImage(Matframe);  //mat ����ת����IplImage
			drawSquares(Cpy, frame, findSquares(frame, storage));
			//Canny(Matframe, MatResult, 50, 150,3);//50,150
			//frame = &IplImage(MatResult);

			/*threshold(Matframe, MatResult, 170, 255, CV_THRESH_BINARY);
			frame = &IplImage(MatResult);  //mat ����ת����IplImage
			IplImage  *result;
			int channel = 1;//image->nChannels;
			int depth = frame->depth;
			CvSize sz;
			sz.width = frame->width;//���
			sz.height = frame->height;//�߶�
			result = cvCreateImage(sz, depth, channel);//����image
			cvCvtColor(frame, result, CV_BGR2GRAY);//ת���ɻҶ�ͼ */

			m_CvvImage.CopyOf(Img, 1);  //���Ƹ�֡ͼ�� 
			m_CvvImage.DrawToHDC(hDC, &rect);
			m_CvvImage.Destroy();
			cvReleaseImage(&Img);
			cvReleaseImage(Cpy);
			waitKey(7);
		}
	}
	if (2==nIDEvent)
	{
		CString StrToIntHeight;
		CString StrToIntWidth;
		StrToIntHeight.Format(_T("%d"),nHeight);
		CarHeight.SetWindowTextW(StrToIntHeight);
		StrToIntWidth.Format(_T("%d"), nWidth);
		CarWidth.SetWindowTextW(StrToIntWidth);
	}
	if (3 == nIDEvent)
	{
	}
}


BOOL Login_Dlog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CPortSendButton.EnableWindow(0);
	CString strFrequence = NULL;
	if (!flage)
	{
		CPortState.SetWindowTextW(_T("����״̬:�ر�"));
	}
	CPortTX.SetWindowTextW(_T("TX"));
	CPortRX.SetWindowTextW(_T("RX"));
	//�����ʳ�ʼ��
	int nFrequence =600;
	for (int i=0; i <7;i++)
	{
		strFrequence.Format(_T("%d"), nFrequence);
		Cfrequence.AddString(strFrequence);
		nFrequence *= 2;
	}
	Cfrequence.AddString(_T("57600"));
	Cfrequence.AddString(_T("115200"));
	Cfrequence.SetCurSel(0);
	//�˿ڳ�ʼ��
	CString strPort = NULL;
	for (int j = 1; j <=15; j++)
	{
		strPort.Format(_T("COM%d"),j);
		Cport.AddString(strPort);
	}
	Cport.SetCurSel(0);

	//У��λ��ʼ��
	Ccorrect.AddString(_T("��NONE"));
	Ccorrect.AddString(_T("��ODD"));
	Ccorrect.AddString(_T("żEVEN"));
	Ccorrect.SetCurSel(0);
	//����λ��ʼ��
	CString strData = NULL;
	int nData = 5;
	for (int k = 0; k <=4; k++)
	{
		strData.Format(_T("%d"),nData);
		Cdata.AddString(strData);
		nData += 1;
	}
	Cdata.SetCurSel(0);

	//ֹͣλ��ʼ��
	Cstop.AddString(_T("1"));
	Cstop.AddString(_T("1.5"));
	Cstop.AddString(_T("2"));
	Cstop.SetCurSel(0);
	//��ʼ��������
	CarHeight.SetWindowTextW(_T("0"));
	CarWidth.SetWindowTextW(_T("0"));
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	pwnd = GetDlgItem(IDC_STA);//����IDֵ��ȡ�Ի������Ӵ���ؼ�����ָ��,
	pDC = pwnd->GetDC();//ȡ�ÿͻ�����ʾ�豸dc
	hDC = pDC->GetSafeHdc();
	pwnd->GetClientRect(&rect);//�õ���ʾ���ߴ�

	
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

//////////////////////////////////////////////////////////////////
//�������ܣ�����������COS��=������֮��/������ģ�ĳ˻��������߶μн�
//���룺   �߶�3��������pt1,pt2,pt0,���һ������Ϊ������
//�����   �߶μнǣ���λΪ�Ƕ�
//////////////////////////////////////////////////////////////////
double Login_Dlog::angle(CvPoint* pt1, CvPoint* pt2, CvPoint* pt0)
{
	double dx1 = pt1->x - pt0->x;
	double dy1 = pt1->y - pt0->y;
	double dx2 = pt2->x - pt0->x;
	double dy2 = pt2->y - pt0->y;
	double angle_line = (dx1*dx2 + dy1*dy2) / sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);//����ֵ
	return angle_line;
}

//////////////////////////////////////////////////////////////////
//�������ܣ����ö���μ�⣬ͨ��Լ������Ѱ�Ҿ���
//���룺   img ԭͼ��
//          storage �洢
//          minarea��maxarea �����ε���С/������
//          minangle,maxangle �����α߼нǷ�Χ����λΪ�Ƕ�
//�����   ��������
//////////////////////////////////////////////////////////////////
CvSeq* Login_Dlog::findSquares(IplImage* img, CvMemStorage* storage)
{
		CvSeq* contours = NULL;//��Ե
		int N = 6;  //��ֵ�ּ�
		CvSize sz = cvSize(img->width & -2, img->height & -2);
		IplImage* timg = cvCloneImage(img);//����һ��img
		IplImage* gray = cvCreateImage(sz, 8, 1); //img�Ҷ�ͼ
		IplImage* pyr = cvCreateImage(cvSize(sz.width / 2, sz.height / 2), 8, 3);  //�������˲�3ͨ��ͼ���м����
		IplImage* tgray = cvCreateImage(sz, 8, 1);
		CvSeq* result;
		double s, t;
		int i;
		CvSeq* squares = cvCreateSeq(0, sizeof(CvSeq), sizeof(CvPoint), storage);
		cvSetImageROI(timg, cvRect(0, 0, sz.width, sz.height));
		//�������˲� 
		cvPyrDown(timg, pyr, 7);
		cvPyrUp(pyr, timg, 7);
		//��3��ͨ����Ѱ�Ҿ��� 
		for (int c = 0; c < 3; c++) //��3��ͨ���ֱ���д��� 
		{
			cvSetImageCOI(timg, c + 1);
			cvCopy(timg, tgray, 0);  //���ν�BGRͨ������tgray         
			for (int l = 0; l < N; l++)
			{
				//��ͬ��ֵ�¶�ֵ��
				if (l == 0)
				{
					cvCanny(tgray, gray, 0, 50, 5);
					cvDilate(gray, gray, 0, 1);
				}
				else
				{
					cvThreshold(tgray, gray, (l + 1) * 255 / N, 255, CV_THRESH_BINARY);
				}

				cvFindContours(gray, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
				while (contours)
				{ //����αƽ�             
					result = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0);
					//�����͹�ı��β�������ڷ�Χ��
					if (result->total == 4 && fabs(cvContourArea(result, CV_WHOLE_SEQ)) > 1000 && cvCheckContourConvexity(result))
					{
						s = 0;
						//�ж�ÿһ����
						for (i = 0; i < 5; i++)
						{
							if (i >= 2)
							{   //�Ƕ�            
								t = fabs(angle((CvPoint*)cvGetSeqElem(result, i), (CvPoint*)cvGetSeqElem(result, i - 2), (CvPoint*)cvGetSeqElem(result, i - 1)));
								s = s > t ? s : t;
							}
						}
						//�����SΪֱ���ж����� ��λΪ�Ƕ�
						if (s < 0.3)
							for (int i = 0; i < 4; i++)
								cvSeqPush(squares, (CvPoint*)cvGetSeqElem(result, i));
					}
					contours = contours->h_next;
				}
			}
		}
		cvReleaseImage(&gray);
		cvReleaseImage(&pyr);
		cvReleaseImage(&tgray);
		cvReleaseImage(&timg);
	
	return squares;
}


//////////////////////////////////////////////////////////////////
//�������ܣ��������о���
//���룺   img ԭͼ��
//          squares ��������
//          wndname ��������
//�����   ͼ���б�Ǿ���
//////////////////////////////////////////////////////////////////
void Login_Dlog::drawSquares(IplImage** cpy,IplImage* img, CvSeq* squares)
{

	CvSeqReader reader;
	 *cpy = cvCloneImage(img);
	int i;
	cvStartReadSeq(squares, &reader, 0);
	for (i = 0; i < squares->total; i += 4)
	{
		CvPoint* rect = pt;
		int count = 4;
		memcpy(pt, reader.ptr, squares->elem_size);
		CV_NEXT_SEQ_ELEM(squares->elem_size, reader);
		memcpy(pt + 1, reader.ptr, squares->elem_size);
		CV_NEXT_SEQ_ELEM(squares->elem_size, reader);
		memcpy(pt + 2, reader.ptr, squares->elem_size);
		CV_NEXT_SEQ_ELEM(squares->elem_size, reader);
		memcpy(pt + 3, reader.ptr, squares->elem_size);
		CV_NEXT_SEQ_ELEM(squares->elem_size, reader);
		//cvPolyLine( cpy, &rect, &count, 1, 1, CV_RGB(255,255,0), 3, CV_AA, 0 );
		//���˵���Ե���
		if (rect->x < 30 || rect->y < 30 || rect->x > 610 || rect->y > 450)
		{
			continue;
		}
		nWidth = pt[1].x - pt[0].x;//������
		nHeight = pt[3].y - pt[0].y;//������
		if (nWidth < 0)
		{
			nWidth = 0 - nWidth; //��������������
		}
		if (nHeight < 0)
		{
			nHeight = 0 - nHeight;//��������������
		}
		cvPolyLine(*cpy, &rect, &count, 1, 1, CV_RGB(255, 255, 0), 3, CV_AA, 0);//��ץ������ͼ����������������
	}
	cvReleaseMemStorage(&squares->storage);	
}


void Login_Dlog::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void Login_Dlog::OnCbnSelchangeCombo2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void Login_Dlog::OnBnClickedButton2()
{
	if (!flage)
	{
		Cport.GetLBText(Cport.GetCurSel(), strGetport);

		Cfrequence.GetLBText(Cfrequence.GetCurSel(), strGetFrequence);

		Ccorrect.GetLBText(Ccorrect.GetCurSel(), strGetCorrect);
		CString CorrectDate = strGetCorrect;

		if (strGetCorrect == _T("��NONE"))

		{
			strGetCorrect = _T("0");
		}
		else if (strGetCorrect == _T("��ODD"))
		{
			strGetCorrect = _T("1");
		}
		else if (strGetCorrect == _T("żEVEN"))
		{
			strGetCorrect = _T("2");
		}

		Cdata.GetLBText(Cdata.GetCurSel(), strGetData);

		Cstop.GetLBText(Cstop.GetCurSel(), strGetStop);

		if (strGetStop == _T("1"))
		{
			strGetStop = _T("0");
		}
		else if (strGetStop == _T("1.5"))
		{
			strGetStop = _T("1");
		}
		else if (strGetStop == _T("2"))
		{
			strGetStop = _T("2");
		}

		BYTE BytePortStop[10];

		BYTE BytePortCorrect[10];

		BYTE BytePortData[10];

		DWORD IntPortFrequence;

		USES_CONVERSION;

		String Portbaudrate = W2CA((LPCWSTR)strGetFrequence);

		IntPortFrequence = (DWORD)atoi(Portbaudrate.c_str());

		strcpy((char*)BytePortStop, (LPSTR)(LPCTSTR)strGetStop);

		strcpy((char*)BytePortCorrect, (LPSTR)(LPCTSTR)strGetCorrect);

		strcpy((char*)BytePortData, (LPSTR)(LPCTSTR)strGetData);

		CSerialOpen(strGetport, IntPortFrequence, BytePortData[0], BytePortCorrect[0], BytePortStop[0]);

		if (flage)//flagλȫ�ֱ���
		{
			//nMyRadioButton = 1;
			CMyRadioButton.SetCheck(nMyRadioButton);
			CPortButton.SetWindowTextW(_T("�رն˿�"));
			CPortState.SetWindowTextW(_T("����״̬:��   �˿ںţ�")+strGetport+_T("   �����ʣ�")+strGetFrequence+_T("   У��λ��")+ CorrectDate +_T("   ����λ��")+strGetData+_T("   ֹͣλ��")+strGetStop);
			CPortSendButton.EnableWindow(TRUE);
		}
	}
	else
	{
		//nMyRadioButton = 0;
		CMyRadioButton.SetCheck(NULL);
		CPortButton.SetWindowTextW(_T("�򿪶˿�"));
		CloseHandle(hCom);
		SetCommMask(hCom, 0);//��ֹ���ж˿������¼�
		EscapeCommFunction(hCom, CLRDTR);//��������ն˾����ź�
		//����ͨ����Դ����������뻺�����ַ�����ֹ��ͨ����Դ�Ϲ���Ķ���д�ٲ���
		PurgeComm(hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
		flage = false;
	    CPortState.SetWindowTextW(_T("����״̬:�ر�"));
		CPortSendButton.EnableWindow(FALSE);
		hCom = NULL;
	}
}

HANDLE Login_Dlog:: CSerialOpen(LPCTSTR PortCOMx, DWORD Portbaudrate, BYTE PortByteSize,BYTE PortParity, BYTE PortStopBits)
{

	
	BOOL state;
	DCB SerialDCB;

	//��
	hCom = CreateFile(
		PortCOMx,              //�򿪴���   ͨ������CreateFile�򿪴���,���һ���������Ǵ��ڵ��߼��˿���,���á�COMX����ʾ��,����X��1~N������,��X����10ʱ,��ʱ������޷��򿪵�����,���߼��˿����ĳ�"\\\\.\\COM
		GENERIC_READ | GENERIC_WRITE,  //�������д����
		0,  //��ռ��ʽ
		NULL,
		OPEN_EXISTING, //�򿪴��ڵĴ���, ������OPEN_EXISTING, �ļ�������CREATE_NEW, ���ڲ��ܴ���
		 0,//FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, //�첽��ʽ��
		NULL
	);

	if (hCom == INVALID_HANDLE_VALUE) 

	{//��ʧ��
		MessageBox(_T("���棺���ڴ�ʧ��!!!"),_T("��ܰ��ʾ"));
		return INVALID_HANDLE_VALUE;
	}
	else
	{
		//AfxMessageBox(_T("���ڴ򿪳ɹ�\n�˿ںţ�")+CString(PortCOMx));
		flage = true;
	}
	//����״̬����
	state = GetCommState(hCom, &SerialDCB);
	SerialDCB.fBinary =1;
	SerialDCB.fParity = 1;
	SerialDCB.BaudRate = Portbaudrate; /* Baudrate at which running, CBR_115200 */  //������
	SerialDCB.ByteSize = PortByteSize-48;        /* Number of bits/byte, 4-8 */   //����λ
	SerialDCB.Parity = PortParity-48;    /* 0-4=None,Odd,Even,Mark,Space */  //У��λ NOPARITY
	SerialDCB.StopBits = PortStopBits-48; /* 0,1,2 = 1, 1.5, 2 */  //ֹͣλ ONESTOPBIT
	state = SetCommState(hCom, &SerialDCB);
	if (!state) 
	{
		int error = GetLastError();
		CloseHandle(hCom);
		return INVALID_HANDLE_VALUE;
	}
	//���û�������С
	state = SetupComm(hCom, SERIAL_RECV_BUFFER, SERIAL_SEND_BUFFER);
	if (!state)
	{
		CloseHandle(hCom);
		return INVALID_HANDLE_VALUE;
	}
	PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_RXABORT); //�����ж�д������������������ | ������������ | �����ж϶�������������뻺����|������뻺����
	return hCom;
}

void Login_Dlog::OnBnClickedButton3()
{
	/*if (PortSendSign==0)
	{
		//CPortSendButton.SetWindowTextW(_T("ֹͣ����"));
		//CString strGetSendText = NULL;
		//unsigned char* cSendBuffer = NULL;
		//AfxMessageBox(strGetSendText);
		//SetTimer(3, 1000, NULL);
		PortSendSign = 1;

	
	}
	else
	{
		CPortSendButton.SetWindowTextW(_T("��ʼ����"));
		KillTimer(3);
		PortSendSign=0;
	}*/

	unsigned char IntToCharCarHeight[255] = { 0 };
	unsigned char IntToCharCarWidth[100] = { 0 };
	sprintf((char*)IntToCharCarHeight, "%d", nHeight);
	strcat((char*)IntToCharCarHeight, "W");//��ӱ�־�ַ� ������λ�����ֳ���ߴ�
	sprintf((char*)IntToCharCarWidth, "%d", nWidth);
	//������Ӣ�Ŀ��ֽ�ת���ֽڷ��͸����ڻ�������ݶ�ʧ�����Լ�д�ײ����
	unsigned char *p = IntToCharCarHeight;
	unsigned char *q = IntToCharCarWidth;
	while (*p)
	{
		p++;
	}
	while (*q)
	{
		*p++ = *q++;
	}
	*p = '\0';

	BOOL bResult;
	DWORD BytesSent = 0;
	bResult = WriteFile(hCom, IntToCharCarHeight, sizeof(IntToCharCarHeight), &BytesSent, &m_ov);
	if (bResult)
	{
		CString strHeight;
		CString strWidth;
		CString TX;
		strHeight.Format(_T("%d"), nHeight);
		strWidth.Format(_T("%d"), nWidth);
		TX = _T("����")+strHeight + _T("  ��")+strWidth;
		CPortTX.SetWindowTextW(_T("TX:") + TX);
	}

}




//���ڷ��ͺ���

BOOL Login_Dlog::WriteChar(HANDLE hCom,BYTE* m_szWriteBuffer, DWORD m_nToSend)
	{
		BOOL bWrite = TRUE;
		BOOL bResult = TRUE;
		DWORD BytesSent = 0;
		HANDLE m_hWriteEvent=NULL;
		ResetEvent(m_hWriteEvent);
		if (bWrite)
		{
			m_ov.Offset = 0;
			m_ov.OffsetHigh = 0;
			// Clear buffer
			bResult = WriteFile(hCom, // Handle to COMM Port
				m_szWriteBuffer, // Pointer to message buffer in calling finction
				m_nToSend,      // Length of message to send
				&BytesSent,     // Where to store the number of bytes sent
				&m_ov);        // Overlapped structure
			if (!bResult)
			{
				DWORD dwError = GetLastError();
				switch (dwError)
				{
				case ERROR_IO_PENDING:
				{
					// continue to GetOverlappedResults()
					BytesSent = 0;
					bWrite = FALSE;
					break;
				}
				default:
				{
					// all other error codes
					break;
				}
				}
			}
		} 
		if (!bWrite)
		{
			bWrite = TRUE;
			bResult = GetOverlappedResult(hCom,   // Handle to COMM port
				&m_ov,     // Overlapped structure
				&BytesSent,    // Stores number of bytes sent
				TRUE);         // Wait flag

							   // deal with the error code
			if (!bResult)
			{
				//printf("GetOverlappedResults() in WriteFile()");
			}
		} // end if (!bWrite)

		  // Verify that the data size send equals what we tried to send
		if (BytesSent != m_nToSend)
		{
			//printf("WARNING: WriteFile() error.. Bytes Sent: %d; Message Length: %d\n", BytesSent, strlen((char*)m_szWriteBuffer));
		}
		return true;
	}


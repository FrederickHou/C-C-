// Login_Dlog.cpp : 实现文件
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
// Login_Dlog 对话框

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


// Login_Dlog 消息处理程序


void Login_Dlog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
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
		//MyCapture.open("E:\\大创\\大创.avi");
		if (MyCapture.isOpened())
		{
			nMySign = 1;

			CameraButton.SetWindowTextW(_T("关闭摄像头"));

			if (!MyCapture.read(Matframe))//是否读取了一帧图像数据
			{
				return;
			}
			else
			{
				frame = &IplImage(Matframe);  //mat 对象转换成IplImage	
				drawSquares(Cpy,frame, findSquares(frame, storage)); 
				//Canny(Matframe, MatResult, 50, 150,3);//算子边框提取
				//frame = &IplImage(MatResult);
				/****************************图像二值化***************************/

				/*threshold(Matframe, MatResult, 170, 255, CV_THRESH_BINARY);
				frame = &IplImage(MatResult);  //mat 对象转换成IplImage

				/****************************图像灰度转换***************************/

				/*int channel = 1;//image->nChannels;
				IplImage  *result;
				int depth = frame->depth;
				CvSize sz;
				sz.width = frame->width;//宽度
				sz.height = frame->height;//高度
				result = cvCreateImage(sz, depth, channel);//生成image
				cvCvtColor(frame, result, CV_BGR2GRAY);//转换成灰度图 */


				m_CvvImage.CopyOf(Img, 1);  //复制该帧图像 
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
			AfxMessageBox(_T("摄像头初始化失败!!!\n请检查摄像头是否连接"));
		}
	}
	else
	{
		CameraButton.SetWindowTextW(_T("打开摄像头"));
		MyCapture.release();
		KillTimer(1);
		KillTimer(2);
		CarHeight.SetWindowTextW(_T("0"));
		CarWidth.SetWindowTextW(_T("0"));
		IplImage *image = NULL;
		if (image) cvReleaseImage(&image);
		image = cvLoadImage("C:\\Users\\jun\\Desktop\\6.jpg", 1); //显示图片
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
		IplImage ** Cpy = &Img;//防止指针返回无法释放内存 ，从而间接开辟指针的指针用来释放内存
		storage = cvCreateMemStorage(0);
		if (!MyCapture.read(Matframe))
		{
			return;
		}
		else
		{
			frame = &IplImage(Matframe);  //mat 对象转换成IplImage
			drawSquares(Cpy, frame, findSquares(frame, storage));
			//Canny(Matframe, MatResult, 50, 150,3);//50,150
			//frame = &IplImage(MatResult);

			/*threshold(Matframe, MatResult, 170, 255, CV_THRESH_BINARY);
			frame = &IplImage(MatResult);  //mat 对象转换成IplImage
			IplImage  *result;
			int channel = 1;//image->nChannels;
			int depth = frame->depth;
			CvSize sz;
			sz.width = frame->width;//宽度
			sz.height = frame->height;//高度
			result = cvCreateImage(sz, depth, channel);//生成image
			cvCvtColor(frame, result, CV_BGR2GRAY);//转换成灰度图 */

			m_CvvImage.CopyOf(Img, 1);  //复制该帧图像 
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
		CPortState.SetWindowTextW(_T("串口状态:关闭"));
	}
	CPortTX.SetWindowTextW(_T("TX"));
	CPortRX.SetWindowTextW(_T("RX"));
	//波特率初始化
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
	//端口初始化
	CString strPort = NULL;
	for (int j = 1; j <=15; j++)
	{
		strPort.Format(_T("COM%d"),j);
		Cport.AddString(strPort);
	}
	Cport.SetCurSel(0);

	//校验位初始化
	Ccorrect.AddString(_T("无NONE"));
	Ccorrect.AddString(_T("奇ODD"));
	Ccorrect.AddString(_T("偶EVEN"));
	Ccorrect.SetCurSel(0);
	//数据位初始化
	CString strData = NULL;
	int nData = 5;
	for (int k = 0; k <=4; k++)
	{
		strData.Format(_T("%d"),nData);
		Cdata.AddString(strData);
		nData += 1;
	}
	Cdata.SetCurSel(0);

	//停止位初始化
	Cstop.AddString(_T("1"));
	Cstop.AddString(_T("1.5"));
	Cstop.AddString(_T("2"));
	Cstop.SetCurSel(0);
	//初始化车辆长
	CarHeight.SetWindowTextW(_T("0"));
	CarWidth.SetWindowTextW(_T("0"));
	// TODO:  在此添加额外的初始化
	pwnd = GetDlgItem(IDC_STA);//根据ID值获取对话框中子窗体控件对象指针,
	pDC = pwnd->GetDC();//取得客户区显示设备dc
	hDC = pDC->GetSafeHdc();
	pwnd->GetClientRect(&rect);//得到显示区尺寸

	
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//////////////////////////////////////////////////////////////////
//函数功能：用向量来做COSα=两向量之积/两向量模的乘积求两条线段夹角
//输入：   线段3个点坐标pt1,pt2,pt0,最后一个参数为公共点
//输出：   线段夹角，单位为角度
//////////////////////////////////////////////////////////////////
double Login_Dlog::angle(CvPoint* pt1, CvPoint* pt2, CvPoint* pt0)
{
	double dx1 = pt1->x - pt0->x;
	double dy1 = pt1->y - pt0->y;
	double dx2 = pt2->x - pt0->x;
	double dy2 = pt2->y - pt0->y;
	double angle_line = (dx1*dx2 + dy1*dy2) / sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);//余弦值
	return angle_line;
}

//////////////////////////////////////////////////////////////////
//函数功能：采用多边形检测，通过约束条件寻找矩形
//输入：   img 原图像
//          storage 存储
//          minarea，maxarea 检测矩形的最小/最大面积
//          minangle,maxangle 检测矩形边夹角范围，单位为角度
//输出：   矩形序列
//////////////////////////////////////////////////////////////////
CvSeq* Login_Dlog::findSquares(IplImage* img, CvMemStorage* storage)
{
		CvSeq* contours = NULL;//边缘
		int N = 6;  //阈值分级
		CvSize sz = cvSize(img->width & -2, img->height & -2);
		IplImage* timg = cvCloneImage(img);//拷贝一次img
		IplImage* gray = cvCreateImage(sz, 8, 1); //img灰度图
		IplImage* pyr = cvCreateImage(cvSize(sz.width / 2, sz.height / 2), 8, 3);  //金字塔滤波3通道图像中间变量
		IplImage* tgray = cvCreateImage(sz, 8, 1);
		CvSeq* result;
		double s, t;
		int i;
		CvSeq* squares = cvCreateSeq(0, sizeof(CvSeq), sizeof(CvPoint), storage);
		cvSetImageROI(timg, cvRect(0, 0, sz.width, sz.height));
		//金字塔滤波 
		cvPyrDown(timg, pyr, 7);
		cvPyrUp(pyr, timg, 7);
		//在3个通道中寻找矩形 
		for (int c = 0; c < 3; c++) //对3个通道分别进行处理 
		{
			cvSetImageCOI(timg, c + 1);
			cvCopy(timg, tgray, 0);  //依次将BGR通道送入tgray         
			for (int l = 0; l < N; l++)
			{
				//不同阈值下二值化
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
				{ //多边形逼近             
					result = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0);
					//如果是凸四边形并且面积在范围内
					if (result->total == 4 && fabs(cvContourArea(result, CV_WHOLE_SEQ)) > 1000 && cvCheckContourConvexity(result))
					{
						s = 0;
						//判断每一条边
						for (i = 0; i < 5; i++)
						{
							if (i >= 2)
							{   //角度            
								t = fabs(angle((CvPoint*)cvGetSeqElem(result, i), (CvPoint*)cvGetSeqElem(result, i - 2), (CvPoint*)cvGetSeqElem(result, i - 1)));
								s = s > t ? s : t;
							}
						}
						//这里的S为直角判定条件 单位为角度
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
//函数功能：画出所有矩形
//输入：   img 原图像
//          squares 矩形序列
//          wndname 窗口名称
//输出：   图像中标记矩形
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
		//过滤掉边缘检测
		if (rect->x < 30 || rect->y < 30 || rect->x > 610 || rect->y > 450)
		{
			continue;
		}
		nWidth = pt[1].x - pt[0].x;//车辆长
		nHeight = pt[3].y - pt[0].y;//车辆宽
		if (nWidth < 0)
		{
			nWidth = 0 - nWidth; //车辆宽数据修正
		}
		if (nHeight < 0)
		{
			nHeight = 0 - nHeight;//车辆长数据修正
		}
		cvPolyLine(*cpy, &rect, &count, 1, 1, CV_RGB(255, 255, 0), 3, CV_AA, 0);//将抓捕到的图像用线条画出轮廓
	}
	cvReleaseMemStorage(&squares->storage);	
}


void Login_Dlog::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void Login_Dlog::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void Login_Dlog::OnBnClickedButton2()
{
	if (!flage)
	{
		Cport.GetLBText(Cport.GetCurSel(), strGetport);

		Cfrequence.GetLBText(Cfrequence.GetCurSel(), strGetFrequence);

		Ccorrect.GetLBText(Ccorrect.GetCurSel(), strGetCorrect);
		CString CorrectDate = strGetCorrect;

		if (strGetCorrect == _T("无NONE"))

		{
			strGetCorrect = _T("0");
		}
		else if (strGetCorrect == _T("奇ODD"))
		{
			strGetCorrect = _T("1");
		}
		else if (strGetCorrect == _T("偶EVEN"))
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

		if (flage)//flag位全局变量
		{
			//nMyRadioButton = 1;
			CMyRadioButton.SetCheck(nMyRadioButton);
			CPortButton.SetWindowTextW(_T("关闭端口"));
			CPortState.SetWindowTextW(_T("串口状态:打开   端口号：")+strGetport+_T("   波特率：")+strGetFrequence+_T("   校验位：")+ CorrectDate +_T("   数据位：")+strGetData+_T("   停止位：")+strGetStop);
			CPortSendButton.EnableWindow(TRUE);
		}
	}
	else
	{
		//nMyRadioButton = 0;
		CMyRadioButton.SetCheck(NULL);
		CPortButton.SetWindowTextW(_T("打开端口"));
		CloseHandle(hCom);
		SetCommMask(hCom, 0);//禁止串行端口所有事件
		EscapeCommFunction(hCom, CLRDTR);//清除数据终端就绪信号
		//丢弃通信资源的输出或输入缓冲区字符并终止在通信资源上挂起的读、写操操作
		PurgeComm(hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
		flage = false;
	    CPortState.SetWindowTextW(_T("串口状态:关闭"));
		CPortSendButton.EnableWindow(FALSE);
		hCom = NULL;
	}
}

HANDLE Login_Dlog:: CSerialOpen(LPCTSTR PortCOMx, DWORD Portbaudrate, BYTE PortByteSize,BYTE PortParity, BYTE PortStopBits)
{

	
	BOOL state;
	DCB SerialDCB;

	//打开
	hCom = CreateFile(
		PortCOMx,              //打开串口   通过函数CreateFile打开串口,其第一个参数就是串口的逻辑端口名,是用”COMX”表示的,其中X是1~N的整数,当X大于10时,有时会出现无法打开的问题,把逻辑端口名改成"\\\\.\\COM
		GENERIC_READ | GENERIC_WRITE,  //允许读和写操作
		0,  //独占方式
		NULL,
		OPEN_EXISTING, //打开存在的串口, 必须是OPEN_EXISTING, 文件还可以CREATE_NEW, 串口不能创建
		 0,//FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, //异步方式打开
		NULL
	);

	if (hCom == INVALID_HANDLE_VALUE) 

	{//打开失败
		MessageBox(_T("警告：串口打开失败!!!"),_T("温馨提示"));
		return INVALID_HANDLE_VALUE;
	}
	else
	{
		//AfxMessageBox(_T("串口打开成功\n端口号：")+CString(PortCOMx));
		flage = true;
	}
	//串口状态设置
	state = GetCommState(hCom, &SerialDCB);
	SerialDCB.fBinary =1;
	SerialDCB.fParity = 1;
	SerialDCB.BaudRate = Portbaudrate; /* Baudrate at which running, CBR_115200 */  //波特率
	SerialDCB.ByteSize = PortByteSize-48;        /* Number of bits/byte, 4-8 */   //数据位
	SerialDCB.Parity = PortParity-48;    /* 0-4=None,Odd,Even,Mark,Space */  //校验位 NOPARITY
	SerialDCB.StopBits = PortStopBits-48; /* 0,1,2 = 1, 1.5, 2 */  //停止位 ONESTOPBIT
	state = SetCommState(hCom, &SerialDCB);
	if (!state) 
	{
		int error = GetLastError();
		CloseHandle(hCom);
		return INVALID_HANDLE_VALUE;
	}
	//设置缓冲区大小
	state = SetupComm(hCom, SERIAL_RECV_BUFFER, SERIAL_SEND_BUFFER);
	if (!state)
	{
		CloseHandle(hCom);
		return INVALID_HANDLE_VALUE;
	}
	PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_RXABORT); //立即中断写操作并清空输出缓冲区 | 清空输出缓冲区 | 立即中断读操作并清空输入缓冲区|清空输入缓冲区
	return hCom;
}

void Login_Dlog::OnBnClickedButton3()
{
	/*if (PortSendSign==0)
	{
		//CPortSendButton.SetWindowTextW(_T("停止发送"));
		//CString strGetSendText = NULL;
		//unsigned char* cSendBuffer = NULL;
		//AfxMessageBox(strGetSendText);
		//SetTimer(3, 1000, NULL);
		PortSendSign = 1;

	
	}
	else
	{
		CPortSendButton.SetWindowTextW(_T("开始发送"));
		KillTimer(3);
		PortSendSign=0;
	}*/

	unsigned char IntToCharCarHeight[255] = { 0 };
	unsigned char IntToCharCarWidth[100] = { 0 };
	sprintf((char*)IntToCharCarHeight, "%d", nHeight);
	strcat((char*)IntToCharCarHeight, "W");//添加标志字符 便于下位机区分长款尺寸
	sprintf((char*)IntToCharCarWidth, "%d", nWidth);
	//这里是英文宽字节转单字节发送给串口会造成数据丢失所以自己写底层解析
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
		TX = _T("长：")+strHeight + _T("  宽：")+strWidth;
		CPortTX.SetWindowTextW(_T("TX:") + TX);
	}

}




//串口发送函数

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


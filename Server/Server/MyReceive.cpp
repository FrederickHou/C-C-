// MyReceive.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Server.h"
#include "MyReceive.h"
#include "ServerDlg.h"
#include "AdoSql.h"
#include <vector>
#include <afxsock.h>
#include<windows.h>
#import"msxml3.dll"
using namespace MSXML2;
using namespace std;
// MyReceive
MyReceive* SocketSend;
extern CServerDlg *pDlog;
extern AdoSql *mysql;
vector<int> MyVector;
vector<int> MyVector1;
MyReceive::MyReceive()
{
	SocketSend = this;
	nNum = 0;
}

MyReceive::~MyReceive()
{
}


// MyReceive ��Ա����


void MyReceive::OnReceive(int nErrorCode)
{
	SocketSend = this;
	::CoInitialize(NULL);
	    CString cstrLogId;
		CString cstrLogAccount;
		CString cstrLogPwd;
		CString nodeName;
		CString nodeName1;
		CString nodeValue;
		CString SocketCilent;
		SocketCilent.Format(_T("%d"), this);
		char buf[1024] = { 0 };
		CString strServerRecText;
		Receive(buf, 1024);
		strServerRecText.Format(_T("%s"), buf);
		MSXML2::IXMLDOMDocumentPtr XMLDOC;
		MSXML2::IXMLDOMElementPtr XMLROOT;
		MSXML2::IXMLDOMNodeListPtr XMLNODES;
		MSXML2::IXMLDOMNodePtr XMLNODE;
		HRESULT HR = XMLDOC.CreateInstance(_uuidof(MSXML2::DOMDocument30));
		if (!SUCCEEDED(HR))
		{
			AfxMessageBox(_T("faild!!"));
			return;
		}
		CString sctrAccount = _T("17782582921");
		CString strpassword = _T("hjh111000");
		//CString  MyXML = _T("<?xml version =\"1.0\" encoding=\"UTF-8\"?>\n<Root><Node><Node1><ID>2</ID><Account>") + sctrAccount + ("</Account><Pwd>") + strpassword + ("</Pwd></Node1></Node></Root>");
	    CString  MyXML = strServerRecText;
		XMLDOC->loadXML((_bstr_t)MyXML);
		XMLROOT = XMLDOC->GetdocumentElement();//��ø��ڵ�;
		XMLROOT->get_childNodes(&XMLNODES);//��ø��ڵ�������ӽڵ�;
		XMLNODES->get_item(0, &XMLNODE);//���ĳ���ӽڵ�
		for (MSXML2::IXMLDOMNodePtr pChild = XMLNODE->firstChild; pChild != NULL; pChild = pChild->nextSibling)
		{
			CString nodeName1 = ((LPCWSTR)pChild->GetnodeName());
			for (MSXML2::IXMLDOMNodePtr MypChild = pChild->firstChild; MypChild != NULL; MypChild = MypChild->nextSibling)
			{
			     nodeName = ((LPCWSTR)MypChild->GetnodeName());
				 nodeValue = ((_variant_t)MypChild->GetnodeTypedValue());
				if (_T("ID")==nodeName)
				{
					 cstrLogId = nodeValue;
					 SYSTEMTIME time = {0};
					 GetLocalTime(&time);
					 int Year = time.wYear;
					 int Month = time.wMonth;
					 int Day = time.wDay;
					 int Hour = time.wHour;
					 int Minute = time.wMinute;
					 int Second = time.wSecond;
					 CString cstrYear;
					 CString cstrMonth;
					 CString cstrDay;
					 CString cstrHour;
					 CString cstrMinute;
					 CString cstrSecond;
					 cstrYear.Format(_T("%d"),Year);
					 cstrMonth.Format(_T("%d"), Month);
					 cstrDay.Format(_T("%d"), Day);
					 cstrHour.Format(_T("%d"), Hour);
					 cstrMinute.Format(_T("%d"), Minute);
					 cstrSecond.Format(_T("%d"), Second);
					 pDlog->Text.SetWindowTextW(_T("����")+cstrYear+_T("/")+ cstrMonth+ _T("/")+ cstrDay + _T("ʱ��")+ cstrHour + _T(":")+cstrMinute + _T(":")+ cstrSecond + _T("  �ͻ���") + SocketCilent + _T("��Ϣ��") + cstrLogId);
				}
				if (_T("Account") == nodeName)
				{
					cstrLogAccount = nodeValue;
				}
				if (_T("Pwd") == nodeName)
				{
					cstrLogPwd = nodeValue;
				}
			}
		}

		if (_T("4") == cstrLogId)//�ֻ������ѯ
		{
			try
			{
				_variant_t CRelog, CRegPwd, CReceive_Sign;
				CRelog = _variant_t(_bstr_t(cstrLogAccount));
				CRegPwd = _variant_t(_T(""));
				CReceive_Sign = _variant_t(cstrLogId);
				mysql->m_pCommand.CreateInstance(__uuidof(Command));
				mysql->m_pCommand->CommandText = (_bstr_t)("Room_Login_1");//�洢��������
				mysql->m_pCommand->CommandType = adCmdStoredProc;
				mysql->m_pCommand->ActiveConnection = mysql->m_pConnection;

				_ParameterPtr p_Param1;
				_ParameterPtr p_Param2;
				_ParameterPtr p_Param3;
				_ParameterPtr p_Param4;

				p_Param1.CreateInstance(__uuidof(Parameter));
				p_Param1->Name = "@My_Receive_Sign";
				p_Param1->Type = adInteger;
				p_Param1->Size = 4;
				p_Param1->Direction = adParamInput;
				p_Param1->Value = CReceive_Sign;
				mysql->m_pCommand->Parameters->Append(p_Param1);

				p_Param2.CreateInstance(__uuidof(Parameter));
				p_Param2->Name = "@My_input_Account";
				p_Param2->Type = adVarChar;
				p_Param2->Size = 20;
				p_Param2->Direction = adParamInput;
				p_Param2->Value = CRelog;
				mysql->m_pCommand->Parameters->Append(p_Param2);

				p_Param3.CreateInstance(__uuidof(Parameter));
				p_Param3->Name = "@My_input_Pwd";
				p_Param3->Type = adVarChar;
				p_Param3->Size = 20;
				p_Param3->Direction = adParamInput;
				p_Param3->Value = CRegPwd;
				mysql->m_pCommand->Parameters->Append(p_Param3);
				
				p_Param4.CreateInstance(__uuidof(Parameter));
				p_Param4->Name = "@My_Receive_Var";
				p_Param4->Type = adVarChar;
				p_Param4->Size = 20;
				p_Param4->Direction = adParamOutput;
				mysql->m_pCommand->Parameters->Append(p_Param4);

				mysql->m_pCommand->Execute(NULL, NULL, adCmdStoredProc);

				CString cstrOutputNum = p_Param4->Value.bstrVal;
				this->Send(cstrOutputNum, 255, 0);
			}

			catch (_com_error e)
			{
				this->Send(_T("�˺Ų�����"), 255, 0);
				XMLDOC.Release();
				XMLROOT.Release();
				XMLNODES.Release();
				::CoInitialize(NULL);
				return;
			}
		}

		if (_T("5") == cstrLogId)//��������ѯ
		{
			try
			{
				_variant_t CRelog, CRegPwd, CReceive_Sign;
				CRelog = _variant_t(_bstr_t(cstrLogAccount));
				CRegPwd = _variant_t(_T(""));
				CReceive_Sign = _variant_t(cstrLogId);
				mysql->m_pCommand.CreateInstance(__uuidof(Command));
				mysql->m_pCommand->CommandText = (_bstr_t)("Room_Login_1");//�洢��������
				mysql->m_pCommand->CommandType = adCmdStoredProc;
				mysql->m_pCommand->ActiveConnection = mysql->m_pConnection;

				_ParameterPtr p_Param1;
				_ParameterPtr p_Param2;
				_ParameterPtr p_Param3;
				_ParameterPtr p_Param4;

				p_Param1.CreateInstance(__uuidof(Parameter));
				p_Param1->Name = "@My_Receive_Sign";
				p_Param1->Type = adInteger;
				p_Param1->Size = 4;
				p_Param1->Direction = adParamInput;
				p_Param1->Value = CReceive_Sign;
				mysql->m_pCommand->Parameters->Append(p_Param1);

				p_Param2.CreateInstance(__uuidof(Parameter));
				p_Param2->Name = "@My_input_Account";
				p_Param2->Type = adVarChar;
				p_Param2->Size = 20;
				p_Param2->Direction = adParamInput;
				p_Param2->Value = CRelog;
				mysql->m_pCommand->Parameters->Append(p_Param2);

				p_Param3.CreateInstance(__uuidof(Parameter));
				p_Param3->Name = "@My_input_Pwd";
				p_Param3->Type = adVarChar;
				p_Param3->Size = 20;
				p_Param3->Direction = adParamInput;
				p_Param3->Value = CRegPwd;
				mysql->m_pCommand->Parameters->Append(p_Param3);

				p_Param4.CreateInstance(__uuidof(Parameter));
				p_Param4->Name = "@My_Receive_Var";
				p_Param4->Type = adVarChar;
				p_Param4->Size = 20;
				p_Param4->Direction = adParamOutput;
				mysql->m_pCommand->Parameters->Append(p_Param4);

				mysql->m_pCommand->Execute(NULL, NULL, adCmdStoredProc);

				CString cstrOutputNum = p_Param4->Value.bstrVal;
				this->Send(cstrOutputNum, 255, 0);
			}

			catch (_com_error e)
			{
				this->Send(_T("�˺Ų�����"), 255, 0);
				XMLDOC.Release();
				XMLROOT.Release();
				XMLNODES.Release();
				::CoInitialize(NULL);
				return;
			}
		}

		if (_T("2") == cstrLogId)//�ֻ���¼�洢����
		{
			try
			{
				_variant_t CRelog, CRegPwd, CReceive_Sign;
				CRelog = _variant_t(_bstr_t(cstrLogAccount));
				CRegPwd = _variant_t(_bstr_t(cstrLogPwd));
				CReceive_Sign = _variant_t(cstrLogId);
				mysql->m_pCommand.CreateInstance(__uuidof(Command));
				mysql->m_pCommand->CommandText = (_bstr_t)("Room_Login_1");//�洢��������
				mysql->m_pCommand->CommandType = adCmdStoredProc;
				mysql->m_pCommand->ActiveConnection = mysql->m_pConnection;

				_ParameterPtr p_Param1;
				_ParameterPtr p_Param2;
				_ParameterPtr p_Param3;
				_ParameterPtr p_Param4;

				p_Param1.CreateInstance(__uuidof(Parameter));
				p_Param1->Name = "@My_Receive_Sign";
				p_Param1->Type = adInteger;
				p_Param1->Size = 4;
				p_Param1->Direction = adParamInput;
				p_Param1->Value = CReceive_Sign;
				mysql->m_pCommand->Parameters->Append(p_Param1);

				p_Param2.CreateInstance(__uuidof(Parameter));
				p_Param2->Name = "@My_input_Account";
				p_Param2->Type = adVarChar;
				p_Param2->Size = 20;
				p_Param2->Direction = adParamInput;
				p_Param2->Value = CRelog;
				mysql->m_pCommand->Parameters->Append(p_Param2);

				p_Param3.CreateInstance(__uuidof(Parameter));
				p_Param3->Name = "@My_input_Pwd";
				p_Param3->Type = adVarChar;
				p_Param3->Size = 20;
				p_Param3->Direction = adParamInput;
				p_Param3->Value = CRegPwd;
				mysql->m_pCommand->Parameters->Append(p_Param3);

				p_Param4.CreateInstance(__uuidof(Parameter));
				p_Param4->Name = "@My_Receive_Var";
				p_Param4->Type = adVarChar;
				p_Param4->Size = 20;
				p_Param4->Direction = adParamOutput;
				mysql->m_pCommand->Parameters->Append(p_Param4);

				mysql->m_pCommand->Execute(NULL, NULL, adCmdStoredProc);

				CString cstrOutputNum = p_Param4->Value.bstrVal;
				this->Send(cstrOutputNum, 255, 0);
				XMLDOC.Release();
				XMLROOT.Release();
				XMLNODES.Release();
				::CoInitialize(NULL);
				return;
			}

			catch (_com_error e)
			{
				CString errormessage;
				errormessage.Format(_T("����"));
				AfxMessageBox(errormessage);
				XMLDOC.Release();
				XMLROOT.Release();
				XMLNODES.Release();
				::CoInitialize(NULL);
				return;
			}
		}
		
		if (_T("3") == cstrLogId)//��������¼
		{
			try
			{
				_variant_t CRelog, CRegPwd, CReceive_Sign;
				CRelog = _variant_t(_bstr_t(cstrLogAccount));
				CRegPwd = _variant_t(_bstr_t(cstrLogPwd));
				CReceive_Sign = _variant_t(cstrLogId);
				mysql->m_pCommand.CreateInstance(__uuidof(Command));
				mysql->m_pCommand->CommandText = (_bstr_t)("Room_Login_1");//�洢��������
				mysql->m_pCommand->CommandType = adCmdStoredProc;
				mysql->m_pCommand->ActiveConnection = mysql->m_pConnection;

				_ParameterPtr p_Param1;
				_ParameterPtr p_Param2;
				_ParameterPtr p_Param3;
				_ParameterPtr p_Param4;

				p_Param1.CreateInstance(__uuidof(Parameter));
				p_Param1->Name = "@My_Receive_Sign";
				p_Param1->Type = adInteger;
				p_Param1->Size = 4;
				p_Param1->Direction = adParamInput;
				p_Param1->Value = CReceive_Sign;
				mysql->m_pCommand->Parameters->Append(p_Param1);

				p_Param2.CreateInstance(__uuidof(Parameter));
				p_Param2->Name = "@My_input_Account";
				p_Param2->Type = adVarChar;
				p_Param2->Size = 20;
				p_Param2->Direction = adParamInput;
				p_Param2->Value = CRelog;
				mysql->m_pCommand->Parameters->Append(p_Param2);

				p_Param3.CreateInstance(__uuidof(Parameter));
				p_Param3->Name = "@My_input_Pwd";
				p_Param3->Type = adVarChar;
				p_Param3->Size = 20;
				p_Param3->Direction = adParamInput;
				p_Param3->Value = CRegPwd;
				mysql->m_pCommand->Parameters->Append(p_Param3);

				p_Param4.CreateInstance(__uuidof(Parameter));
				p_Param4->Name = "@My_Receive_Var";
				p_Param4->Type = adVarChar;
				p_Param4->Size = 20;
				p_Param4->Direction = adParamOutput;
				mysql->m_pCommand->Parameters->Append(p_Param4);

				mysql->m_pCommand->Execute(NULL, NULL, adCmdStoredProc);

				CString cstrOutputNum = p_Param4->Value.bstrVal;
				this->Send(cstrOutputNum, 255, 0);
				XMLDOC.Release();
				XMLROOT.Release();
				XMLNODES.Release();
				::CoInitialize(NULL);
				return;
			}

			catch (_com_error e)
			{
				CString errormessage;
				errormessage.Format(_T("����"));
				AfxMessageBox(errormessage);
				XMLDOC.Release();
				XMLROOT.Release();
				XMLNODES.Release();
				::CoInitialize(NULL);
				return;
			}
		}

		if (_T("1") == cstrLogId)//�ֻ�ע��
		{
			try
			{
				_variant_t CRelog, CRegPwd, CReceive_Sign;
				CRelog = _variant_t(_bstr_t(cstrLogAccount));
				CRegPwd = _variant_t(_bstr_t(cstrLogPwd));
				CReceive_Sign = _variant_t(cstrLogId);
				mysql->m_pCommand.CreateInstance(__uuidof(Command));
				mysql->m_pCommand->CommandText = (_bstr_t)("Room_Login_1");//�洢��������
				mysql->m_pCommand->CommandType = adCmdStoredProc;
				mysql->m_pCommand->ActiveConnection = mysql->m_pConnection;

				_ParameterPtr p_Param1;
				_ParameterPtr p_Param2;
				_ParameterPtr p_Param3;
				_ParameterPtr p_Param4;

				p_Param1.CreateInstance(__uuidof(Parameter));
				p_Param1->Name = "@My_Receive_Sign";
				p_Param1->Type = adInteger;
				p_Param1->Size = 4;
				p_Param1->Direction = adParamInput;
				p_Param1->Value = CReceive_Sign;
				mysql->m_pCommand->Parameters->Append(p_Param1);

				p_Param2.CreateInstance(__uuidof(Parameter));
				p_Param2->Name = "@My_input_Account";
				p_Param2->Type = adVarChar;
				p_Param2->Size = 20;
				p_Param2->Direction = adParamInput;
				p_Param2->Value = CRelog;
				mysql->m_pCommand->Parameters->Append(p_Param2);

				p_Param3.CreateInstance(__uuidof(Parameter));
				p_Param3->Name = "@My_input_Pwd";
				p_Param3->Type = adVarChar;
				p_Param3->Size = 20;
				p_Param3->Direction = adParamInput;
				p_Param3->Value = CRegPwd;
				mysql->m_pCommand->Parameters->Append(p_Param3);

				p_Param4.CreateInstance(__uuidof(Parameter));
				p_Param4->Name = "@My_Receive_Var";
				p_Param4->Type = adVarChar;
				p_Param4->Size = 20;
				p_Param4->Direction = adParamOutput;
				mysql->m_pCommand->Parameters->Append(p_Param4);

				mysql->m_pCommand->Execute(NULL, NULL, adCmdStoredProc);

				CString cstrOutputNum = p_Param4->Value.bstrVal;
				this->Send(cstrOutputNum, 255, 0);
				XMLDOC.Release();
				XMLROOT.Release();
				XMLNODES.Release();
				::CoInitialize(NULL);
				return;
			}

			catch (_com_error e)
			{
				CString errormessage;
				errormessage.Format(_T("����"));
				AfxMessageBox(errormessage);
				XMLDOC.Release();
				XMLROOT.Release();
				XMLNODES.Release();
				::CoInitialize(NULL);
				return;
			}
		}

		if (_T("-1") == cstrLogId)//����ע��
		{
			try
			{
				_variant_t CRelog, CRegPwd, CReceive_Sign;
				CRelog = _variant_t(_bstr_t(cstrLogAccount));
				CRegPwd = _variant_t(_bstr_t(cstrLogPwd));
				CReceive_Sign = _variant_t(cstrLogId);
				mysql->m_pCommand.CreateInstance(__uuidof(Command));
				mysql->m_pCommand->CommandText = (_bstr_t)("Room_Login_1");//�洢��������
				mysql->m_pCommand->CommandType = adCmdStoredProc;
				mysql->m_pCommand->ActiveConnection = mysql->m_pConnection;

				_ParameterPtr p_Param1;
				_ParameterPtr p_Param2;
				_ParameterPtr p_Param3;
				_ParameterPtr p_Param4;

				p_Param1.CreateInstance(__uuidof(Parameter));
				p_Param1->Name = "@My_Receive_Sign";
				p_Param1->Type = adInteger;
				p_Param1->Size = 4;
				p_Param1->Direction = adParamInput;
				p_Param1->Value = CReceive_Sign;
				mysql->m_pCommand->Parameters->Append(p_Param1);

				p_Param2.CreateInstance(__uuidof(Parameter));
				p_Param2->Name = "@My_input_Account";
				p_Param2->Type = adVarChar;
				p_Param2->Size = 20;
				p_Param2->Direction = adParamInput;
				p_Param2->Value = CRelog;
				mysql->m_pCommand->Parameters->Append(p_Param2);

				p_Param3.CreateInstance(__uuidof(Parameter));
				p_Param3->Name = "@My_input_Pwd";
				p_Param3->Type = adVarChar;
				p_Param3->Size = 20;
				p_Param3->Direction = adParamInput;
				p_Param3->Value = CRegPwd;
				mysql->m_pCommand->Parameters->Append(p_Param3);

				p_Param4.CreateInstance(__uuidof(Parameter));
				p_Param4->Name = "@My_Receive_Var";
				p_Param4->Type = adVarChar;
				p_Param4->Size = 20;
				p_Param4->Direction = adParamOutput;
				mysql->m_pCommand->Parameters->Append(p_Param4);

				mysql->m_pCommand->Execute(NULL, NULL, adCmdStoredProc);

				CString cstrOutputNum = p_Param4->Value.bstrVal;
				this->Send(cstrOutputNum, 255, 0);
				XMLDOC.Release();
				XMLROOT.Release();
				XMLNODES.Release();
				::CoInitialize(NULL);
				return;
			}

			catch (_com_error e)
			{
				CString errormessage;
				errormessage.Format(_T("����"));
				AfxMessageBox(errormessage);
				XMLDOC.Release();
				XMLROOT.Release();
				XMLNODES.Release();
				::CoInitialize(NULL);
				return;
			}
		}

}





void MyReceive::OnAccept(int nErrorCode)
{
	
	//CSocket::OnAccept(nErrorCode);
	SocketRecv = new MyReceive();
		if (Accept(*SocketRecv))
		{
			CString IpAdreess;
			nNum += 1;
			CString strShowNum;
			strShowNum.Format(_T("%d"), nNum);
			pDlog->CLogNum.SetWindowTextW(strShowNum);
			MyVector.push_back((int)SocketRecv);

			CString strSize;
			strSize.Format(_T("%d"), MyVector[MyVector.size()-1]);
		   // AfxMessageBox(strSize);
		}


}


/*void MyReceive::OnSend(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	
	CSocket::OnSend(nErrorCode);
}*/

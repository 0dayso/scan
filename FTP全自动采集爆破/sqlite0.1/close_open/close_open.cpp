// close_open.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "close_open.h"
#include<windows.h>
#include <Wininet.h>
#include <TLHELP32.H>
//#include <afx.h>
#include <afxtempl.h>
#include <vector>
using namespace std;
#include <iostream>   

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

int close_exe(CString strProcessName)
{
		BOOL bResult;
	CString strTemp;
	HANDLE hSnapshot;				//�ڴ���̵ġ����ա����   
	PROCESSENTRY32 ProcessEntry;	//�������̵Ľṹ   ����ṹ��Ҫ#include <TLHELP32.H>ͷ�ļ�
	vector<DWORD> vtPID;			//����ID����
	//����Ҫ�����Ľ�������
//strProcessName="main.exe";
//GetDlgItem(IDC_EDIT1)->GetWindowText(strProcessName);//��ȡ�ı�������Ľ�����
	
//MessageBox(strProcessName);
	strProcessName.MakeLower();
	//�����ڴ����н��̵Ŀ��ա�����ΪTH32CS_SNAPPROCESSȡ�еĽ���,���Բ���2��
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	//��ȡҪ�����Ľ������ƶ�Ӧ�����н���ID
	ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
	bResult = Process32First(hSnapshot,&ProcessEntry);//��ȡ��һ������
	while(bResult)
	{
		//�ж��Ƿ�ΪҪ�����Ľ���
		strTemp.Format("%s",ProcessEntry.szExeFile);
		strTemp.MakeLower();
		//		MessageBox(strTemp);
		if(strTemp==strProcessName)
			vtPID.push_back(ProcessEntry.th32ProcessID);
		//��ȡ��һ������
		bResult = Process32Next(hSnapshot,&ProcessEntry);
	}
	//��������
	bResult = FALSE;
	vector<DWORD>::iterator it = vtPID.begin();
	for(;it!=vtPID.end();++it)
	{
		if(*it)
		{
			//��ȡ���̾��
			HANDLE hProcess;
			hProcess = OpenProcess(PROCESS_ALL_ACCESS,FALSE,*it);
			//��������
			if(hProcess)
				bResult = TerminateProcess(hProcess,0);
			if(!bResult)
				break;
		}
	}
	
	//
	if(bResult)
		return 1;  //�����ɹ�
	else
		return 0;  //����ʧ��
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	if(argv[1]!=NULL)
	{
		CString   str;   
		str.Format("��ʼ�������̣�%s\n",argv[1]);
		printf (str);
		if(close_exe(argv[1]))
		{
			printf ("�������̳ɹ��ȴ�10�������������\n");
			_sleep(10*1000); //��ʱ5�� 
			//MessageBox(NULL,"text","�������̳ɹ���",MB_OK);
			//_sleep(60*1000); //��ʱ60�� 
			if(argv[2]!=NULL)
				ShellExecute( 0,"open",argv[2],NULL,NULL,SW_SHOWMAXIMIZED);
		}
		else
			//MessageBox(NULL,"text","��������ʧ�ܣ�",MB_OK);
			printf ("��������ʧ�ܣ�\n");
	}
}



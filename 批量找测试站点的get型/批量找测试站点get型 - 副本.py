#! /usr/bin/env python
#coding=gb2312

#�����Ҳ���վ���С����get��

import re
import httplib
import threading
import Queue
import msvcrt, os

class test(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
    
    
    def run(self):
        while 1:
            if queue.empty() == True:
                break
            self.test()
    def test(self):
        url = queue.get()
        jieguo = []
        ddatas = []
        datas = open('data.txt','r')
        for site in datas:
            ddatas.append(site)
        retest = ddatas[1][7:].strip()
        datas.close()
        jindu = queue.qsize()
        if 'testget' in ddatas[0]:#get�������ж�
            site = ddatas[0][8:].strip()
            self.testget(url,site,retest,jindu)
        elif 'testpost' in ddatas[0]:
            print 'postxing'
        else:
            print '������,�㵽�׻᲻����?����͵���İ�'    
        
        
    def testget(self,arg,site,retest,jindu):
        headers = {'User-Agent':'Mozilla/5.0 (compatible; Googlebot/2.1; +http://www.google.com/bot.html)'}
        try:
            conn = httplib.HTTPConnection(arg)
            conn.request('GET',site,None,headers)
            httpres = conn.getresponse()
            html = httpres.read()
            code = httpres.status
            if html and code == 200:
                tt = re.compile(retest)
                ss = tt.findall(html)
                if ss:
                    jieguo.append(arg)
                    print '[%s]<��,��վ����©��,�Ѿ�����> %s ' % (jindu,arg)
                else:
                    print '[%s]<��,������©��> %s ' % (jindu,arg)
            else:
                print '[%s]<��,�����ڴ�����> %s ' % (jindu,arg)
        except Exception,e:
            print e
            
            
class stop(threading.Thread):
	def run(self):
		try:		   
			self.chr = msvcrt.getch()
			if self.chr == 'q':
				print "stopped by your action ( q )"
				os._exit(1)
		except:
			pass

    
    
if __name__ == '__main__':
    global queue,jieguo
    jieguo = []
    threads = []
    urls = []
    line = 10
    queue = Queue.Queue()
    txt = open('url.txt','r')
    for url in txt:
        if url.strip() not in urls:
            urls.append(url.strip())
            
    shouhu = stop()
    shouhu.setDaemon(True)#��;ֹͣ��ť
    shouhu.start()  
    
    for url in urls:
        queue.put(url)
        
    for x in range(line):
        y = test()
        y.start()
        threads.append(y)
    for x in threads:
        x.join()
    
    if jieguo:
        print '<info �����õ���%s���Ϊ>' % len(jieguo)
        for url in jieguo:
            print url
    else:
        print '���泶����һ��û�õ�'    
        
    raw_input('')
    
    
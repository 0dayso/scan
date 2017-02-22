# -*- coding: cp936 -*-

import logging
import traceback
import multiprocessing
import os
import argparse

'''�����ģ�飬���κε������ṩ����̽ӿ�,�ɸ�������˼·��д�Զ����ɴ���Ĵ���'''

class multi_process(multiprocessing.Process):
    '''���ú����������������б�---��һ��Ԫ��ΪԪ���б��ڶ���Ԫ��Ϊ�ؼ����ֵ��б�'''
    def __init__(self,func_name,func_arg):
        multiprocessing.Process.__init__(self)
        self.func_name=func_name
        self.func_arg=func_arg
    def set_func_name(self):
        self.func_name=''
    def run(self):
        try:
            apply(self.func_name,self.func_arg)
        except:
            pass

def process_job(process_num,func_name,arg_list):
    process_list=[]
    for i in range(process_num):
        print arg_list[i]
        p=multi_process(func_name,arg_list[i])
        process_list.append(p)
    for i in range(process_num):
        process_list[i].daemon=True
        process_list[i].start()
    for i in range(process_num):
        process_list[i].join()

def test(fn):
    print fn

if __name__=="__main__":
    process_job(3,test,[1,2,3])
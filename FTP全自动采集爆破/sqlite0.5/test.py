#!/usr/local/bin/python
#-*- coding: UTF-8 -*-
queue = []
def enQ():
    queue.append(raw_input('Enter new string: ').strip())

#调用list的列表的pop()函数.pop(0)为列表的第一个元素
def deQ():   #www.2cto.com
    if len(queue) == 0:
        print 'Cannot pop from an empty queue!'
    else:
        print 'Removed [', queue.pop(0) ,']'

def viewQ():
    print queue

CMDs = {'e': enQ, 'd': deQ, 'v': viewQ}

def showmenu():
    pr = """
    (E)nqueue
    (D)equeue
    (V)iew
    (Q)uit
    Enter choice: """

    while True:
        while True:
            try:
                choice = raw_input(pr).strip()[0].lower()
            except (EOFError, KeyboardInterrupt, IndexError):
                choice = 'q'

            print '\nYou picked: [%s]' % choice
            if choice not in 'devq':
                print 'Invalid option, try again'
            else:
                break
        if choice == 'q':
            break
        CMDs[choice]()



if __name__ == '__main__':
    showmenu()




    #def worker():
#    while True:
#        task = _queue.pop()
#        ......
#
#
#        _writequeue.push(.....)
#python   队列
#if __name__=='__main__':

# while True:
#     if threadpool.idle() > 0:
#         tasks = sql.fetch_task(threadpool.idel())
#         _queue.push(tass)
#
#    time.sleep(5)
#
#
#    _writequeue.toitems().update()
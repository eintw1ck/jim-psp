#-*- coding: ISO-8859-1 -*-

import psp, threading, time

class NumberedThread(threading.Thread):
    def __init__(self, n, lock):
        self.n = n
        self.lock = lock

        threading.Thread.__init__(self)

    def run(self):
        for i in xrange(10):
            psp.debug('Hello, thread %d here\n' % self.n)
            time.sleep(1)

def main():
    psp.debugScreenInit()

    # We use a lock so that output doesn't get mangled
    lock = threading.Lock()

    thr1 = NumberedThread(1, lock)
    thr2 = NumberedThread(2, lock)

    thr1.start()
    thr2.start()

    thr1.join()
    thr2.join()

    psp.debug('==== FINISHED\n')
    time.sleep(2)

if __name__ == '__main__':
    main()

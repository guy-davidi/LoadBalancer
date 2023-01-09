#! /usr/bin/env python2.7

import os.path
import time
import sys

filename = sys.argv[1]
timeout = float(sys.argv[2])

start_time = time.time()
while True:
    if os.path.isfile(filename):
        sys.exit(0)
    if time.time() - start_time > timeout:
        print 'Error: File %s not created within %.2f seconds' % (filename, timeout)
        sys.exit(1)
    time.sleep(0.1)

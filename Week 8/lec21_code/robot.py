#!/usr/bin/env python

import socket
import sys
import time

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((sys.argv[1], int(sys.argv[2])))

linenum = 0
while True:
  s.send("huckleberry finn" + "\n")
  print linenum
  print s.recv(3000).strip()
  time.sleep(1)
  linenum += 1

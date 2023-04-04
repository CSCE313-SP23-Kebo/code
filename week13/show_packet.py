# view mycode.py
#!/usr/bin/env python3
from scapy.all import *

pkt = IP()
pkt.dst = "192.168.1.1"
pkt.src = "192.168.8.14"
pkt.ttl = 10

pkt.show()

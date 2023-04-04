#!/bin/env python3
from scapy.all import *

print("SNIFFING PACKETS.........")

def print_pkt(pkt):
   print("Source IP:", pkt[IP].src)
   print("Destination IP:", pkt[IP].dst)
   print("Protocol:", pkt[IP].proto)
   print("\n")

#pkt = sniff(iface='br-5336efd1c0d5', filter='ip',prn=print_pkt)
#pkt = sniff(iface='br-5336efd1c0d5', filter='ip and dst port 23',prn=print_pkt)
pkt = sniff(iface='br-5336efd1c0d5', filter='dst port 23',prn=print_pkt)

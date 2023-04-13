'''
Sniff packets on the network.

Note:
Use the following commands to see your network interface:
ip addr show
or
ifconfig -a
'''

#!/bin/env python3
from scapy.all import *

print("SNIFFING PACKETS.........")

def print_pkt(pkt):
   print("Source IP:", pkt[IP].src)
   print("Destination IP:", pkt[IP].dst)
   print("Protocol:", pkt[IP].proto)
   print("\n")

#pkt = sniff(filter='icmp', prn=print_pkt) # no interface
#pkt = sniff(iface='ens4', filter='icmp', prn=print_pkt) # no interface 
#pkt = sniff(iface='ens4', filter='ip',prn=print_pkt)
pkt = sniff(iface='ens4', filter='ip and dst port 23',prn=print_pkt)
#pkt = sniff(iface='ens4', filter='dst port 23',prn=print_pkt)

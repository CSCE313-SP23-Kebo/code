from Crypto.Cipher import PKCS1_OAEP
from Crypto.PublicKey import RSA

message = b'Santa train leaves town at 6:AM\n'
key = RSA.importKey(open('public.pem').read())
cipher = PKCS1_OAEP.new(key)
ciphertext = cipher.encrypt(message)
f = open('ciphertext.bin','wb')
f.write(ciphertext)
f.close() 

import sys
import random
n=int(sys.argv[1])
m=int(sys.argv[2])
s=int(sys.argv[3])
print n,m,s
ih=1
iv=1
bh=n
bv=m
print ih,iv,bh,bv

for i in range(n-1):
	for i in range(m-1):
		print random.randint(0,400),
	print '\n',
	for i in range(m):
		print random.randint(0,400),
	print '\n',
for i in range(m-1):
	print random.randint(0,400),
print '\n',

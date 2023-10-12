import matplotlib.pyplot as plt
import sys

if sys.argv[1] == '1':
	with open('results/homhops.txt') as f:
    		lines = f.readlines()
    		homhops = [0 for x in range(len(lines))]
    		for x in range(len(lines)): homhops[x] = float(lines[x])
					
	x = [x+1 for x in range(len(homhops))]
	plt.plot(x, homhops, label='homHoPS', color = 'b')
	f.close()

if sys.argv[2] == '1':
	with open('results/homhopsplus.txt') as f2:
	    	lines = f2.readlines()
	    	homhopsplus = [0 for x in range(len(lines))]
	    	for x in range(len(lines)): homhopsplus[x] = float(lines[x])

	x2 = [x+1 for x in range(len(homhopsplus))]
	plt.plot(x2, homhopsplus, label='homHoPS+', color = 'c')

if sys.argv[3] == '1':
	with open('results/hops.txt') as f3:
	    	lines = f3.readlines()
	    	hops = [0 for x in range(len(lines))]
	    	for x in range(len(lines)): hops[x] = float(lines[x])

	x3 = [x+1 for x in range(len(hops))]
	plt.plot(x3, hops, label='HoPS', color = 'r')

if sys.argv[4] == '1':
	with open('results/sghd.txt') as f4:
	    	lines = f4.readlines()
	    	sghd = [0 for x in range(len(lines))]
	    	for x in range(len(lines)): sghd[x] = float(lines[x])

	x4 = [x+1 for x in range(len(sghd))]
	plt.plot(x4, sghd, label='sGHD', color = 'g')

plt.xlabel('time [s]')
plt.ylabel('relative error')

plt.legend()

plt.show()
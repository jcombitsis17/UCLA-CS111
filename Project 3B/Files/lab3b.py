#!/usr/local/cs/bin/python3

# NAME: Jordan Combitsis, Anchal Sinha
# EMAIL: jcombitsis17@gmail.com, anchalsinha@ucla.edu
# ID: 004921527, 204986787


import sys

if len(sys.argv) != 2:
	print('Error: Invalid number of arguments. Usage: python3 ./lab3b FILE', file=sys.stderr)
	sys.exit(1)
try:
	summary_file = open(sys.argv[1], 'r')
except Exception as e:
	print('Error: Unable to open csv file', file=sys.stderr)
	sys.exit(1)

group_list = []
bfree_list = []
ifree_list = []
inode_list = []
inode_nums = []
dirent_list = []
indirect_list = []

for line in summary_file.readlines():
	row = line.split(',')
	line_type = row[0]

	if line_type == 'SUPERBLOCK':
		num_blocks = int(row[1])
		superblock = row
	elif line_type == 'GROUP':
		group_list.append(row)
	elif line_type == 'IFREE':
		ifree_list.append(int(row[1]))
	elif line_type == 'BFREE':
		bfree_list.append(int(row[1]))
	elif line_type == 'INODE':
		inode_nums.append(int(row[1]))
		inode_list.append(row)
	elif line_type == 'DIRENT':
		dirent_list.append(row)
	elif line_type == 'INDIRECT':
		indirect_list.append(row)
	
###block consistency audit
blocks = {}
#check inode inconsistencies
for inode in inode_list:
	inode_num = int(inode[1])

	for i in range(12, 27):  #blocks
		offset = i - 12
		block_type = ''
		if i == 26:
			block_type = 'TRIPLE INDIRECT '
			offset = 65804
		elif i == 25:
			block_type = 'DOUBLE INDIRECT '
			offset = 268
		elif i == 24:
			block_type = 'INDIRECT '
			offset = 12
		block_type += 'BLOCK'
		
		block_num = int(inode[i])
		if block_num != 0:
			if block_num < 0 or block_num > num_blocks:
				print(f'INVALID {block_type} {block_num} IN INODE {inode_num} AT OFFSET {offset}')
			elif block_num < 8:
				print(f'RESERVED {block_type} {block_num} IN INODE {inode_num} AT OFFSET {offset}')
			elif block_num in blocks:
				blocks[block_num].append((block_type, inode_num, offset))
			else:
				blocks[block_num] = [(block_type, inode_num, offset)]

#check indirect inconsistencies
for indirect in indirect_list:
	offset = int(indirect[3])
	block_type = ''
	level = int(indirect[2])
	if level == 3:
		block_type += 'DOUBLE '
	if i == 2:
		block_type += 'INDIRECT '
	block_type += 'BLOCK'

	block_num = int(indirect[5])
	if block_num != 0:
		if block_num < 0 or block_num > num_blocks:
			print(f'INVALID {block_type} {block_num} IN INODE {inode_num} AT OFFSET {offset}')
		elif block_num < 8:
			print(f'RESERVED {block_type} {block_num} IN INODE {inode_num} AT OFFSET {offset}')
		elif block_num in blocks:
			blocks[block_num].append((block_type, int(indirect[1]), offset))
		else:
			blocks[block_num] = [(block_type, int(indirect[1]), offset)]

#check allocated, reserved, and duplicate blocks
for block_num in range(8, num_blocks):
	if block_num not in blocks and block_num not in bfree_list:
		print(f'UNREFERENCED BLOCK {block_num}')
	elif block_num in blocks and block_num in bfree_list:
		print(f'ALLOCATED BLOCK {block_num} ON FREELIST')
	if block_num in blocks and len(blocks[block_num]) > 1:
		for (block_type, inode_num, offset) in blocks[block_num]:
			print(f'DUPLICATE {block_type} {block_num} IN INODE {inode_num} AT OFFSET {offset}')
		

#inode allocation audit
for inode in inode_list:
	inode_num = int(inode[1])
	if inode_num in ifree_list:
		print(f'ALLOCATED INODE {inode_num} ON FREELIST')
for inode in range(int(superblock[7]), int(superblock[2])):
	if inode not in inode_nums and inode not in ifree_list:
		print(f'UNALLOCATED INODE {inode} NOT ON FREELIST')
	
#directory consistency audits
inode_parent_list = [None] * int(superblock[2])
inode_links = [0] * int(superblock[2])
inode_parent_list[2] = 2
for dirent in dirent_list:
	parent = int(dirent[1])
	inode_num = int(dirent[3])
	name = dirent[6].strip()
	if inode_num < 1 or inode_num > int(superblock[2]):
		print(f'DIRECTORY INODE {parent} NAME {name} INVALID INODE {inode_num}')
	elif inode_num not in inode_nums:
		print(f'DIRECTORY INODE {parent} NAME {name} UNALLOCATED INODE {inode_num}')
	else:
		# if inode_num in inode_links:
		inode_links[inode_num] += 1
		if name != '\'.\'' and name != '\'..\'':
			inode_parent_list[inode_num] = parent

for inode in inode_list:
	inode_num = int(inode[1])
	linkcount = int(inode[6])
	# if inode_num in inode_links:
	if linkcount != inode_links[inode_num]:
		print(f'INODE {inode_num} HAS {inode_links[inode_num]} LINKS BUT LINKCOUNT IS {linkcount}')

for dirent in dirent_list:
	parent = int(dirent[1])
	inode = int(dirent[3])
	name = dirent[6].strip()
	if name == '\'.\'' and inode != parent:
		print(f'DIRECTORY INODE {parent} NAME {name} LINK TO INODE {inode} SHOULD BE {parent}')
	if name == '\'..\'' and inode != inode_parent_list[inode]:
		print(f'DIRECTORY INODE {parent} NAME {name} LINK TO INODE {inode} SHOULD BE {parent}')

summary_file.close()
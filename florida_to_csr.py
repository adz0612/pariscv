import sys

fp = open(sys.argv[1],'r')
lines = fp.readlines()



#rows = (int)(lines[0].split(' ')[0])
#columns = (int)(lines[0].split(' ')[1])
#nnz = (int)(lines[0].split(' ')[2])

#print(rows)
#print(nnz)
#print(columns)
i=0
rows=2048
column=2048
nnz=12358
no_value = 0
i =0
#row_ptr = [0 for x in range(rows+1)]
#col_ptr = [[] for x in range(rows+1)]
#values   = [[] for x in range(rows+1)]
list1 =[]
list2 = []
#for line in lines:
  #  print (line)
#    if i != 0:
#        splits = line.split(' ')
#        node1 =(int)(line.split(' ')[0])
#        node2 =(int)(line.split(' ')[1])
#        row_ptr[node1] = row_ptr[node1]+1
#        col_ptr[node1].append(node2)
#        values[node1].append(node1)
#    i = i + 1
for line in lines:
    node1 =(int)(line.split(' ')[0])
    node2 =(int)(line.split(' ')[1])
    list1.append(node1)
#    list2.append(node2)
#    col_ptr[i].append(node2)
#    values[i].append(node1)
    i = i + 1
#print (row_ptr[1])
#print (col_ptr[1])
#splits = line.split(' ')\
#print(splits)
fp_csr = open(sys.argv[2],'w')



#fp_csr.write((str)(rows))
#fp_csr.write('\n')
#fp_csr.write((str)(nnz))
#fp_csr.write('\n')
rows=2048
acc = 0
keys=0
vals=0
for i in range(rows):
#    fp_csr.write((str)(acc))
#    fp_csr.write('{')
#    keys=list1[i]
#    vals=list2[i]
   # fp_csr.write((str)(values[i]))
    fp_csr.write('-1')
    fp_csr.write(',')
#    fp_csr.write(str(vals))
#    fp_csr.write('}, ')
    if(i%100==0):
    	fp_csr.write('\n')
	
#    acc = acc + row_ptr[i]


#col_ptr =  [inner for outer in col_ptr for inner in outer]
#for i in range(nnz):
#    fp_csr.write((str)(col_ptr[i]))
#    fp_csr.write(',')
#    if(i%100==0):
#    	fp_csr.write('\n')

#values =  [inner for outer in values for inner in outer]
#for i in range(nnz):
#    fp_csr.write((str)(values[i]))
#    fp_csr.write('\n')

fp.close()
fp_csr.close()

        


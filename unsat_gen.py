import sys
import random

def generate_unsat_graph(n):
	l = [(0,1)]
	for i in range(2, n):
		l.append((i, random.randrange(0, i)))
	return l
	
def graph_to_string(g):
	return map(lambda x: str(x[0])+" "+str(x[1])+"\n", g)

try:
	nnodes = int(sys.argv[1])
	if nnodes < 3:
		raise
	g = generate_unsat_graph(nnodes)
	gl = graph_to_string(g)
	gl = [str(nnodes) + " " + str(len(g)) + " " + str(nnodes - 2) + "\n"] + gl
	with open("unsat_graph.txt","w") as f:
		f.writelines(gl)
except:
	print "Usage: python unsat_gen.py NODES_IN_GRAPH\n NODES_IN_GRAPH>3"
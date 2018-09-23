import sys
import random

def choose_random_subset(chl, remove = False):
	l = []
	for i in range(len(chl)):
		if chl[i] != -1 and random.randrange(0, 2):
			l.append(chl[i])
			if remove:
				chl[i] = -1
	return l
	
def create_cross_links(l1, l2):
	return [(x,y) for x in l1 for y in l2]
	
def create_self_links(l):
	ans = []
	for i in xrange(len(l)):
		for j in range(i+1, len(l)):
			ans.append((l[i], l[j]))
	return ans

# k is number of nodes
def generate_sat_graph(k):
	l = []
	nodes = range(k)
	ctr = 0
	chosen = []
	
	while len(nodes)>0:
		ctr += 1
		
		currg = []
		currg.append(nodes[-1])
		nodes.pop()
		currg.extend(choose_random_subset(nodes, remove=True))
		
		if chosen != []:
			cross = chosen[:1] + choose_random_subset(chosen[1:])
		else: cross = []
		l.extend(create_cross_links(cross, currg))
		l.extend(create_self_links(currg))
		
		chosen.extend(currg)
		nodes = [x for x in nodes if x != -1]
	
	return ctr, l

def graph_to_string(g):
	return map(lambda x: str(x[0])+" "+str(x[1])+"\n", g)
	
try:
	nnodes = int(sys.argv[1])
	cqn, g = generate_sat_graph(nnodes)
	gl = graph_to_string(g)
	gl = [str(nnodes) + " " + str(len(g)) + " " + str(cqn) + "\n"] + gl
	with open("sat_graph.txt","w") as f:
		f.writelines(gl)
except:
	print "Usage: python sat_gen.py NODES_IN_GRAPH"


#import time
import cProfile, pstats
import shorter
import random

class Test(object):
	
	def __init__(self, v, title=""):
		self.title = random.choice([
			"Over Kredit Toyota Great Corolla '95 Manual Maknyussss, rugi ga masuk...",
			"JUAL: mobil toyota kijang sx 2001 gan!",
			"JUAL: toyota great corolla 1.6SEG Full S.System",
			"JUAL: Toyota corona mark ii' 1985",
			"toyota corona 1978, retro, 13 jt negoo",
			"Toyota Corolla Twincam 1.3SE",
			"JUAL: TOYOTA AVANZA G 2004 BANDUNG (mantap banget mobilnya...liat aja dulu)",
			"JUAL: Toyota Yaris Silver tahun 2007 S Limited A/T muluss!",
			"JUAL: Jual mobil toyota avanza g hitam bandung lsg dr pemakai",
			"JUAL: Toyota Harrier 3.0 Th.2002"
		])
		self.value = v
		self.value2 = random.randint(0,10000)
		
	def __repr__(self):
		return "(%s:%d %d)" % (self.title,self.value, self.value2)



test_list = [
	Test(random.randint(0,5)) for x in xrange(0,5)
]

rv = []

def test_sort():
	
	def do_csort():
		global rv
		rv = sorted(test_list,shorter.sort)
		return rv

	def do_pysort():
		global rv
		def py_sorter(a,b):
			n = cmp(a.value,b.value)
			if n == 0:
				n = cmp(a.value2,b.value2)
			return n

		rv = sorted(test_list,py_sorter)

	cProfile.run('do_csort()',"Csort")
	p = pstats.Stats('Csort')
	p.strip_dirs().sort_stats(-1).print_stats()

	cProfile.run('do_pysort()',"Pysort")
	p = pstats.Stats('Pysort')
	p.strip_dirs().sort_stats(-1).print_stats()


	print rv[:10]


def do_crank():
	global rv
	rv = []
	
	def crank(obj):
		keywords = "toyota avanza hitam"
		absrank = 50
	
		rank = shorter.rank(obj, keywords, absrank)
		print "rank of `%s` = %s" % (obj,rank)
		return (rank, obj)
	
	rv = map( crank, test_list )
		
	print rv
	
	return rv


do_crank()








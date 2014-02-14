#!/usr/bin/python


__author__ = "Jeremy Dobbins-Bucklad"
__email__ = "j.american.db@gmail.com"
__class__ = "CS671"

import string
from operator import itemgetter
from collections import Counter

# Write a filter(f, lst) function which takes a function and 
# and a list and gives back a list containing
# only elements of lst for which f evaluates to True.
def filter(f, lst):
	return [x for x in lst if f(x)]

# Write a function matchBrackets(s) which looks at string s and determines 
# whether all brackets ((), {}, [], <>) have a matched pair and are closed 
# in the same order in which they were opened. 
# For instance, matchBrackets("{{}") and matchBrackets("({)}") return False, # while matchBrackets("({})") and matchBrackets("no brackets") return True.
def matchBrackets(s):
	brackets = "(){}[]<>"
	brktTpls = [("(",")"),("{","}"),("[","]"),("<",">")]
	stack = []
	for c in s:
		if c in brackets:
			if len(stack) > 0 and (stack[len(stack)-1],c) in brktTpls:
				stack.pop()
			else:
				stack.append(c)

	return len(stack) is 0


# Write a wordCounts(s) function which looks at the words in the string 
# s (separated by spaces, ignoring case and removing punctuation marks 
# at the ends), and returns a list of tuples in the form 
# (word, count), sorted by highest count to lowest. 
def wordCounts(s): 
	strArr = s.split()
	strArr = [x.strip(string.punctuation) for x in strArr]
	strArr = [x.lower() for x in strArr]

	cnt = Counter()
	for word in strArr:
	    cnt[word] += 1

	return sorted(cnt.items(),key=itemgetter(1),reverse=True)


def nthPrime(n):
	"""Finds the nth prime, with the optimization of memoization."""
	# Setup memoized list
	if "primes" not in nthPrime.__dict__: 
		nthPrime.primes = [1,2,3]

	def isNotPrime(x,l):
		"""Determines primeness by attempting to divide x by all of the
		previously determined prime numbers. If a prime cleanly divides x
		(no remainder), then x is not prime."""
		for n in l:
			if x % n is 0:
				# print (str(x)+" is not prime")
				return True
		# print (str(x)+" is prime")
		return False

	def findNextPrime(l):
		"""Finds prime numbers by searching past the largest prime number
		found. Does so by adding 2 (to a guaranteed minimum of 3), checking
		for primeness, and repeating until it hits a prime"""
		curr = l[len(l)-1] + 2 # add 2 to last prime number found
		while( isNotPrime(curr,l) ):
			curr += 2
		# print str(curr)+" is prime"
		return curr

	length = len(nthPrime.primes)
	if n >= length: # Build list up to requested prime
		gap = n - (length -1)
		for i in xrange(gap):
			nthPrime.primes.append(findNextPrime(nthPrime.primes[1:]))

	# print nthPrime.primes
	return nthPrime.primes[n]



class USDollar(object):
	"""Represents a US Dollar, with implementation of basic arithmetical
	and comparison operators (+,-,<,>,<=,>=). An exercise in properties, 
	instance-checking, and operator overrides.
	"""
	def __init__(self,other=0):
		if isinstance (other,USDollar):
			self._value = other._value
		elif isinstance (other,float) or isinstance (other,int):
			self.value = other
		else:
			self._value = 0

	@staticmethod
	def truncate(n):
		return float(int(n*100))/100

	@staticmethod
	def ftoi(f):
		"""Truncates a float to two decimal places and stores as an Int"""
		return int(f*100)

	@staticmethod
	def itof(i):
		return float(i)/100

	@property
	def value(self):
		"""Get the US dollar value"""
		return float(self._value)/100

	@value.setter
	def value(self,v):
		self._value = int(v*100)


	@value.deleter
	def value(self):
		self._value = 0

	def __repr__(self):
		return "${:.2f}".format(self.value)

	def __add__(self,other):
		if isinstance (other,USDollar):
			v = USDollar(self.value + other.value)
		elif isinstance (other,float):
			v = USDollar(self.value+USDollar.truncate(other))
		elif isinstance (other,int):
			v = USDollar(self.value + other)
		else:
			return None
		return v		

	def __sub__(self,other):
		if isinstance (other,USDollar):
			v = USDollar(self.value - other.value)
		elif isinstance (other,float):
			v = USDollar(self.value - USDollar.truncate(other))
		elif isinstance (other,int):
			v = USDollar(self.value - other)
		else:
			return None
		return v		

	def __iadd__(self,other):
		if isinstance (other,USDollar):
			self._value += other._value
			return self
		elif isinstance (other,float):
			self.value = self.value + USDollar.truncate(other)
			return self
		elif isinstance (other,int):
			self.value = self.value + other
			return self
		else:
			return None
		return v		

	def __isub__(self,other):
		if isinstance (other,USDollar):
			self._value -= other._value
			return self
		elif isinstance (other,float):
			self.value = self.value - USDollar.truncate(other)
			return self
		elif isinstance (other,int):
			self.value = self.value - other
			return self
		else:
			return None
		return v

	def __lt__(self,other):
		if isinstance (other,USDollar):
			return self._value < other._value
		elif isinstance (other,float):
			return self.value < USDollar.truncate(other)
		elif isinstance (other,int):
			return self.value < other
		else:
			return None
		return v

	def __le__(self,other):
		if isinstance (other,USDollar):
			return self._value <= other._value
		elif isinstance (other,float):
			return self.value <= USDollar.truncate(other)
		elif isinstance (other,int):
			return self.value <= other
		else:
			return None
		return v

	def __eq__(self,other):
		if isinstance (other,USDollar):
			return self._value == other._value
		elif isinstance (other,float):
			return self.value == USDollar.truncate(other)
		elif isinstance (other,int):
			return self.value == other
		else:
			return None
		return v

	def __ne__(self,other):
		ret = self.__eq__(other)
		if ret is None:
			return None
		else:
			return not ret 

	def __gt__(self,other):
		if isinstance (other,USDollar):
			return self._value > other._value
		elif isinstance (other,float):
			return self.value > USDollar.truncate(other)
		elif isinstance (other,int):
			return self.value > other
		else:
			return None
		return v

	def __ge__(self,other):
		if isinstance (other,USDollar):
			return self._value >= other._value
		elif isinstance (other,float):
			return self.value >= USDollar.truncate(other)
		elif isinstance (other,int):
			print "{} >= {}".format(self._value,other)
			return self.value >= other
		else:
			return None
		return v


d = USDollar(3.009)
e = USDollar(124.678)
f = USDollar(7)
print "3.76 - 2 = "+str(3.76-2)

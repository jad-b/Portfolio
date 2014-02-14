import unittest
from timeout import timeout
from time import time
import main

hamlet = "To be, or not to be? That is the question."
primes = [1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223, 1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291, 1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373, 1381, 1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451, 1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511, 1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583, 1597, 1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657, 1663, 1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733, 1741, 1747, 1753, 1759, 1777, 1783, 1787, 1789, 1801, 1811, 1823, 1831, 1847, 1861, 1867, 1871, 1873, 1877, 1879, 1889, 1901, 1907, 1913, 1931, 1933, 1949, 1951, 1973, 1979, 1987, 1993, 1997, 1999, 2003, 2011, 2017, 2027, 2029, 2039, 2053, 2063, 2069, 2081, 2083, 2087, 2089, 2099, 2111, 2113, 2129, 2131, 2137, 2141, 2143, 2153, 2161, 2179, 2203, 2207, 2213, 2221, 2237, 2239, 2243, 2251, 2267, 2269, 2273, 2281, 2287, 2293, 2297, 2309, 2311, 2333, 2339, 2341, 2347, 2351, 2357, 2371, 2377, 2381, 2383, 2389, 2393, 2399, 2411, 2417, 2423, 2437, 2441, 2447, 2459, 2467, 2473, 2477, 2503, 2521, 2531, 2539, 2543, 2549, 2551, 2557, 2579, 2591, 2593, 2609, 2617, 2621, 2633, 2647, 2657, 2659, 2663, 2671, 2677, 2683, 2687, 2689, 2693, 2699, 2707, 2711, 2713, 2719, 2729, 2731, 2741, 2749, 2753, 2767, 2777, 2789, 2791, 2797, 2801, 2803, 2819, 2833, 2837, 2843, 2851, 2857, 2861, 2879, 2887, 2897, 2903, 2909, 2917, 2927, 2939, 2953, 2957, 2963, 2969, 2971, 2999, 3001, 3011, 3019, 3023, 3037, 3041, 3049, 3061, 3067, 3079, 3083, 3089, 3109, 3119, 3121, 3137, 3163, 3167, 3169, 3181, 3187, 3191, 3203, 3209, 3217, 3221, 3229, 3251, 3253, 3257, 3259, 3271, 3299, 3301, 3307, 3313, 3319, 3323, 3329, 3331, 3343, 3347, 3359, 3361, 3371, 3373, 3389, 3391, 3407, 3413, 3433, 3449, 3457, 3461, 3463, 3467, 3469, 3491, 3499, 3511, 3517, 3527, 3529, 3533, 3539, 3541, 3547, 3557, 3559]

class TestFilter(unittest.TestCase):

    @timeout(1)
    def testEmpty(self):
        orig = []
        result = []
        self.assertEqual(main.filter(lambda x: x>3, orig), result)

    @timeout(1)
    def testNumbers(self):
        orig = [1,2,3,4,5,7,0,9]
        result = [3,0,9]
        self.assertEqual(main.filter(lambda x: x%3==0, orig), result)

    @timeout(1)
    def testStrings(self):
        orig = hamlet.split()
        result = ['To', 'or', 'to', 'is']
        self.assertEqual(main.filter(lambda x: len(x)<3, orig), result)


class TestMatchBrackets(unittest.TestCase):

    @timeout(1)
    def testEmpty(self):
        orig = ""
        result = True
        self.assertEqual(main.matchBrackets(orig), result)

    @timeout(1)
    def testNoBrackets(self):
        orig = "no brackets"
        result = True
        self.assertEqual(main.matchBrackets(orig), result)

    @timeout(1)
    def testNotClosed(self):
        orig = "{{}"
        result = False
        self.assertEqual(main.matchBrackets(orig), result)

    @timeout(1)
    def testSinglePair(self):
        orig = "()"
        result = True
        self.assertEqual(main.matchBrackets(orig), result)

    @timeout(1)
    def testMultiplePairs(self):
        orig = "()<>"
        result = True
        self.assertEqual(main.matchBrackets(orig), result)

    @timeout(1)
    def testOutOfOrder(self):
        orig = "({)}"
        result = False
        self.assertEqual(main.matchBrackets(orig), result)
        

class TestWordCounts(unittest.TestCase):

    @timeout(1)
    def testEmpty(self):
        orig = ""
        result = []
        self.assertEqual(main.wordCounts(orig), result)

    @timeout(1)
    def testOneWord(self):
        orig = "word"
        result = [("word", 1)]
        self.assertEqual(main.wordCounts(orig), result)

    @timeout(1)
    def testOrder(self):
        orig = "the quick fox jumped over the lazy dog while the dog slept"
        result = [('the', 3), ('dog', 2), ('lazy', 1), ('jumped', 1),
                  ('over', 1), ('slept', 1), ('fox', 1), ('while', 1),
                  ('quick', 1)]
        ret = main.wordCounts(orig)
        self.assertEqual(ret[0], result[0])
        self.assertEqual(ret[1], result[1])
        for x in ret[2:]:
            self.assertTrue(x[1]==1)

    @timeout(1)
    def testCapitalization(self):
        orig = "same Same SAME samE SAme SaMe"
        result = [('same', 6)]
        self.assertEqual(main.wordCounts(orig), result)

    @timeout(1)
    def testPunctuation(self):
        orig = "same same. same, not_same same?"
        result = [('same', 4), ('not_same', 1)]
        self.assertEqual(main.wordCounts(orig), result)
    

class TestNthPrime(unittest.TestCase):

    def setup(self):
        try:
            main.nthPrime.primes = main.nthPrime.primes[:5]
        except:
            pass

    @timeout(1)
    def testFirst(self):
        orig = 0
        result = 1
        self.assertEqual(main.nthPrime(orig), result)

    @timeout(1)
    def testStored(self):
        self.setup()
        orig = 49
        result = 50
        main.nthPrime(orig)
        self.assertEqual(len(main.nthPrime.primes), result)

    @timeout(1)
    def testFifth(self):
        orig = 5
        result = 11
        self.assertEqual(main.nthPrime(orig), result)

    @timeout(3)
    def testHundredth(self):
        self.setup()
        orig = 100
        result = 541
        self.assertEqual(main.nthPrime(orig), result)

    @timeout(4)
    def testPast(self):
        self.setup()
        orig = 1001
        result = 7919
        #start timing
        t1 = time()
        main.nthPrime(orig)
        t1 = time() - t1
        #start timing
        t2 = time()
        ret = main.nthPrime(orig-1)
        t2 = time() - t2
        self.assertEqual(ret, result)
        self.assertTrue(t2<(t1/2.0))

    @timeout(5)
    def testSame(self):
        self.setup()
        orig = 1000
        result = 7919
        #start timing
        t1 = time()
        main.nthPrime(orig)
        t1 = time() - t1
        #start timing
        t2 = time()
        ret = main.nthPrime(orig)
        t2 = time() - t2
        self.assertEqual(ret, result)
        self.assertTrue(t2<(t1/2.0))

    @timeout(4)
    def testAllValid(self):
        self.setup()
        orig = 499
        main.nthPrime(orig)
        self.assertEqual(main.nthPrime.primes, primes)


class TestUSDollar(unittest.TestCase):

    @timeout(1)
    def testOne(self):
        orig = 1.0
        result = 1.0
        self.assertEqual(main.USDollar(orig).value, result)

    @timeout(1)
    def testCents(self):
        orig = 1.05
        result = 1.05
        self.assertEqual(main.USDollar(orig).value, result)

    @timeout(1)
    def testLow(self):
        orig = 2.001
        result = 2.0
        self.assertEqual(main.USDollar(orig).value, result)

    @timeout(1)
    def testHigh(self):
        orig = 2.999
        result = 2.99
        self.assertEqual(main.USDollar(orig).value, result)

    @timeout(1)
    def testStrLow(self):
        orig = 1.07
        result = "$1.07"
        self.assertEqual(str(main.USDollar(orig)), result)

    @timeout(1)
    def testStrWholeDollar(self):
        orig = 2.00
        result = "$2.00"
        self.assertEqual(str(main.USDollar(orig)), result)

    @timeout(1)
    def testStrZero(self):
        orig = 0.0
        result = "$0.00"
        self.assertEqual(str(main.USDollar(orig)), result)

    @timeout(1)
    def testEq(self):
        orig = 0.009
        self.assertTrue(main.USDollar(orig)==main.USDollar(orig))
        self.assertFalse(main.USDollar(orig)==main.USDollar(1.0))
        self.assertTrue(main.USDollar(orig)==orig)
        self.assertFalse(main.USDollar(orig)==1.0)
        self.assertTrue(main.USDollar(orig)==int(orig))
        self.assertFalse(main.USDollar(orig)==int(1.0))

    @timeout(1)
    def testLt(self):
        orig = 2.009
        self.assertTrue(main.USDollar(orig)<main.USDollar(5.0))
        self.assertFalse(main.USDollar(orig)<main.USDollar(orig))
        self.assertFalse(main.USDollar(5.0)<main.USDollar(orig))
        self.assertTrue(main.USDollar(orig)<5.0)
        self.assertFalse(main.USDollar(orig)<orig)
        self.assertFalse(main.USDollar(5.0)<orig)
        self.assertTrue(main.USDollar(orig)<int(5.0))
        self.assertFalse(main.USDollar(orig)<int(orig))
        self.assertFalse(main.USDollar(5.0)<int(orig))

    @timeout(1)
    def testLe(self):
        orig = 2.009
        self.assertTrue(main.USDollar(orig)<=main.USDollar(5.0))
        self.assertTrue(main.USDollar(orig)<=main.USDollar(orig))
        self.assertFalse(main.USDollar(5.0)<=main.USDollar(orig))
        self.assertTrue(main.USDollar(orig)<=5.0)
        self.assertTrue(main.USDollar(orig)<=orig)
        self.assertFalse(main.USDollar(5.0)<=orig)
        self.assertTrue(main.USDollar(orig)<=int(5.0))
        self.assertTrue(main.USDollar(orig)<=int(orig))
        self.assertFalse(main.USDollar(5.0)<=int(orig))

    @timeout(1)
    def testGt(self):
        orig = 2.009
        self.assertFalse(main.USDollar(orig)>main.USDollar(5.0))
        self.assertFalse(main.USDollar(orig)>main.USDollar(orig))
        self.assertTrue(main.USDollar(5.0)>main.USDollar(orig))
        self.assertFalse(main.USDollar(orig)>5.0)
        self.assertFalse(main.USDollar(orig)>orig)
        self.assertTrue(main.USDollar(5.0)>orig)
        self.assertFalse(main.USDollar(orig)>int(5.0))
        self.assertFalse(main.USDollar(orig)>int(orig))
        self.assertTrue(main.USDollar(5.0)>int(orig))

    @timeout(1)
    def testGe(self):
        orig = 2.009
        self.assertFalse(main.USDollar(orig)>=main.USDollar(5.0))
        self.assertTrue(main.USDollar(orig)>=main.USDollar(orig))
        self.assertTrue(main.USDollar(5.0)>=main.USDollar(orig))
        self.assertFalse(main.USDollar(orig)>=5.0)
        self.assertTrue(main.USDollar(orig)>=orig)
        self.assertTrue(main.USDollar(5.0)>=orig)
        self.assertFalse(main.USDollar(orig)>=int(5.0))
        self.assertTrue(main.USDollar(orig)>=int(orig))
        self.assertTrue(main.USDollar(5.0)>=int(orig))

    @timeout(1)
    def testAdd(self):
        orig = 6.009
        result = 8.0
        ret = (main.USDollar(orig)+main.USDollar(2.001))
        self.assertEqual(ret.value, result)
        ret = (main.USDollar(orig)+2.001)
        self.assertEqual(ret.value, result)
        ret = (main.USDollar(orig)+int(2.001))
        self.assertEqual(ret.value, result)

    @timeout(1)
    def testSub(self):
        orig = 3.009
        result = 1.0
        ret = (main.USDollar(orig)-main.USDollar(2.001))
        self.assertEqual(ret.value, result)
        ret = (main.USDollar(orig)-2.001)
        self.assertEqual(ret.value, result)
        ret = (main.USDollar(orig)-int(2.001))
        self.assertEqual(ret.value, result)

    @timeout(1)
    def testiAdd(self):
        orig = 6.009
        result = 8.0
        d = main.USDollar(orig)
        d += main.USDollar(2.001)
        self.assertEqual(d.value, result)
        d = main.USDollar(orig)
        d += 2.001
        self.assertEqual(d.value, result)
        d = main.USDollar(orig)
        d += int(2.001)
        self.assertEqual(d.value, result)

    @timeout(1)
    def testiSub(self):
        orig = 3.009
        result = 1.0
        d = main.USDollar(orig)
        d -= main.USDollar(2.001)
        self.assertEqual(d.value, result)
        d = main.USDollar(orig)
        d -= 2.001
        self.assertEqual(d.value, result)
        d = main.USDollar(orig)
        d -= int(2.001)
        self.assertEqual(d.value, result)
    

if __name__ == "__main__":
    suite = unittest.TestSuite()
    classes = [TestFilter, TestMatchBrackets, TestWordCounts,
               TestNthPrime, TestUSDollar]
    for c in classes:
        suite.addTests(unittest.TestLoader().loadTestsFromTestCase(c))

    import sys
    r = unittest.TestResult()
    suite.run(r)
    if r.wasSuccessful():
        print "All tests passed."
    else:
        print "Failed test traces:"
        for f in r.failures:
            for x in f: print x
        print "Errored test traces:"
        for f in r.errors:
            for x in f: print x

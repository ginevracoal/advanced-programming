import unittest

# class Problem1(unittest.TestCase):
    
#     def test(self):
#         self.assertEqual(2,3)

function_problem2 = lambda x: sum([n for n in range(x) if n%3==0 or n%5==0])

class Problem2(unittest.TestCase):

	def setUp(self):
		self.func = function_problem2 # funzione scritta dall'altro gruppo

	def test_size1000(self):
		res = self.func(1000)
		self.assertEqual(res, 233168)

	def test_size10000(self):
		res = self.func(10000)
		self.assertEqual(res, 233168)

if __name__ == '__main__':
    unittest.main()
    
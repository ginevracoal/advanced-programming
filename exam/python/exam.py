#importing modules
import unittest
import datetime
from collections import defaultdict

class PostcardList(object):
  
    def __init__(self): # __init__ invokes the constructor for the class, self is like this in c++
        self._file = None
        self._postcards = [] 
        self._date = {}
        self._from = {}
        self._to = {}
        self._addss = '/home/ginevracoal/MEGA/DSSC/advanced_programming/advanced-programming-exam/python/home/ginevracoal/MEGA/DSSC/advanced_programming/advanced-programming-exam/python'
    
    def readFile(self, _file_read):
        with open(self._addss + _file_read) as file_pc: # open() returns file object
            for pc in file_pc: # access all postcards 
                self._postcards.append(pc)

        self._file = _file_read
        self.parsePostcards()

    def parsePostcards(self):
        # To extract all the code
        for id_postcard, tx_postcard in enumerate(self._postcards):

            r_date, r_from, r_to, _ = tx_postcard.split(";") # use ; as separator
            _, str_date = r_date.split("date:", 1) # _ serve per lo spazio, mentre str_date per la stringa della data
            _, str_from = r_from.split("from:", 1) 
            _, str_to = r_to.split("to:", 1)

            self._date.update({str_date: id_postcard}) # fill the attributes
            self._from.update({str_from: id_postcard})
            self._to.update({str_to: id_postcard})

    def writeFile(self, _file_write, _date_write, _from_write, _to_write):
        _list = []
        format = "date:{_date}; from:{_from}; to:{_to};\n"

        for i, _ in enumerate(self._postcards):
            tx_date, = [j for j in self._date if i in self._date[j]]
            tx_from, = [j for j in self._from if i in self._from[j]]
            tx_to, = [j for j in self._to if i in self._to[j]]

            _list.append(format.format(_date=tx_date, _from=tx_from, _to=tx_to))

        with open(self._file, 'w') as f:
            for line in _list:
                f.write(line)

    def updateFile(self, _file_update, _date_update, _from_update, _to_update):
        with open(self._addss + '/' + _file_update + '.txt', 'a') as file_pc:
            file_pc.write('date:' + _date_update + '; ' + 'from:' +
                          _from_update + '; ' + 'to:' + _to_update + ';\n')

        self.readFile(_file_update)

    def updateLists(self):
        self.readFile(self._file)

    def getNumberOfPostcards(self):
        return len(self._postcards)

    def getPostcardsByDateRange(self, date_range):
        dt_start, dt_end = date_range

        dt_range = []
        for i in self._date:
            k_date = datetime.strptime(i, '%Y-%m-%d')

            dt_range.extend([p for i, p in enumerate(self._postcards) if k_date >=
                             dt_start and k_date <= dt_end and i in self._date[i]])

        return dt_range


    def getPostcardsBySender(self, sender):
        if sender in self._from:
            return [p for i, p in enumerate(self._postcards) if i in self._from[sender]]
        else:
            return []

    def getPostcardsByReceiver(sefl):
        if receiver in self._to:
            return [p for i, p in enumerate(self._postcards) if i in self._to[receiver]]
        else:
            return []

    def printList(self):
        print('Att _file: {}'.format(self._file))
        print('--------')
        print('Att _postcards: {}'.format(self._postcards))
        print('--------')
        print('Att _date: {}'.format(self._date))
        print('--------')
        print('Att _from: {}'.format(self._from))
        print('--------')
        print('Att _to: {}'.format(self._to))
        print('--------')
        print('Att Qtt.Postcards: {}'.format(self.getNumberOfPostcards()))


# class Test(unittest.TestCase):

#     @classmethod
#     def setUpClass(self):
#         self._files = ['/exam_postcard_list{}.txt'.format(i)
#                        for i in range(10)]
#         self._PstLst = [PostcardList() for f in self._files]
#         [p.readFile(f) for f, p in zip(self._files, self._PstLst)]

#     def test_missing_attributes(self):
#         attributes_to_define = ['_file', '_postcards', '_date', '_from', '_to',
#                                 'writeFile', 'readFile', 'parsePostcards',
#                                 'updateFile', 'updateLists',
#                                 'getNumberOfPostcards',
#                                 'getPostcardsByDateRange',
#                                 'getPostcardsBySender',
#                                 'getPostcardsByReceiver']
#         for attr in attributes_to_define:
#             if attr not in dir(self._PstLst[0]):
#                 raise Exception(attr + ' is missing')

#     def test_check_getPostcardByDateRange(self):
#         dr_test = []
#         for i in [0, 1, 4, 6]:
#             dr_test.append(self._PstLst[i].getPostcardsByDateRange(date_range=(datetime.datetime.strptime('2008-1-1', "%Y-%m-%d"),
#                                                                     datetime.datetime.strptime('2010-12-31', "%Y-%m-%d"))))
#         self.assertListEqual(sorted(dr_test[0]), sorted(['date:2010-06-23; from:Sneezy; to:Alice;\n', 'date:2009-12-12; from:Dopey; to:Peter;\n',
#                                                          'date:2008-03-23; from:Sneezy; to:Pluto;\n', 'date:2008-06-03; from:Goofy; to:Pluto;\n']))
#         self.assertEqual(len(dr_test[1]), 1)
#         self.assertListEqual(sorted(dr_test[2]), sorted(['date:2010-03-30; from:Louie; to:Sneezy;\n', 'date:2010-03-05; from:Goofy; to:Dopey;\n', 'date:2009-11-08; from:Daisy; to:Minnie;\n',
#                                                          'date:2010-07-13; from:Bashful; to:Louie;\n', 'date:2008-06-29; from:Huey; to:Dopey;\n', 'date:2009-01-04; from:Alice; to:Hook;\n', 'date:2009-04-28; from:Bashful; to:Mickey;\n']))
#         self.assertEqual(len(dr_test[3]), 7)

#     def test_check_getPostcardBySender(self):
#         s_test = []
#         for i in [2, 3, 5, 7]:
#             for sender in ['Daisy', 'Bashful', 'Peter']:
#                 s_test.append(
#                     self._PstLst[i].getPostcardsBySender(sender=sender))
#         self.assertIn('date:2011-12-11; from:Daisy; to:Goofy;\n', s_test[0])
#         self.assertListEqual(s_test[1], [])
#         self.assertEqual(len(s_test[2]), 1)
#         self.assertEqual(len(s_test[5]), 0)
#         self.assertGreater(len(s_test[8]), len(s_test[9]))

#     def test_check_getPostcardByReceiver(self):
#         r_test = []
#         for i in [0, 3, 8, 9]:
#             for receiver in ['Peter', 'Hook', 'Alice', 'SnowWhite']:
#                 r_test.append(
#                     self._PstLst[i].getPostcardsByReceiver(receiver=receiver))
#         self.assertIn('date:2009-12-12; from:Dopey; to:Peter;\n', r_test[0])
#         self.assertListEqual(
#             r_test[1], ['date:2016-10-23; from:Sneezy; to:Hook;\n'])
#         self.assertEqual(len(r_test[2]), 2)
#         self.assertEqual(len(r_test[6]), 3)

#     def test_check_sent_received_when(self):
#         srw_test = []
#         for ii in range(10):
#             for jj in ["Mickey", "Minnie", "Goofy", "Pluto", "Donald", "Daisy", "$crooge", "Huey", "Dewey", "Louie", "Peter", "Hook", "Alice", "SnowWhite", "Doc", "Sleepy", "Sneezy", "Bashful", "Dopey", "Happy", "Grumpy"]:
#                 try:
#                     srw_test.append(self._PstLst[ii]._from[jj])
#                     srw_test.append(self._PstLst[ii]._to[jj])
#                     srw_test.append(self._PstLst[ii]._date[jj])
#                 except:
#                     pass
#         # self.assertListEqual(srw_test[0], [1])
#         self.assertListEqual(srw_test[130], [14, 25])
#         self.assertListEqual(srw_test[138], [10])
#         self.assertListEqual(srw_test[140], [15])
#         self.assertListEqual(srw_test[192], [13, 26])
#         self.assertListEqual(srw_test[203], [6, 9, 11, 12, 24, 31, 42])
 

if __name__ == '__main__':
    # unittest.main()

    file = PostcardList()
    file.readFile('exam_postcard_list0')

    # file.getNumberOfPostcards()
    # file.updateFile('exam_postcard_list0', '2018-03-01', 'Nilson', 'Gine')
    # file.updateFile('exam_postcard_list1', '2018-03-01', 'Nilson', 'Gine')
    # file.writeFile('exam_postcard_list20', '2018-03-01', 'Nilson', 'Gine')

    file.printList()

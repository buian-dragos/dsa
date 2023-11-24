class Bag1:
    def __init__(self):
        self.__elems = []

    def add(self,e):
        self.__elems.append(e)

    def remove(self,e):
        if e in self.__elems:
            self.__elems.remove(e)

    def __str__(self):
        return str(self.__elems)

    def nrOccurences(self,e):
        ct = 0
        for i in range(0,len(self.__elems)):
            if self.__elems[i] == e:
                ct+=1
        return ct


class BagIterator:
    def __init__(self, b):
        self.__current = 0
        self.__bag = b

    def valid(self):
        return self.__current < len(self.__bag.__Bag__elems)

    def getCurrent(self):
        if self.valid():
            return self.__bag.__Bag__elems[self.__current]
        raise ValueError()

    def next(self):
        if self.valid():
            self.__current += 1
        raise ValueError()
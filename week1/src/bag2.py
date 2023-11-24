class Bag2:
    def __init__(self,b):
        self.__elems = []
        self.__freq = []

    def add(self,e):
        if e in self.__elems:
            self.__freq[self.__elems.index(e)] += 1
        else:
            self.__elems.append(e)
            self.__freq.append(1)

    def remove(self,e):
        if e in self.__elems:
            index = self.__elems.index(e)
            del self.__elems[index]
            del self.__freq[index]
        else:
            raise ValueError()

    def size(self):
        return sum(self.__freq)

class Bag1Iterator:
    def __init__(self,b):
        self.__bag = b
        self.__currentIndex = 0
        self.__currentFreq = 0

    def valid(self):
        return self.__currentIndex < len(self.__bag.__Bag2__elems)

    def next(self):
        if self.valid():
            if self.__currentFreq == self.__bag.__Bag2__freq[self.__currentIndex]:
                self.__currentFreq = 1
                self.__currentIndex += 1
            else:
                self.__currentFreq += 1
        else:
            raise ValueError()

    def getCurrent(self):
        if self.valid():
            return self.__bag.__Bag2__elems[self.__currentIndex]
        else:
            raise ValueError()





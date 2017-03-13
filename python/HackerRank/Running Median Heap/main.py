class BaseHeap:
    def __init__(self):
        pass

class MinHeap(BaseHeap):
    def __init__(self):
        self.values = [None]

    def peek(self):
        return self.values[1]

    def pop(self):
        peekValue = self.peek()
        lastValue = self.values.pop()
        if len(self.values) < 2:
            return lastValue
        self.values[1] = lastValue
        parentIndex = 1
        while True:
            leftChildIndex = 2 * parentIndex
            if leftChildIndex >= len(self.values):
                return peekValue
            rightChildIndex = leftChildIndex + 1
            if rightChildIndex >= len(self.values) \
                    or self.values[leftChildIndex] <= self.values[rightChildIndex]:
                swapChildIndex = leftChildIndex
            else:
                swapChildIndex = rightChildIndex
            if self.values[swapChildIndex] >= self.values[parentIndex]:
                return peekValue
            self.values[parentIndex], self.values[swapChildIndex] = \
                self.values[swapChildIndex], self.values[parentIndex]
            parentIndex = swapChildIndex

    def push(self, value):
        self.values.append(value)
        childIndex = len(self.values) - 1
        while True:
            parentIndex = childIndex // 2
            if parentIndex == 0:
                return
            if self.values[parentIndex] <= self.values[childIndex]:
                return
            self.values[parentIndex], self.values[childIndex] = \
                self.values[childIndex], self.values[parentIndex]
            childIndex = parentIndex

if __name__ == '__main__':
    heap = MinHeap()
    input = [40, 18, 25, 17, 10, 19, 12, 15]
    for i in input:
        heap.push(i)
    for _ in input:
        print heap.pop()



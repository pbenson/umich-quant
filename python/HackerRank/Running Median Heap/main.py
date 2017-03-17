class MedianHeap:
    def __init__(self):
        self.minHeap = MinHeap()
        self.maxHeap = MaxHeap()

    def peek(self):
        if self.minHeap.size() == self.maxHeap.size():
            return (self.minHeap.peek() + self.maxHeap.peek()) * 0.5
        if self.minHeap.size() > self.maxHeap.size():
            return self.minHeap.peek()
        return self.maxHeap.peek()

    def push(self, value):
        if (self.minHeap.size() == 0) and (self.maxHeap.size() == 0):
            self.minHeap.push(value)
            return
        if value < self.peek():
            self.maxHeap.push(value)
        else:
            self.minHeap.push(value)
        # balance the two heaps so that they differ in size by no more than one element
        if self.minHeap.size() > self.maxHeap.size() + 1:
            self.maxHeap.push(self.minHeap.pop())
        elif self.maxHeap.size() > self.minHeap.size() + 1:
            self.minHeap.push(self.maxHeap.pop())


class BaseHeap:
    def __init__(self):
        self.values = [None]

    def size(self):
        return len(self.values) - 1

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
                    or self.useLeftIndex(leftChildIndex):
                swapChildIndex = leftChildIndex
            else:
                swapChildIndex = rightChildIndex
            if not self.needToSwapChildWithParent(swapChildIndex):
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
            if not self.needToSwapChildWithParent(childIndex):
                return
            self.values[parentIndex], self.values[childIndex] = \
                self.values[childIndex], self.values[parentIndex]
            childIndex = parentIndex

class MaxHeap(BaseHeap):
    def useLeftIndex(self, leftChildIndex):
        return self.values[leftChildIndex] >= self.values[leftChildIndex + 1]

    def needToSwapChildWithParent(self, swapChildIndex):
        return self.values[swapChildIndex] > self.values[swapChildIndex // 2]


class MinHeap(BaseHeap):
    def useLeftIndex(self, leftChildIndex):
        return self.values[leftChildIndex] <= self.values[leftChildIndex + 1]

    def needToSwapChildWithParent(self, swapChildIndex):
        return self.values[swapChildIndex] < self.values[swapChildIndex // 2]

if __name__ == '__main__':
    heap = MedianHeap()
    input = [40, 18, 25, 17, 10, 19, 12, 15]
    for i in input:
        heap.push(i)
        print heap.peek()
    # for _ in input:
    #     print heap.pop()



with open('data/d1.data') as dataStream:
    rawData = dataStream.read().splitlines()

numbers=[]

for d in rawData:
    numbers.append(int(d))

numbers.sort()

revPtr = len(numbers) - 1

for fwdPtr in numbers:
    for revPtr in reversed(numbers):
        if revPtr + fwdPtr == 2020:
            print(revPtr * fwdPtr)

for first in numbers:
    for second in numbers:
        for third in numbers:
            if first + second + third == 2020:
                print(first * second * third)
                break

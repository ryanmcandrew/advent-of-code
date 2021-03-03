with open('data/d3.data') as dataStream:
    rawData = [line.split() for line in dataStream]

trees = 0

for i in range(len(rawData)):
    index = 3*i
    if (index < len(rawData) and i < len(rawData)):
        print(rawData[i][index])

def listIndicesForSlope(slope):
    arr = []

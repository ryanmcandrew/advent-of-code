with open('data/d2.data') as dataStream:
    rawData = dataStream.read().splitlines()

class Record:
    def __init__(self, word_min, word_max, pass_char, pass_str):
        self.word_min = int(word_min)
        self.word_max = int(word_max)
        self.pass_char = pass_char
        self.pass_str = pass_str

    def __repr__(self):
        return "min {} max {} char {} string {} \n".format(self.word_min, self.word_max, self.pass_char,  self.pass_str  )


def process_data(data):
    records = []
    for d in data:
        records.append(Record(d[0:d.find('-')], 
                        d[d.find('-')+1:d.find(' ')], 
                        d[d.find(' ')+1:d.find(':')],
                        d[d.find(':')+2:len(d)]))

    return records

def num_valid_partone(tuples):
    print("num tuples:{}".format(len(tuples)) )
    errors = 0
    for r in tuples:
        occurences = r.pass_str.count(r.pass_char)
        if occurences < r.word_min:
            errors += 1
        elif occurences > r.word_max:
            errors += 1
    print("num errors detected:{}".format(errors))
    print("num correct: {}".format(len(tuples) - errors))

def num_invalid(tuples):
    errors=0
    for rec in tuples:
        if rec.pass_str[rec.word_min - 1] == rec.pass_char:
            if rec.pass_str[rec.word_max - 1] == rec.pass_char:
                errors += 1
        if rec.pass_str[rec.word_min - 1] != rec.pass_char:
            if rec.pass_str[rec.word_max - 1] != rec.pass_char:
                errors += 1
    return errors

d = process_data(rawData)
print(len(d) - num_invalid(d))
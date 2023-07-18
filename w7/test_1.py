from functools import reduce
class Mapper:
    def __init__(self, it):
        self.it = it
        self.maps = []
    
    def apply(self, fn):
        self.maps.append(fn)
        return self
    
    def __iter__(self):
        for item in self.it:
            yield reduce(lambda acc, cur: cur(acc), self.maps, item)
    
    def to_map(self):
        return map(lambda item: reduce(lambda acc, cur: cur(acc), self.maps, item), self.it)

print(reduce(lambda acc, cur: acc + cur + 1, range(100), 0))
print("Strings " + "also " + f"work! ({1 << 2})")
my_mapper = Mapper(range(8)).apply(lambda n: n + 1).apply(lambda n: 1 << n).apply(lambda n: n - 1).apply(str)
print(", ".join(my_mapper))
print(", ".join(my_mapper.to_map()))
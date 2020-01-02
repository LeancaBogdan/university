
class MyList:
    def __init__(self):
        self._lst = []
        self._index = 0
    
    def index(self, obj):
        return self._lst.index(obj)
    
    def append(self, item):
        self._lst.append(item)
        
    def __getitem__(self, idx):
        return self._lst[idx]
    
    def __setitem__(self, idx, value):
        self._lst[idx] = value
        
    def __delitem__(self, idx):
        del self._lst[idx]
        return
    
    def remove(self, item):
        self._lst.remove(item)
        
    def __iter__(self):
        self._index = 0
        return self
    
    def __next__(self):
        try:
            result = self._lst[self._index]
        except IndexError:
            raise StopIteration
        self._index += 1
        return result
    
    def __len__(self):
        return len(self._lst)
    
    def get_all(self):
        return self._lst

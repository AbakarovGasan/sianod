#функция prefix_str возвращает массив длин префиксов строк
def prefix_str(s):
    lps = [0]*len(s) # массив длин префиксов строк
    
    for i in range(1,len(s)):
        
        #найти, какой префикс-суффикс можно расширить
        k = lps[i-1]
        while k > 0 and (s[k] != s[i]): 
            k = lps[k-1]
            
        #расширить префикс
        if s[k] == s[i]:
            k = k + 1
        lps[i] = k
    return lps


#print(prefix_str(input()))


#реализация алгоритма Кнута-Морриса-Пратта 
def kmp(pat, txt, index=0): 
    M = len(pat) 
    N = len(txt) 
    #если длина cтроки pat + index больше длины строки txt, возвращаем -1
    if M+index > N: return -1
    #построить префикс-функцию (lps) строки pat
    lps = prefix_str(pat)
    i = index # индекс для txt 
    j = 0 # индекс для pat
    while i < N: 
        if pat[j] == txt[i]: 
            i += 1
            j += 1
        if j == M: 
            return (i-j) 
        elif i < N and pat[j] != txt[i]: 
            if j != 0: 
                j = lps[j-1] 
            else: 
                i += 1
    return -1

#print(kmp('asshole', 'aaaassholeqr'))
                
#функция строит таблицу смещении для строки
def bad_table(pat):
    L = len(pat)
    t = [L]*256
    for i in range(L-1):
        s = pat[i]
        t[int(s)] = L - i - 1
    return t
    
#реализация алгоритма Бойера — Мура — Хорспула
#или упрощенного алгоритма Бойера — Мура
def bmh(pat, txt, index):
    M = len(pat)
    N = len(txt)
    #если длина cтроки pat + index больше длины строки txt, возвращаем -1
    if M+index > N: return -1
    #получить таблицу смещений
    bt = bad_table(pat)
    
    
    i = M + index - 1
    r = M - 1
    u = i 
    
    while u < N:
        while (r >= 0):
            if (pat[r] != txt[u]): 
                break
            r -= 1
            u -= 1
        if r == -1:
            return i - M + 1
        i += bt[int(txt[r])] 
        u = i
        r = M - 1
    return -1

def search(pattern, string, index, algorithm, is_case_sensitive=False):
    #pattern - образец, который следует найти
    #string - строка, в которой следует найти образец
    #index - индекс, с которого ведется поиск
    #algorithm - алгоритм поиска с параметрами pattern, string, index
    #is_case_sensitive - опция чувствительности регистра
    pattern = pattern.encode()
    string = string.encode()
    if (is_case_sensitive): 
        pattern = pattern.lower()
        string = string.lower()
    return algorithm(pattern, string, index)
    
import time
#функция выводит время выполнения алгоритма
def get_execution_time(name, func, *b, **c):
    j = time.time()
    a = func(*b, **c)
    j = time.time() - j
    print(name)
    print("Время выполнения: %.30f" % j)
    print("Результат:", a)

#
#source = input('Введите строку: ')
#pattern = input('Введите подстроку: ')
#is_case_sensitive = (input('чувствительность к регистру: {1: нет, 2: да, по умолчанию: да}').strip() == '1')

#get_execution_time('поиск методом Кнута-Морриса-Пратта', search, pattern, source, 0, kmp, is_case_sensitive)
#get_execution_time('поиск методом Бойера — Мура — Хорспула', search, pattern, source, 0, bmh, is_case_sensitive)

#Класс, реализующее состояние доски пятнашек
class Board:
    board_list = []
    board = [[]]
    size = 0
    def __eq__(self, other):
        if type(None) == type(other):
            return False
        if self.hashcode == other.hashcode:
            return True
        s = self.board_list
        f = other.board_list 
        for i in range(len(s)):
            if s[i] != f[i]:
                return False
        return True
    def __str__(self):
        s = self.size
        t = 0
        u = ''
        for i in self.board_list:
            t += 1
            u += str(i)
            if t == s:
                u += '\n'
                t = 0
            else:
                u += ' '
        return u
    def __repr__(self):
        s = self.size
        t = 0
        u = ''
        for i in self.board_list:
            t += 1
            u += str(i)
            if t == s:
                u += '\n'
                t = 0
            else:
                u += ' '
        return u  
    def __lt__(self, other): 
        return False
    def __gt__(self, other): 
        return False
    def __init__(self, array, size = 4, prev=None, trace=None):
        try:
            v = list(array)
            board_list = tuple(v)
            v.sort()
            sq = size ** 2
            for i in range(sq):
                if v[i] != i:
                     raise Exception("")
            self.size = size
            self.sq = size ** 2
            self.board_list = tuple(board_list)
            self.hashcode = hash(board_list)
            h = 0
            for u,i in enumerate(board_list):
                if i == 0:
                    continue
                else:
                    u += 1
                    if u != i:
                        h += 1
            if prev == None:
                g = 0
            else:
                g = prev.g + 1
            self.h = h
            self.g = g
            self.measure = h + g
            self.trace=trace
            self.prev=prev
        except Exception as e:
            raise Exception("usage: <array of "+str(sq)+" integers from 0 to "+str(sq-1)+'>')
            
    #метод, который находит все соседние позиции
    def neighbours(self):
        v = self.board_list
        i = v.index(0)
        bb = []
        s = self.size
        sq = s * s
        if (i + s) < sq:
            j = list(v)
            j[i] = j[i + s]
            j[i + s] = 0
            bb.append(Board(j, s, self, j[i])) 
        if (i - s) >= 0:
            j = list(v)
            j[i] = j[i - s]
            j[i - s] = 0
            bb.append(Board(j, s, self, j[i])) 
        if (((i % s) + 1) < s) and ((i + 1) < sq):
            j = list(v)
            j[i] = j[i + 1]
            j[i + 1] = 0
            bb.append(Board(j, s, self, j[i])) 
        if (((i % s) - 1) >= 0) and ((i - 1) >= 0):
            j = list(v)
            j[i] = j[i - 1]
            j[i - 1] = 0
            bb.append(Board(j, s, self, j[i]))
        return bb

#Алгоритм, проверяющее, является ли позиция "решаемой"
def is_solvable(v):
    size = v.size
    if size != 4:
        return True
    v = v.board_list
    sq = size ** 2
    s = 0
    for i, u in enumerate(v):
        if u == 0:
            s += int(i / size)
            s += 1
        else:
            for t in range(i+1, sq):
                if u > v[t] and v[t] != 0:
                    s += 1
    return (s % 2) == 0

#Kласс, реализующий очередь
class priorityQueue:
    cn = []
    def add(self, a):
        self.cn.append((a.measure, a))
        self.cn.sort()
    def pool(self):
        return self.cn.pop(0)[1]
        
#Aлгоритм А* поиска решения пятнашек
def AStar(initial):
    if not is_solvable(initial): return
    queue = priorityQueue()
    set = []
    
    queue.add(initial)
    while True:
        t = queue.pool()
        set.append(t)
        if t.h == 0: return t
        for i in t.neighbours():
            if i == None:
                continue
            if i in set:
                continue
            queue.add(i)

#функция, которая возвращает решения
def get_trace(b):
  v = []
  while not (b.prev == None):
   v.append(b.trace)
   b=b.prev
  v.reverse()
  return v

l = Board([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 15, 13, 14, 0])
j=AStar(l);
print(get_trace(j));


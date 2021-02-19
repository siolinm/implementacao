import numpy as np

class Point:    
    def __init__(self, name, x, y):
        self.name = name
        self.x = x
        self.y = y

    def subtract(self, point):
        self.x -= point.x
        self.y -= point.y

    def sum(self, point):
        self.x += point.x
        self.y += point.y

    def rotate(self, angle):
        angle = np.radians(angle)
        self.x = self.x*np.cos(angle) + self.y*np.sin(angle)
        self.y = -self.x*np.sin(angle) + self.y*np.cos(angle)

    def transform(self, angle):
        angle = np.radians(angle)
        self.x = self.x*np.cos(angle) - self.y*np.sin(angle)
        self.y = self.x*np.sin(angle) + self.y*np.cos(angle)

    def to_string(self):
        # return self.name.upper() + " = (" + str(self.x) + ", " + str(self.y) + ")"
        return str(self.x) + " " + str(self.y) + " 0 0 " + self.name 

class PointList:
    def __init__(self):
        self.list = {}

    def add(self, point):
        self.list[point.name] = point

    def rotate(self, angle):
        for i in self.list:
            self.list[i].rotate(angle)

    def transform(self, angle):
        for i in self.list:
            if str(i) != "p":
                self.list[i].transform(angle)

    def subtract(self, point):
        for i in self.list:
            if str(i) != str(point):
                self.list[i].subtract(self.list[point])

    def sum(self, point):
        for i in self.list:
            if str(i) != str(point):
                self.list[i].sum(self.list[point])

    def to_string(self):
        a = ""
        for i in self.list:
            a += self.list[i].to_string() + "\n"
        return a


pl = PointList()
arquivo = input("Digite o nome do arquivo: ")
arq = open(arquivo, 'r')
linhas = list(arq)

for i in linhas:
    valores = i.split()
    ponto = Point(valores[2], float(valores[0]), float(valores[1]))
    pl.add(ponto)

angulo = input("Digite o angulo de rotação em graus: ")
ponto = input("Digite o ponto: ")

angulo = float(angulo)
pl.subtract(ponto)
pl.transform(angulo)
pl.sum(ponto)
print(pl.to_string())
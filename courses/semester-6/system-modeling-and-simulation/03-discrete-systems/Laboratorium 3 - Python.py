from math import *
import matplotlib.pyplot as plt
from scipy import integrate as inte

def wachadlo(t, input):
   th0, th1 = input
   # stałe
   k = 1
   m = 10
   l = 3
   g = 10

   # najwyzsza pochodna
   th2 = -k/m * th1 - g/l*sin(th0)
   # zwracamy pochonde, przy czym kolejnosc pochdonych 
   # musi byc zgodna z kolejnoscia zmiennych, do ktorych 
   # wyliczenia są potrzebne: th0 -> th1, th1 -> th2
   return [th1, th2]

th0 = 90*pi/180
th1 = 0
t_min = 0
t_max = 100
max_st = 0.01

# tworzymy obiekt calkujacy (RK45 - Dormand–Prince)
integrator = inte.RK45(wachadlo, t_min, [th0, th1], t_max, max_step = max_st)

# listy zbierajace wyniki do wykresu
times = [t_min]
thetas = [th0]
thetas_p = [th1]
# kolejne kroki symulacji
while integrator.t < t_max:
   integrator.step() 
   times.append(integrator.t)
   thetas.append(integrator.y[0])
   thetas_p.append(integrator.y[1])

plt.plot(times, thetas, '-')
plt.show()
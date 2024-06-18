import numpy as np
if __name__ == '__main__':

    a = np.array([1,2,3,4,4,5,6,7,8,9,10])
    # print(a[1])

    a=np.array([1,2,3,4,5,6,7])
    b=np.array([[1,2,3,4,5], [6,7,8,9,10]])
    np.transpose(b)
    # print(b)

    # print(np.arange(0, 100, 1, dtype=int))

    d=np.linspace(0,2,10)
    # print(d)

    np.arange(0, 100, 5, dtype=int)
    rng = np.random.default_rng()

    rng.standard_normal(10).round(2)

    rng.integers(low=1, high=1000, size=100)



    # print(rng.standard_normal(20).round(2))
    # print(rng.integers(low=1, high=1000, size=100))

    # print(np.zeros((3,2)), "\n")
    # print(np.ones((3,2)))

    # print(np.arange(0, 100, 1, dtype='i'))

    np.random.randint(0, 100, (5, 5)).astype('int32')


    aa = np.random.random((3, 3))*10
    # print(aa)
    aa.astype('int')
    bb = aa
    aa.round()
    # print(aa.round())
    # print(aa.round().astype("int"))
    # print(bb.astype('int'))
    # e = np.
    b = np.array([[1, 2, 3, 4, 5], [6, 7, 8, 9, 10]], dtype=np.int32)
    # print(b)
    # print(b.ndim)
    # print(b.size)

    c = b[0][1], b[0][3]
    # print(c)
    d = b[0]
    # print(d)

    a = np.random.randint(0, 100, (20, 7)).astype('int32')
    # print(a, "\n")
    # print(a[:,:4])

    a=np.array([[1,2,3], [4,5,6], [8,9,10]])
    b=np.array([[1,2,3], [6,7,8], [8,9,10]])

    # print(a)
    # print(b)

    # print(a+b)
    # print(a-b)
    # print(a*b)
    # print(np.power(a,b))
    #
    # print(a >=4)
    #
    # print('Diagonal (sum): ', np.trace(b))
    # print(sum(b))
    # print(np.min(b))
    # print(np.max(b))
    # print(np.std(b))

    a = np.arange(50).reshape((10, 5))
    # print(a)
    a = np.arange(50)
    a = np.resize(a, (10, 5))
    # print(a)

    a = np.array([1, 2, 3, 4, 5])
    b = np.array([1, 2, 3, 4])
    # print(a+b)
    x1_new = a+b[:, np.newaxis]
    # print(x1_new)
    # Rzutowanie wymiarów za pomocą shape lub resize:

    # sortowanie:

    # Tasks
    # 1.
    b = np.random.randint(0, 100, (10, 5)).astype('int32')
    # print(b)

    # print('Diagonal (sum): ', np.trace(b))
    # print(np.diag(b))

    # 2.
    a = rng.standard_normal(10)
    b = rng.standard_normal(10)
    # print(a*b)
    # 3.
    a = np.random.randint(101, size=100)
    b = np.random.randint(101, size=100)

    # print(a)
    # print(b)

    np.asmatrix(a)
    np.asmatrix(b)

    a = np.reshape(a, (20,5))
    b = np.reshape(b, (20,5))
    #
    # print("a:\n",a, "\n")
    # print("b:\n",b, "\n")
    c=a+b
    # print(c)
    # 4.
    a = np.random.randint(0, 100, (4, 5)).astype('int32')
    b = np.random.randint(0, 100, (5, 4)).astype('int32')
    # print(b)
    # print(a)

    a = np.reshape(a,(5,4))
    # print(a)

    c = a+b
    # print(c)

    # 5.
    # Pomnóż kolumny 3 i 4, stworzonych przez siebie macierzy

    a = np.random.randint(0, 100, (4, 5)).astype('int32')
    b = np.random.randint(0, 100, (4, 5)).astype('int32')

    # print(a)
    # print(a[:,2:3])
    # print(b)
    # print(b[:,3:4])

    c = a[:,2:3] * b[:,3:4]
    # print(c)
    # 6.
    # Wygeneruj dwie macierze o rozkładzie normalnym (np.random.normal)
    # i jednostajnym(np.random.uniform). Policz wartość średnią, odchyle-
    # nie standardowa, wariancję itp. Porównaj wyniki z obu zbiorów da-
    # nych.zobacz
    # a = np.random.normal(0, 0.1, 1000)
    # # print(a)
    # print("mean: ", np.mean(a),"standard deviation: ", np.std(a), "variance: ", np.var(a))
    # b = np.random.uniform(-1, 0, 1000)
    # # print(b)
    # print("mean: ", np.mean(b),"standard deviation: ", np.std(b), "variance: ", np.var(b))
    # a: <, <, <
    # b: >, >, >
    # 7.
    # Wygeneruj dwie macierze kwadratowe a i b, pomnóż je przez siebie
    # używając (a*b) oraz funkcji dot.zobacz Jaka jest różnica? Napisz kie-
    # dy warto wykorzystać funkcję dot?
    # vector v1 of dimension (2, 2)
    v1 = np.array([[1, 0], [1, 1]])
    v2 = np.array([[1, 0], [1, 1]])

    # print(np.dot(v1, v2))
    # print(v1 * v2)

    # ‘*’ operation caries out element-wise multiplication on array elements.
    # Working of numpy.dot()
    # It carries of normal matrix multiplication.
    # https://www.geeksforgeeks.org/difference-between-numpy-dot-and-operation-in-python/

    # 8.
    # Sprawdź funkcję strides oraz as strided. Zastosuj je do wyboru danych
    # z macierzy np. 5 kolumn z trzech pierwszych wierszy.
    x = np.arange(25)
    y = x.reshape(5,5)
    # print(x.shape)
    # print(x.strides)
    # print(x)
    # print(y)
    # print(y.strides)

    c = np.lib.stride_tricks.as_strided(y, shape=(3, 5))

    print(c)

    # 9.
    # Wygeneruj dwie tablice a i b. Połącz je z użyciem funkcji vstack i
    # hstack. Czym one się różnią? Zastanów się i napisz, w jakich przypad-
    # kach warto je zastosować?
    a = np.array([1, 2, 3])
    b = np.array([9, 8, 7])
    print(np.vstack((a, b)))
    print(np.hstack((a, b)))

    # Stack arrays in sequence vertically (row wise). jedno pod drugim
    # Stack arrays in sequence horizontally (column wise). jedno obok drugiego

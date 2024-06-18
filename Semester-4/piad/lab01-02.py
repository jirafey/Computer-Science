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

    print(a)
    print(b)

    np.asmatrix(a)
    np.asmatrix(b)

    a = np.reshape(a, (20,5))
    b = np.reshape(b, (20,5))
    # 
    # print("a:\n",a, "\n")
    # print("b:\n",b, "\n")
    # 4.
    
    # 5.
    # 6.
    # 7.
    # 8.
    # 9.

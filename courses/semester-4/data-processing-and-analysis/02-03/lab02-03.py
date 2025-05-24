import pandas as pd;
import numpy as np;
from numpy.polynomial.polynomial import polyfit
from scipy.stats import pearsonr
import matplotlib.pyplot as plt
from scipy.stats import gaussian_kde

def zad1():
    grouped_df = df.groupby('y')['x'].mean();
    print(grouped_df);


def zad2():
    value_counts_y = df['y'].value_counts();
    value_counts_x = df['x'].value_counts();
    print(value_counts_y);
    print(value_counts_x);


def zad3(path: str):
    np_ds=np.loadtxt(path, dtype='str', delimiter=",");
    print(np_ds);

    pd_ds= pd.read_csv(path,index_col=0);
    print(pd_ds.head);


def zad4(path: str):
    # 4. Zgrupować ramkę danych po zmiennej ’make’ a następnie wy- znaczyć średnie
    # zużycie paliwa dla każdego z producentów.
    pd_ds_grouped = pd_ds.groupby('make')['fuel-type'].mean();
    print(pd_ds_grouped);


def zad5():
    # 5. Zgrupować ramkę danych po zmiennej ’make’ liczności dla atry- butu
    # ’fuel-type’.
    pd_ds_grouped = pd_ds.groupby('make')['fuel-type'].value_counts();
    print(pd_ds_grouped);


def zad6():
    poly_1 = polyfit(pd_ds['length'], pd_ds['city-mpg'], 1);
    poly_2 = polyfit(pd_ds['length'], pd_ds['city-mpg'], 2);
    print(poly_1);
    print(poly_2);

# 6. Dopasować wielomian 1 i 2 stopnia prognozujący wartość zmien- nej ’city-mpg’, względem ’length’ (
# np.polyfit , np.polyval).
#


def zad7():
    cc, _ = pearsonr(pd_ds['length'], pd_ds['city-mpg']);
    print(cc);
# 7. Wyznaczyć współczynnik korelacji liniowej pomiędzy tymi zmien- nymi (scipy.stats).


def zad8():

    # Example data
    x = pd_ds['length']
    y = pd_ds['city-mpg']

    # Fit polynomial of degree 1 and 2
    poly_1 = np.polyfit(x, y, 1)
    poly_2 = np.polyfit(x, y, 2)

    # Create polynomial functions
    poly1d_fn1 = np.poly1d(poly_1)
    poly1d_fn2 = np.poly1d(poly_2)

    # Scatter plot of data
    plt.scatter(x, y, label='Dane')

    # Plot polynomial fits
    plt.plot(x, poly1d_fn1(x), '--', label='poly_1')
    plt.plot(x, poly1d_fn2(x), '-.', label='poly_2')

    # Add labels and legend
    plt.xlabel('Length')
    plt.ylabel('City MPG')
    plt.legend()

    # Show plot
    plt.show()
# 8.
# Zwizualizować wyniki dopasowania, zaznaczając próbki oraz do- pasowane krzywe na tle próbek dla zmiennych
# ’city-mpg’, ’length’.


def zad9():
    pass;
# 9. Dlazmiennej’length’utworzyćjednowymiarowyestymatorfunk- cji gęstości, w tym celu użyć
# scipy.stats.gaussian kde. Zwizualizować wynik przedstawiając jednocześnie próbki i funk- cję gęstości. Do wykresu
# dodać legendę. W tym celu użyć (plot(..., label=’...’), legend) 4

    # Creating KDE for 'length'
    kde = gaussian_kde(pd_ds['length'])

    # Generating x values for plotting, max vals
    x_values = np.linspace(pd_ds['length'].min(), pd_ds['length'].max(), 100)

    # Plotting KDE and data points
    plt.plot(x_values, kde(x_values), label='KDE')
    plt.scatter(pd_ds['length'], np.zeros_like(pd_ds['length']), alpha=0.5, label='Data')

    plt.xlabel('Length')
    plt.ylabel('Density')
    plt.legend()
    plt.show()
def zad10():
    fig =  plt.subplots(2)[0];
    axes = plt.subplots(2)[1];
    axes[0].plot(pd_ds['length'], pd_ds['city-mpg'], label='City');
    axes[0].set_xlabel('Length');
    axes[0].set_ylabel('City MPG');

    axes[1].plot(pd_ds['width'], pd_ds['city-mpg'], label='City MPG')
    axes[1].set_xlabel('Width')
    axes[1].set_ylabel('City MPG')

    plt.tight_layout()
    plt.show()
    # 10. Utworzyć w jednym oknie graficznym dwa
# wykresy ax=subplot(...), ax.plot(...) Na drugim wykresie przedstawić analogicznie rozkład dla zmien- nej ’width’.



def zad11():
    # Generating data for 'width' and 'length'
    width = np.random.normal(loc=4, scale=2, size=400)
    length = np.random.normal(loc=2, scale=1, size=400)

    # Creating meshgrid
    x_for_mg= np.linspace(min(width), max(width), 100);
    y_for_mg = np.linspace(min(length), max(length), 100);
    x, y = np.meshgrid(x_for_mg, y_for_mg);
    positions = np.vstack([x.ravel(), y.ravel()])
    values = np.vstack([width, length])

    # Creating KDE
    kernel = gaussian_kde(values)
    z = np.reshape(kernel(positions).T, x.shape)

    # Plotting
    plt.contourf(x, y, z, cmap='viridis')
    plt.colorbar(label='Density')
    plt.xlabel('Width')
    plt.ylabel('Length')
    plt.title('2D Kernel Density Estimation')
    plt.scatter(width, length, s=1, color='red', alpha=0.5, label='Data Points')
    plt.legend()
    plt.savefig('density_estimation.png')  # Save plot as PNG
    plt.savefig('density_estimation.pdf')  # Save plot as PDF
    plt.show()


# 11. Utworzyć dwuwymiarowy estymator funkcji gęstości dla zmien- nych ’width’ i ’length’, wynik przedstawić
# graficznie w nowym oknie rysując próbki poleceniem plot oraz funkcję gęstości uży- wając polecenia meshgrid i
# contour. Wynik zapisać do plików w formacie *.png i *.pdf (savefig).
#

if __name__ == "__main__":
    df = pd.DataFrame({"x": [1, 2, 3, 4, 5], 'y': ['a', 'b', 'a', 'b', 'b']});
    path = '/Users/jirafey/Downloads/autos.csv';
    np_ds = np.loadtxt(path, dtype='str', delimiter=",");
    pd_ds = pd.read_csv(path, index_col=0);
    # zad1();
    # zad2();
    # zad3(path=path);

    # zad4(path=path);
    # zad5();

    zad6();
    zad7();
    zad8();
    zad9();
    zad10();
    zad11();

# 3 Zadania df = pd.DataFrame({"x": [1, 2, 3, 4, 5], ’y’: [’a’, ’b’, ’a’, ’b’, ’b’]})
# 1. Zgrupować tabele po zmiennej
# symbolicznej Y, a następnie wy- znaczyć średnią wartość atrybutu numerycznego X w grupach wy- znaczonych przez Y.
# 2. Wyznaczyć rozkład liczności atrybutów (value counts).
# 3. Wyczytać dane autos.csv, za pomocą polecenia np.loadtxt
# oraz pandas.read csv. Sprawdź różnice.



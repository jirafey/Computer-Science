package pl.edu.zut.wo.wzorce.pizzeria.metoda_fabrykująca;

import pl.edu.zut.wo.wzorce.pizzeria.pizza.*;

public class WłoskaPizzeria {
    Pizza utwórzPizza(String type){
        Pizza pizza = null;
        if (type.equals("serowa")) {
            pizza = new WłoskaSerowaPizza();
        } else if (type.equals("pepperoni")) {
            pizza = new WłoskaPepperoniPizza();
        } else if (type.equals("owocemorza")) {
            pizza = new WłoskaOwoceMorzaPizza();
        } else if (type.equals("wegetariańska")) {
            pizza = new WłoskaWegetariańskaPizza();
        }
        return pizza;
    }
    public Pizza zamówPizza(String typ) {
        Pizza pizza = utwórzPizza(typ);
        pizza.przygotowanie();
        pizza.pieczenie();
        pizza.krojenie();
        pizza.pakowanie();
        return pizza;
    }
}

package pl.edu.zut.wo.wzorce.pizzeria.metoda_fabrykująca;

import pl.edu.zut.wo.wzorce.pizzeria.pizza.Pizza;

public abstract class Pizzeria {

	abstract Pizza utwórzPizza(String typ);

	public Pizza zamówPizza(String typ) {
		Pizza pizza = utwórzPizza(typ);
		pizza.przygotowanie();
		pizza.pieczenie();
		pizza.krojenie();
		pizza.pakowanie();
		return pizza;
	}

}

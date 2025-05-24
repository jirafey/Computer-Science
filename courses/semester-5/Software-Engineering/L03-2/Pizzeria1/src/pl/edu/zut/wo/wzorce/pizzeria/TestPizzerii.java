package pl.edu.zut.wo.wzorce.pizzeria;

import pl.edu.zut.wo.wzorce.pizzeria.metoda_fabrykująca.AmerykańskaPizzeria;
import pl.edu.zut.wo.wzorce.pizzeria.metoda_fabrykująca.WłoskaPizzeria;
import pl.edu.zut.wo.wzorce.pizzeria.pizza.Pizza;

public class TestPizzerii {

	public static void main(String[] args) {
		Pizzeria1 pizzeria = new Pizzeria1();
		Pizza pizza = pizzeria.zamówPizza("serowa");
		System.out.println(pizzeria.getClass().getSimpleName() + " wyprodukowała " + pizza.getClass().getSimpleName());

		AmerykańskaPizzeria amerykańskaPizzeria = new AmerykańskaPizzeria();
		Pizza pizza2 = amerykańskaPizzeria.zamówPizza("serowa");
		System.out.println(amerykańskaPizzeria.getClass().getSimpleName() + " wyprodukowała " + pizza2.getClass().getSimpleName());

		WłoskaPizzeria włoskaPizzeria = new WłoskaPizzeria();
		Pizza pizza3 = włoskaPizzeria.zamówPizza("serowa");
		System.out.println(włoskaPizzeria.getClass().getSimpleName() + " wyprodukowała " + pizza3.getClass().getSimpleName());
	}
}

package pl.edu.zut.wo.wzorce.pogodynka;

import pl.edu.zut.wo.wzorce.pogodynka.wyświetl.PrognozaWyświetlanie;
import pl.edu.zut.wo.wzorce.pogodynka.wyświetl.StatystykaWyświetlanie;
import pl.edu.zut.wo.wzorce.pogodynka.wyświetl.WarunkiBieżąceWyświetlanie;

public class DanePogodowe {
	private float temperatura;
	private float wilgotność;
	private float ciśnienie;
	
	private PrognozaWyświetlanie prognozaWyświetl = new PrognozaWyświetlanie();
	private WarunkiBieżąceWyświetlanie warunkiBieżąceWyświetl = new WarunkiBieżąceWyświetlanie();
	private StatystykaWyświetlanie statystykaWyświetl = new StatystykaWyświetlanie();

	public void odczytyZmiana(){
		float temp = pobierzTemperaturę();
		float wilgotność = pobierzWilgotność();
		float ciśnienie = pobierzCiśnienie();
		warunkiBieżąceWyświetl.aktualizacja(temp, wilgotność, ciśnienie);
		statystykaWyświetl.aktualizacja(temp, wilgotność, ciśnienie);
		prognozaWyświetl.aktualizacja(temp, wilgotność, ciśnienie);
	}

	private float pobierzTemperaturę(){
		return temperatura;
	}

	private float pobierzWilgotność(){
		return wilgotność;
	}

	private float pobierzCiśnienie(){
		return ciśnienie;
	}
	
	public void ustawOdczyty(float temperatura, float wilgotność, float ciśnienie) {
		this.temperatura = temperatura;
		this.wilgotność = wilgotność;
		this.ciśnienie = ciśnienie;
		odczytyZmiana();
	}
	
}

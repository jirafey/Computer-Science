package pl.edu.zut.wo.wzorce.pogodynka.wyświetl;

public class StatystykaWyświetlanie {

	private float temperatura;
	private float wilgotność;
	private float ciśnienie;

	public void aktualizacja(float temperatura, float wilgotność, float ciśnienie) {
		this.temperatura = temperatura;
		this.wilgotność = wilgotność;
		this.ciśnienie = ciśnienie;
		wyświetl();
	}
	
	public void wyświetl() {
		System.out.println("Staystyka " + temperatura + " stopni C oraz " + wilgotność + "% wilgotność");
	}

}
package pl.edu.zut.wo.wzorce.symulator;

public class MiniSymulatorKaczki {

	public static void main(String[] args) {
		Kaczka dzika = new DzikaKaczka();
		dzika.ustawLeć(new LatamBoMamSkrzydła());
		dzika.ustawKwacz(new Kwacz());
		dzika.wyświetl();
		dzika.wykonajKwacz();
		dzika.wykonajLeć();
		
		Kaczka gumowa = new GumowaKaczka();
		gumowa.ustawLeć(new NieLatam());
		gumowa.ustawKwacz(new Piszcz());
		gumowa.wyświetl();
		gumowa.wykonajKwacz();
		gumowa.wykonajLeć();

		Kaczka płaskonos = new PłaskonosKaczka();
		płaskonos.ustawLeć(new LatamBoMamSkrzydła());
		płaskonos.ustawKwacz(new Kwacz());
		płaskonos.wyświetl();
		płaskonos.wykonajKwacz();
		płaskonos.wykonajLeć();

		Kaczka wabik = new WabikKaczka();
		płaskonos.ustawLeć(new NieLatam());
		płaskonos.ustawKwacz(new NieKwacz());
		płaskonos.wyświetl();
		płaskonos.wykonajKwacz();
		płaskonos.wykonajLeć();
	}
}


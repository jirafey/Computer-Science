package pl.edu.zut.wo.wzorce.symulator;

//public class DzikaKaczka extends Kaczka {
//
//	public void wyświetl(){
//		System.out.println("Wygląda jak dzika kaczka");
//	}
//}

public class DzikaKaczka extends Kaczka {
	public DzikaKaczka() {
//		LatanieInterfejs = new LatamBoMamSkrzydła();
//		KwakanieInterfejs = new Kwacz();
		ustawLeć(new LatamBoMamSkrzydła());
		ustawKwacz(new Kwacz());
	}



	public void wyświetl(){
		System.out.println("Wygląda jak dzika kaczka");
	}

}
package pl.edu.zut.wo.wzorce.symulator;
import pl.edu.zut.wo.wzorce.symulator.interfejs.*;

public class WabikKaczka extends Kaczka  {
    public WabikKaczka() {

    }

    public void wyświetl() {
        System.out.println("Jestem kaczką wabikiem.");
    }
}

//
//public class GumowaKaczka extends Kaczka {
//    public GumowaKaczka() {
//        latanieInterfejs = new NieLatam();
//        kwakanieInterfejs = new Piszcz();
//    }
//
//    public void wyświetl() {
//        System.out.println("Jestem gumową kaczką.");
//    }
//}

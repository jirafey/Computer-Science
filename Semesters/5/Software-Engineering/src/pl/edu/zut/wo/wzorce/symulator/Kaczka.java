package pl.edu.zut.wo.wzorce.symulator;

import pl.edu.zut.wo.wzorce.symulator.interfejs.*;

public class Kaczka{
    void ustawKwacz(KwakanieInterfejs kwakanie) {
        kwakanieInt = kwakanie;
    }

    void ustawLeć(LatanieInterfejs latanie) {
        latanieInt = latanie;
    }
    LatanieInterfejs latanieInt;
    KwakanieInterfejs kwakanieInt;
    void pływaj() {
    	System.out.println("Pływam jak kaczka.");
    }
    void wyświetl() {
    	System.out.println("Wyglądam jak kaczka.");
    }

    public void wykonajLeć() {
        latanieInt.leć();
    }

    public void wykonajKwacz() {
        kwakanieInt.kwacz();
    }
}
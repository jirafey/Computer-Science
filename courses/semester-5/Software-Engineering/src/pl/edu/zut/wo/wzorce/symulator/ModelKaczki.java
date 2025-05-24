package pl.edu.zut.wo.wzorce.symulator;

import pl.edu.zut.wo.wzorce.symulator.interfejs.KwakanieInterfejs;
import pl.edu.zut.wo.wzorce.symulator.interfejs.LatanieInterfejs;

public class ModelKaczki {
    public LatanieInterfejs latanie;
    public KwakanieInterfejs kwakanie;

    public void ustawLatanie(LatanieInterfejs li) {
        latanie = li;
    }

    public void ustawKwakanie(KwakanieInterfejs ki) {
        kwakanie = ki;
    }
}

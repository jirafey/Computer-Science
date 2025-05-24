package pl.edu.zut.wo.wzorce.symulator;

import pl.edu.zut.wo.wzorce.symulator.interfejs.LatanieInterfejs;

// Fly behaviors
public class LatamBoMamSkrzydła implements LatanieInterfejs {
    public void leć() {
        System.out.println("Latam jak kaczka z skrzydłami.");
    }
}

import java.text.MessageFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

public class lab_01_03 {
    public static void main(String[] args){
        System.out.println(MessageFormat.format("{0,date,yyyy-MM-dd HH:mm:ss.SSS}", new Date()));
        System.out.println(MessageFormat.format("2030{0,date,-MM-dd HH:mm:ss.SSS}", new Date()));

    }
}
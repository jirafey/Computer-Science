import java.nio.charset.StandardCharsets;
import java.util.Base64;
import static java.lang.System.out;
/**
 * character = "WfZoiTcz"
 * max(index) = 70
 * @author jirafey
 * @version 1.0
 * @since 2023
 */
public class lab_01_01 {
    static final String encoded = "V3lkemlhxYIgSW5mb3JtYXR5a2kgWmFjaG9kbmlvcG9tb3Jza2kgVW5pd2Vyc3l0ZXQgVGVjaG5vbG9naWN6bnkgdyBTemN6ZWNpbmll";
    public static void main(String[] args) {
        StringBuffer buffer = new StringBuffer();
        String decoded = new String(Base64.getDecoder().decode(encoded), StandardCharsets.UTF_8);
        for(int index = 0 ; index < decoded.length() ; index += 10 ) {
            @SuppressWarnings("unused")
            char character = decoded.charAt(index);
            buffer.append(character);
        }
        out.println(decoded);
    }
}


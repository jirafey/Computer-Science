public class lab_01_04 {
    enum Color {
        RED, GREEN, BLUE;
    }

    public static void main( String[ ] args ) {
        for( Color value : Color.values( ) ) {
            // Returns an array containing the constants of this enum type,
            // in the order they are declared.
            // Tworzy array z wartości, które można na luzie przelecieć pętlą.
            System.out.println( value.toString( ) );
        }
    }
}
/**
 * public static Component.BaselineResizeBehavior[] values()
 * Returns an array containing the constants of this enum type, in the order they are declared.
 * This method may be used to iterate over the constants as follows:
 * for (Component.BaselineResizeBehavior c : Component.BaselineResizeBehavior.values())
 *     System.out.println(c);
 * Returns:
 * an array containing the constants of this enum type, in the order they are declared
 */
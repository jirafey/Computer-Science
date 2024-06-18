import java.util.Scanner;

public class Menu {
    public static void printMenu(){
        System.out.println("Input <<");
        System.out.println("1 = Input matrices\n");
        System.out.println("Transpose ⍉");
        System.out.println("2 = Transpose inputted matrices");
        System.out.println("3 = Transpose result matrices\n");
        System.out.println("Multiply ×");
        System.out.println("4 = Multiply inputted matrices\n");
        System.out.println("Output >>");
        System.out.println("5 = Output inputted matrices");
        System.out.println("6 = Output result matrices\n");
        System.out.println("DANGER !");
        System.out.println("7 = Stop this program");
        Scanner sc=new Scanner(System.in);
    };
    public static void Menu() {
        printMenu();
        System.out.println("Select an operation to perform by inputting a number");
        Scanner sc = new Scanner(System.in);
        int option = sc.nextInt();
        while (1 == 1) {
            switch (option) {
                case 1:
                    if (option == 1) {
                        Calculator.Transpose();
                    }
                    printMenu();
                    option =-1;
                    break;
                case 2:
                    if (option == 2) {
//                        Calculator.Multiply();
                    }
                    printMenu();
                    option =-1;
                    break;
                case 3:
                    if (option == 3) {
                        System.exit(0);
                    }
                    printMenu();
                    option =-1;
                    break;
                case 4:
                    if (option == 3) {
                        System.exit(0);
                    }
                    printMenu();
                    option =-1;
                    break;
                default:
                    Scanner scn = new Scanner(System.in);
                    option = scn.nextInt();
                    printMenu();
                    break;
            }


        }
    }
}

public class Main{
    public static void main(String[] args){
//        Menu.Menu();
        int a[][]={{1,1,1},{2,2,2},{3,3,3}};
        int b[][]={{1,1,1},{2,2,2},{3,3,3}};
        int[][] c = Calculator.Multiply(a, b, 3, 3, 3, 3);
        for (int i = 0; i<3; i++){
            for (int j=0; j<3; j++){
                System.out.println(c[i][j]);
            }
        }
    }
    }
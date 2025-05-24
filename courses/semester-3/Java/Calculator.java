public class Calculator {
    public static int[][] Transpose(int[][] result) {
        return result;
    }
    public static int[][] Multiply(int matrix1[][], int matrix2[][],int rows1, int  columns1, int rows2, int columns2){
        int[][] result = new int[rows1][columns2];
        for (int i=0; i<rows1; i++){
            for (int j=0; j<columns2; j++){
                for (int k=0; k<columns1; k++){
                    result[i][j] += matrix1[i][k]*matrix2[k][j];
                }
            }
        }
        return result;
//
//    //multiplying and printing multiplication of 2 matrices
//    public static int[][] Multiply(int a[][], int b[][], int rows1, int columns1, int rows2, int columns2) {
//        int c[][] = new int[3][3];  //3 rows and 3 columns
//
//        for (int i = 0; i < 3; i++) {
//            for (int j = 0; j < 3; j++) {
//                c[i][j] = 0;
//                for (int k = 0; k < 3; k++) {
//                    c[i][j] += a[i][k] * b[k][j];
//                }//end of k loop
//            }//end of j loop
//        }
//        return c;
    }
}

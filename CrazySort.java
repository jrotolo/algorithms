package crazysort;

import java.io.*;
import java.util.Scanner;


public class CrazySort {
    
    public void crazySort(int[] items) {
        int i, j, small, dataComparisons = 0, exchanges = 0;
        for (i=0; i<items.length; i++) {
            for(j=i+1; j<items.length; j++) {
              dataComparisons++;
		      if (items[i] > items[j]) {
      	        small = items[j]; items[j] = items[i];
                items[i] = small;
                exchanges++;
              }
            }
        }
        System.out.println("numExchanges = "+exchanges+", numDataComparisons = "
                            +dataComparisons);
    }
    
    public int[] readInput(String fileName) {
        int numItems;
	int[] items = new int[6];
	try {
            File file = new File(fileName);
            FileReader filereader = new FileReader(file);
            BufferedReader reader = new BufferedReader(filereader);
            Scanner scan = new Scanner(new File(fileName));
            reader.readLine();
            numItems = scan.nextInt(); scan.nextLine();
            for (int i=0; i<numItems; i++) {
                items[i] = scan.nextInt();
            }
        } catch (IOException e) { e.printStackTrace(); }
        
        return items;
    }
    
    public static String toString(int[] items) {
        String result = "[";
        for(int i=0; i<items.length-1; i++) {
            result += items[i]+", ";
        }
        result += items[5]+"]";
        return result;
    }
 
    public static void main(String[] args) {
        CrazySort app = new CrazySort();
        int[] items1 = app.readInput("crazySort1.dat");
        System.out.println("Input = "+toString(items1));
        app.crazySort(items1);
        System.out.println("Sorted = "+toString(items1));
        System.out.println();
        
        int[] items2 = app.readInput("crazySort2.dat");
        System.out.println("Input = "+toString(items2));
        app.crazySort(items2);
        System.out.println("Sorted = "+toString(items2));
        
    }
}

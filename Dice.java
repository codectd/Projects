package com.java24hours;

import java.util.*;
 
class Dice {
    public static void main(String[] arguments) {
        Random generator = new Random();
        int value = generator.nextInt();//nextInt is the method for the class random
        System.out.println("The random number is "
            + value);
    }
}

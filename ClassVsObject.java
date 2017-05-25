/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.java24hours;

import java.util.LinkedList;

/**
 *
 * @author BossMan
 */
public class ClassVsObject {
    public static int instanceCounter;
    
    public int thisInstance;
    
    public ClassVsObject(){
        instanceCounter++;
        thisInstance=instanceCounter;
    }
    
    
    
    public static void main(String[] args){
        LinkedList<ClassVsObject> instances=new LinkedList<>();
        
        
        for(int loopInstance=0;loopInstance<5;loopInstance++){
            ClassVsObject loopObject=new ClassVsObject();
            
            System.out.println(loopObject.thisInstance + " " + ClassVsObject.instanceCounter);
            
            loopObject.thisInstance += 10;
            
            instances.add(loopObject);
        }
        
        for(ClassVsObject loopObject:instances){
            System.out.println(loopObject.thisInstance + " " + loopObject.instanceCounter);
        }
        
        ClassVsObject.instanceCounter = 20;
        
        for(ClassVsObject loopObject:instances){
            System.out.println(loopObject.thisInstance + " " + loopObject.instanceCounter);
        }
        
    }
    
}

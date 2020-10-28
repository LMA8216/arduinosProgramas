#ifndef __CIS_H__
#define __CIS_H__

#include <Arduino.h>


String ciNand =   String("$7400\n" +
                  String("Quad 2-input NAND gate\n") +
                  String("14\n") +
                  String("00H00HGH00H00V\n") +
                  String("10H10HGH10H10V\n") +
                  String("01H01HGH01H01V\n") +
                  String("11L11LGL11L11V\n"));

String ciNor =   String("$7402\n" +
                  String("Quad 2-input NOR gates\n") +
                  String("14\n") +
                  String("H00H00G00H00HV\n") +
                  String("L10L10G10L10LV\n") +
                  String("L01L01G01L01LV\n") +
                  String("L11L11G11L11LV\n"));

String ciNot =   String("$7404\n" +
                  String("Hex inverters\n") +
                  String("14\n") +
                  String("0H0H0HGH0H0H0V\n") +
                  String("1L1L1LGL1L1L1V\n"));

String ciAnd =   String("$7408\n" +
                  String("Quad 2-input AND gates\n") +
                  String("14\n") +
                  String("00L00LGL00L00V\n") +
                  String("01L01LGL01L01V\n") +
                  String("10L10LGL10L10V\n") +
                  String("11H11HGH11H11V"));

//String ciAnd = String("7408$Quad 2-input AND gates$14$00L00LGL00L00V$01L01LGL01L01V$10L10LGL10L10V$11H11HGH11H11V");

String ciOr =   String("$7432\n" +
                  String("Quad 2-input OR gates\n") +
                  String("14\n") +
                  String("00L00LGL00L00V\n") +
                  String("01H01HGH10H10V\n") +
                  String("10H10HGH01H01V\n") +
                  String("11H11HGH11H11V\n"));

String ciXor =   String("$7486\n" +
                  String("Quad 2-input XOR gates\n") +
                  String("14\n") +
                  String("00L00LGL00L00V\n") +
                  String("01H01HGH01H01V\n") +
                  String("10H10HGH10H10V\n") +
                  String("11L11LGL11L11V\n"));


#endif
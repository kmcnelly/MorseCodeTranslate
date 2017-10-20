package assignment6;

import java.util.Scanner;

import jssc.SerialPortException;


public class MorseCodeToPC {
	public static void main(String[] args) {		
		// TODO:  Complete program to show "training messages" and decoded Morse code
		SerialComm myPort;
		try {
			myPort = new SerialComm("/dev/cu.usbserial-DN02BGGE");
			Scanner sc = new Scanner(System.in);
			while(myPort.available())
			{
				try {
					myPort.readByte();
				} catch (SerialPortException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		} catch (SerialPortException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}

}

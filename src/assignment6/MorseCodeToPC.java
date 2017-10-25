package assignment6;

import assignment6.SerialComm;
import jssc.SerialPortException;


public class MorseCodeToPC {
	public static void main(String[] args) {		
		// TODO:  Complete program to show "training messages" and decoded Morse code
		SerialComm myPort;
		try {
			myPort = new SerialComm("/dev/cu.usbserial-DN02BGGE");
			while(true)
			{
				if(myPort.available())
				{
					byte character = myPort.readByte();
					if(character != 35){
						System.out.println((char)character);
					}
					else{
						System.out.println();
					}
				}
				
			}
		} catch (SerialPortException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}

}

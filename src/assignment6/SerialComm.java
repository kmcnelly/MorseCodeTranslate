package assignment6;

import jssc.*;

public class SerialComm {

	SerialPort port;

	private boolean debug;  // Indicator of "debugging mode"
	
	// This function can be called to enable or disable "debugging mode"
	void setDebug(boolean mode) {
		debug = mode;
	}	
	

	// Constructor for the SerialComm class
	public SerialComm(String name) throws SerialPortException {
		port = new SerialPort(name);		
		port.openPort();
		port.setParams(SerialPort.BAUDRATE_9600,
			SerialPort.DATABITS_8,
			SerialPort.STOPBITS_1,
			SerialPort.PARITY_NONE);
		
		debug = false; // Default is to NOT be in debug mode
	}
	
	
		
	// TODO: Add writeByte() method that you created in Studio 5
	public byte readByte() throws SerialPortException{
		byte[] bytesIn = port.readBytes();
		byte result = bytesIn[0];
		return result;	
	}
	
	// TODO: Add available() and readByte() that you created in Studio 6
	public boolean available(){
		try {
			if(port.getInputBufferBytesCount() > 0)
			{
				return true;
			}
		} catch (SerialPortException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return false;
	}
	
}

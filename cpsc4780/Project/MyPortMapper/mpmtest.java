import java.io.*;
import java.net.*;
import java.lang.String;
import java.util.Vector;

class mpmtest {
    
    public static void main(String args[]) {
        
        try { 
            
            Vector<service> servicesToSend = new Vector<service>();

            final int numberOfServicesToCreate = 4;
            
            final String d = ";";
            String outCmd;
            String outName;
            String outPort;
            String outIP;

            for ( int i = 0; i < numberOfServicesToCreate; i++ ) {
            
                outCmd = "register";
                outName = "service" + Integer.toString(i);
                outPort = " ";
                outIP = "127.0.0." + Integer.toString(i);
                service newService = new service( outCmd, outName, outPort, outIP );
                servicesToSend.add( newService );
            
            } 
            
            outCmd = "lookup";
            outName = "service" + Integer.toString(numberOfServicesToCreate);
            outPort = " ";
            outIP = " ";            
            service newService = new service( outCmd, outName, outPort, outIP );
            servicesToSend.add( newService );            
            
                        
            for ( int i = 0; i < servicesToSend.size(); i++ ) { 

                // this should be left to localhost so that we are querying our local myportmapper
                Socket socket = new Socket("127.0.0.1", 10111); 
                PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
                BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                
                String toSend = 
                servicesToSend.get(i).service_command + d + 
                servicesToSend.get(i).service_name + d + 
                servicesToSend.get(i).service_port_number + d + 
                servicesToSend.get(i).service_ip;
                
                System.out.println("Sending string: " + toSend);
                out.println(toSend);

                if ( servicesToSend.get(i).service_command.equals("lookup") ) {
                    System.out.println("Response: " + in.readLine() );
                }

                Thread.sleep(750);

                socket.close();
                out.close();
                in.close();
                
            } // end for

        } catch (Exception e) {
            e.printStackTrace();
        } // end try catch
    } // end main
} // end mpmtest

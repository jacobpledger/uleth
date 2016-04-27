import java.io.*;
import java.net.*;
import java.util.ArrayList;

class receiver implements Runnable
{
    Socket receiver_socket;
    ArrayList<service> registered_services;
    
    final int NUM_HOSTS = 0;
    
    public receiver(Socket rs, ArrayList<service> reg_serv)
    {
        this.receiver_socket = rs;
        this.registered_services = reg_serv;
    }
    
    public void run()
    {
        try
        {

            // read input stream into buffered reader
            BufferedReader in = new BufferedReader(new InputStreamReader(receiver_socket.getInputStream()));
            String service_string = in.readLine();
            String incoming[] = service_string.split(";");
            
            if (incoming.length != 4 ) {
                System.out.println("Wrong number of arguments, stupid.");
            }
            
            // read them from stream reader scanner
            String service_command = incoming[0];
            final String service_name = incoming[1];
            String service_port = incoming[2];
            final String service_ip = incoming[3];
            final String d = ";";
            
            // print to the myportmapper shell the received request
            System.out.println("Received command: " + service_command);
            System.out.println("Received name: " + service_name);
            
            // decide now if it's a duplicate, instead of doing it in each case
            int exists = -1;
			
            for (int i = 0; i < registered_services.size(); i++)
            {
                if (service_name.equals(registered_services.get(i).getName()))
                {
                    System.out.println("The requested name exists: " + service_name );
                    exists = i;
                } // end if
            } // end for
            
            
            // handle the incoming service
            if (service_command.equals("register"))
            {
                // test for copy of service so we don't create duplicate entries
                if ( exists == -1 )
                {
                 
                    // set default port if this is the first service to register
                    int assignNewPortInt = 10112;
                    
                    // assign next available port number
                    for ( int i = 0; i < registered_services.size() ; i++ ) {
                        
                        if ( Integer.parseInt( registered_services.get(i).service_port_number ) >= assignNewPortInt ) {
                            assignNewPortInt++;
                        } 
                        
                    } 
                    
                    service_port = Integer.toString(assignNewPortInt);
                    
                    // define them in a class
                    service new_service = new service(service_command, service_name, service_port, service_ip);

                    // push class into vector
                    registered_services.add(new_service);
                    System.out.println("Registered: " + service_name + " @ " + service_ip + ":" +  service_port);
                    
                    // open the file                    
                    BufferedReader inFile = new BufferedReader(new FileReader("addressConfig.txt"));
                    
                    // fetch our own IP
                    InetAddress selfIP = InetAddress.getLocalHost();
                    String selfIPString = selfIP.getHostAddress();
                                        
                    // broadcast the service to other hosts
                    for (int i = 0; i < NUM_HOSTS; ++i)
                    {

                        String host = inFile.readLine();
                        
                        // if the addressConfig.txt file doesn't have the right content, break
                        if ( host == null ) {
                            System.out.println("Error in addressConfig.txt");
                            break;
                        }
                        
                        // skip over our selves, so that we don't run an infinite loop
                        if ( host == selfIPString ) {
                            continue;
                        }

                        System.out.println("Broadcasting " + service_name + " to " + host);

                        int port = 10111;
                        Socket sender_socket = new Socket(host, port);
                        service_command = "update";
                        String new_service_string = service_command + d + service_name + d + service_port + d + service_ip;
                        new Thread(new sender(sender_socket, new_service_string)).start();
                            
                    } // end for
                    
                    // close file
                    in.close();
                } // end if
            }
            else if(service_command.equals("update"))
            {
                // test for copy of service so we don't create duplicate entries
                if ( exists == -1 )
                {
                    // define them in a class
                    service new_service = new service(service_command, service_name, service_port, service_ip);
                    
                    // push class into vector
                    registered_services.add(new_service);
                    System.out.println("Updated: " + service_name);
                    
                } // end if
            }
            else if(service_command.equals("lookup")) // if we want to receive
            {
                
                if ( exists != -1 )
                {
                    final String command = "response";
                    final String name = registered_services.get(exists).getName();
                    final String port = registered_services.get(exists).getPort();
                    final String ip = registered_services.get(exists).getIP();

                    String new_service_string = command + d + name + d + port + d + ip;
                    new Thread(new sender(receiver_socket, new_service_string)).start();
                    System.out.println("Lookup successful for: " + service_name);
                    
                }
                else // this means that shit doesn't exist, so what do we tell our client?
                {
                    final String command = "response";
                    final String name = "";
                    final String port = "";
                    final String ip = "";
                                        
                    String new_service_string = command + d + name + d + port + d + ip;
                    new Thread(new sender(receiver_socket, new_service_string)).start();
                    System.out.println("Lookup NOT successful for: " + service_name);
                } // end nested if else
            } // end if else
        }
        catch (Exception e)
        {
            System.out.println("Error in recieve " + e.getMessage());
            e.printStackTrace();
        } // end try/catch block
    } // end run
} //end class

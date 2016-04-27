import java.lang.String;

class service
{
	String service_command;
    String service_name;
    String service_port_number;
    String service_ip;
	
	service()
	{
        service_command = "";
        service_name = "";
        service_port_number = "";
        service_ip = "";        
    }
    
	service(String cmd, String name, String port, String ip)
	{
        service_command = cmd;
        service_name = name;
        service_port_number = port;
        service_ip = ip;   
    }
	
	public String getCommand()
	{
		return this.service_command;
	}
	
	public String getName()
	{
		return this.service_name;
	}
	
	public String getPort()
	{
		return this.service_port_number;
	}
	
	public String getIP()
	{
		return this.service_ip;
	}

}

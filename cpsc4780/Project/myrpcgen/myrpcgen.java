import java.io.*;
import java.lang.*;
import java.util.*;

class myrpcgen
{    
    public static void main( String args[] )
	{
        
        // define variables to be used in different try / catch blocks
        String interfaceFilename = "";
		String programName = "";
        String programVersion = "";
        
        Vector<String> defines = new Vector<String>();
        Vector<function> functions = new Vector<function>();
        
        // for testing purposes, to save us the hassle of specifying the interfaceFilename on execution
        if ( args.length == 0 )
		{
			interfaceFilename = "interface.x";
		}
		else
		{
            if (!args[0].matches("\\w+.x"))
			{
                System.out.println("Please specify a valed RPC interface .x file.");
                System.exit(1);
            }
			else
			{
				interfaceFilename = args[0];
			}
        }
        
        // define output filenames
        String header_filename      = interfaceFilename.replace(".x",      ".h");
        String client_stub_filename = interfaceFilename.replace(".x", "_clnt.cpp");
        String server_stub_filename = interfaceFilename.replace(".x",  "_svc.cpp");
        
        // read interface.x file into memory                        
        try { 

            // read from file
            BufferedReader in = new BufferedReader(new FileReader(interfaceFilename));
            System.out.print("Reading " + interfaceFilename + " ... ");
            String buffer = in.readLine();
            
            while ( buffer != null )
			{
                buffer = buffer.trim();
                
				if (buffer.contains("#define"))
				{
                    defines.add(buffer);
                }
				else if(buffer.matches( "program \\w+ \\p{Punct}" ))
				{
                    int firstSpace = buffer.indexOf(' ');
                    programName = buffer.substring(firstSpace +1, buffer.indexOf(' ', firstSpace+1));
                    
				}
				else if(buffer.contains("} = ") && buffer.contains(";"))
				{                    
                    buffer = buffer.substring(4);
                    buffer = buffer.replace(';',' ');
                    programVersion = buffer.trim();
                    
                }
				else if(buffer.matches("\\w+ \\w+\\p{Punct}\\w+\\p{Punct} = \\d\\p{Punct}"))
				{
                    String r = buffer.substring(0, buffer.indexOf(' '));
                    buffer = buffer.substring(r.length()).trim();
                    String n = buffer.substring(0, buffer.indexOf('('));
                    buffer = buffer.substring(n.length()).trim();
                    String p = buffer.substring(1, buffer.indexOf(')'));
                    buffer = buffer.substring( buffer.indexOf( "=" ) ).trim();
                    String i = buffer.substring(1, buffer.indexOf(';')).trim();
                    
                    functions.add( new function( r, n, p, i ) );
				}
                buffer = in.readLine();
            }
            in.close(); 
            
            defines.add( "#define " + programName + " " + programVersion ); 
                        
            System.out.println("Complete");          
            
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("You may have failed to specify a file name as an executing parameter.");
            System.exit(2);
        } catch (FileNotFoundException e) {
            System.out.println("File not found: " + interfaceFilename);
            System.exit(2);
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(2);
        } // end read interface.x file into memory
        
        // write the header file
        try
		{
            PrintWriter header_out = new PrintWriter(new FileWriter(header_filename));
			System.out.print("Writing " + header_filename + " ... ");
            
            // define class
			header_out.println("#ifndef _"+ header_filename.replace(".h","_H").toUpperCase() + "_RPCGEN" );
			header_out.println("#define _"+ header_filename.replace(".h","_H").toUpperCase() + "_RPCGEN" );
            header_out.println("");
            
            // include our functions
			header_out.println("#include \"myrpc.h\"");
            header_out.println("");
            
            // print their define statements
            for (int i = 0; i < defines.size(); i++)
			{
                header_out.println(defines.get(i));   
            }
            header_out.println("");
            
            // define program name and version
            //header_out.println( programName.toUpperCase() + "_PROG " + programVersion );
            //header_out.println("");
            
            // define functions
            function fb;
            for (int i = 0; i < functions.size(); i++)
			{
                fb = new function( functions.get(i) );
                header_out.println( "#define " + fb.name.toUpperCase() + " " + fb.index );
                header_out.println( "extern " +  fb.returnValue + " * " + fb.name + "_1" + "(void *, client *);" );
                header_out.println( "extern " +  fb.returnValue + " * " + fb.name + "_1" + "_svc(void *, struct my_svc_req *);" );
            }
			
            header_out.println("");
            header_out.println("#endif");
            header_out.close(); //file done
            System.out.println("Complete");
        }
		catch (Exception e) {
            e.printStackTrace();
            System.exit(3);
        } // end write the header file
        
        
        // write the client stub file            
        try
		{  
            PrintWriter client_out = new PrintWriter(new FileWriter(client_stub_filename));
			System.out.print("Writing " + client_stub_filename + " ... ");
            client_out.println("#include \"" + header_filename + "\"");
            client_out.println("");
			
			for (int i = 0; i < functions.size(); i++)
			{
				client_out.println(functions.get(i).returnValue + " *"); // return value
				client_out.println(functions.get(i).name + "_1(void* args, client *clnt)"); // function declaration line with parameters
				client_out.println("{"); // open function
				client_out.println(functions.get(i).returnValue + "* clnt_res;"); // declare pointer for return value

				// call the function
				client_out.print("my_clnt_call(");

                // function parameters
                client_out.print(" clnt, "); // client struct pointer
                client_out.print(functions.get(i).name.toUpperCase() + ", "); // function name
                client_out.print("&my_xdr_" + functions.get(i).parameter + ", "); // input type
                client_out.print("(caddr_t) args," ); // input arguments
                client_out.print(" &my_xdr_" + functions.get(i).returnValue + ", "); // output type
                client_out.print("(caddr_t) clnt_res" ); // output arguments                                 
                                 
                // end the function call
                client_out.println(" );");
                
                client_out.println("return clnt_res;"); // return value
				client_out.println("}"); // end function definition
                client_out.println("");
			}
            client_out.close();
            System.out.println("Complete");
        }
		catch (Exception e) {
            e.printStackTrace();
        } // end write client stub file
        
        // write the server stub file        
        try
		{ 
            System.out.print("Writing " + server_stub_filename + " ... ");
            PrintWriter server_out = new PrintWriter(new FileWriter(server_stub_filename));
            server_out.println("#include \"" + header_filename + "\"");
			server_out.println("#include <stdio.h>");
			server_out.println("#include <iostream>");
			server_out.println("#include <stdlib.h>");
			server_out.println("#include <string.h>");
			server_out.println("#include <sys/socket.h>");
			server_out.println("#include <netinet/in.h>");
			server_out.println("");
			
            
            // print their define statements
            for(int i = 0; i < defines.size(); i++)
			{
				server_out.println(defines.get(i));   
            }
            server_out.println("");
			
			//define program
			if (functions.size() != 0)
			{
				server_out.println("static void");
				server_out.println(programName + "_1" + "(struct my_svc_req *rqstp, myrpcsvc *transp)");
				server_out.println("{");
				server_out.println("void* result;");
				server_out.println("void (*_xdr_argument) (void* typ , void* str);");
				server_out.println("void (*_xdr_result) (void* typ , void* str);");
                server_out.println("void *(*local)(void *, struct my_svc_req *);");
				server_out.println("caddr_t argument;");
                server_out.println("");
				
				server_out.println("switch (rqstp->my_rq_proc) {");
				for (int i = 0; i < functions.size(); i++)
				{
                    server_out.println("");
					server_out.println("case " + functions.get(i).name.toUpperCase() + ":");
					server_out.println("_xdr_argument = &my_xdr_" + functions.get(i).parameter + ";");
					server_out.println("_xdr_result = &my_xdr_" + functions.get(i).returnValue + ";");
					server_out.println("local = (void *(*)(void *, struct my_svc_req *))" + functions.get(i).name + "_1_svc;");
					server_out.println("break;");
				}
				
                server_out.println("");
				server_out.println("default:");
				server_out.println("cout << \" Error in interface definition. \" << endl;");
                server_out.println("}");
				server_out.println("my_svc_getargs (transp, _xdr_argument, argument);");
				server_out.println("result = (*local)((void *)argument, rqstp);");
				server_out.println("my_svc_sendreply(transp, _xdr_result, (char*)result);");
				server_out.println("return;");
				server_out.println("}");
			}
			
			server_out.println("");
			server_out.println("int main(int argc, char **argv)");
			server_out.println("{");
            server_out.println("myrpcsvc* transp;");
			server_out.println("if (!my_svc_register(transp, " + programName + ", " + 1 + ", " + programName + "_1 )) {");
			server_out.println("std::cout << \"Error: unable to register: " + programName + ", " + programVersion + " \" << std::endl;");
			server_out.println("exit(1);");
			server_out.println("}");
			server_out.println("");
			server_out.println("my_svcudp_create();");
			server_out.println("my_svc_run();");
			server_out.println("std::cout << \" Error: svc_ren returned. \" << std::endl;");
			server_out.println("return 0; // should never be reached");
			server_out.println("}");
            server_out.println("");
            server_out.close();
            System.out.println("Complete");
            
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(4);
        }// end write server stub file
        
    } // end main
} // end class myrpcgen

class function
{
    function()
	{
        returnValue = "";
        name = "";
        parameter = "";
        index = "";
    }
    
    function(String r, String n, String p, String i )
	{
        returnValue = r;
        name = n;
        parameter = p;
        index = i;
    }
    
    function( function f )
	{
        returnValue = f.returnValue;
        name = f.name;
        parameter = f.parameter;
        index = f.index;
    }
    
    String returnValue;
    String name;
    String parameter;
    String index;
    
} // end class function

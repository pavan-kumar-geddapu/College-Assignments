import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Client1
{
    private String logFile ;

    Client1(){
        this.logFile = "Client/client1log.txt";
    }

    public void createFile(){
        File file = new File(this.logFile);

        boolean temp = file.delete();

        try {
            if(file.createNewFile()){
                System.out.println("file created : "+this.logFile);
            }
            else{
                System.out.println("file creation failed");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void deleteFile(){
        File file = new File(this.logFile);

        if(file.delete()){
            System.out.println("file deleted : "+this.logFile);
        }
        else{
            System.out.println("file does not exist");
        }
    }

    public void writeFile(String fileContent){
        String[] toBeWritten = fileContent.split("@");
        if(toBeWritten.length  == 0) return;
        File file = new File(logFile);
        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter(this.logFile, true));
            writer.write(toBeWritten[0]);
            for(int i=1; i<toBeWritten.length; i++){
                writer.newLine();
                writer.write(toBeWritten[i]);
            }
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public String readFile(){
        String fileContent = "";
        try {
            File file = new File(this.logFile);
            Scanner sc = new Scanner(file);
            while(sc.hasNextLine()){
                fileContent += sc.nextLine();
                if(sc.hasNextLine()){
                    fileContent += "@";
                }
            }
            sc.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        return fileContent;
    }

    public static void main(String[] args) throws IOException
    {
        Client1 client = new Client1();

        try
        {
            Scanner scn = new Scanner(System.in);
            InetAddress ip = InetAddress.getByName("localhost");
            Socket s = new Socket(ip, 5056);
            DataInputStream dis = new DataInputStream(s.getInputStream());
            DataOutputStream dos = new DataOutputStream(s.getOutputStream());

            while (true)
            {
                String inString = dis.readUTF() ;
                System.out.println(inString);
                String toSend = scn.nextLine();
                dos.writeUTF(toSend);

                if(inString.equals("Exit"))
                {
                    System.out.println("Closing this connection : " + s);
                    s.close();
                    client.deleteFile();
                    System.out.println("Connection closed");
                    break;
                }

                else if(toSend.equals("logFile")){
                    String fileContent= dis.readUTF();
                    client.createFile();
                    client.writeFile(fileContent);
                    System.out.println("file downloaded...type Y after reading it");
                    while(!scn.nextLine().equals("Y")){
                        continue;
                    }
                    dos.writeUTF(client.readFile());
                }

                else{
                    inString= dis.readUTF();
                    System.out.println(inString);
                }

                inString = dis.readUTF();
                if(!inString.equals("NoError")){
                    System.out.println(inString);
                    inString = dis.readUTF();
                    if(inString.equals("Exit")){
                        System.out.println("Closing this connection : " + s);
                        s.close();
                        client.deleteFile();
                        System.out.println("Connection closed");
                        break;
                    }
                    else{
                        System.out.println(inString);
                    }
                }

            }
            scn.close();
            dis.close();
            dos.close();
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}
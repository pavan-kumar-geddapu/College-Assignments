import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;
import java.util.concurrent.Executors;
import java.util.Date;
import java.lang.*;
import java.sql.Timestamp;

public class Server {

    public static boolean systemError = false;
    public static String daemonClient = null;
    public static int clientCount = 0;


    public static void main(String[] args) throws Exception {
        try (var listener = new ServerSocket(5056)) {
            System.out.println("The server is running...");
            var pool = Executors.newFixedThreadPool(10);
            int clientIndex = 0;
            while (true) {
                clientIndex += 1;
                pool.execute(new classHandler(listener.accept(), clientIndex));
            }
        }
    }

    private static class classHandler implements Runnable {
        private Socket socket;
        private String logFile;
        private String clientName;
        private boolean clientStatus = true;
        private String backupFile;

        classHandler(Socket socket, int clientIndex) {
            this.socket = socket;
            this.clientName = "client"+clientIndex;
            this.logFile = "Server/client"+clientIndex+"log.txt";
            Server.clientCount += 1;
            this.backupFile = "Server/clientbackup"+clientIndex+"log.txt";

            //System.out.println("----------------------------------------------"+Server.clientCount);
        }

        public void createFile(String fileName){
            File file = new File(fileName);

            boolean temp = file.delete();

            try {
                if(file.createNewFile()){
                    System.out.println("file created : "+fileName);
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
            File backupFile = new File(this.backupFile);
            boolean temp = file.delete();
            temp = backupFile.delete();
        }

        public String readFile(String fileName){
            String fileContent = "";
            try {
                File file = new File(fileName);
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

        public void writeTOFile(String toBeWritten, boolean isFileEmpty) throws IOException {
            Date date= new Date();
            long time = date.getTime();
            Timestamp ts = new Timestamp(time);
            toBeWritten = ts + " " + toBeWritten;
            BufferedWriter writer = new BufferedWriter(new FileWriter(this.logFile, true));
            if(!isFileEmpty){
                writer.newLine();
            }
            writer.write(toBeWritten);
            writer.close();
        }

        public void writeFile(String fileName,String fileContent){
            String[] toBeWritten = fileContent.split("@");
            if(toBeWritten.length  == 0) return;
            createFile(fileName);
            try {
                BufferedWriter writer = new BufferedWriter(new FileWriter(fileName, true));
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

        public void setErrorRecovery(DataOutputStream dos) throws IOException {
            if(this.clientName == Server.daemonClient){
                dos.writeUTF("Exit");
                this.clientStatus = false;
                Server.clientCount -= 1;
                if (Server.clientCount <= 0){
                    Server.clientCount = 0;
                    Server.daemonClient = null;
                    Server.systemError = false;
                }
            }
            else{
                Server.clientCount -= 1;
                if (Server.clientCount <= 0){
                    Server.clientCount = 0;
                    Server.daemonClient = null;
                    Server.systemError = false;
                }
                writeFile(this.logFile,readFile(this.backupFile));
                dos.writeUTF("Error Recovery Set");
            }
        }

        @Override
        public void run() {
            System.out.println("Connected: " + socket);
            try {
                createFile(this.logFile);
                createFile(this.backupFile);
                int backupCycle = 0;
                DataInputStream dis = new DataInputStream(socket.getInputStream());
                DataOutputStream dos = new DataOutputStream(socket.getOutputStream());
                String inString ;
                boolean isFileEmpty = true;

                while(this.clientStatus){
                    dos.writeUTF("Select your request[logFile]..\n"+"Type Exit to terminate connection...");
                    inString = dis.readUTF();
                    if(inString.equals("Exit")){
                        writeTOFile("Exit Y", isFileEmpty);
                        System.out.println("client "+this.socket+"wants to terminate connection");
                        break;
                    }
                    switch (inString){
                        case "logFile" :
                            String logContent = readFile(this.logFile);
                            dos.writeUTF(logContent);
                            String receivedContent = dis.readUTF();
                            //System.out.println(logContent);
                            //System.out.println(receivedContent);
                            writeTOFile("logFile Y", isFileEmpty);
                            if(!logContent.equals(receivedContent)){
                                Server.systemError = true;
                                Server.daemonClient = this.clientName;
                            }

                            break;

                        default :
                            writeTOFile(inString+" N", isFileEmpty);
                            dos.writeUTF("invalid Input");
                            break;
                    }
                    isFileEmpty = false;

                    if(Server.systemError == true){
                        dos.writeUTF("There is an error occured. "+Server.daemonClient+" corrupted the log file.");
                        setErrorRecovery(dos);
                        //System.out.println("----------------------------------------------"+Server.clientCount);
                    }
                    else{
                        dos.writeUTF("NoError");
                    }

                    backupCycle += 1;
                    if(backupCycle % 2 == 0){
                        writeFile(this.backupFile,readFile(this.logFile));
                    }

                }

            } catch (Exception e) {
                System.out.println("Error:" + socket);
            } finally {
                try {
                    socket.close();
                    //Server.clientCount -= 1;
                    deleteFile();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                System.out.println("Closed: " + socket);
            }
        }
    }
}

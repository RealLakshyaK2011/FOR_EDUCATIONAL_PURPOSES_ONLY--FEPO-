package net.chauhandevs.hacked.fepo.mitm_attacker.console;

import net.chauhandevs.hacked.fepo.mitm_attacker.sniffing_spoofing.ArpPoisoner;

import java.util.Scanner;

public class Console {
    private static Console Instance;

    private boolean running = false;
    private String consolePrefix = "Console: ";
    private Scanner inputScanner;

    public Console() {
        boolean finalize = false;

        if(Instance != null) finalize = true;
        if(finalize){
            try{
                Instance.StopConsole();
                Instance.finalize();
            }catch (Throwable e) {
                System.err.println("==========GOT ERROR!==========");
                e.printStackTrace(System.err);
                System.err.println("==============================");
            } finally {
                finalize = false;
                Instance = null;
            }
        }

        Instance = this;

        inputScanner = new Scanner(System.in);
    }

    public void StartConsole(){
        running = true;

        while (running){
            System.out.print(consolePrefix);
            String input = inputScanner.nextLine();
            System.out.println(ExecuteCommand(input));
        }
    }

    public void StopConsole(){
        running = false;
    }

    public void changeConsolePrefix(String prefix){
        consolePrefix = prefix;
    }

    private String ExecuteCommand(String command){
        String ret = "Invalid Command!";
        if(command.equals("exit")){
            System.exit(1);
            ret = "Exiting!";
        } else if(command.equals("arp-poison")) {
            boolean happened = ArpPoisoner.arp_poison("192.168.0.1", "127.0.0.1");
            System.out.println(happened);
        }
        return ret;
    }

    public static Console getInstance() {
        return Instance;
    }
}

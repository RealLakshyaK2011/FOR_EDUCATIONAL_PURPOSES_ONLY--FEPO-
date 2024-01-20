package net.chauhandevs.hacked.fepo.mitm_attacker;

import net.chauhandevs.hacked.fepo.mitm_attacker.console.Console;

public class MITMAttacker {
    private static MITMAttacker Instance;
    private static Console currentConsole;

    public MITMAttacker(){
        Instance = this;
        System.out.println("Initializing Libraries!");
        LibraryLoader.init();

        System.out.println("Starting up MITMAttacker console!");
        currentConsole = new Console();
        currentConsole.changeConsolePrefix(">>> MITMAttacker >>>  ");
    }

    public Console getConsole() {
        return currentConsole;
    }
    public static MITMAttacker getInstance() {
        return Instance;
    }

    public static void main(String[] args) {
        MITMAttacker client = new MITMAttacker();
        client.getConsole().StartConsole();
    }
}
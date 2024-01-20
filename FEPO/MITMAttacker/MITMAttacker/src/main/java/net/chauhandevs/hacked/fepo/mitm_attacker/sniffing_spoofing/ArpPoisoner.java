package net.chauhandevs.hacked.fepo.mitm_attacker.sniffing_spoofing;

public class ArpPoisoner {
    public static native boolean arp_poison(String target_ip, String pretend_ip);
}

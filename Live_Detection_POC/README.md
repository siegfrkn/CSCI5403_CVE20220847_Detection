### Description
This Proof-of-Concept (POC) code demonstrates how simple monitoring for linux processes can be used to detect cache-modifying exploits such as dirtypipe. The code does live scans of both the '/etc/passwd' file using `pwck` and live scans of user commands on a machine leveraging the `sysdig` function to detect when a root shell is opened and alert the admin.

### Usage
Follow the steps below to compile the various files on the target Ubuntu 20.04 LTS on the 5.8.0 kernel. On a clean boot up of the attacker and target machine, run the main program on the target machine, then perform the exploit on the attacker machine to see the detection of both the '/etc/passwd' diff check and the opening of a root shell from the "admin" account.

### Compile
gcc detect_root_escalation.c -o detect_root_escalation \
gcc live_escalation_scan.c -o live_escalation_scan \
gcc check_passwd_file.c -o check_passwd_file \
gcc main.c -o main

### Run
`sudo ./main` on the target machine as the 'setup' user

### TODO
- cleanup, add comments
- cmake file for compiling code

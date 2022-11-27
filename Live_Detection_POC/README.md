### Compile
gcc detect_root_escalation.c -o detect_root_escalation \
gcc live_escalation_scan.c -o live_escalation_scan \
gcc check_passwd_file.c -o check_passwd_file \
gcc main.c -o main

### Run
`sudo ./main` on the target machine as the 'setup' user

### TODO
- cleanup, add comments
- update README

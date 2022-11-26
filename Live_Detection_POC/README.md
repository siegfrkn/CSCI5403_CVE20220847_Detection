### Compile
gcc detect_root_escalation.c -o detect_root_escalation
gcc live_escalation_scan.c -o live_escalation_scan

### TODO
- the buffer isn't flushing between the write by the parent process and the read of the child process
- cleanup, add comments
- update README

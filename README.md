# CSCI5403_CVE20220847_Detection

## Summary
This repository hosts the instructions to setup an environment, perform the dirtypipe CVE20222847 exploit, and a proof-of-concept (POC) scanning demo which demonstrates how a cache manipulation exploit such as dirtypipe can be detected in real time.

## Description
The dirtypipe exploit takes advantage of a vulnerability that allows a user with only read-only privledges to root-owned files, the ability to make modifications to the cached copy of a file, while the actual contents of the file on the disk remains untouched and unmodified. This allows a read-only user to escalate to root during a single session. When that cache is flushed or the user ends the session, all traces of the exploit will be removed. The original discovery of this exploit was only made due to a series of strange log file artifacts.

Additional detail about the original exploit are detailed by the discovering engineer [here](https://dirtypipe.cm4all.com/).

## Video Demonstration
A video of the exploit and live detection can be found [here](https://youtu.be/zFXZ-Wd7Jek).

## Team Links
- [Proposal](https://docs.google.com/document/d/1Ej5i50u-w15W4MOU5rrApcnDrz5du96RQaN6N_96zIk/edit?usp=sharing)
- [Progress Report](https://docs.google.com/document/d/1YTQE10_W-f9DNDSEviGpOtVneBLEFnfrtC05tbwd9sI/edit?usp=sharing)
- [Final Report](https://docs.google.com/document/d/1gMS296A2NKfuEo7xz9yeFFJtiSfsbORWJUUcKy9a7fI/edit?usp=sharing)


## Resources
#### DirtyPipe
- https://dirtypipe.cm4all.com/
- https://raxis.com/blog/exploiting-dirty-pipe-cve-2022-0847
- https://github.com/Al1ex/CVE-2022-0847
- https://attack.mitre.org/techniques/T1003/008/
#### Linux
- https://releases.ubuntu.com/20.04/?_ga=2.158895674.1041833567.1668977229-1417524537.1668977229
- https://www.addictivetips.com/ubuntu-linux-tips/downgrade-ubuntu-kernel/
- https://unix.stackexchange.com/questions/198003/set-default-kernel-in-grub#:~:text=As%20mentioned%20in%20the%20comments,and%20then%20running%20update%2Dgrub%20.
#### VirtualBox
- https://fabian-voith.de/2020/04/21/understanding-virtualbox-networking-schemes-to-set-up-a-good-and-safe-lab/
#### Root Escalations
- https://biriukov.dev/docs/page-cache/2-essential-page-cache-theory/
- https://manpages.ubuntu.com/manpages/bionic/en/man5/passwd.5.html
- https://manpages.ubuntu.com/manpages/bionic/en/man3/crypt.3.html
- https://www.hackingarticles.in/editing-etc-passwd-file-for-privilege-escalation/
- https://www.networkstraining.com/nmap-scan-ip-range/#:~:text=Simple%20NMAP%20scan%20of%20IP,if%20a%20host%20is%20up.
#### C Programming
- https://faq.cprogramming.com/cgi-bin/smartfaq.cgi?answer=1044654269&id=1043284392
- https://stackoverflow.com/questions/259355/how-can-you-flush-a-write-using-a-file-descriptor
- http://www.crasseux.com/books/ctutorial/Writing-files-at-a-low-level.html

## TODO
- Video demo
- Add team presentation

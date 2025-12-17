# Study of Linux Commands

## File and Directory Commands
1. **ls** - List directory contents
   - `ls -l` : Long format
   - `ls -a` : Show hidden files
   - `ls -lh` : Human-readable sizes

2. **cd** - Change directory
   - `cd /path` : Change to path
   - `cd ..` : Go to parent directory
   - `cd ~` : Go to home directory

3. **pwd** - Print working directory

4. **mkdir** - Make directory
   - `mkdir dir` : Create directory
   - `mkdir -p dir1/dir2` : Create nested directories

5. **rmdir** - Remove empty directory

6. **rm** - Remove files/directories
   - `rm file` : Remove file
   - `rm -r dir` : Remove directory recursively
   - `rm -f file` : Force remove

7. **cp** - Copy files/directories
   - `cp source dest` : Copy file
   - `cp -r dir1 dir2` : Copy directory recursively

8. **mv** - Move/rename files
   - `mv old new` : Rename
   - `mv file /path` : Move file

## File Content Commands
9. **cat** - Display file content
   - `cat file` : Display file
   - `cat file1 file2 > file3` : Concatenate files

10. **more/less** - View file page by page

11. **head** - Display first lines
    - `head -n 10 file` : First 10 lines

12. **tail** - Display last lines
    - `tail -n 10 file` : Last 10 lines
    - `tail -f file` : Follow file updates

13. **grep** - Search text patterns
    - `grep pattern file` : Search pattern
    - `grep -i pattern file` : Case insensitive
    - `grep -r pattern dir` : Recursive search

## File Permissions
14. **chmod** - Change file permissions
    - `chmod 755 file` : rwxr-xr-x
    - `chmod +x file` : Add execute permission

15. **chown** - Change file owner
    - `chown user:group file`

## Process Management
16. **ps** - Display running processes
    - `ps aux` : All processes

17. **top** - Dynamic process viewer

18. **kill** - Terminate process
    - `kill PID` : Send TERM signal
    - `kill -9 PID` : Force kill

19. **bg/fg** - Background/foreground jobs

## System Information
20. **uname** - System information
    - `uname -a` : All information

21. **df** - Disk space usage
    - `df -h` : Human-readable

22. **du** - Directory space usage
    - `du -sh dir` : Summary of directory

23. **free** - Memory usage
    - `free -h` : Human-readable

24. **whoami** - Current user

25. **date** - Display/set date and time

## Network Commands
26. **ping** - Test network connectivity
    - `ping host`

27. **ifconfig/ip** - Network configuration

28. **wget/curl** - Download files
    - `wget URL`
    - `curl -O URL`

## Archiving
29. **tar** - Archive files
    - `tar -czf archive.tar.gz files` : Create compressed archive
    - `tar -xzf archive.tar.gz` : Extract archive

30. **zip/unzip** - Compress/decompress files
    - `zip archive.zip files`
    - `unzip archive.zip`

## Text Processing
31. **sort** - Sort lines

32. **uniq** - Remove duplicate lines

33. **wc** - Word count
    - `wc -l file` : Line count
    - `wc -w file` : Word count

34. **sed** - Stream editor
    - `sed 's/old/new/g' file`

35. **awk** - Pattern scanning and processing

## Other Useful Commands
36. **man** - Manual pages
    - `man command`

37. **find** - Search for files
    - `find /path -name "*.txt"`

38. **echo** - Display message

39. **which** - Locate command

40. **history** - Command history

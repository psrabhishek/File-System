# File-System | MRND - Summer Course

## OVERVIEW:

This is a simple implementation of File Systems. This was developed using a 100 MB HardDisk.  This uses a block structure with direct and indirect implementations for memory locations (With top of the memory being the Meta Data). This handles external fragmentation by having scope for non-continuous allocation of blocks and internal fragmentation with small block size (Block size can be initialized by user.)   

To execute the application, execute the ```Source.cpp``` file

[Hard Disk Link](https://drive.google.com/open?id=16ZStufxgXD7CS2p8GxvR_GzHqrjZ2AVY)

### Defaults:
- Block size   : 8 - 100
- No of Files  : 32
- No of Blocks : 6400
- Block Size   : 1024 bytes

> They can be modified in the ```disk_io.h``` header file, but the others values must be changed accordingly. In currnent Implementation the ```metadata``` is stored in a single block which limits the min Block Size to ```sizeof(meta)/1024``` 

## COMMANDS:

  ### Hard Disk commands

Command to create HardDisk : ```fsutil file createnew <hddName>.hdd <size in bytes>```
 
  ### File System commands

```MOUNT <harddiskfilename> <blockSize>``` - should use the given file as the disk.

ex: MOUNT harddisk.hdd 16384



```STORE <sourceFileName> <destFileName>``` - should upload the file which is present in the machine's file system to your file system.

ex: STORE dog.jpg puppy.jpg


```GET <sourceFileName> <destFileName>``` - should download the file from your file system to machine's file system.

ex: GET puppy.jpg dogfromfs.jpg



```FORMAT``` - should format your file system.



```LS``` - should list all the files present in your file system.



```DEL <fileName>``` - should delete the file specified from your file system.



```DEBUG``` - should list the available blocks in the file system.



```UNMOUNT``` - unmount the current disk.



```EXIT``` - stop the program.

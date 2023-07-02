# Operating System Project
Making an operating system from zero. This project will consist of research and eventual development of an operating system, starting from our current (January 20223) knowledge—nothing. Through reading and tutorial, we will eventually reach a level sufficient to create the most elementary parts of an operating system running, before likely calling it a day.

## Toolchain
The currently-in-use toolchain is a cross-compiler to a generic i686-ELF-based system, which is used to output code for the target OS.
In order to create the cross-compiler, we compile GCC with the i686-elf target.
You can do this with the script `xcompiler_install.sh`; GCC is complex software inherent with compilation bugs, so there may initially be a number
of issues, although with luck, if you have all the needed dependencies (the script ensures most of them are there), you will not encounter them. 

## Resources
* [Full Course on YouTube](https://www.youtube.com/watch?v=mXw9ruZaxzQ)
* [OSDev Wiki](https://wiki.osdev.org/Expanded_Main_Page)
* [Assembly Tutorial in a New OS](https://www.youtube.com/watch?v=MwPjvJ9ulSc)
* [Operating System Beginnings, like above](https://www.youtube.com/watch?v=W3DdyiO3Fy8)

**I am currently rewriting this project. WIP.**   
  
HTTP server written from scratch in C99.     
  
Plan to implement:
+ hashmaps [implemented]  
+ arena allocator   
+ multithreading  
+ mime types  
+ routing  

By default server listens on the port **8080**.    
  
### PREREQUISITES
---
+ CMake >= 3.23
+ C compiler

### INSTALLATION
---
```
$ cmake -B build -S .
$ cmake --build build
```
------------

Credits to these amazing people:  
+ [by namishh](https://github.com/namishh/webby): For amazingly clean source code.  
+ [by ryan radder](https://medium.com/@ryanradder0/building-an-http-server-from-scratch-a-journey-beyond-frameworks-28dc49e94a2a): For nice explanations.  
  
Good Luck~.  
# CS2 Sdk Example  

## Example CS2 Hook Using [xsip/cs2-sdk-offsets-interfaces-dump](https://github.com/xsip/cs2-sdk-offsets-interfaces-dump)  

# How to setup  
This app is using submodules ( imgui, minhook & [xsip/cs2-sdk-offsets-interfaces-dump](https://github.com/xsip/cs2-sdk-offsets-interfaces-dump)  )  
  So you need to clone with submodules  
```bash
git clone git@github.com:xsip/CS2-SDK-EXAMPLE-V1.git --recurse-submodules
```
# How to update SDK?  
## In the cloned repo execute:   
```bash
cd Internal\Libraries\XSIP-CS2-DUMP
git pull
```

# Known Bugs
If you unload using the DELETE key, and reinject, thex DX Hook can't be re-enabled. Everything else gets unhooked fine.





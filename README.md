# CS2 SDK Example Internal Base

## Example CS2 Hook Using [xsip/cs2-sdk-offsets-interfaces-dump](https://github.com/xsip/cs2-sdk-offsets-interfaces-dump)  
This base includes DX Hook using gameoverlayrenderer and CGameEntitySystem interface,  
as well as a example on how to use the SDK by retrieving the Local Player's health  
and a ESP.  

*Please note that this is not a ready to use cheat!*  
*This is a example on how to use  [xsip/cs2-sdk-offsets-interfaces-dump](https://github.com/xsip/cs2-sdk-offsets-interfaces-dump)*   


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

# Preview  
![Preview](https://raw.githubusercontent.com/xsip/CS2-SDK-EXAMPLE-V1/refs/heads/main/Preview.png "Preview")

![Preview2](https://raw.githubusercontent.com/xsip/CS2-SDK-EXAMPLE-V1/refs/heads/main/Preview2.png "Preview2")





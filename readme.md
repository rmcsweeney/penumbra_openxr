# Penumbra: Overture OpenXR/64bit Mod

Fork of the veryjos/penumbra_vr mod, which is 32bit and uses OpenVR. 
That mod is in a released state, and should be used.
Will only be built & tested on Linux at this time.

Current progress: the game can be compiled & built from source on a Linux system as a 
64-bit native application. 
Doesn't *immediately* crash, but early in the bugfixing stage.
## Status

- [X] OpenVR implementation refactored and made optional
- [X] Engine code compiles on a 64-bit system
- [X] Remove 32-bit binary dependencies in favor of system 64-bit dependencies.
- [X] Migrate AngelScript to 2.35
- [X] Migrate Newton to 2.36
- [ ] Migrate Cg shaders to GLSL shaders
- [ ] Migrate SDL1.2 to SDL2
#### [X] Milestone 1: Native 64-bit Penumbra
- [ ] Fix a multitude of bugs during playtesting
- [ ] Restore all flat-play functionality that was refactored out in OpenVR impl (click interaction, crouch, etc)
- [ ] Get physics on updated engine to an acceptable standard vs original
- [ ] Finish upgrades of SDL and Cg from pre-milestone 1
#### [ ] Milestone 2: Functional upgraded Penumbra
- [ ] OpenXR new backend
#### [ ] Milestone 3: OpenXR functional in upgraded Penumbra
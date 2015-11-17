settings = NewSettings()

if family == "windows" then
   settings.cc.includes:Add("SDL2-2.0.1/include");
   settings.cc.includes:Add("glew-1.13.0/include");
   settings.debug = 0
   settings.cc.flags:Add("/MD");
   settings.link.flags:Add("/SUBSYSTEM:CONSOLE");   
   settings.link.libpath:Add("SDL2-2.0.1/lib/x86");
   settings.link.libpath:Add("glew-1.13.0/lib/Release/Win32");
   settings.link.libs:Add("SDL2main");
   settings.link.libs:Add("OpenGl32"); 
   settings.link.libs:Add("glew32");
else
   settings.link.libs:Add("GL");
   settings.link.libs:Add("GLEW");
end



settings.link.libs:Add("SDL2");


source = Collect("*.c", "libsoil/*.c");

objects = Compile(settings, source)
exe = Link(settings, "cengine", objects)

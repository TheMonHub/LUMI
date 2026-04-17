# Implementation of LUMI

This file is intended to list the planned features, and all the current
plans for the implementation of LUMI 1.0. 
A personal note for implementing LUMI

This project is focused on being an opinionated framework or game engine.

Statically typed lua is planned but not yet implemented for now.

Possibly use the miniaudio

The `lumi` executable acts as a command line tool which can be used to:
- Create a new project from a template
- Run a project from the source – referred to as a run process
- Build a project into an executable – referred to as a build process
- Information about the executable itself

A lumi project source code is organized in a particular way and is forced
to follow this structure.

A lumi project will contain:
- A `lumi.conf` file
- A `src` directory
- A `shared` directory
- A `res` directory

All the codes and scripts are referred to as `lua` files.

A `lumi.conf` file is used to configure the project.
Containing the name of the project, the version, the author, etc.
Most of the configuration options listed above are optional.
The default values are used if the option is not specified.
It can also be used to:
- Enforce the LUMI version that the project is compatible with.
- Configure the build system
    - Exclude a specific scene from being included in the run or build process.
    - Configure the default first scene to be run.
    - Asset compression
        - Can be used to set the compression level for the supported formats (png, jpg, etc.).
          From setting the whole folder to setting a specific file. Unplanned feature.
    - Texture atlas generation
        - Can be used to specify each image to be generated in a texture atlas. The format
          of the atlas is `png` along with the `atlas_name.atl` file which is a custom format
          containing each texture name or id and its position and size in the atlas.
          Lumi should provide a way for the Lua scripts to access the atlas easily such as
          `atlas:get_texture(texture_name)`. Unplanned feature.
    - Other build options

Inside the `src` directory, there will be a `scenes` directory.
Inside it, there must be subdirectories for each scene.
Inside each scene directory, there must be a `main.lua` file.
There should not be any other files than the scripts.
Furthermore, inside the `src` directory, there should be a `start.lua` file.
Containing the code to run when the project is started.
The scenes are discovered automatically by the build system.

Inside the `shared` directory, it will contain all the code that should be
shared between all scenes. It is used to store the code shared between
the scenes such as modules, classes, etc. It may contain subdirectories.
This directory can be used in `require` statements.
For an example of `require` a module called `module`,
```
require("shared.module")
```

Inside the `res` directory, it will contain all the resources of the project
(images, models, sounds, etc.). It may contain subdirectories. The scripts
can access to the resources using the engine's resource manager API.

The project execution flow is as follows:
- The engine starts and initializes
- The engine loads and runs the `start.lua` file
- The engine loads and runs the `main.lua` file of the first scene configured
- The engine runs the scene logic in a loop

The engine should contain a way to close, window management,
rendering (wrapping the vulkan) and input handling.

The engine will use vulkan as the rendering backend and may use software rendering
if configured to do so. macOS support will use MoltenVK. OpenGL support is not
planned.

It uses LuaJIT as the scripting language.

`main.lua` should be a lua module that exports a function called `start` and a function
called `run`. The `start` function will be called before the first `run` call.
The `run` function will be called in a loop and yields the loop until it returns to be
called again. Code and initialization logic are heavily unrecommended to be placed outside
of functions. Any other function is allowed.
```
local scene = {}

-- There should be no other code outside of functions as the initialization
-- of the scene is unpredictable and not defined. You should only do the declaration
-- of the variables and functions.
local x = 0
local hello = "Hello, World!"

-- Any other function you have
local function sum(a, b)
    return a + b
end

local function print_hello()
    print(hello)
end

function scene:start()
    -- When a scene is started
    -- This is callled before the first scene:run() call
    -- This method yields the scene logic until it returns
end

function scene:run(dt)
    -- dt is the time since the last frame in seconds
    -- This is called in a loop
end

return scene
```

Talking about the API, the engine will provide a way to access to the resource manager,
window, input, rendering, etc. The API may be extended using plugins, which is a planned
feature using the `lumi.conf` file to import plugins.
This feature is not yet planned.


This file was written by `TheMonHub` | Last updated `2026-04-18` | All rights reserved
